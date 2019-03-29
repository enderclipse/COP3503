//
// Created by JOSHUA HADDAD on 2019-03-18.
//

#include <iostream>
#pragma once

using namespace std;

class Color{
private:
    string name;
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    string hex;
public:
    //Color();
    void SetValue(int value);
    void SetName(const string name);
    bool operator<(const Color B);

    unsigned char GetR() const;
    unsigned char GetG() const;
    unsigned char GetB() const;
    string GetHexValue() const;
    string GetName() const;
    string hexConversion(int value);
};
