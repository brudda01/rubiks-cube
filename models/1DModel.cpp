//
// Created by sarth on 08-06-2024.
//

#include "generic_cube.h"

class model1D : public generic_cube {
private:

    static inline int getIndex(int ind, int row, int col) {
        return (ind * 9) + (row * 3) + col;
    }

    void rotateFace(int ind) {
        char arr[9] = {};
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                arr[i * 3 + j] = cube[getIndex(ind, i, j)];
            }
        }
        for (int i = 0; i < 3; i++) cube[getIndex(ind, 0, i)] = arr[getIndex(0, 2 - i, 0)];
        for (int i = 0; i < 3; i++) cube[getIndex(ind, i, 2)] = arr[getIndex(0, 0, i)];
        for (int i = 0; i < 3; i++) cube[getIndex(ind, 2, 2 - i)] = arr[getIndex(0, i, 2)];
        for (int i = 0; i < 3; i++) cube[getIndex(ind, 2 - i, 0)] = arr[getIndex(0, 2, 2 - i)];
    }

public:
    char cube[54]{};

    // initializing to solved state
    model1D() {
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    cube[i * 9 + j * 3 + k] = getColorLetter(COLOR(i));
                }
            }
        }
    }

    COLOR getColor(FACE face, unsigned row, unsigned col) const override {
        char color = cube[getIndex((int) face, (int) row, (int) col)];
        switch (color) {
            case 'B':
                return COLOR::BLUE;
            case 'R':
                return COLOR::RED;
            case 'G':
                return COLOR::GREEN;
            case 'O':
                return COLOR::ORANGE;
            case 'Y':
                return COLOR::YELLOW;
            default:
                return COLOR::WHITE;
        }
    }

    bool isSolved() const override {
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    if (this->cube[getIndex(i, j, k)] == getColorLetter(COLOR(i))) continue;
                    return false;
                }
            }
        }
        return true;
    }

    generic_cube &u() override {
        this->rotateFace(0);

        char arr[3] = {};
        for (int i = 0; i < 3; i++) arr[i] = cube[getIndex(4, 0, 2 - i)];
        for (int i = 0; i < 3; i++) cube[getIndex(4, 0, 2 - i)] = cube[getIndex(1, 0, 2 - i)];
        for (int i = 0; i < 3; i++) cube[getIndex(1, 0, 2 - i)] = cube[getIndex(2, 0, 2 - i)];
        for (int i = 0; i < 3; i++) cube[getIndex(2, 0, 2 - i)] = cube[getIndex(3, 0, 2 - i)];
        for (int i = 0; i < 3; i++) cube[getIndex(3, 0, 2 - i)] = arr[i];

        return *this;
    }

    generic_cube &uPrime() override {
        this->u();
        this->u();
        this->u();

        return *this;
    }

    generic_cube &u2() override {
        this->u();
        this->u();

        return *this;
    }

    generic_cube &l() override {
        this->rotateFace(1);

        char arr[3] = {};
        for (int i = 0; i < 3; i++) arr[i] = cube[getIndex(0, i, 0)];
        for (int i = 0; i < 3; i++) cube[getIndex(0, i, 0)] = cube[getIndex(4, 2 - i, 2)];
        for (int i = 0; i < 3; i++) cube[getIndex(4, 2 - i, 2)] = cube[getIndex(5, i, 0)];
        for (int i = 0; i < 3; i++) cube[getIndex(5, i, 0)] = cube[getIndex(2, i, 0)];
        for (int i = 0; i < 3; i++) cube[getIndex(2, i, 0)] = arr[i];

        return *this;
    }

    generic_cube &lPrime() override {
        this->l();
        this->l();
        this->l();

        return *this;
    }

    generic_cube &l2() override {
        this->l();
        this->l();

        return *this;
    }

    generic_cube &f() override {
        this->rotateFace(2);

        char arr[3] = {};
        for (int i = 0; i < 3; i++) arr[i] = cube[getIndex(0, 2, i)];
        for (int i = 0; i < 3; i++) cube[getIndex(0, 2, i)] = cube[getIndex(1, 2 - i, 2)];
        for (int i = 0; i < 3; i++) cube[getIndex(1, 2 - i, 2)] = cube[getIndex(5, 0, 2 - i)];
        for (int i = 0; i < 3; i++) cube[getIndex(5, 0, 2 - i)] = cube[getIndex(3, i, 0)];
        for (int i = 0; i < 3; i++) cube[getIndex(3, i, 0)] = arr[i];

        return *this;
    }

    generic_cube &fPrime() override {
        this->f();
        this->f();
        this->f();

        return *this;
    }

    generic_cube &f2() override {
        this->f();
        this->f();

        return *this;
    }

    generic_cube &r() override {
        this->rotateFace(3);

        char arr[3] = {};
        for (int i = 0; i < 3; i++) arr[i] = cube[getIndex(0, 2 - i, 2)];
        for (int i = 0; i < 3; i++) cube[getIndex(0, 2 - i, 2)] = cube[getIndex(2, 2 - i, 2)];
        for (int i = 0; i < 3; i++) cube[getIndex(2, 2 - i, 2)] = cube[getIndex(5, 2 - i, 2)];
        for (int i = 0; i < 3; i++) cube[getIndex(5, 2 - i, 2)] = cube[getIndex(4, i, 0)];
        for (int i = 0; i < 3; i++) cube[getIndex(4, i, 0)] = arr[i];

        return *this;
    }

    generic_cube &rPrime() override {
        this->r();
        this->r();
        this->r();

        return *this;
    }

    generic_cube &r2() override {
        this->r();
        this->r();

        return *this;
    }

    generic_cube &b() override {
        this->rotateFace(4);

        char arr[3] = {};
        for (int i = 0; i < 3; i++) arr[i] = cube[getIndex(0, 0, 2 - i)];
        for (int i = 0; i < 3; i++) cube[getIndex(0, 0, 2 - i)] = cube[getIndex(3, 2 - i, 2)];
        for (int i = 0; i < 3; i++) cube[getIndex(3, 2 - i, 2)] = cube[getIndex(5, 2, i)];
        for (int i = 0; i < 3; i++) cube[getIndex(5, 2, i)] = cube[getIndex(1, i, 0)];
        for (int i = 0; i < 3; i++) cube[getIndex(1, i, 0)] = arr[i];

        return *this;
    }

    generic_cube &bPrime() override {
        this->b();
        this->b();
        this->b();

        return *this;
    }

    generic_cube &b2() override {
        this->b();
        this->b();

        return *this;
    }

    generic_cube &d() override {
        this->rotateFace(5);

        char arr[3] = {};
        for (int i = 0; i < 3; i++) arr[i] = cube[getIndex(2, 2, i)];
        for (int i = 0; i < 3; i++) cube[getIndex(2, 2, i)] = cube[getIndex(1, 2, i)];
        for (int i = 0; i < 3; i++) cube[getIndex(1, 2, i)] = cube[getIndex(4, 2, i)];
        for (int i = 0; i < 3; i++) cube[getIndex(4, 2, i)] = cube[getIndex(3, 2, i)];
        for (int i = 0; i < 3; i++) cube[getIndex(3, 2, i)] = arr[i];

        return *this;
    }

    generic_cube &dPrime() override {
        this->d();
        this->d();
        this->d();

        return *this;
    }

    generic_cube &d2() override {
        this->d();
        this->d();

        return *this;
    }

    bool operator==(const model1D &curr) const {
        for (int i = 0; i < 54; i++) {
            if (cube[i] != curr.cube[i]) return false;
        }
        return true;
    }

    model1D &operator=(const model1D &curr) {
        for (int i = 0; i < 54; i++) {
            cube[i] = curr.cube[i];
        }
        return *this;
    }

};

struct Hash1d {
private:
    hash<string> hasher;
public:
    size_t operator()(const model1D &curr) const {
        string str = "";
        for (int i = 0; i < 54; i++) str += curr.cube[i];
        return hasher(str);
    }
};