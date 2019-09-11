//
// Created by JOSHUA HADDAD on 2019-03-11.
//

#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <unistd.h>
using namespace std;

struct Header{
    char idLength;
    char colorMapType;
    char dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char bitsPerPixel;
    char imageDescriptor;

    bool operator==(Header B) {
        if(B.idLength != idLength || B.colorMapType != colorMapType || B.dataTypeCode != dataTypeCode ||
                B.colorMapOrigin != colorMapOrigin || B.colorMapLength != colorMapLength ||
                B.colorMapDepth != colorMapDepth || B.xOrigin != xOrigin || B.yOrigin != yOrigin || B.width != width ||
                B.height != height || B.bitsPerPixel != bitsPerPixel || B.imageDescriptor != imageDescriptor)
            return false;

        return true;
    }

    void printHead(){
        cout << (int)idLength << endl;
        cout << (int)colorMapType << endl;
        cout << (int)colorMapOrigin << endl;
        cout << (int)colorMapLength << endl;
        cout << (int)colorMapDepth << endl;
        cout << (int)dataTypeCode << endl;
        cout << (int)width << endl;
        cout << (int)height << endl;
        cout << (int)bitsPerPixel << endl;
        cout << (int)imageDescriptor << endl;
    }
};
struct Pixel{
    unsigned char red;
    unsigned char green;
    unsigned char blue;

    Pixel(){}

    Pixel(unsigned char _red, unsigned char _green, unsigned char _blue){
        red = _red;
        green = _green;
        blue = _blue;
    }
    bool operator!=(Pixel B){
        if(B.red != red || B.green != green || B.blue != blue) {
            //green is wrong should be 30 but is 31
            cout << (int)B.red << " should be " << (int)red << endl;
            cout << (int)B.green << " should be " << (int)green << endl;
            cout << (int)B.blue << " should be " << (int)blue << endl;
            return true;
        }
        else{
            return false;
        }
    }
};

struct Image{
    Header head;
    vector<Pixel> pixels;
    int size;

    bool operator==(Image B){
        if(!(B.head == head)){
            cout << "B head: " << endl;
            B.head.printHead();
            cout << "This head " << endl;
            head.printHead();
            return false;
        }
        for(int i = 0; i < B.size; i++){
            if(B.pixels.at(i) != pixels.at(i)){
                cout << "Pixel? at position " << i << endl;
                return false;
            }
        }
        return true;
    }
};

class ImageProcessor{
private:
    float ColorProduct(float A, float B);
    float ColorNegative(float A);
    float ColorOverlay(unsigned char A, unsigned char B);
public:
    bool checkImages(string, string, string, string);
    Image loadImage(string,string);
    bool writeImage(Image, string);
    Image Multiply(Image &A, Image &B);
    Image Subtract(Image &A, Image &B);
    Image Combine(Image &R, Image &G, Image &B);
    Image Screen(Image &A, Image &B);
    Image Negative(Image &A);
    Image Overlay(Image &A, Image &B);
    Image Add(Image &A, unsigned char value, string channel);
    Image MultiplyChannel(Image &A, float value, string channel);
    Image Rotate(Image A);
    void writeChannels(Image A);
    Image extraCredit(Image A, Image B, Image C, Image D);


};



