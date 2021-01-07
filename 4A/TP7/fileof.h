#ifndef __FILEOF_H__
#define __FILEOF_H__

#include <fstream>
#include <iostream>

// Writable interface: defines behaviour of writable binary files
class Writable {
  public:
    virtual void write(int to_write) = 0;
    virtual unsigned int tellp() = 0;
    virtual void seekp(unsigned int offset) = 0;
    virtual void seekp(unsigned int offset, std::ios_base::seekdir dir) = 0;

    friend Writable &operator<<(Writable &os, const int n);
};

// Readable interface: defines behaviour of readable binary files
class Readable {
  public:
    virtual int read() = 0;
    virtual unsigned int tellg() = 0;
    virtual void seekg(unsigned int offset) = 0;
    virtual void seekg(unsigned int offset, std::ios_base::seekdir dir) = 0;

    friend Readable &operator>>(Readable &is, int &n);
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
class W_File_of_Int : public Writable, virtual public FileOf {
  public:
    W_File_of_Int(const char *filename);
    W_File_of_Int(){};  // default: do nothing
    ~W_File_of_Int(){}; // default: do nothing

    void write(int to_write) override;
    unsigned int tellp() override;
    void seekp(unsigned int offset) override;
    void seekp(unsigned int offset, std::ios_base::seekdir dir) override;
};

// Binary file open in read-only mode
class R_File_of_Int : public Readable, virtual public FileOf {
  public:
    R_File_of_Int(){}; // default: do nothing
    R_File_of_Int(const char *filename);
    ~R_File_of_Int(){};

    int read() override;
    unsigned int tellg() override;
    void seekg(unsigned int offset) override;
    void seekg(unsigned int offset, std::ios_base::seekdir dir) override;
};

// Binary file open in read-write mode
class RW_File_of_Int : public W_File_of_Int, public R_File_of_Int {
  public:
    RW_File_of_Int(){}; // default: do nothing
    RW_File_of_Int(const char *filename);
    ~RW_File_of_Int(){}; // default: do nothing
};

#endif // __FILEOF_H__
