#include <set> 
#include <vector> 

#include "../brute_force.h"
#include "gtest/gtest.h"


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

    Voronoi<Point> voronoi(points);

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

    EXPECT_TRUE(LineCross(line, point, (line == side), ToPointers(points))== &points[0]);
}


TEST(BruteForce, LineCross2) {

    Straight line({1, 0}, {0.5, 0}); 
    Straight side({0, 1}, {0.0, 0}); 

    data_points points;
    points.push_back({cos(45 * M_PI / 180.0), sin(45 * M_PI / 180.0)});
    points.push_back({cos(90 * M_PI / 180.0), sin(90 * M_PI / 180.0)});
    points.push_back({cos(135 * M_PI / 180.0), sin(135 * M_PI / 180.0)});
    points.push_back({cos(180 * M_PI / 180.0), sin(180 * M_PI / 180.0)});

    Point point({0, 0});
    Point* cross(LineCross(line, point, (line == side), ToPointers(points)));

    EXPECT_TRUE(cross == &points[0]);
}

TEST(BruteForce, LineCross3) {

    Straight line({cos(45 * M_PI / 180.0), sin(45 * M_PI / 180.0)}, {0.5, 0.5}); 
    Straight side({cos(135 * M_PI / 180.0), sin(135 * M_PI / 180.0)}, {0.5, 0.0}); 

    data_points points;
    points.push_back({cos(90 * M_PI / 180.0), sin(90 * M_PI / 180.0)});
    points.push_back({cos(135 * M_PI / 180.0), sin(135 * M_PI / 180.0)});
    points.push_back({cos(180 * M_PI / 180.0), sin(180 * M_PI / 180.0)});

    Point point({0, 0});
    Point* cross(LineCross(line, point, (line == side), ToPointers(points)));
    EXPECT_TRUE(cross == &points[0]);
}

TEST(BruteForce, CellHalfCircle) {
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

TEST(BruteForce, CellCircleCenter) {
    data_points points;
    points.push_back({cos(0), sin(0)});
    points.push_back({cos(45 * M_PI / 180.0), sin(45 * M_PI / 180.0)});
    points.push_back({0, 1});
    points.push_back({cos(135 * M_PI / 180.0), sin(135 * M_PI / 180.0)});
    points.push_back({cos(180 * M_PI / 180.0), sin(180 * M_PI / 180.0)});
    points.push_back({cos(225 * M_PI / 180.0), sin(225 * M_PI / 180.0)});
    points.push_back({cos(270 * M_PI / 180.0), sin(270 * M_PI / 180.0)});
    points.push_back({cos(315 * M_PI / 180.0), sin(315 * M_PI / 180.0)});
    points.push_back({0, 0});

    auto neighbors(CellNeighbors(points, points[8]));
    EXPECT_EQ(neighbors.size(), 8);
}

TEST(BruteForce, CellCircleBorder) {
    data_points points;
    points.push_back({cos(0), sin(0)});
    points.push_back({cos(45 * M_PI / 180.0), sin(45 * M_PI / 180.0)});
    points.push_back({0, 1});
    points.push_back({cos(135 * M_PI / 180.0), sin(135 * M_PI / 180.0)});
    points.push_back({cos(180 * M_PI / 180.0), sin(180 * M_PI / 180.0)});
    points.push_back({cos(225 * M_PI / 180.0), sin(225 * M_PI / 180.0)});
    points.push_back({cos(270 * M_PI / 180.0), sin(270 * M_PI / 180.0)});
    points.push_back({cos(315 * M_PI / 180.0), sin(315 * M_PI / 180.0)});
    points.push_back({0, 0});

    EXPECT_EQ((CellNeighbors(points, points[0])).size(), 3);
    EXPECT_EQ((CellNeighbors(points, points[1])).size(), 3);
    EXPECT_EQ((CellNeighbors(points, points[2])).size(), 3);
    EXPECT_EQ((CellNeighbors(points, points[3])).size(), 3);
    EXPECT_EQ((CellNeighbors(points, points[5])).size(), 3);
    EXPECT_EQ((CellNeighbors(points, points[6])).size(), 3);
    EXPECT_EQ((CellNeighbors(points, points[7])).size(), 3);
}

TEST(BruteForce, CellSquareCenter) {
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

    auto neighbors(CellNeighbors(points, points[0]));
    EXPECT_EQ(neighbors.size(), 4);
}

TEST(BruteForce, CellSquareCorner) {
    data_points points;
    points.push_back({0, 0});
    points.push_back({0, 1});
    points.push_back({0, 2});
    points.push_back({0, -1});
    points.push_back({0, -2});
    points.push_back({1.2, 0});
    points.push_back({2, 0});
    points.push_back({-1, 0});
    points.push_back({-2, 0});

    auto neighbors(CellNeighbors(points, points[5]));
    EXPECT_EQ(neighbors.size(), 6);
}

TEST(BruteForce, CellTriangle) {
    data_points points;
    points.push_back({0, 0});
    points.push_back({0, 1});
    points.push_back({0, -1});
    points.push_back({1, 0});

    EXPECT_EQ((CellNeighbors(points, points[0])).size(), 3);
    EXPECT_EQ((CellNeighbors(points, points[1])).size(), 2);
    EXPECT_EQ((CellNeighbors(points, points[2])).size(), 2);
    EXPECT_EQ((CellNeighbors(points, points[3])).size(), 3);
}

TEST(BruteForce, SullivanMain) {
    data_points points;
    points.push_back({-22, -9});
    points.push_back({-17, 31});
    points.push_back({4, 13});
    points.push_back({22, -5});

    EXPECT_EQ((CellNeighbors(points, points[0])).size(), 3);
    EXPECT_EQ((CellNeighbors(points, points[1])).size(), 2);
    EXPECT_EQ((CellNeighbors(points, points[2])).size(), 3);
    EXPECT_EQ((CellNeighbors(points, points[3])).size(), 2);
}

TEST(BruteForce, NeighborsVoronoi) {
    data_points points;
    points.push_back({-22, -9});
    points.push_back({-17, 31});
    points.push_back({4, 13});
    points.push_back({22, -5});

    Voronoi<Point> voro(points);
    std::unordered_map<geometry::Point*, std::set<geometry::Point*>>  neighbors(voro.Neighbors());

    EXPECT_EQ(neighbors[&points[0]].size(), 3);
    EXPECT_EQ(neighbors[&points[1]].size(), 2);
    EXPECT_EQ(neighbors[&points[2]].size(), 3);
    EXPECT_EQ(neighbors[&points[3]].size(), 2);
}

TEST(BruteForce, NeighborsVoronoiPointer) {
    data_points points;
    points.push_back({-22, -9});
    points.push_back({-17, 31});
    points.push_back({4, 13});
    points.push_back({22, -5});

    Voronoi<Point> voro(points);
    std::unordered_map<geometry::Point*, std::set<geometry::Point*>>  neighbors(voro.Neighbors());

    EXPECT_EQ(neighbors[&points[0]].size(), 3);
    EXPECT_EQ(neighbors[&points[1]].size(), 2);
    EXPECT_EQ(neighbors[&points[2]].size(), 3);
    EXPECT_EQ(neighbors[&points[3]].size(), 2);
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
