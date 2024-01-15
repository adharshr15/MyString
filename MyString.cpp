// TODO: Implement this source file
# include <iostream>
# include "MyString.h"

using std::cout, std::endl;

MyString::MyString() : str(nullptr), strCapacity(1), strLength(0) {
    str = new char[strCapacity];
    str[0] = '\0';
}

MyString::MyString(const MyString& cpyStr) : str(nullptr), strCapacity(1), strLength(0) {
    copyStr(cpyStr.str);
}

MyString::MyString(const char* cpyChars) : str(nullptr), strCapacity(1), strLength(0) {
    copyStr(cpyChars);
}  

MyString::~MyString() {
    delete[] str;
    strLength = 0;
    strCapacity = 1;
}

void MyString::resize(int newLength) {
    int curCapacity = strCapacity;
    if (curCapacity - 1 != newLength) {
        char* tempStr = new char[newLength + 1]; // allocates tempStr 
        
        for (unsigned int i = 0; i < strCapacity; ++i) {   // copys str to tempStr, only until strCapacity
            tempStr[i] = str[i];
        }

        strCapacity = newLength + 1;
        delete[] str;
        str = new char[strCapacity];          // reallocates str
        

        for (unsigned int i = 0; i < strCapacity; ++i) {   // copys newStr to str
            str[i] = tempStr[i];
        }

        delete[] tempStr;
    }
}

int MyString::capacity() {
    return strCapacity;
}

size_t MyString::size() const {
    return strLength;
}

int MyString::length() {
    return size();
}

char* MyString::data() {
    return str;
}

bool MyString::empty() {
    if (size() == 0) {return true;}
    else {return false;}
}

const char& MyString::front() const {
    char& frontChar = str[0];
    return frontChar;
}

const char& MyString::at(int pos) const {
    int strLengthInt = strLength;
    if (pos >= strLengthInt || pos < 0) {
        throw std::out_of_range("index Invalid");
    }
    return str[pos];
}

void MyString::clear() {
    delete[] str;
    str = new char[1];
    str[0] = '\0';
    strCapacity = 1;
    strLength = 0;
}

MyString& MyString::operator=(const MyString& string) {
    if (this != &string) {
        clear();
        copyStr(string.str);
    }
    return *this;
}

MyString& MyString::operator+=(const MyString& string) {
    resize(strLength + string.strLength);
    for (unsigned int i = 0; i < string.strCapacity; ++i) { // adds string to newData
        str[strLength + i] = string.str[i];
    }
    strLength += string.strLength;

    return *this;
}

int MyString::find(const MyString& string, int pos) const noexcept {
    //cout << "string: " << string.str << ", str: " << str << ", pos: " << pos << endl;
    int index = 0;
    for (unsigned int i = pos; i < strLength; ++i) { 
        if (string.str[index] == str[i]) { // checks if first char in string is equal to current char in str
            if (string.strLength == 1) {
                return i;
            }
            unsigned int ogI = i + 1;
            index += 1;
            while(string.str[index] == str[ogI]) { // checks if next char in st
                if (ogI - i == string.strLength - 1) {
                    return i;
                }
                ogI += 1;
                index += 1;
                
            }
            index = 0;
        }
    }

    return -1;
}



void MyString::copyStr(const char* chars) { // Helper method that returns a copy of the given char array
    if (chars != nullptr) {
        delete[] str; // deallocates str to begin with
        strLength = 0;
        while (chars[strLength] != '\0') { // finds the length of chars
            strLength += 1;
        }
        
        strCapacity = strLength + 1;
        
        str = new char[strCapacity + 1]; // allocates memory for str

        for (unsigned int i = 0; i < strCapacity; ++i) { // copys chars to str.
            str[i] = chars[i];
        }
    }
}