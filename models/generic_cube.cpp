//
// Created by sarth on 04-06-2024.
//

#include "generic_cube.h"

char generic_cube::getColorLetter(COLOR color) {
    switch (color) {
        case COLOR::BLUE:
            return 'B';
        case COLOR::GREEN:
            return 'G';
        case COLOR::RED:
            return 'R';
        case COLOR::YELLOW:
            return 'Y';
        case COLOR::WHITE:
            return 'W';
        case COLOR::ORANGE:
            return 'O';
    }
}

string generic_cube::getMove(MOVE ind) {
    switch (ind) {
        case MOVE::L:
            return "L";
        case MOVE::LPRIME:
            return "L'";
        case MOVE::L2:
            return "L2";
        case MOVE::R:
            return "R";
        case MOVE::RPRIME:
            return "R'";
        case MOVE::R2:
            return "R2";
        case MOVE::U:
            return "U";
        case MOVE::UPRIME:
            return "U'";
        case MOVE::U2:
            return "U2";
        case MOVE::D:
            return "D";
        case MOVE::DPRIME:
            return "D'";
        case MOVE::D2:
            return "D2";
        case MOVE::F:
            return "F";
        case MOVE::FPRIME:
            return "F'";
        case MOVE::F2:
            return "F2";
        case MOVE::B:
            return "B";
        case MOVE::BPRIME:
            return "B'";
        case MOVE::B2:
            return "B2";
    }
}

generic_cube &generic_cube::move(MOVE ind) {
    switch (ind) {
        case MOVE::L:
            return this->l();
        case MOVE::LPRIME:
            return this->lPrime();
        case MOVE::L2:
            return this->l2();
        case MOVE::R:
            return this->r();
        case MOVE::RPRIME:
            return this->rPrime();
        case MOVE::R2:
            return this->r2();
        case MOVE::U:
            return this->u();
        case MOVE::UPRIME:
            return this->uPrime();
        case MOVE::U2:
            return this->u2();
        case MOVE::D:
            return this->d();
        case MOVE::DPRIME:
            return this->dPrime();
        case MOVE::D2:
            return this->d2();
        case MOVE::F:
            return this->f();
        case MOVE::FPRIME:
            return this->fPrime();
        case MOVE::F2:
            return this->f2();
        case MOVE::B:
            return this->b();
        case MOVE::BPRIME:
            return this->bPrime();
        case MOVE::B2:
            return this->b2();
    }
}

generic_cube &generic_cube::invert(MOVE ind) {
    switch (ind) {
        case MOVE::L:
            return this->lPrime();
        case MOVE::LPRIME:
            return this->l();
        case MOVE::L2:
            return this->l2();
        case MOVE::R:
            return this->rPrime();
        case MOVE::RPRIME:
            return this->r();
        case MOVE::R2:
            return this->r2();
        case MOVE::U:
            return this->uPrime();
        case MOVE::UPRIME:
            return this->u();
        case MOVE::U2:
            return this->u2();
        case MOVE::D:
            return this->dPrime();
        case MOVE::DPRIME:
            return this->d();
        case MOVE::D2:
            return this->d2();
        case MOVE::F:
            return this->fPrime();
        case MOVE::FPRIME:
            return this->f();
        case MOVE::F2:
            return this->f2();
        case MOVE::B:
            return this->bPrime();
        case MOVE::BPRIME:
            return this->b();
        case MOVE::B2:
            return this->b2();
    }
}

