#include "tile.h"

enum class SelectionMode{ OnlyPieces, OnlyLinkedPieces, All, OnlyLinkedTiles };

class Board {
public:
    Board(Point position_0, int num_tiles, double max_width_px, double max_heigh_px, SelectionMode selection_mode = SelectionMode::All):
        position_0{position_0}, num_tiles{num_tiles}, max_height_px{max_heigh_px}, max_width_px{max_width_px},
        position_end{Point{position_0.x + max_width_px, position_0.y + max_heigh_px}},
        selection_mode{selection_mode} {
        calc_tile_size();
    };

    double get_tile_size() { return tile_size; };
    void fill_retangle();
    int size() { return hexes.size(); }
    void render();
    void select(Point rect_start, Point rect_end, bool add = false);
    void select(Point p, bool add = false);
    void clear_selection();
    Tile& get_tile(HCoords coords) { return get_tile(coords.to_str()); }
    Tile& get_tile(string coords);
    vector<string> get_coords();
    void set_piece(Piece* piece, string coords) { hexes[coords].set_piece(piece); }

private:
    Point position_0;
    int num_tiles;
    double max_height_px;
    double max_width_px;
    Point position_end;
    double tile_size;
    map<string, Tile> hexes;
    SelectionMode selection_mode;
    bool bad_selection = false;
    int num_selected = 0;

    void calc_tile_size();
    void expand_hex(Tile& t);
    bool selectable(Tile& t);
    void bad_selection_check();
};

