#include <set> 
#include <vector> 

#include "../brute_force.h"
#include "gtest/gtest.h"

//#include "../geometric_utils/geometry.h" 

//*
using namespace BruteForce;
using namespace geometry;
TEST(BruteForce, data_points_def) {
    data_points points;
    points.push_back({1,2});
    points.push_back({3,4});
    EXPECT_EQ(points[0][0], 1);
    EXPECT_EQ(points[0][1], 2);
    EXPECT_EQ(points[1][0], 3);
    EXPECT_EQ(points[1][1], 4);
}

TEST(BruteForce, constructor) {
    data_points points;
    points.push_back({1,2});
    points.push_back({3,4});
    Voronoi voronoi(points);
    EXPECT_EQ(voronoi.size(), 2);
    EXPECT_EQ(voronoi.get_points()[0][0], 1);
    EXPECT_EQ(voronoi.get_points()[0][1], 2);
    EXPECT_EQ(voronoi.get_points()[1][0], 3);
    EXPECT_EQ(voronoi.get_points()[1][1], 4);
}

TEST(BruteForce, LineCross) {

    Straight line({1, 1}, {0, 0}); 
    Straight side({0, 1}, {0, 0}); 
    data_points points;
    points.push_back({0, 1});
    points.push_back({0, 2});
    points.push_back({2, 2});
    points.push_back({2, 0});
    points.push_back({-1, -1});
    Point point({0, 0});
    EXPECT_TRUE(LineCross(line, point, side, ToPointers(points))== &points[0]);
}

TEST(BruteForce, LineCross2) {

    Straight line({1, 0}, {0.5, 0}); 
    Straight side({0, 1}, {0.0, 0}); 

    data_points points;
//    points.push_back({cos(0), sin(0)});
    points.push_back({cos(45 * M_PI / 180.0), sin(45 * M_PI / 180.0)});
    points.push_back({cos(90 * M_PI / 180.0), sin(90 * M_PI / 180.0)});
    points.push_back({cos(135 * M_PI / 180.0), sin(135 * M_PI / 180.0)});
    points.push_back({cos(180 * M_PI / 180.0), sin(180 * M_PI / 180.0)});

    Point point({0, 0});
    Point* cross(LineCross(line, point, side, ToPointers(points)));
    EXPECT_TRUE(cross == &points[0]);
}

TEST(BruteForce, LineCross3) {

    Straight line({cos(45 * M_PI / 180.0), sin(45 * M_PI / 180.0)}, {0.5, 0.5}); 
    Straight side({cos(135 * M_PI / 180.0), sin(135 * M_PI / 180.0)}, {0.5, 0.0}); 

    std::cout << (line == side) << std::endl;

    data_points points;
    points.push_back({cos(90 * M_PI / 180.0), sin(90 * M_PI / 180.0)});
    points.push_back({cos(135 * M_PI / 180.0), sin(135 * M_PI / 180.0)});
    points.push_back({cos(180 * M_PI / 180.0), sin(180 * M_PI / 180.0)});

    Point point({0, 0});
    Point* cross(LineCross(line, point, side, ToPointers(points)));
    EXPECT_TRUE(cross == &points[0]);
}

//*
TEST(BruteForce, CellHalf) {
    data_points points;

    Point point({0, 0});

    points.push_back({cos(0), sin(0)});
    points.push_back({cos(45 * M_PI / 180.0), sin(45 * M_PI / 180.0)});
    points.push_back({0, 1});
    points.push_back({cos(135 * M_PI / 180.0), sin(135 * M_PI / 180.0)});
    points.push_back({cos(180 * M_PI / 180.0), sin(180 * M_PI / 180.0)});

    auto neighbors(CellNeighbors(points, point));
    EXPECT_EQ(neighbors.size(), 5);
}

TEST(BruteForce, Cell) {
    data_points points;

    Point point({0, 0});

    points.push_back({cos(0), sin(0)});
    points.push_back({cos(45 * M_PI / 180.0), sin(45 * M_PI / 180.0)});
    points.push_back({0, 1});
    points.push_back({cos(135 * M_PI / 180.0), sin(135 * M_PI / 180.0)});
    points.push_back({cos(180 * M_PI / 180.0), sin(180 * M_PI / 180.0)});

    points.push_back({cos(225 * M_PI / 180.0), sin(225 * M_PI / 180.0)});
    points.push_back({cos(270 * M_PI / 180.0), sin(270 * M_PI / 180.0)});
    points.push_back({cos(315 * M_PI / 180.0), sin(315 * M_PI / 180.0)});

    auto neighbors(CellNeighbors(points, point));
    EXPECT_EQ(neighbors.size(), 8);
}
/*
TEST(BruteForce, Neighbors) {
    data_points points;

    points.push_back({0, 0});

    points.push_back({0, 1});
    points.push_back({0, 2});

    points.push_back({0, -1});
    points.push_back({0, -2});

    points.push_back({1, 0});
    points.push_back({2, 0});

    points.push_back({-1, 0});
    points.push_back({-2, 0});

    Voronoi voro(points);
//    voro.neighbors();
    auto neighbors(voro.neighbors());
    std::cout << neighbors.size() << std::endl;
    //for(auto iten(neighbors.begin()); iten < neighbors.end(); ++iten)
     //   std::cout << (*iten).first.size() << std::endl;
//    for(auto &iten: neighbors)
//        std::cout << ((iten.second)).size() << std::endl;

}

//*/
int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
