#include "fileof.h"

#include <fstream>
#include <iostream>

FileOf::~FileOf() {
    if (this->is_open()) {
        this->close();
    }
}
std::fstream &FileOf::get_file() {
    return _file;
}
void FileOf::open(const char *filename, std::ios_base::openmode mode) {
    _file.open(filename, mode);
}
void FileOf::close() {
    _file.close();
}
void FileOf::clear() {
    _file.clear();
}

bool FileOf::is_open() {
    return _file.is_open();
}
bool FileOf::eof() {
    return _file.eof();
}
bool FileOf::operator!() {
    return !is_open();
}