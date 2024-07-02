//
// Created by sarth on 24-06-2024.
//

#include "patternDBstructure.h"

patterDBstucture::patterDBstucture(const size_t size) :
        database(size, 0xFF), size(size), numItems(0) {
}

patterDBstucture::patterDBstucture(const size_t size, uint8_t init_val) :
        database(size, init_val), size(size), numItems(0) {
}

bool patterDBstucture::setNumMoves(const uint32_t ind, const uint8_t numMoves) {
    uint8_t oldMoves = this->getNumMoves(ind);

    if (oldMoves == 0xF) {
        ++this->numItems;
    }

    if (oldMoves > numMoves) {
        this->database.set(ind, numMoves);
        return true;
    }
    return false;

}

bool patterDBstucture::setNumMoves(const generic_cube &cube, const uint8_t numMoves) {
    return this->setNumMoves(this->getDatabaseIndex(cube), numMoves);
}

uint8_t patterDBstucture::getNumMoves(const uint32_t ind) const {
    return this->database.get(ind);
}

uint8_t patterDBstucture::getNumMoves(const generic_cube &cube) const {
    return this->getNumMoves(this->getDatabaseIndex(cube));
}

size_t patterDBstucture::getSize() const {
    return this->size;
}

size_t patterDBstucture::getNumItems() const {
    return this->numItems;
}

bool patterDBstucture::isFull() const {
    return this->numItems == this->size;
}

void patterDBstucture::toFile(const string &filePath) const {

    ofstream writer(filePath, ios::out | ios::binary | ios::trunc);

    if (!writer.is_open())
        throw "Unable to open the file to write!";

    writer.write(
            reinterpret_cast<const char *>(this->database.data()),
            this->database.storageSize()
    );

    writer.close();
}

bool patterDBstucture::fromFile(const string &filePath) {
    ifstream reader(filePath, ios::in | ios::ate);

    if (!reader.is_open())
        return false;

    size_t fileSize = reader.tellg();

    if (fileSize != this->database.storageSize()) {
        reader.close();
        throw "Corrupted Database!";
    }

    reader.seekg(0, ios::beg);
    reader.read(
            reinterpret_cast<char *> (this->database.data()),
            this->database.storageSize()
    );
    reader.close();
    this->numItems = this->size;
    return true;
}

vector<uint8_t> patterDBstucture::inflate() const {
    vector<uint8_t> inflated;
    this->database.inflate(inflated);
    return inflated;
}

void patterDBstucture::reset() {
    if (this->numItems != 0) {
        this->database.reset(0xFF);
        this->numItems = 0;
    }
}
