//
// Created by sarth on 26-06-2024.
//

#include "corner_patternDB_maker.h"
#include "../models/bitsModel.cpp"

corner_patternDB_maker::corner_patternDB_maker(string fileName) {
    this->fileName = fileName;
}

corner_patternDB_maker::corner_patternDB_maker(string fileName, uint8_t init_val) {
    this->fileName = fileName;
    cornerDB = corner_patternDB(init_val);
}

bool corner_patternDB_maker::bfs_and_store() {
    modelbits cube;
    queue<modelbits> q;
    q.push(cube);
    cornerDB.setNumMoves(cube, 0);
    int curr_depth = 0;
    while (!q.empty()) {
        int n = q.size();
        curr_depth++;
        if (curr_depth == 9) break;
        for (int counter = 0; counter < n; counter++) {
            modelbits node = q.front();
            q.pop();
            for (int i = 0; i < 18; i++) {
                auto curr_move = generic_cube::MOVE(i);
                node.move(curr_move);
                if ((int) cornerDB.getNumMoves(node) > curr_depth) {
                    cornerDB.setNumMoves(node, curr_depth);
                    q.push(node);
                }
                node.invert(curr_move);
            }
        }
    }

    cornerDB.toFile(fileName);
    return true;
}