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
    //storing data
    std::vector<Point*> neighborhood(ToPointers(points));
    std::vector<Point*> neighborhood_right;
    std::vector<Point*> neighborhood_left;
    std::vector<Point*> neighbors;

    Point* nearest_neighbor(&NearestNeighbor(neighborhood, point));
    neighbors.push_back(nearest_neighbor);

    //removing the point from the neighborhood
    std::vector<Point*>::iterator position = std::find(neighborhood.begin(), neighborhood.end(), &point);
    if(position != neighborhood.end())
        neighborhood.erase(position);
    //removing the nearest neighbor from the neighborhood
    std::vector<Point*>::iterator p_near_neighbor = std::find(neighborhood.begin(), neighborhood.end(), nearest_neighbor);
    if(p_near_neighbor != neighborhood.end())
        neighborhood.erase(p_near_neighbor);

    //starting the neighborhood and the line
    Vector direction_init(GenVector(point, *nearest_neighbor));
    auto half_direction_init(direction_init / 2.0);
    Straight first_line(direction_init, half_direction_init + point);

    Straight midle_line_right(NormalVector(direction_init), point);
    DivideDots(midle_line_right, neighborhood, neighborhood_right, neighborhood_left);

    std::cout << "neighborhood size: "<< points.size() << std::endl;
    std::cout << "first neighbor: "<< (*nearest_neighbor) << std::endl;
    for(auto iten: neighborhood)
        std::cout << "points: " << (*iten) << std::endl;


    std::cout << std::endl;

    //################## righ side ############################
    std::cout << "############ right side ###############" << std::endl;
    //neighborhood_right = OnNormalSide(midle_line_right, neighborhood_right);

    bool flag(true);
    Point* element(NULL);
    Straight line(first_line);
    Straight last_line(first_line);
    Straight side(midle_line_right);
    Point vertex(side == line);
    Point vertex_init(side == line);
    while(flag){
       for(auto iten: neighborhood_right)
            std::cout << "points: "<< (*iten) << std::endl;

        last_line = line;
        element = LineCross(line, point, vertex, neighborhood_right);
        if(element) {
            Vector direction(GenVector(point, *element));
            Vector normal(NormalVector(direction));
            auto half_direction(direction / 2.0);
            line = Straight(direction, half_direction + point);
            side = Straight(normal, *element);
            vertex = (last_line == line);

        std::cout << "line vec: "<< line.get_normal() << std::endl;
        std::cout << "line point: "<< line.get_point() << std::endl;
        std::cout << "side: "<< side.get_normal() << std::endl;
        std::cout << "side point: "<< side.get_point() << std::endl;
 
            std::cout << "element: "<< (*element) << std::endl;
            std::cout << "encontro " << (line == side) << std::endl;
            std::cout << "vertice " << vertex << std::endl;
            neighbors.push_back(element);
            neighborhood_right = OnNormalSide(side, neighborhood_right);
        }else{
            flag = false; 
        }

        std::cout << "n neighbors " << neighbors.size() <<  std::endl;
        std::cout <<  std::endl;
    }
//****************left side **************************/
    std::cout << "################# left side #######################" << std::endl;
    Straight midle_line_left(NormalVectorInverted(direction_init), point);
    //neighborhood_left = OnNormalSide(midle_line_left, neighborhood_left);
    std::cout << "neig_left " <<  neighborhood_left.size() << std::endl;

    flag = true;
    element = NULL;
    line = first_line;
    side = midle_line_left;
    vertex = vertex_init;
    while(flag){
       for(auto iten: neighborhood_left)
            std::cout << "points: "<< (*iten)[0] << " " << (*iten)[1] << std::endl;


        last_line = line;
        element = LineCross(line, point, vertex, neighborhood_left);
        if(element) {
            Vector direction(GenVector(point, *element));
            Vector normal(NormalVectorInverted(direction));
            auto half_direction(direction / 2.0);
            line = Straight(direction, half_direction + point);
            side = Straight(normal, *element);
            vertex = (last_line == line);
        std::cout << "line vec: "<< line.get_normal() << std::endl;
        std::cout << "line point: "<< line.get_point() << std::endl;
        std::cout << "side: "<< side.get_normal() << std::endl;
        std::cout << "side point: "<< side.get_point() << std::endl;
 

            std::cout << "encontro " << (line == side) << std::endl;
            std::cout << "vertice " << vertex << std::endl;
            neighbors.push_back(element);
            neighborhood_left = OnNormalSide(side, neighborhood_left);
            std::cout << "element: "<< (*element) << std::endl;
        }else{
            flag = false; 
        }
        std::cout <<  std::endl;
    }

    return neighbors;
}

geometry::Point* BruteForce::LineCross(const geometry::Straight& line, geometry::Point& point,  
                                       const geometry::Point& point_ref, std::vector<geometry::Point*> points){ 
    using namespace geometry;

    geometry::Point* neighbor = NULL;
    //const Point point_ref(line == side_line);
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
