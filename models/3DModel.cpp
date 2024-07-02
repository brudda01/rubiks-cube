//
// Created by sarth on 09-06-2024.
//

#include "generic_cube.h"

class model3D : public generic_cube {
private:

    void rotateFace(int ind) {
        char arr[3][3] = {};
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                arr[i][j] = cube[ind][i][j];
            }
        }
        for (int i = 0; i < 3; i++) cube[ind][0][i] = arr[2 - i][0];
        for (int i = 0; i < 3; i++) cube[ind][i][2] = arr[0][i];
        for (int i = 0; i < 3; i++) cube[ind][2][2 - i] = arr[i][2];
        for (int i = 0; i < 3; i++) cube[ind][2 - i][0] = arr[2][2 - i];
    }

public:
    char cube[6][3][3]{};

    model3D() {
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++)
                    cube[i][j][k] = getColorLetter(COLOR(i));
            }
        }
    }

    COLOR getColor(FACE face, unsigned row, unsigned col) const override {
        char color = cube[int(face)][row][col];
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
                    if (this->cube[i][j][k] == getColorLetter(COLOR(i))) continue;
                    return false;
                }
            }
        }
        return true;
    }

    generic_cube &u() override {
        this->rotateFace(0);

        char arr[3] = {};
        for (int i = 0; i < 3; i++) arr[i] = cube[4][0][2 - i];
        for (int i = 0; i < 3; i++) cube[4][0][2 - i] = cube[1][0][2 - i];
        for (int i = 0; i < 3; i++) cube[1][0][2 - i] = cube[2][0][2 - i];
        for (int i = 0; i < 3; i++) cube[2][0][2 - i] = cube[3][0][2 - i];
        for (int i = 0; i < 3; i++) cube[3][0][2 - i] = arr[i];

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
        for (int i = 0; i < 3; i++) arr[i] = cube[0][i][0];
        for (int i = 0; i < 3; i++) cube[0][i][0] = cube[4][2 - i][2];
        for (int i = 0; i < 3; i++) cube[4][2 - i][2] = cube[5][i][0];
        for (int i = 0; i < 3; i++) cube[5][i][0] = cube[2][i][0];
        for (int i = 0; i < 3; i++) cube[2][i][0] = arr[i];

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
        for (int i = 0; i < 3; i++) arr[i] = cube[0][2][i];
        for (int i = 0; i < 3; i++) cube[0][2][i] = cube[1][2 - i][2];
        for (int i = 0; i < 3; i++) cube[1][2 - i][2] = cube[5][0][2 - i];
        for (int i = 0; i < 3; i++) cube[5][0][2 - i] = cube[3][i][0];
        for (int i = 0; i < 3; i++) cube[3][i][0] = arr[i];

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
        for (int i = 0; i < 3; i++) arr[i] = cube[0][2 - i][2];
        for (int i = 0; i < 3; i++) cube[0][2 - i][2] = cube[2][2 - i][2];
        for (int i = 0; i < 3; i++) cube[2][2 - i][2] = cube[5][2 - i][2];
        for (int i = 0; i < 3; i++) cube[5][2 - i][2] = cube[4][i][0];
        for (int i = 0; i < 3; i++) cube[4][i][0] = arr[i];

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
        for (int i = 0; i < 3; i++) arr[i] = cube[0][0][2 - i];
        for (int i = 0; i < 3; i++) cube[0][0][2 - i] = cube[3][2 - i][2];
        for (int i = 0; i < 3; i++) cube[3][2 - i][2] = cube[5][2][i];
        for (int i = 0; i < 3; i++) cube[5][2][i] = cube[1][i][0];
        for (int i = 0; i < 3; i++) cube[1][i][0] = arr[i];

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
        for (int i = 0; i < 3; i++) arr[i] = cube[2][2][i];
        for (int i = 0; i < 3; i++) cube[2][2][i] = cube[1][2][i];
        for (int i = 0; i < 3; i++) cube[1][2][i] = cube[4][2][i];
        for (int i = 0; i < 3; i++) cube[4][2][i] = cube[3][2][i];
        for (int i = 0; i < 3; i++) cube[3][2][i] = arr[i];

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

    bool operator==(const model3D &curr) const {
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    if (curr.cube[i][j][k] != cube[i][j][k]) return false;
                }
            }
        }
        return true;
    }

    model3D &operator=(const model3D &curr) {
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    cube[i][j][k] = curr.cube[i][j][k];
                }
            }
        }
        return *this;
    }
};

struct Hash3d {
private:
    hash<string> hasher;
public:
    size_t operator()(const model3D &curr) const {
        string str = "";
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    str += curr.cube[i][j][k];
                }
            }
        }
        return hasher(str);
    }

};