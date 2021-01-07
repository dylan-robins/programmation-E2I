#include <cctype>
#include <cstring>
#include <iostream>

/* CLASSES */
class string {
  private:
    char *_str;
    unsigned int _len;

  public:
    /* CONSTRUCTORS */
    // default
    string() : _len(0) {
        _str = new char[_len + 1];
        strcpy(_str, "");
    }
    // char
    string(const char c) : _len(1) {
        _str = new char[_len + 1];
        _str[0] = c;
        _str[1] = '\0';
    }
    // cstr array
    string(const char *cstr) : _len(strlen(cstr)) {
        _str = new char[_len + 1];
        strcpy(_str, cstr);
    }
    // repeated char
    string(const char c, const unsigned int repeat) : _len(repeat) {
        _str = new char[_len + 1];
        for (int i = 0; i < repeat; i++) {
            _str[i] = c;
        }
        _str[_len] = '\0'; // null terminator
    }
    // copy constructor
    string(const string &other) : _len(other._len) {
        _str = new char[_len + 1];
        strcpy(_str, other._str);
    }

    /* DESTRUCTOR */
    ~string() {
        delete[] _str;
    }

    /* METHODS */
    // Resizes the member cstring
    void resize(const unsigned int new_len) {
        char *new_str = new char[new_len + 1];

        // impose limit of new_len-1 to avoid overflow
        strncpy(new_str, _str, new_len - 1);

        if (new_len < _len) {
            _str[new_len] = '\0'; // add null terminator incase we overflow
        }

        delete[] _str;
        _str = new_str;
    }
    void concat(const string &other) {
        resize(_len + other._len);
        strcat(_str, other._str);
    }
    string to_lower() {
        string lower(*this);
        for (int i = 0; i < _len; i++) {
            if (isupper(lower[i])) {
                toupper(lower[i]);
            }
        }
        return lower;
    }

    /* OPERATORS */
    string &operator=(const string &to_copy) {
        resize(to_copy._len);
        strcpy(_str, to_copy._str);
        return *this;
    }
    string &operator=(const char *cstr) {
        resize(strlen(cstr));
        strcpy(_str, cstr);
        return *this;
    }
    string &operator+=(const string &to_concat) {
        concat(to_concat);
        return *this;
    }
    string &operator+=(const char c) {
        concat(c);
        return *this;
    }
    char operator[](const size_t i) const {
        return _str[i];
    }
    char &operator[](const size_t i) {
        return _str[i];
    }
    // in accordance with https://github.com/isocpp/CppCoreGuidelines/blob/036324/CppCoreGuidelines.md#c161-use-nonmember-functions-for-symmetric-operators
    friend string operator+(const string &str1, const string &str2);
    friend bool operator==(const string &str1, const string &str2);

    friend std::ostream &operator<<(std::ostream &os, const string &str);
    friend std::istream &operator>>(std::istream &is, string &str);
};

/* FUNCTIONS */
string operator+(const string &str1, const string &str2) {
    string out_str(str1);
    out_str.concat(str2);
    return out_str;
}
bool operator==(const string &str1, const string &str2) {
    return (str1._len == str2._len) && (strcmp(str1._str, str2._str) == 0);
}
bool operator!=(const string &str1, const string &str2) {
    return !(str1 == str2);
}
std::ostream &operator<<(std::ostream &os, const string &str) {
    os << str._str;
    return os;
}
std::istream &operator>>(std::istream &is, string &str) {
    char buffer[2048];
    is >> buffer;
    str = buffer;
    return is;
}

/* MAIN */
int main() {
    string ch1("essai"), ch2 = ch1, ch3('=', 80);
    const string ch4("chaîne de caractères constante");
    ch1[1] = 'E';
    // le premier caractère de la chaîne
    std::cout << ch4[1] << std::endl;
    ch1 = "<<<< " + ch2 + " >>>>";
    std::cout << ch1 << std::endl;
    std::cin >> ch2;
    ch2 += " de la classe Strin";
    ch2 += 'g';
    if (ch2 != "")
        std::cout << ch2 << std::endl;
    std::cout << ch2.to_lower() << std::endl;

    return 0;
}