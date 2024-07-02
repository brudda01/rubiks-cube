//
// Created by sarth on 16-06-2024.
//

#ifndef RUBIKS_CUBE_BFS_SOLVER_H
#define RUBIKS_CUBE_BFS_SOLVER_H

#include "../models/generic_cube.h"

template<typename T, typename H>
class bfs_solver {
private:
    vector<generic_cube::MOVE> backptr;
    unordered_map<T, bool, H> vis;
    unordered_map<T, generic_cube::MOVE, H> par_move;

    T bfs() {
        queue<T> q;
        q.push(curr_cube);
        vis[curr_cube] = true;

        while (!q.empty()) {
            T node = q.front();
            q.pop();
            if (node.isSolved()) {
                return node;
            }
            for (int i = 0; i < 18; i++) {
                auto curr_move = generic_cube::MOVE(i);
                node.move(curr_move);
                if (!vis[node]) {
                    vis[node] = true;
                    par_move[node] = curr_move;
                    q.push(node);
                }
                node.invert(curr_move);
            }
        }
        return curr_cube;
    }

public:
    T curr_cube;

    bfs_solver(T shuffled_cube) {
        this->curr_cube = shuffled_cube;
    }

    vector<generic_cube::MOVE> solve() {
        T solved_cube = bfs();
        assert(solved_cube.isSolved());

        T curr_cube = solved_cube;
        while (!(curr_cube == curr_cube)) {
            generic_cube::MOVE curr_move = par_move[curr_cube];
            backptr.push_back(curr_move);
            curr_cube.invert(curr_move);
        }
        curr_cube = solved_cube;
        reverse(backptr.begin(), backptr.end());
        return backptr;
    }
};


#endif //RUBIKS_CUBE_BFS_SOLVER_H
