//
// Created by sarth on 28-06-2024.
//

#include <bits/stdc++.h>
#include <chrono>
#include "models/3DModel.cpp"
#include "models/1DModel.cpp"
#include "models/bitsModel.cpp"
#include "solvers/dfs_solver.h"
#include "solvers/bfs_solver.h"
#include "solvers/iddfs_solver.h"
#include "solvers/idastar_solver.h"
#include "patternDB/corner_patternDB.h"
#include "patternDB/corner_patternDB_maker.h"

using namespace std;
using namespace std::chrono;

int main() {
    // DFS Solver Testing
    modelbits cube;
    cube.print();

    vector<generic_cube::MOVE> shuffle_moves = cube.randomShuffleCube(8);
    cout << "Shuffled Moves : ";
    for (auto move: shuffle_moves) cout << cube.getMove(move) << " ";
    cout << "\n";
    cube.print();

    auto start_time = high_resolution_clock::now();

    dfs_solver<modelbits, HashBitboard> dfsSolver(cube, 18);
    vector<generic_cube::MOVE> solve_moves = dfsSolver.solve();

    auto end_time = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end_time - start_time);

    cout << "Solving Moves : ";
    for (auto move: solve_moves) cout << cube.getMove(move) << " ";
    cout << "\n";
    dfsSolver.curr_cube.print();

    cout << "Time taken to solve: " << duration.count() << " microseconds" << endl;
    return 0;
}
