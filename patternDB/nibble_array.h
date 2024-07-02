//
// Created by sarth on 22-06-2024.
//

#ifndef RUBIKS_CUBE_NIBBLE_ARRAY_H
#define RUBIKS_CUBE_NIBBLE_ARRAY_H

#include <bits/stdc++.h>
using namespace std;

class nibble_array {
    size_t size;
    vector<uint8_t> arr;

public:
    nibble_array(const size_t size, const uint8_t val = 0xFF);

    uint8_t get(const size_t pos) const;

    void set(const size_t pos, const uint8_t val);

    unsigned char *data();

    const unsigned char *data() const;

    size_t storageSize() const;

    void inflate(vector<uint8_t> &dest) const;

    void reset(const uint8_t val = 0xFF);

};


#endif //RUBIKS_CUBE_NIBBLE_ARRAY_H
