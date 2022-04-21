#include <catch2/catch_test_macros.hpp>
#include "tile.h"
#include <iostream>

double t_round(double num) { return round(num * 100) / 100; }

TEST_CASE( "GeneralTests", "[every_test]" ) {
    SECTION("should test Point add"){
        Point a{30, 50};
        Point b{10, 25};
        REQUIRE(a + b == Point{40, 75});
    }

    SECTION("should convert HCoords to string"){
        HCoords c{3, -5, 8};
        REQUIRE(c.to_str() == "3:-5:8");
    }
}

TEST_CASE("TestTile", "[tests]") {
    SECTION("should calculate poly correctly"){
        Tile t{Point{20, 30}, 10};
        REQUIRE(t.get_points().size() == 6);
    }

    SECTION("should fetch the surround hexes from zero"){
        Tile t{Point{0, 0}, 20};
        auto surrounds = t.get_surround();

        REQUIRE(t_round(surrounds["1:-1:0"].get_center().x) == 30.0);
        REQUIRE(t_round(surrounds["1:-1:0"].get_center().y) == -17.32);

        REQUIRE(t_round(surrounds["1:0:-1"].get_center().x) == 30.0);
        REQUIRE(t_round(surrounds["1:0:-1"].get_center().y) == 17.32);

        REQUIRE(t_round(surrounds["-1:1:0"].get_center().x) == -30.0);
        REQUIRE(t_round(surrounds["-1:1:0"].get_center().y) == 17.32);

        REQUIRE(t_round(surrounds["-1:0:1"].get_center().x) == -30.0);
        REQUIRE(t_round(surrounds["-1:0:1"].get_center().y) == -17.32);

        REQUIRE(t_round(surrounds["0:1:-1"].get_center().x) == 0.0);
        REQUIRE(t_round(surrounds["0:1:-1"].get_center().y) == 34.64);

        REQUIRE(t_round(surrounds["0:-1:1"].get_center().x) == 0.0);
        REQUIRE(t_round(surrounds["0:-1:1"].get_center().y) == -34.64);
    }

}
