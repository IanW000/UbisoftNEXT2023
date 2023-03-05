#pragma once
using namespace std;
#include <vector>
#include <set>

struct PathFinding {

    static vector<pair<int, int>> a_star_pathfinding(int start_x, int start_y, int goal_x, int goal_y, const vector<vector<int>>& board);

};


