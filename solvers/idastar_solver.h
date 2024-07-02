//
// Created by sarth on 20-06-2024.
//

#ifndef RUBIKS_CUBE_IDASTAR_SOLVER_H
#define RUBIKS_CUBE_IDASTAR_SOLVER_H

#include "../models/generic_cube.h"
#include "../patternDB/corner_patternDB.h"

template<typename T, typename H>
class idastar_solver {
private:
    corner_patternDB cornerDB;
    vector<generic_cube::MOVE> backptr;
    unordered_map<T, generic_cube::MOVE, H> par_move;
    unordered_map<T, bool, H> vis;

    struct Node {
        T cube;
        int depth;
        int estimate;

        Node(T cube, int depth, int estimate) {
            this->cube = cube;
            this->depth = depth;
            this->estimate = estimate;
        }
    };

    void resetcube() {
        backptr.clear();
        par_move.clear();
        vis.clear();
    }

    struct compareCube {
        bool operator()(pair<Node, int> const &p1, pair<Node, int> const &p2) {
            auto n1 = p1.first, n2 = p2.first;
            if (n1.depth + n1.estimate == n2.depth + n2.estimate) {
                return n1.estimate > n2.estimate;
            } else return n1.depth + n1.estimate > n2.depth + n2.estimate;
        }
    };

    pair<T, int> IDAstar(int bound) {
        priority_queue<pair<Node, int>, vector<pair<Node, int >>, compareCube> pq;
        Node start = Node(curr_cube, 0, cornerDB.getNumMoves(curr_cube));
        pq.push(make_pair(start, 0));
        int next_bound = 100;
        while (!pq.empty()) {
            auto p = pq.top();
            Node node = p.first;
            pq.pop();

            if (vis[node.cube]) continue;

            vis[node.cube] = true;
            par_move[node.cube] = generic_cube::MOVE(p.second);

            if (node.cube.isSolved()) return make_pair(node.cube, bound);
            node.depth++;
            for (int i = 0; i < 18; i++) {
                auto curr_move = generic_cube::MOVE(i);
                node.cube.move(curr_move);
                if (!vis[node.cube]) {
                    node.estimate = cornerDB.getNumMoves(node.cube);
                    if (node.estimate + node.depth > bound) {
                        next_bound = min(next_bound, node.estimate + node.depth);
                    } else {
                        pq.push(make_pair(node, i));
                    }
                }
                node.cube.invert(curr_move);
            }

        }
        return make_pair(curr_cube, next_bound);
    }

public:
    T curr_cube;

    idastar_solver(T curr_cube, string fileName) {
        this->curr_cube = curr_cube;
        cornerDB.fromFile(fileName);
    }

    vector<generic_cube::MOVE> solve() {
        int bound = 1;
        auto p = IDAstar(bound);
        while (p.second != bound) {
            resetcube();
            bound = p.second;
            p = IDAstar(bound);
        }
        T solved_cube = p.first;
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

#endif //RUBIKS_CUBE_IDASTAR_SOLVER_H
