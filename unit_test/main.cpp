#include <set> 
#include <vector> 

#include "../brute_force.h"
#include "gtest/gtest.h"

//#include "../geometric_utils/geometry.h" 

//*
using namespace BruteForce;
TEST(BruteForce, data_points_def) {
    Voronoi::data_points points;
    points.push_back({1,2});
    points.push_back({3,4});
    EXPECT_EQ(points[0][0], 1);
    EXPECT_EQ(points[0][1], 2);
    EXPECT_EQ(points[1][0], 3);
    EXPECT_EQ(points[1][1], 4);
}

TEST(BruteForce, constructor) {
    Voronoi::data_points points;
    points.push_back({1,2});
    points.push_back({3,4});
    Voronoi voronoi(points);
    EXPECT_EQ(voronoi.size(), 2);
    EXPECT_EQ(voronoi.get_points()[0][0], 1);
    EXPECT_EQ(voronoi.get_points()[0][1], 2);
    EXPECT_EQ(voronoi.get_points()[1][0], 3);
    EXPECT_EQ(voronoi.get_points()[1][1], 4);
}

TEST(BruteForce, Cell) {
    Voronoi::data_points points;

    points.push_back({0, 0});

    points.push_back({0, 1});
    points.push_back({0, 2});

    points.push_back({0, -1});
    points.push_back({0, -2});

    points.push_back({1, 0});
    points.push_back({2, 0});

    points.push_back({-1, 0});
    points.push_back({-2, 0});

    Voronoi voronoi(points);

    EXPECT_EQ(voronoi.CellNeighbors(points, points[0]).size(), 4);
}
//*/
int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
