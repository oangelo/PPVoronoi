#include "brute_force.h"

BruteForce::Voronoi::Voronoi(const data_points & data): points(data) {
    
}

const BruteForce::data_points &  BruteForce::Voronoi::get_points() const {
    return points;
}

size_t BruteForce::Voronoi::size() const {
    return points.size();
}

std::unordered_map<geometry::Point*, std::set<geometry::Point*>> BruteForce::Voronoi::neighbors() {
    using namespace geometry;
    std::unordered_map<geometry::Point*, std::set<geometry::Point*>> result;
    auto pointers(ToPointers(points));
    for(auto iten(points.begin()); iten < points.end(); ++iten) {
        std::set<geometry::Point*> neighbors_set;
        auto cell_neighbors(CellNeighbors(points, *iten));
        std::cout << "cell nei"<< cell_neighbors.size() << std::endl;
        for(auto element: cell_neighbors)
            neighbors_set.insert(element); 
        result[&(*iten)] = neighbors_set;
        std::cout << "set "<< neighbors_set.size() << std::endl;
    }
    return result;
}

std::vector<geometry::Point*>  BruteForce::CellNeighbors(BruteForce::data_points& points, geometry::Point& point) { 

    using namespace geometry;
    std::vector<Point*> neighborhood(ToPointers(points));
    std::vector<Point*> neighbors;

    std::cout << "neighborhood.size "<< neighborhood.size() << std::endl;
    //starting the neighborhood and the line
    Point* neighbor_aux(&NearestNeighbor(neighborhood, point));
    //neighbors.push_back(neighbor_aux);
    Vector direction_init(GenVector(point, *neighbor_aux));
    auto half_direction_init(direction_init / 2.0);
    Straight first_line(direction_init, half_direction_init + point);
    Straight midle_line(NormalVector(direction_init), point);
    neighborhood = OnNormalSide(midle_line, neighborhood);
    std::cout << "neigh first: "<< (*neighbor_aux)[0] << " " << (*neighbor_aux)[1] << std::endl;
    for(auto iten: neighborhood)
        std::cout << "points: "<< (*iten)[0] << " " << (*iten)[1] << std::endl;
    std::cout << "neighborhood.size "<< neighborhood.size() << std::endl;

    //Search the normal direction for neighbors
    bool flag(true);
    Point* element(NULL);
    Straight line(first_line);
    Straight side(midle_line);
    while(flag){
        std::cout << "line vec: "<< line.get_normal() << std::endl;
        std::cout << "line point: "<< line.get_point() << std::endl;
        std::cout << "side: "<< side.get_normal() << std::endl;
        std::cout << "side point: "<< side.get_point() << std::endl;
        for(auto iten: neighborhood)
            std::cout << "points: "<< (*iten)[0] << " " << (*iten)[1] << std::endl;

        element = LineCross(line, point, side, neighborhood);
        if(element) {
            Vector direction(GenVector(point, *element));
            Vector normal(NormalVector(direction));
            auto half_direction(direction / 2.0);
            line = Straight(direction, half_direction + point);
            side = Straight(normal, *element);
            std::cout << "encontro " << (line == side) << std::endl;
            neighbors.push_back(element);
            neighborhood = OnNormalSide(side, neighborhood);
            std::cout << "element: "<< (*element) << std::endl;
        }else{
            flag = false; 
        }
        std::cout <<  std::endl;
    }
    return neighbors;
}

geometry::Point* BruteForce::LineCross(const geometry::Straight& line, geometry::Point& point,  
                                       const geometry::Straight& side_line, std::vector<geometry::Point*> points){ 
    using namespace geometry;

    geometry::Point* neighbor = NULL;
    const Point point_ref(line == side_line);
//    std::cout << "point ref " << point_ref[0] << " " << point_ref[1] << std::endl;
    double max_distance = DBL_MAX;
/*    for(auto iten: points)
        std::cout << "line_Cross: "<< (*iten)[0] << " " << (*iten)[1] << std::endl;
    std::cout << "neighborhood.size "<< points.size() << std::endl;
    std::cout <<  std::endl;
*/
    for(auto element: points) {
        //line of the element
        Vector direction(GenVector(point, *element));
        auto half_direction(direction / 2.0);
        Straight element_line(direction, half_direction + point);
        Point line_cross(element_line == line);
 //       std::cout << "element cadidate " << (*element)[0] << " " << (*element)[1] << std::endl;
        if(line_cross.size() > 1){
            double distance = EuclideanDistance(line_cross, point_ref); 
//            std::cout << "cross " << line_cross[0] << " " << line_cross[1] << std::endl;
//            std::cout << "distance "<< distance << std::endl;
            //std::cout << "side "<< NormalSide(line_cross, side_line)<< std::endl;
            if( max_distance > distance) {
                max_distance = distance;
                neighbor = element;
/*                std::cout << "element direction " << element_line.get_normal()[0] << " " << element_line.get_normal()[1] << std::endl;
                std::cout << "element point " << element_line.get_point()[0] << " " << element_line.get_point()[1] << std::endl;
                std::cout << std::endl;
                std::cout << "line direction " << line.get_normal()[0] << " " << line.get_normal()[1] << std::endl;
                std::cout << "line point " << line.get_point()[0] << " " << line.get_point()[1] << std::endl;
                std::cout << std::endl;
                std::cout << "neighbor " << (*neighbor)[0] << " " << (*neighbor)[1] << std::endl;
//                */
            }
        }
        
    }
    //std::cout << (*neighbor)[0] << " " << (*neighbor)[1] << std::endl;
    return neighbor;
}
