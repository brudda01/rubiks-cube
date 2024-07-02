//
// Created by sarth on 25-06-2024.
//

#ifndef RUBIKS_CUBE_CORNER_PATTERNDB_H
#define RUBIKS_CUBE_CORNER_PATTERNDB_H

#include "../models/generic_cube.h"
#include "patternDBstructure.h"
#include "perm_indexer.h"

class corner_patternDB : public patterDBstucture {

    perm_indexer<8> permIndexer;

public:
    corner_patternDB();

    corner_patternDB(uint8_t init_val);

    uint32_t getDatabaseIndex(const generic_cube &cube) const;
};

#endif //RUBIKS_CUBE_CORNER_PATTERNDB_H
