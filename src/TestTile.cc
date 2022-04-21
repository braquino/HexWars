#include "gtest/gtest.h"
#include "tile.h"

TEST(TestTiles, calculate_poly) {
    Tile t{ Point{50, 50}, 20 };
    vector<Point> exp{ Point{1,1},Point{1,1}, Point{1,1}, Point{1,1}, Point{1,1}, Point{1,1} };
    vector<Point> act = t.get_points();
    EXPECT_EQ(6, (int)act.size());
}
