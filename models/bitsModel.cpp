//
// Created by sarth on 13-06-2024.
//

#include "generic_cube.h"

class modelbits : public generic_cube {

private:
    uint64_t solved_state[6]{};

    int arr[3][3] = {{0, 1, 2},
                     {7, 8, 3},
                     {6, 5, 4}};

    uint64_t set_8 = (1 << 8) - 1, set_24 = (1 << 24) - 1;

    void rotateFace(int ind) {
        uint64_t side = bitboard[ind];
        side = side >> (8 * 6);
        bitboard[ind] = (bitboard[ind] << 16) | (side);
    }

    void rotateSide(int s1, int s1_1, int s1_2, int s1_3, int s2, int s2_1, int s2_2, int s2_3) {
        uint64_t colocurr = (bitboard[s2] & (set_8 << (8 * s2_1))) >> (8 * s2_1);
        uint64_t color2 = (bitboard[s2] & (set_8 << (8 * s2_2))) >> (8 * s2_2);
        uint64_t color3 = (bitboard[s2] & (set_8 << (8 * s2_3))) >> (8 * s2_3);

        bitboard[s1] = (bitboard[s1] & ~(set_8 << (8 * s1_1))) | (colocurr << (8 * s1_1));
        bitboard[s1] = (bitboard[s1] & ~(set_8 << (8 * s1_2))) | (color2 << (8 * s1_2));
        bitboard[s1] = (bitboard[s1] & ~(set_8 << (8 * s1_3))) | (color3 << (8 * s1_3));
    }

    int get5bitCorner(string corner) {
        int ret = 0;
        string actual_str;
        for (auto c: corner) {
            if (c != 'W' && c != 'Y') continue;
            actual_str.push_back(c);
            if (c == 'Y') {
                ret |= (1 << 2);
            }
        }

        for (auto c: corner) {
            if (c != 'R' && c != 'O') continue;
            if (c == 'O') {
                ret |= (1 << 1);
            }
        }

        for (auto c: corner) {
            if (c != 'B' && c != 'G') continue;
            if (c == 'G') {
                ret |= (1 << 0);
            }
        }

        if (corner[1] == actual_str[0]) {
            ret |= (1 << 3);
        } else if (corner[2] == actual_str[0]) {
            ret |= (1 << 4);
        }
        return ret;
    }

public:
    uint64_t bitboard[6]{};

    // initializing to solved state
    modelbits() {
        for (int side = 0; side < 6; side++) {
            uint64_t color = 1 << side;
            bitboard[side] = 0;
            for (int faceIdx = 0; faceIdx < 8; faceIdx++) {
                bitboard[side] |= color << (8 * faceIdx);
            }
            solved_state[side] = bitboard[side];
        }
    }

    COLOR getColor(FACE face, unsigned row, unsigned col) const override {
        int ind = arr[row][col];
        if (ind == 8) return (COLOR)((int) face);

        uint64_t side = bitboard[(int) face];
        uint64_t color = (side >> (8 * ind)) & set_8;

        int bit_pos = 0;
        while (color != 0) {
            color = color >> 1;
            bit_pos++;
        }
        return (COLOR)(bit_pos - 1);
    }

    bool isSolved() const override {
        for (int i = 0; i < 6; i++) {
            if (solved_state[i] != bitboard[i]) return false;
        }
        return true;
    }

    generic_cube &u() override {
        this->rotateFace(0);
        uint64_t temp = bitboard[2] & set_24;
        bitboard[2] = (bitboard[2] & ~set_24) | (bitboard[3] & set_24);
        bitboard[3] = (bitboard[3] & ~set_24) | (bitboard[4] & set_24);
        bitboard[4] = (bitboard[4] & ~set_24) | (bitboard[1] & set_24);
        bitboard[1] = (bitboard[1] & ~set_24) | temp;

        return *this;
    }

    generic_cube &uPrime() override {
        this->u();
        this->u();
        this->u();

        return *this;
    };

    generic_cube &u2() override {
        this->u();
        this->u();

        return *this;
    };

    generic_cube &l() override {
        this->rotateFace(1);
        uint64_t colocurr = (bitboard[2] & (set_8 << (8 * 0))) >> (8 * 0);
        uint64_t color2 = (bitboard[2] & (set_8 << (8 * 6))) >> (8 * 6);
        uint64_t color3 = (bitboard[2] & (set_8 << (8 * 7))) >> (8 * 7);

        this->rotateSide(2, 0, 7, 6, 0, 0, 7, 6);
        this->rotateSide(0, 0, 7, 6, 4, 4, 3, 2);
        this->rotateSide(4, 4, 3, 2, 5, 0, 7, 6);

        bitboard[5] = (bitboard[5] & ~(set_8 << (8 * 0))) | (colocurr << (8 * 0));
        bitboard[5] = (bitboard[5] & ~(set_8 << (8 * 6))) | (color2 << (8 * 6));
        bitboard[5] = (bitboard[5] & ~(set_8 << (8 * 7))) | (color3 << (8 * 7));

        return *this;

    };

