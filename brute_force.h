#ifndef BRUTE_FORCE_H
#define BRUTE_FORCE_H 

#include <unordered_map>
#include <vector>
#include <cstring>
#include <set>


#include "geometric_utils/geometry.h" 

namespace BruteForce{

typedef std::vector<geometry::Point> data_points;

class Voronoi {
    public:
        Voronoi(const data_points & data);
        
        const data_points & get_points() const;
        size_t size() const;
        std::unordered_map<geometry::Point*, std::set<geometry::Point*>> neighbors();

    private:
        data_points points;
};

std::vector<geometry::Point*> CellNeighbors(data_points& points, geometry::Point& point); 

geometry::Point* LineCross(const geometry::Straight& line,  geometry::Point& point,  
                           const geometry::Point& point_ref, std::vector<geometry::Point*> points); 

}

#endif /* BRUTE_FORCE_H */
