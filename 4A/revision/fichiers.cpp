#include <fstream>
#include <iostream>

using namespace std;

struct vec3 {
    int a;
    int b;
    int c;

    vec3() : a(0), b(0), c(0) {}
    vec3(int na, int nb, int nc) : a(na), b(nb), c(nc) {}

    void display() {
        cout << a << ", " << b << ", " << c << endl;
    }
};

int main() {
    ofstream ofile;
    ifstream ifile;

    vec3 my_data1(1, 2, 3);
    vec3 my_data2(0, 15, 50);

    ofile.open("output.txt", ios::out | ios::binary);

    ofile.write((const char *)&my_data1, sizeof(my_data1));
    ofile.write((const char *)&my_data2, sizeof(my_data2));

    ofile.close();

    vec3 read_data;

    ifile.open("output.txt", ios::in | ios::binary);
    while (true) {
        ifile.read((char *)&read_data, sizeof(read_data));
        if (ifile.eof()) {
            break;
        }
        read_data.display();
    }
    ifile.close();

    return 0;
}