    generic_cube &lPrime() override {
        this->l();
        this->l();
        this->l();

        return *this;
    };

    generic_cube &l2() override {
        this->l();
        this->l();

        return *this;
    };

    generic_cube &f() override {
        this->rotateFace(2);

        uint64_t colocurr = (bitboard[0] & (set_8 << (8 * 4))) >> (8 * 4);
        uint64_t color2 = (bitboard[0] & (set_8 << (8 * 5))) >> (8 * 5);
        uint64_t color3 = (bitboard[0] & (set_8 << (8 * 6))) >> (8 * 6);

        this->rotateSide(0, 4, 5, 6, 1, 2, 3, 4);
        this->rotateSide(1, 2, 3, 4, 5, 0, 1, 2);
        this->rotateSide(5, 0, 1, 2, 3, 6, 7, 0);

        bitboard[3] = (bitboard[3] & ~(set_8 << (8 * 6))) | (colocurr << (8 * 6));
        bitboard[3] = (bitboard[3] & ~(set_8 << (8 * 7))) | (color2 << (8 * 7));
        bitboard[3] = (bitboard[3] & ~(set_8 << (8 * 0))) | (color3 << (8 * 0));

        return *this;
    };

    generic_cube &fPrime() override {
        this->f();
        this->f();
        this->f();
        return *this;
    };

    generic_cube &f2() override {
        this->f();
        this->f();

        return *this;
    };

    generic_cube &r() override {
        this->rotateFace(3);
        uint64_t colocurr = (bitboard[0] & (set_8 << (8 * 2))) >> (8 * 2);
        uint64_t color2 = (bitboard[0] & (set_8 << (8 * 3))) >> (8 * 3);
        uint64_t color3 = (bitboard[0] & (set_8 << (8 * 4))) >> (8 * 4);

        this->rotateSide(0, 2, 3, 4, 2, 2, 3, 4);
        this->rotateSide(2, 2, 3, 4, 5, 2, 3, 4);
        this->rotateSide(5, 2, 3, 4, 4, 7, 6, 0);

        bitboard[4] = (bitboard[4] & ~(set_8 << (8 * 7))) | (colocurr << (8 * 7));
        bitboard[4] = (bitboard[4] & ~(set_8 << (8 * 6))) | (color2 << (8 * 6));
        bitboard[4] = (bitboard[4] & ~(set_8 << (8 * 0))) | (color3 << (8 * 0));

        return *this;
    };

    generic_cube &rPrime() override {
        this->r();
        this->r();
        this->r();

        return *this;
    };

    generic_cube &r2() override {
        this->r();
        this->r();

        return *this;
    };

    generic_cube &b() override {
        this->rotateFace(4);

        uint64_t colocurr = (bitboard[0] & (set_8 << (8 * 0))) >> (8 * 0);
        uint64_t color2 = (bitboard[0] & (set_8 << (8 * 1))) >> (8 * 1);
        uint64_t color3 = (bitboard[0] & (set_8 << (8 * 2))) >> (8 * 2);

        this->rotateSide(0, 0, 1, 2, 3, 2, 3, 4);
        this->rotateSide(3, 2, 3, 4, 5, 4, 5, 6);
        this->rotateSide(5, 4, 5, 6, 1, 6, 7, 0);

        bitboard[1] = (bitboard[1] & ~(set_8 << (8 * 6))) | (colocurr << (8 * 6));
        bitboard[1] = (bitboard[1] & ~(set_8 << (8 * 7))) | (color2 << (8 * 7));
        bitboard[1] = (bitboard[1] & ~(set_8 << (8 * 0))) | (color3 << (8 * 0));

        return *this;
    };

    generic_cube &bPrime() override {
        this->b();
        this->b();
        this->b();

        return *this;
    };

    generic_cube &b2() override {
        this->b();
        this->b();

        return *this;
    };

