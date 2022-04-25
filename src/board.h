#include "tile.h"


class Board {
public:
    Board(Point position_0, int num_tiles, double max_width_px, double max_heigh_px):
        position_0{position_0}, num_tiles{num_tiles}, max_height_px{max_heigh_px}, max_width_px{max_width_px},
        position_end{Point{position_0.x + max_width_px, position_0.y + max_heigh_px}} {
        calc_tile_size();
    };

    double get_tile_size() { return tile_size; };
    void fill_retangle();
    int size() { return hexes.size(); }
    void render();

private:
    Point position_0;
    int num_tiles;
    double max_height_px;
    double max_width_px;
    Point position_end;
    double tile_size;
    map<string, Tile> hexes;

    void calc_tile_size();
    void expand_hex(Tile& t);
};