void generic_cube::print() const {
    cout << "Rubik's Cube:\n\n";

    for (int row = 0; row <= 2; row++) {
        for (unsigned i = 0; i < 7; i++) cout << " ";
        for (int col = 0; col <= 2; col++) {
            cout << getColorLetter(getColor(FACE::UP, row, col)) << " ";
        }
        cout << "\n";
    }

    cout << "\n";

    for (int row = 0; row <= 2; row++) {

        for (int col = 0; col <= 2; col++) {
            cout << getColorLetter(getColor(FACE::LEFT, row, col)) << " ";
        }
        cout << " ";

        for (int col = 0; col <= 2; col++) {
            cout << getColorLetter(getColor(FACE::FRONT, row, col)) << " ";
        }
        cout << " ";

        for (int col = 0; col <= 2; col++) {
            cout << getColorLetter(getColor(FACE::RIGHT, row, col)) << " ";
        }
        cout << " ";

        for (int col = 0; col <= 2; col++) {
            cout << getColorLetter(getColor(FACE::BACK, row, col)) << " ";
        }
        cout << "\n";
    }

    cout << "\n";

    for (int row = 0; row <= 2; row++) {
        for (unsigned i = 0; i < 7; i++) cout << " ";
        for (int col = 0; col <= 2; col++) {
            cout << getColorLetter(getColor(FACE::DOWN, row, col)) << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

vector<generic_cube::MOVE> generic_cube::randomShuffleCube(unsigned int times) {
    vector<MOVE> moves;
    srand(time(0));
    for (unsigned int i = 0; i < times; i++) {
        unsigned int selectMove = (rand() % 18);
        moves.push_back(static_cast<MOVE>(selectMove));
        this->move(static_cast<MOVE>(selectMove));
    }
    return moves;
}

string generic_cube::getCornerColorString(uint8_t ind) const {
    string corner_string = "";

    switch (ind) {
        case 0:
            corner_string += getColorLetter(getColor(FACE::UP, 2, 2));
            corner_string += getColorLetter(getColor(FACE::FRONT, 0, 2));
            corner_string += getColorLetter(getColor(FACE::RIGHT, 0, 0));
            break;

        case 1:
            corner_string += getColorLetter(getColor(FACE::UP, 2, 0));
            corner_string += getColorLetter(getColor(FACE::FRONT, 0, 0));
            corner_string += getColorLetter(getColor(FACE::LEFT, 0, 2));
            break;

        case 2:
            corner_string += getColorLetter(getColor(FACE::UP, 0, 0));
            corner_string += getColorLetter(getColor(FACE::BACK, 0, 2));
            corner_string += getColorLetter(getColor(FACE::LEFT, 0, 0));
            break;

        case 3:
            corner_string += getColorLetter(getColor(FACE::UP, 0, 2));
            corner_string += getColorLetter(getColor(FACE::BACK, 0, 0));
            corner_string += getColorLetter(getColor(FACE::RIGHT, 0, 2));
            break;

        case 4:
            corner_string += getColorLetter(getColor(FACE::DOWN, 0, 2));
            corner_string += getColorLetter(getColor(FACE::FRONT, 2, 2));
            corner_string += getColorLetter(getColor(FACE::RIGHT, 2, 0));
            break;

        case 5:
            corner_string += getColorLetter(getColor(FACE::DOWN, 0, 0));
            corner_string += getColorLetter(getColor(FACE::FRONT, 2, 0));
            corner_string += getColorLetter(getColor(FACE::LEFT, 2, 2));
            break;

        case 6:
            corner_string += getColorLetter(getColor(FACE::DOWN, 2, 2));
            corner_string += getColorLetter(getColor(FACE::BACK, 2, 0));
            corner_string += getColorLetter(getColor(FACE::RIGHT, 2, 2));
            break;

        case 7:
            corner_string += getColorLetter(getColor(FACE::DOWN, 2, 0));
            corner_string += getColorLetter(getColor(FACE::BACK, 2, 2));
            corner_string += getColorLetter(getColor(FACE::LEFT, 2, 0));
            break;
    }
    return corner_string;
}

uint8_t generic_cube::getCornerIndex(uint8_t ind) const {
    string corner = getCornerColorString(ind);

    uint8_t corner_ind = 0;
    for (auto c: corner) {
        if (c != 'W' && c != 'Y') continue;
        if (c == 'Y') {
            corner_ind |= (1 << 2);
        }
    }

    for (auto c: corner) {
        if (c != 'R' && c != 'O') continue;
        if (c == 'O') {
            corner_ind |= (1 << 1);
        }
    }

    for (auto c: corner) {
        if (c != 'B' && c != 'G') continue;
        if (c == 'G') {
            corner_ind |= (1 << 0);
        }
    }
    return corner_ind;
}

uint8_t generic_cube::getCornerOrientation(uint8_t ind) const {
    string corner = getCornerColorString(ind);

    string curr_string = "";

    for (auto c: corner) {
        if (c != 'W' && c != 'Y') continue;
        curr_string.push_back(c);
    }

    if (corner[1] == curr_string[0]) {
        return 1;
    } else if (corner[2] == curr_string[0]) {
        return 2;
    } else return 0;
}