#include <iostream>
#include <cstring>

struct X {
    int i {};

    X(int i_ = 0) : i { i_ } {}

    X &operator--() {
        --i;
        return *this;
    }

    X operator--(int) {
        X tmp { *this };
        --i;
        return tmp;
    }
};

class MyString {
    friend std::ostream &operator<<(std::ostream &out, MyString ob);
    friend std::istream &operator>>(std::istream &in, MyString &ob);

private:
    char *str;
    int size;

public:
    MyString();
    explicit MyString(const char *s);
    MyString(const MyString &ob);
    ~MyString();
    int Size();
    char &operator[](int index);
    MyString &operator=(MyString ob);
    MyString &operator=(const char *s);
    MyString operator+(MyString &ob);
    MyString operator+(const char *s);
    bool operator>(MyString &ob);
    bool operator>(const char *s);
};

MyString operator+(const char *s, MyString &str) {
    return str + s;
}

MyString::MyString() {
    str = new char[0];
    size = 0;
}

MyString::MyString(const char *s) {
    // cout << "MyString 有参构造" << endl;
    size = strlen(s);
    str = new char[size + 1];
    strcpy(str, s);
}

MyString::MyString(const MyString &ob) {
    //  cout << "MyString 拷贝构造" << endl;
    size = ob.size;
    str = new char[size + 1];
    strcpy(str, ob.str);
}

MyString::~MyString() {
    if (str != NULL) {
        delete[] str;
        str = NULL;
    }
}

int MyString::Size() { return this->size; }

char &MyString::operator[](int index) { return str[index]; }

MyString &MyString::operator=(MyString ob) {
    if (str != NULL) {
        delete[] str;
        str = NULL;
    }
    size = ob.size;
    str = new char[size + 1];
    strcpy(str, ob.str);

    return *this;
}

MyString &MyString::operator=(const char *s) {
    if (str != NULL) {
        delete[] str;
        str = NULL;
    }
    size = strlen(s);
    str = new char[size + 1];
    strcpy(str, s);

    return *this;
}

MyString MyString::operator+(MyString &ob) {
    MyString tmp;
    tmp.size = size + ob.size;
    tmp.str = new char[tmp.size];
    strcpy(tmp.str, str);
    strcat(tmp.str, ob.str);

    return tmp;
}

MyString MyString::operator+(const char *s) {
    MyString tmp;
    tmp.size = size + strlen(s);
    tmp.str = new char[tmp.size];
    strcpy(tmp.str, str);
    strcat(tmp.str, s);

    return tmp;
}

bool MyString::operator>(MyString &ob) {
    if ((strcmp(str, ob.str)) > 0)
        return true;
    else
        return false;
}

bool MyString::operator>(const char *s) {
    if ((strcmp(str, s)) > 0)
        return true;
    else
        return false;
}

std::ostream &operator<<(std::ostream &out, MyString ob) {
    out << ob.str;
    return out;
}

std::istream &operator>>(std::istream &in, MyString &ob) {
    if (ob.str != NULL) {
        delete[] ob.str;
        ob.str = NULL;
    }
    char buf[1024] = { 0 };
    in >> buf;
    ob.size = strlen(buf);
    ob.str = new char[ob.size + 1];
    strcpy(ob.str, buf);

    return in;
}