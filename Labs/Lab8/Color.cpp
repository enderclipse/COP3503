//
// Created by JOSHUA HADDAD on 2019-03-18.
//

#include "Color.h"

//Mutators
void Color::SetValue(int value){
    //Set the hex field to the hex version of the decimal value
    hex = hexConversion(value);
    unsigned char r,g,b;
    int bitAnd = 255;

    //The data structure of value is first 8 bits = blue data, next 8 bits = green, next 8 bits = red
    //Compare the value to 255 (11111111) to recover which bits are flipped "On"
    b = value & bitAnd;

    //Shift and compare to 255
    g = (value >> 8) & bitAnd;
    //Shift and compare to 255
    r = (value >> 16) & bitAnd;

    //Assign the fields in the Color object
    red = r; green = g; blue = b;
}
void Color::SetName(string _name){
    name = _name;
}

//Accessors for data within color
unsigned char Color::GetR() const{
    return red;
}
unsigned char Color::GetG() const{
    return green;
}
unsigned char Color::GetB() const{
    return blue;
}
string Color::GetHexValue() const{
    return hex;
}
string Color::GetName() const{
    return name;
}

//Converts a value to hex by dividing by 16 and examining remainders
string Color::hexConversion(int value){
    int remainder;
    string hexValue;
    remainder = value % 16;

    //Standard hex conversion, divide by 16, if remainder is < 10 add to string, else add A-F depending on if 10-15
    while(value != 0){
        value /= 16;
        if(remainder < 10)
            hexValue = to_string(remainder) + hexValue;
        else if(remainder >= 10){
            //Add the remainder +55 (This will give ASCII A for 10, B for 11, etc)
            char hexDigit = remainder + 55;

            //Concatenate the found digit to the end of the string
            hexValue = hexDigit+hexValue;
        }
        remainder = value % 16;
    }

    //Pad with 0s if the string does not have 6 digits
    int size = hexValue.size();
    while(size - 6 < 0){
        hexValue = "0"+hexValue;
        size++;
    }

    //Add 0x at the beginning to signify the hex value
    hexValue = "0x"+hexValue;

    //return the string found.
    return hexValue;
}
bool Color::operator<(const Color B){

    //If this' name is lexicographically before B's name return false.
    if(name.compare(B.name) > 0){
        return false;
    }
    else{
        //Since this is used for sorting and we dont care about duplicates, if they are the same we return false.
        return true;
    }
}