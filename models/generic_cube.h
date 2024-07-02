//
// Created by sarth on 03-06-2024.
//

#ifndef RUBIKS_CUBE_GENERIC_CUBE_H
#define RUBIKS_CUBE_GENERIC_CUBE_H

#include <bits/stdc++.h>
using namespace std;

class generic_cube {
public:

    // fixing things for bug free code
    enum class FACE {
        UP,
        LEFT,
        FRONT,
        RIGHT,
        BACK,
        DOWN
    };

    enum class COLOR {
        WHITE,
        GREEN,
        RED,
        BLUE,
        ORANGE,
        YELLOW
    };

    enum class MOVE {
        L, LPRIME, L2,
        R, RPRIME, R2,
        U, UPRIME, U2,
        D, DPRIME, D2,
        F, FPRIME, F2,
        B, BPRIME, B2
    };

    virtual COLOR getColor(FACE face, unsigned row, unsigned col) const = 0;

    static char getColorLetter(COLOR color);

    virtual bool isSolved() const = 0;

    static string getMove(MOVE ind);

//    here is how it gets printed
//    Color wise:
//            W W W
//            W W W
//    W W W
//            G G G   R R R   B B B   O O O
//            G G G   R R R   B B B   O O O
//            G G G   R R R   B B B   O O O
//            Y Y Y
//    Y Y Y
//            Y Y Y

    void print() const;

    vector<MOVE> randomShuffleCube(unsigned int times);

    // making moves on the Rubik's cube

    generic_cube &move(MOVE ind);

    generic_cube &invert(MOVE ind);

    virtual generic_cube &f() = 0;

    virtual generic_cube &fPrime() = 0;

    virtual generic_cube &f2() = 0;

    virtual generic_cube &u() = 0;

    virtual generic_cube &uPrime() = 0;

    virtual generic_cube &u2() = 0;

    virtual generic_cube &l() = 0;

    virtual generic_cube &lPrime() = 0;

    virtual generic_cube &l2() = 0;

    virtual generic_cube &r() = 0;

    virtual generic_cube &d() = 0;

    virtual generic_cube &dPrime() = 0;

    virtual generic_cube &d2() = 0;

    virtual generic_cube &rPrime() = 0;

    virtual generic_cube &r2() = 0;

    virtual generic_cube &b() = 0;

    virtual generic_cube &bPrime() = 0;

    virtual generic_cube &b2() = 0;

    string getCornerColorString(uint8_t ind) const;

    uint8_t getCornerIndex(uint8_t ind) const;

    uint8_t getCornerOrientation(uint8_t ind) const;
};


#endif //RUBIKS_CUBE_GENERIC_CUBE_H
