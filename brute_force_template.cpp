template <class Type>
BruteForce::Voronoi<Type>::Voronoi(std::vector<Type*>& data): points() {
    for(size_t i = 0; i < data.size(); ++i) {
        points.push_back({(*data[i])[0], (*data[i])[1]});
    }
    for(size_t i = 0; i < data.size(); ++i) 
        pointer_translate[&points[i]] = (data)[i]; 
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
std::unordered_map<Type*, std::set<Type*>> BruteForce::Voronoi<Type>::Neighbors() {

    using namespace geometry;
    std::unordered_map<Type*, std::set<Type*>> result;
    auto pointers(ToPointers(points));
    for(auto iten(points.begin()); iten < points.end(); ++iten) {
        std::set<Type*> neighbors_set;
        auto cell_neighbors(CellNeighbors(points, *iten));
        for(auto &element: cell_neighbors)
            neighbors_set.insert(pointer_translate[element]); 
        result[pointer_translate[&(*iten)]] = neighbors_set;
    }
    return result;
}

