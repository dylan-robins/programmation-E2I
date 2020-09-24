#include <iostream>
#include <iomanip>

using namespace std;

class matrix {
private:
    int **_array;
    size_t _N;
    size_t _M;
public:
    matrix();
    matrix(const size_t N, const size_t M);
    ~matrix();
    void print();
    void fill();
};

matrix::matrix() {
    cout << "Width of new matrix: ? >>> ";
    cin >> _M;
    cout << "Height of new matrix: ? >>> ";
    cin >> _N;

    cout << "Dimensions : " << _N << "x" << _M << endl;

    _array = new int *[_N];
    for (size_t i = 0; i < _M; i++) {
        _array[i] = new int [_M];
    }
}

matrix::matrix(const size_t N, const size_t M) : _N(N), _M(M) {
    _array = new int *[N];
    for (size_t i = 0; i < M; i++) {
        _array[i] = new int [M];
    }
}

matrix::~matrix() {
    for (size_t i = 0; i < _N; i++) {
        delete _array[i];
    }
    delete _array;
}

void matrix::print() {
    for (size_t i = 0; i < _N; i++) {
        for (size_t j = 0; j < _M; j++) {
            cout << setw(4) << _array[i][j];
        }
        cout << endl;
    }
}

void matrix::fill() {
    for (size_t i = 0; i < _N; i++) {
        for (size_t j = 0; j < _M; j++) {
            cout << "index " << i << "x" << j << " ? >>> ";
            cin >> _array[i][j];
        }
    }
}

ostream & operator<<(ostream & os, matrix & obj) {
    obj.print();
    return os;
}


int main(void) {    
    matrix ma_matrice;
    ma_matrice.fill();
    cout << ma_matrice;

    return 0;
}