#include "fileof.h"

#include <iostream>
#include <fstream>

FileOf::~FileOf() {
    if (this->is_open()) {
        this->close();
    }
}
std::fstream& FileOf::get_file() {
    return _file;
}
void FileOf::open(const char* filename, std::ios_base::openmode mode) {
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
    return is_open();
}

W_File_of_Int::W_File_of_Int(const char * filename) {
    using std::ios;
    this->open(filename, ios::out | ios::binary);
}
void W_File_of_Int::write(int to_write) {
    char * first_byte = reinterpret_cast<char *>(&to_write);
    this->get_file().write(first_byte, sizeof(to_write));
}
std::streampos W_File_of_Int::tellp() {
    return this->get_file().tellp();
}
void W_File_of_Int::seekp(std::streampos offset) {
    this->get_file().seekp(offset);
}
void W_File_of_Int::seekp(std::streampos offset, std::ios_base::seekdir dir) {
    this->get_file().seekp(offset, dir);
}

R_File_of_Int::R_File_of_Int(const char * filename) {
    using std::ios;
    this->open(filename, ios::in | ios::binary);
}
int R_File_of_Int::read() {
    int buffer;
    char * first_byte = reinterpret_cast<char *>(&buffer);
    this->get_file().read(first_byte, sizeof(buffer));
}
std::streampos R_File_of_Int::tellg() {
    return this->get_file().tellg();
}
void R_File_of_Int::seekg(std::streampos offset) {
    this->get_file().seekg(offset);
}
void R_File_of_Int::seekg(std::streampos offset, std::ios_base::seekdir dir) {
    this->get_file().seekg(offset, dir);
}

RW_File_of_Int::RW_File_of_Int(const char * filename) {
    using std::ios;
    this->open(filename, ios::in | ios::out | ios::binary);
}

Writable& operator<<(Writable& os, const int n) {
    os.write(n);
    return os;
}
Readable& operator>>(Readable& is, int& n) {
    n = is.read();
    return is;
}