#include "board.h"
#include<iostream>

void Board::calc_tile_size(){
    // Should be 2, because (2 x side = hex_width), but (1.788 x side = height)
    // For some reason a minor rate works better
    double k{1.7};
    double v_tiles_num = sqrt(this->num_tiles / (this->max_width_px / this->max_height_px)) * k;
    this->tile_size = this->max_height_px / (v_tiles_num + 1);
}

void Board::fill_retangle() {
    Point point_center = (this->position_end - this->position_0) / 2;
    HCoords c0 = HCoords{0, 0, 0};
    this->hexes[c0.to_str()] = Tile{point_center, static_cast<int>(this->tile_size), c0};
    this->expand_hex(this->hexes[c0.to_str()]);

}

void Board::expand_hex(Tile& t){
    t.expanded = true;
    map<string, Tile> expansion = t.get_surround();
    for (auto& [key, new_tile] : expansion ) {
        if (this->hexes.find(key) == this->hexes.end()
                && new_tile.inside_rect(this->position_0, this->position_end)) {
            this->hexes[key] = new_tile;
            this->expand_hex(this->hexes[key]);
        }
    }
}

void Board::render() {
    for (auto& [key, tile] : this->hexes ) {
        if (!tile.selected) tile.render();
    }
    for (auto& [key, tile] : this->hexes ) {
        if (tile.selected) tile.render();
    }
}

void Board::clear_selection(){
    for (auto& [key, tile] : this->hexes ) {
        tile.selected = false;
    }
}

void Board::select(Point rec_start, Point rec_end, bool add){
    for (auto& [key, tile] : this->hexes ) {
        if (tile.inside_rect(rec_start, rec_end)) {
            tile.selected = true;
        } else if (!add) {
            tile.selected = false;
        }
    }
}

void Board::select(Point p, bool add) {
    if (!add) this->clear_selection();
    for (auto& [key, tile] : this->hexes ) {
        if (tile.check_collision(p)) {
            tile.selected = true;
            return;
        }
    }
}
