#ifndef BRUTE_FORCE_H
#define BRUTE_FORCE_H 

#include <vector>
#include <cstring>
#include <set>

#include "geometric_utils/geometry.h" 

namespace BruteForce{

    class Voronoi {
        public:
            typedef std::vector<std::vector<double>> data_points;
            Voronoi(const data_points & data);

            const data_points & get_points() const;
            size_t size() const;

            std::vector<geometry::Point*> CellNeighbors(data_points& points, geometry::Point& point); 
            
        private:
            data_points points;
            
    };
}

#endif /* BRUTE_FORCE_H */
