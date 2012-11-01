#ifndef BRUTE_FORCE_H
#define BRUTE_FORCE_H 

#include <unordered_map>
#include <vector>
#include <cstring>
#include <set>
#include <map>

#include "geometric_utils/geometry.h" 


namespace BruteForce{

typedef std::vector<geometry::Point> data_points;

template <class Type>
class Voronoi {
    public:
        Voronoi(const std::vector<Type*>& data);
        Voronoi(std::vector<Type>& data);
        
        const data_points & get_points() const;
        size_t size() const;
        std::unordered_map<Type*, std::set<Type*>> Neighbors();

    private:
        data_points points;
        std::map<Type*, geometry::Point*> pointer_translate;
};

std::vector<geometry::Point*> CellNeighbors(data_points& points, geometry::Point& point); 

geometry::Point* LineCross(const geometry::Straight& line,  geometry::Point& point,  
                           const geometry::Point& point_ref, std::vector<geometry::Point*> points); 

}

#include "brute_force_template.cpp"

#endif /* BRUTE_FORCE_H */
