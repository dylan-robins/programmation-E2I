#ifndef __FILEOF_H__
#define __FILEOF_H__

#include <fstream>
#include <iostream>

// Writable interface: defines behaviour of writable binary files
template <typename T>
class Writable {
  public:
    virtual void write(T to_write) = 0;
    virtual unsigned int tellp() = 0;
    virtual void seekp(unsigned int offset) = 0;
    virtual void seekp(unsigned int offset, std::ios_base::seekdir dir) = 0;

    friend Writable<T> &operator<<(Writable<T> &os, const T n) {
        os.write(n);
        return os;
    }
};

// Readable interface: defines behaviour of readable binary files
template <typename T>
class Readable {
  public:
    virtual T read() = 0;
    virtual unsigned int tellg() = 0;
    virtual void seekg(unsigned int offset) = 0;
    virtual void seekg(unsigned int offset, std::ios_base::seekdir dir) = 0;

    friend Readable<T> &operator>>(Readable<T> &is, T &n) {
        n = is.read();
        return is;
    }
};

// Generic binary file
class FileOf {
  private:
    std::fstream _file;

  protected:
    std::fstream &get_file();

  public:
    FileOf(){}; // Default constructor: do nothing
    ~FileOf();  // close file on destruction

    void open(const char *filename, std::ios_base::openmode mode);
    void close();
    void clear();

    bool is_open();
    bool eof();
    unsigned int tellp();
    void seekp(unsigned int offset);
    void seekp(unsigned int offset, std::ios_base::seekdir dir);

    bool operator!();
};

// Binary file open in write-only mode
template <typename T>
class W_File_of_Int : public Writable<T>, virtual public FileOf {
  public:
    W_File_of_Int(const char *filename) {
        using std::ios;
        this->open(filename, ios::out | ios::binary);
    }
    W_File_of_Int(){};  // default: do nothing
    ~W_File_of_Int(){}; // default: do nothing

    void write(T to_write) override {
        char *first_byte = reinterpret_cast<char *>(&to_write);
        this->get_file().write(first_byte, sizeof(T));
    }
    unsigned int tellp() override {
        return this->get_file().tellp() / sizeof(T);
    }
    void seekp(unsigned int offset) override {
        this->get_file().seekp(offset * sizeof(T), std::ios_base::beg);
    }
    void seekp(unsigned int offset, std::ios_base::seekdir dir) override {
        this->get_file().seekp(offset * sizeof(T), dir);
    }
};

// Binary file open in read-only mode
template <typename T>
class R_File_of_Int : public Readable<T>, virtual public FileOf {
  public:
    R_File_of_Int(){}; // default: do nothing
    R_File_of_Int(const char *filename) {
        using std::ios;
        this->open(filename, ios::in | ios::binary);
    }
    ~R_File_of_Int(){};

    T read() override {
        T buffer;
        char *first_byte = reinterpret_cast<char *>(&buffer);
        this->get_file().read(first_byte, sizeof(T));
        return buffer;
    }
    unsigned int tellg() override {
        return this->get_file().tellg() / sizeof(T);
    }
    void seekg(unsigned int offset) override {
        this->get_file().seekg(offset * sizeof(T));
    }
    void seekg(unsigned int offset, std::ios_base::seekdir dir) override {
        this->get_file().seekg(offset * sizeof(T), dir);
    }
};

// Binary file open in read-write mode
template <typename T>
class RW_File_of_Int : public W_File_of_Int<T>, public R_File_of_Int<T> {
  public:
    RW_File_of_Int(){}; // default: do nothing
    RW_File_of_Int(const char *filename) {
        using std::ios;
        this->open(filename, ios::in | ios::out | ios::binary);
    }
    ~RW_File_of_Int(){}; // default: do nothing
};

#endif // __FILEOF_H__