    generic_cube &d() override {
        this->rotateFace(5);

        uint64_t colocurr = (bitboard[2] & (set_8 << (8 * 4))) >> (8 * 4);
        uint64_t color2 = (bitboard[2] & (set_8 << (8 * 5))) >> (8 * 5);
        uint64_t color3 = (bitboard[2] & (set_8 << (8 * 6))) >> (8 * 6);

        this->rotateSide(2, 4, 5, 6, 1, 4, 5, 6);
        this->rotateSide(1, 4, 5, 6, 4, 4, 5, 6);
        this->rotateSide(4, 4, 5, 6, 3, 4, 5, 6);

        bitboard[3] = (bitboard[3] & ~(set_8 << (8 * 4))) | (colocurr << (8 * 4));
        bitboard[3] = (bitboard[3] & ~(set_8 << (8 * 5))) | (color2 << (8 * 5));
        bitboard[3] = (bitboard[3] & ~(set_8 << (8 * 6))) | (color3 << (8 * 6));

        return *this;
    };

    generic_cube &dPrime() override {
        this->d();
        this->d();
        this->d();

        return *this;
    };

    generic_cube &d2() override {
        this->d();
        this->d();

        return *this;
    }

    bool operator==(const modelbits &curr) const {
        for (int i = 0; i < 6; i++) {
            if (bitboard[i] != curr.bitboard[i]) return false;
        }
        return true;
    }

    modelbits &operator=(const modelbits &curr) {
        for (int i = 0; i < 6; i++) {
            bitboard[i] = curr.bitboard[i];
        }
        return *this;
    }


    uint64_t getCorners() {
        uint64_t ret = 0;
        string top_front_right = "";
        top_front_right += getColorLetter(getColor(FACE::UP, 2, 2));
        top_front_right += getColorLetter(getColor(FACE::FRONT, 0, 2));
        top_front_right += getColorLetter(getColor(FACE::RIGHT, 0, 0));

        string top_front_left = "";
        top_front_left += getColorLetter(getColor(FACE::UP, 2, 0));
        top_front_left += getColorLetter(getColor(FACE::FRONT, 0, 0));
        top_front_left += getColorLetter(getColor(FACE::LEFT, 0, 2));

        string top_back_left = "";
        top_back_left += getColorLetter(getColor(FACE::UP, 0, 0));
        top_back_left += getColorLetter(getColor(FACE::BACK, 0, 2));
        top_back_left += getColorLetter(getColor(FACE::LEFT, 0, 0));

        string top_back_right = "";
        top_back_right += getColorLetter(getColor(FACE::UP, 0, 2));
        top_back_right += getColorLetter(getColor(FACE::BACK, 0, 0));
        top_back_right += getColorLetter(getColor(FACE::RIGHT, 0, 2));

        string bottom_front_right = "";
        bottom_front_right += getColorLetter(getColor(FACE::DOWN, 0, 2));
        bottom_front_right += getColorLetter(getColor(FACE::FRONT, 2, 2));
        bottom_front_right += getColorLetter(getColor(FACE::RIGHT, 2, 0));

        string bottom_front_left = "";
        bottom_front_left += getColorLetter(getColor(FACE::DOWN, 0, 0));
        bottom_front_left += getColorLetter(getColor(FACE::FRONT, 2, 0));
        bottom_front_left += getColorLetter(getColor(FACE::LEFT, 2, 2));

        string bottom_back_right = "";
        bottom_back_right += getColorLetter(getColor(FACE::DOWN, 2, 2));
        bottom_back_right += getColorLetter(getColor(FACE::BACK, 2, 0));
        bottom_back_right += getColorLetter(getColor(FACE::RIGHT, 2, 2));

        string bottom_back_left = "";
        bottom_back_left += getColorLetter(getColor(FACE::DOWN, 2, 0));
        bottom_back_left += getColorLetter(getColor(FACE::BACK, 2, 2));
        bottom_back_left += getColorLetter(getColor(FACE::LEFT, 2, 0));

        ret |= get5bitCorner(top_front_right);
        ret = ret << 5;

        ret |= get5bitCorner(top_front_left);
        ret = ret << 5;

        ret |= get5bitCorner(top_back_right);
        ret = ret << 5;

        ret |= get5bitCorner(top_back_left);
        ret = ret << 5;

        ret |= get5bitCorner(bottom_front_right);
        ret = ret << 5;

        ret |= get5bitCorner(bottom_front_left);
        ret = ret << 5;

        ret |= get5bitCorner(bottom_back_right);
        ret = ret << 5;

        ret |= get5bitCorner(bottom_back_left);
        ret = ret << 5;

        return ret;
    }

};

struct HashBitboard {
    size_t operator()(const modelbits &curr) const {
        uint64_t hashed = curr.bitboard[0];
        for (int i = 1; i < 6; i++) hashed ^= curr.bitboard[i];
        return (size_t) hashed;
    }
};