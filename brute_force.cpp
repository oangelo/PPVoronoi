#include "brute_force.h"

BruteForce::Voronoi::Voronoi(const data_points & data): points(data) {
    
}

const BruteForce::Voronoi::data_points &  BruteForce::Voronoi::get_points() const {
    return points;
}

size_t BruteForce::Voronoi::size() const {
    return points.size();
}
            

std::vector<geometry::Point*>  BruteForce::Voronoi::CellNeighbors(data_points& points, geometry::Point& point){ 
    using namespace geometry;
    std::vector<Point*> neighborhood(ToPointers(points));
    std::vector<Point*> neighbors;
    while(neighborhood.size() > 1){
        Point* neighbor_aux(&NearestNeighbor(neighborhood, point));
        neighbors.push_back(neighbor_aux);
        Vector direction(GenVector(point, *neighbor_aux));
        Straight line(direction, direction / 2.0);
        neighborhood = OnLeftSide(line, neighborhood);
    }
    return neighbors;
}
