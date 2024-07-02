//
// Created by sarth on 26-06-2024.
//

#ifndef RUBIKS_CUBE_CORNER_PATTERNDB_MAKER_H
#define RUBIKS_CUBE_CORNER_PATTERNDB_MAKER_H

#include "corner_patternDB.h"

class corner_patternDB_maker {
private:
    string fileName;
    corner_patternDB cornerDB;

public:
    corner_patternDB_maker(string _fileName);
    corner_patternDB_maker(string _fileName, uint8_t init_val);

    bool bfs_and_store();
};

#endif //RUBIKS_CUBE_CORNER_PATTERNDB_MAKER_H
