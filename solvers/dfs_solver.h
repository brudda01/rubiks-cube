//
// Created by sarth on 17-06-2024.
//

#ifndef RUBIKS_CUBE_DFS_SOLVER_H
#define RUBIKS_CUBE_DFS_SOLVER_H

#include "../models/generic_cube.h"

template<typename T, typename H>
class dfs_solver {
private:

    vector<generic_cube::MOVE> moves;
    int max_search_depth;

    bool dfs(int dep) {
        if (curr_cube.isSolved()) return true;
        if (dep > max_search_depth) return false;
        for (int i = 0; i < 18; i++) {
            curr_cube.move(generic_cube::MOVE(i));
            moves.push_back(generic_cube::MOVE(i));
            if (dfs(dep + 1)) return true;
            moves.pop_back();
            curr_cube.invert(generic_cube::MOVE(i));
        }
        return false;
    }

public:
    T curr_cube;

    dfs_solver(T shuffled_cube, int search_depth = 8) {
        curr_cube = shuffled_cube;
        max_search_depth = search_depth;
    }

    vector<generic_cube::MOVE> solve() {
        dfs(1);
        return moves;
    }

};

#endif //RUBIKS_CUBE_DFS_SOLVER_H
