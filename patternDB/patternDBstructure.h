//
// Created by sarth on 23-06-2024.
//

#ifndef RUBIKS_CUBE_PATTERNDBSTRUCTURE_H
#define RUBIKS_CUBE_PATTERNDBSTRUCTURE_H

#include "../models/generic_cube.h"
#include "nibble_array.h"

class patterDBstucture {

    nibble_array database;
    size_t size;
    size_t numItems;

    patterDBstucture();

public:
    patterDBstucture(const size_t size);

    patterDBstucture(const size_t size, uint8_t init_val);

    virtual uint32_t getDatabaseIndex(const generic_cube &cube) const = 0;

    virtual bool setNumMoves(const generic_cube &cube, const uint8_t numMoves);

    virtual bool setNumMoves(const uint32_t ind, const uint8_t numMoves);

    virtual uint8_t getNumMoves(const generic_cube &cube) const;

    virtual uint8_t getNumMoves(const uint32_t ind) const;

    virtual size_t getSize() const;

    virtual size_t getNumItems() const;

    virtual bool isFull() const;

    virtual void toFile(const string &filePath) const;

    virtual bool fromFile(const string &filePath);

    virtual vector<uint8_t> inflate() const;

    virtual void reset();
};


#endif //RUBIKS_CUBE_PATTERNDBSTRUCTURE_H
