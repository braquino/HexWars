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
    Color select_border = (this->bad_selection) ? RED : GREEN;
    for (auto& [key, tile] : this->hexes ) {
        if (tile.selected) tile.render(select_border);
    }
}

void Board::clear_selection(){
    for (auto& [key, tile] : this->hexes ) {
        tile.selected = false;
    }
}

bool Board::selectable(Tile& t) {
    return !((this->selection_mode == SelectionMode::OnlyPieces || this->selection_mode == SelectionMode::OnlyLinkedPieces)
             && t.get_piece() == nullptr);
}

void Board::bad_selection_check() {
    if (this-> num_selected > 1 &&
            (this->selection_mode == SelectionMode::OnlyLinkedTiles || this->selection_mode == SelectionMode::OnlyLinkedPieces)){
        vector<Tile*> sel;
        bool right = true;
        for (auto& [key, tile] : this->hexes ) { if (tile.selected) sel.push_back(&tile); }
        for (Tile* t1 : sel) {
            bool one_linked = false;
            for (Tile* t2 : sel) {
                double dist = t1->get_center().distance(t2->get_center());
                if (dist > 0.1){
                    one_linked |= dist < t1->get_size() * 2.2;
                }
            }
            right &= one_linked;
        }
        this->bad_selection = !right;
    } else {
        this->bad_selection = false;
    }

}

void Board::select(Point rec_start, Point rec_end, bool add){
    if (!add) this->num_selected = 0;
    for (auto& [key, tile] : this->hexes ) {
        if (tile.inside_rect(rec_start, rec_end)) {
            tile.selected = this->selectable(tile);
            if (tile.selected) this->num_selected++;
        } else if (!add) {
            tile.selected = false;
        }
    }
    this->bad_selection_check();
}

void Board::select(Point p, bool add) {
    if (!add) {
        this->clear_selection();
        this->num_selected = 0;
    }
    for (auto& [key, tile] : this->hexes ) {
        if (tile.check_collision(p)) {
            if (tile.selected && add){
                tile.selected = false;
                this->num_selected--;
            } else {
                tile.selected = this->selectable(tile);
                if (tile.selected) this->num_selected++;
            }
            this->bad_selection_check();
            return;
        }
    }
    this->bad_selection_check();
}

vector<string> Board::get_coords() {
    vector<string> right;
    for (auto& [key, tile] : this->hexes ) {
        right.push_back(key);
    }
    return right;
}

Tile& Board::get_tile(string coords) {
    auto iter = this->hexes.find(coords);
    if (iter != this->hexes.end()) return iter->second;
    else throw out_of_range("This coords: " + coords + " doesn't belong to this Board");
}
