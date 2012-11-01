//#include "brute_force.h"

template <class Type>
BruteForce::Voronoi<Type>::Voronoi(const std::vector<Type*>& data): points() {
    for(size_t i = 0; i < data.size(); ++i) {
        points.push_back({(*data[i])[0], (*data[i])[1]});
    }
    for(size_t i = 0; i < data.size(); ++i) 
        pointer_translate[&points[i]] = data[i]; 
}

template <class Type>
BruteForce::Voronoi<Type>::Voronoi(std::vector<Type>& data): points() {
    for(size_t i = 0; i < data.size(); ++i) {
        points.push_back({(data[i])[0], (data[i])[1]});
    }
    for(size_t i = 0; i < data.size(); ++i) {
        pointer_translate[&points[i]] = &data[i]; 
    }
}

template <class Type>
const BruteForce::data_points &  BruteForce::Voronoi<Type>::get_points() const {
    return points;
}

template <class Type>
size_t BruteForce::Voronoi<Type>::size() const {
    return points.size();
}

template <class Type>
std::unordered_map<geometry::Point*, std::set<geometry::Point*>> BruteForce::Voronoi<Type>::Neighbors() {

    using namespace geometry;
    std::unordered_map<geometry::Point*, std::set<geometry::Point*>> result;
    auto pointers(ToPointers(points));
    for(auto iten(points.begin()); iten < points.end(); ++iten) {
        std::set<geometry::Point*> neighbors_set;
        auto cell_neighbors(CellNeighbors(points, *iten));
        for(auto &element: cell_neighbors)
            neighbors_set.insert(pointer_translate[element]); 
        result[pointer_translate[&(*iten)]] = neighbors_set;
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

    //################## righ side ############################

    bool flag(true);
    Point* element(NULL);
    Straight line(first_line);
    Straight last_line(first_line);
    Straight side(midle_line_right);
    Point vertex(side == line);
    Point vertex_init(side == line);
    while(flag){
        last_line = line;
        element = LineCross(line, point, vertex, neighborhood_right);
        if(element) {
            Vector direction(GenVector(point, *element));
            Vector normal(NormalVector(direction));
            auto half_direction(direction / 2.0);
            line = Straight(direction, half_direction + point);
            side = Straight(normal, *element);
            vertex = (last_line == line);
            neighbors.push_back(element);
            neighborhood_right = OnNormalSide(side, neighborhood_right);
        }else{
            flag = false; 
        }
    }

    //****************left side **************************/
    Straight midle_line_left(NormalVectorInverted(direction_init), point);
    flag = true;
    element = NULL;
    line = first_line;
    side = midle_line_left;
    vertex = vertex_init;
    while(flag){
        last_line = line;
        element = LineCross(line, point, vertex, neighborhood_left);
        if(element) {
            Vector direction(GenVector(point, *element));
            Vector normal(NormalVectorInverted(direction));
            auto half_direction(direction / 2.0);
            line = Straight(direction, half_direction + point);
            side = Straight(normal, *element);
            vertex = (last_line == line);
            neighbors.push_back(element);
            neighborhood_left = OnNormalSide(side, neighborhood_left);
        }else{
            flag = false; 
        }
    }

    return neighbors;
}

geometry::Point* BruteForce::LineCross(const geometry::Straight& line, geometry::Point& point,  
                                       const geometry::Point& point_ref, std::vector<geometry::Point*> points){ 
    using namespace geometry;

    geometry::Point* neighbor = NULL;
    double max_distance = DBL_MAX;

    for(auto element: points) {
        Vector direction(GenVector(point, *element));
        auto half_direction(direction / 2.0);
        Straight element_line(direction, half_direction + point);
        Point line_cross(element_line == line);
        if(line_cross.size() > 1){
            double distance = EuclideanDistance(line_cross, point_ref); 
            if( max_distance > distance) {
                max_distance = distance;
                neighbor = element;
            }
        }
        
    }
    return neighbor;
}
