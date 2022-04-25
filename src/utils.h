#include<string>
#include<vector>
#include<algorithm>

using namespace std;

struct HCoords{
    int x, y, z;

    string to_str(){
        return to_string(x) + ":"
               + to_string(y) + ":"
               + to_string(z);
    }

    HCoords& operator+=(const HCoords& left){
        x += left.x;
        y += left.y;
        z += left.z;
        return *this;
    }

    HCoords operator+(const HCoords& left){
        return HCoords{ x + left.x, y + left.y, z + left.z };
    }

    int dist_from_center(){
        return max(max(abs(x), abs(y)), abs(z));
    }
};

const vector<HCoords> SURROUND_COORDS {
    HCoords{1, 0, -1},
    HCoords{0, 1, -1},
    HCoords{-1, 1, 0},
    HCoords{-1, 0, 1},
    HCoords{0, -1, 1},
    HCoords{1, -1, 0}
};

