#include <catch2/catch_test_macros.hpp>
#include "board.h"
#include <iostream>

double t_round(double num) { return round(num * 100) / 100; }

TEST_CASE( "GeneralTests", "[test]" ) {
    SECTION("should convert HCoords to string"){
        HCoords c{3, -5, 8};
        REQUIRE(c.to_str() == "3:-5:8");
    }
}

TEST_CASE("TestPoint", "[test]") {
    SECTION("should test Point add"){
        Point a{30, 50};
        Point b{10, 25};
        REQUIRE(a + b == Point{40, 75});
    }

    SECTION("should test correctly if the point is out of a retangle") {
        Point p_n30_n30{-30, -30};
        Point p_n20_n20{-20, -20};
        Point p_0_0{0, 0};
        Point p_60_60{60, 60};
        Point p_20_20{20, 20};
        Point p_20_60{20, 60};
        Point p_40_40{40, 40};
        Point p_30_50{30, 50};
        REQUIRE(p_30_50.inside_rec(p_0_0, p_60_60));
        REQUIRE(p_30_50.inside_rec(p_n20_n20, p_60_60));
        REQUIRE(p_n20_n20.inside_rec(p_n30_n30, p_60_60));
        REQUIRE(!p_30_50.inside_rec(p_0_0, p_20_20));
        REQUIRE(!p_30_50.inside_rec(p_0_0, p_20_60));
        REQUIRE(!p_30_50.inside_rec(p_0_0, p_40_40));
        REQUIRE(!p_30_50.inside_rec(p_40_40, p_60_60));
        REQUIRE(!p_30_50.inside_rec(p_20_60, p_60_60));
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

    SECTION("should fetch the surround hexes from specific tile"){
        Tile t{Point{50, 30}, 20, HCoords{-3, 1, 2}};
        auto surrounds = t.get_surround();

        REQUIRE(t_round(surrounds["-2:0:2"].get_center().x) == 80.0);
        REQUIRE(t_round(surrounds["-2:0:2"].get_center().y) == 12.68);

        REQUIRE(t_round(surrounds["-2:1:1"].get_center().x) == 80.0);
        REQUIRE(t_round(surrounds["-2:1:1"].get_center().y) == 47.32);

    }

    SECTION("should test if a tile is inside a rectangle") {
        Point p_0_0{0, 0};
        Point p_60_60{60, 60};

        Tile t1{Point{30, 30}, 20};
        Tile t2{Point{30, 30}, 40};
        Tile t3{Point{50, 30}, 20};

        REQUIRE(t1.inside_rect(p_0_0, p_60_60));
        REQUIRE(!t2.inside_rect(p_0_0, p_60_60));
        REQUIRE(!t3.inside_rect(p_0_0, p_60_60));
    }

}

TEST_CASE("TestBoard", "[tests") {
    SECTION("should calculare the correct tile size") {
        Board b{Point{5, 5}, 40, 400, 1000};
        REQUIRE(t_round(b.get_tile_size()) == 55.56);
    }

    SECTION("should create 30 tiles"){
        Board b{Point{5, 5}, 20, 600, 600};
        REQUIRE(b.size() == 0);
        b.fill_retangle();
        REQUIRE(b.size() == 20);
    }
}
