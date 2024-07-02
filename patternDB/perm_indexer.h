//
// Created by sarth on 02-07-2024.
//

#ifndef RUBIKS_CUBE_PERM_INDEXER_H
#define RUBIKS_CUBE_PERM_INDEXER_H

#include "reqmath.h"

template<size_t N, size_t K = N>
class perm_indexer {
    array<uint32_t, (1 << N) - 1> all_ones;
    array<uint32_t, K> all_fact;

public:
    perm_indexer() {
        for (uint32_t i = 0; i < (1 << N) - 1; ++i) {
            bitset<N> bits(i);
            this->all_ones[i] = bits.count();
        }

        for (uint32_t i = 0; i < K; ++i)
            this->all_fact[i] = pick(N - 1 - i, K - 1 - i);
    }

    uint32_t rank(const array<uint8_t, K> &perm) const {
        array<uint32_t, K> lehmer;

        bitset<N> vis;

        lehmer[0] = perm[0];

        vis[N - 1 - perm[0]] = 1;

        for (uint32_t i = 1; i < K; ++i) {
            vis[N - 1 - perm[i]] = 1;
            uint32_t numOnes = this->all_ones[vis.to_ulong() >> (N - perm[i])];
            lehmer[i] = perm[i] - numOnes;
        }

        uint32_t index = 0;

        for (uint32_t i = 0; i < K; ++i)
            index += lehmer[i] * this->all_fact[i];

        return index;
    }
};

#endif //RUBIKS_CUBE_PERM_INDEXER_H
