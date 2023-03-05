#include "stdafx.h"
#include "PathFinding.h"

vector<pair<int, int>> PathFinding::a_star_pathfinding(int start_x, int start_y, int goal_x, int goal_y, const vector<vector<int>>& board) {
    // Define the heuristic function
    auto heuristic = [](int x1, int y1, int x2, int y2) -> double {
        return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    };

    // Define the cell structure
    struct cell {
        int x;
        int y;
        double f;
        double g;
        double h;
        cell* parent;
        bool operator<(const cell& other) const {
            return f < other.f;
        }
    };

    // Create the start and goal cells
    cell start_cell{ start_x, start_y, 0, 0, 0, nullptr };
    cell goal_cell{ goal_x, goal_y, 0, 0, 0, nullptr };

    // Create the open and closed sets
    set<cell> open_set;
    set<cell> closed_set;
    open_set.insert(start_cell);

    // Loop until the open set is empty
    while (!open_set.empty()) {
        // Get the cell with the lowest f score from the open set
        cell current_cell = *open_set.begin();
        open_set.erase(open_set.begin());

        // Check if the current cell is the goal cell
        if (current_cell.x == goal_x && current_cell.y == goal_y) {
            // Reconstruct the path
            vector<pair<int, int>> path;
            cell* current = &current_cell;
            while (current != nullptr) {
                path.push_back({ current->x, current->y });
                current = current->parent;
            }
            reverse(path.begin(), path.end());
            return path;
        }

        // Add the current cell to the closed set
        closed_set.insert(current_cell);

        // Check the neighbors of the current cell
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                // Skip the current cell and diagonal neighbors
                if (dx == 0 && dy == 0) {
                    continue;
                }
                if (dx != 0 && dy != 0) {
                    continue;
                }

                // Calculate the coordinates of the neighbor
                int neighbor_x = current_cell.x + dx;
                int neighbor_y = current_cell.y + dy;

                // Skip neighbors that are out of bounds or blocked
                if (neighbor_x < 0 || neighbor_x >= board.size()) {
                    continue;
                }
                if (neighbor_y < 0 || neighbor_y >= board[0].size()) {
                    continue;
                }
                if (board[neighbor_x][neighbor_y] == 1) {
                    continue;
                }

                // Check if the neighbor is in the closed set
                cell neighbor_cell{ neighbor_x, neighbor_y, 0, 0, 0, nullptr };
                if (closed_set.count(neighbor_cell) > 0) {
                    continue;
                }

                // Calculate the tentative g score for the neighbor
                double tentative_g = current_cell.g + heuristic(current_cell.x, current_cell.y, neighbor_x, neighbor_y);

                // Check if the neighbor is already in the open set
                bool found = false;
                cell* neighbor_ptr = nullptr;
                for (auto it = open_set.begin(); it != open_set.end(); ++it) {
                    if (it->x == neighbor_x && it->y == neighbor_y) {
                        found = true;
                        neighbor_ptr = const_cast<cell*>(&(*it));
                        break;
                    }
                }

                // If the neighbor is not in the open set, add it
                if (!found) {
                    neighbor_cell.h = heuristic(neighbor_x, neighbor_y, goal_x, goal_y);
                    neighbor_cell.g = tentative_g;
                    neighbor_cell.f = neighbor_cell.g + neighbor_cell.h;
                    neighbor_cell.parent = &current_cell;
                    open_set.insert(neighbor_cell);
                }
                // If the neighbor is already in the open set, update its g score if the tentative g score is lower
                else if (tentative_g < neighbor_ptr->g) {
                    neighbor_ptr->g = tentative_g;
                    neighbor_ptr->f = neighbor_ptr->g + neighbor_ptr->h;
                    neighbor_ptr->parent = &current_cell;
                }
            }
        }
    }

    // If the goal cell is unreachable, return an empty path
    return {};

}
