//
// Created by sarth on 20-06-2024.
//

#ifndef RUBIKS_CUBE_IDDFS_SOLVER_H
#define RUBIKS_CUBE_IDDFS_SOLVER_H

#include "../models/generic_cube.h"
#include "dfs_solver.h"

template<typename T, typename H>
class iddfs_solver {

private:
    int max_search_depth;
    vector <generic_cube::MOVE> moves;

public:
    T curr_cube;

    iddfs_solver(T shuffled_cube, int search_depth = 7) {
        curr_cube = shuffled_cube;
        max_search_depth = search_depth;
    }

    vector <generic_cube::MOVE> solve() {
        for (int i = 1; i <= max_search_depth; i++) {
            dfs_solver <T, H> dfsSolver(curr_cube, i);
            moves = dfsSolver.solve();
            if (dfsSolver.curr_cube.isSolved()) {
                curr_cube = dfsSolver.curr_cube;
                break;
            }
        }
        return moves;
    }

};

#endif //RUBIKS_CUBE_IDDFS_SOLVER_H
