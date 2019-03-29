//
// Created by JOSHUA HADDAD on 2019-03-28.
//

#include "Shapes.h"


//Shape2D

void Shape2D::ShowArea() const {
    cout << "The area of the " << GetName2D() << " is : " << Area() << endl;
}

bool Shape2D::operator>(const Shape2D &rhs) const{
    return Area() > rhs.Area();
}

bool Shape2D::operator<(const Shape2D &rhs) const{
    return Area() < rhs.Area();
}

bool Shape2D::operator==(const Shape2D &rhs) const{
    return Area() == rhs.Area();
}


//Shape3D

void Shape3D::ShowVolume() const {
    cout << "The volume of the " << GetName3D() << " is : " << Volume() << endl;
}

bool Shape3D::operator>(const Shape3D &rhs) const {
    return Volume() > rhs.Volume();
}

bool Shape3D::operator<(const Shape3D &rhs) const {
    return Volume() < rhs.Volume();
}

bool Shape3D::operator==(const Shape3D &rhs) const {
    return Volume() == rhs.Volume();
}


//Square

Square::Square() {
    side = 0;
}

Square::Square(float _side) {
    side = _side;
}

float Square::Area() const {
    return side*side;
}

string Square::GetName2D() const {
    return "Square";
}

void Square::Scale(float scaleFactor) {
    side *= scaleFactor;
}

void Square::Display() {
    cout << "The area of the " << GetName2D() << " is : " << Area() << endl;
    cout << "Length of a side: " << side << endl;
}

//Triangle
Triangle::Triangle() {
    base = 0;
    height = 0;
}

Triangle::Triangle(float _base, float _height) {
    base = _base;
    height = _height;
}

float Triangle::Area() const {
    return .5*base*height;
}

string Triangle::GetName2D() const {
    return "Triangle";
}

void Triangle::Scale(float scaleFactor) {
    base *= scaleFactor;
    height *= scaleFactor;
}

void Triangle::Display() {
    cout << "The area of the " << GetName2D() << " is : " << Area() << endl;
    cout << "Base: " << base << endl;
    cout << "Height: " << height << endl;
}

//Rectangle
Rectangle::Rectangle() {
    width = 0;
    length = 0;
}


Rectangle::Rectangle(float _length, float _width) {
    length = _length;
    width = _width;
}

float Rectangle::Area() const {
    return length*width;
}

string Rectangle::GetName2D() const {
    return "Rectangle";
}

void Rectangle::Scale(float scaleFactor) {
    length *= scaleFactor;
    width *= scaleFactor;
}

void Rectangle::Display() {
    cout << "The area of the " << GetName2D() << " is : " << Area() << endl;
    cout << "Length: " << length << endl;
    cout << "Width: " << width << endl;
}

//Circle
Circle::Circle() {
    radius = 0;
}

Circle::Circle(float _radius) {
    radius = _radius;
}

float Circle::Area() const {
    return PI*radius*radius;
}

string Circle::GetName2D() const {
    return "Circle";
}

void Circle::Scale(float scaleFactor) {
    radius *= scaleFactor;
}

void Circle::Display() {
    cout << "The area of the " << GetName2D() << " is : " << Area() << endl;
    cout << "Radius: " << radius << endl;
}

//Ellipse
Ellipse::Ellipse() {
    major = 0;
    minor = 0;
}

Ellipse::Ellipse(float _major, float _minor) {
    major = _major;
    minor = _minor;
}

float Ellipse::Area() const {
    return PI*minor*major;
}

string Ellipse::GetName2D() const {
    return "Ellipse";
}

void Ellipse::Scale(float scaleFactor) {
    major *= scaleFactor;
    minor *= scaleFactor;
}

void Ellipse::Display() {
    cout << "The area of the " << GetName2D() << " is : " << Area() << endl;
    cout << "Length of semi-major axis: " << major << endl;
    cout << "Length of semi-minor axis: " << minor << endl;
}

//Trapezoid
Trapezoid::Trapezoid() {
    lengthOne = 0;
    lengthTwo = 0;
    height = 0;
}

Trapezoid::Trapezoid(float _lengthOne, float _lengthTwo, float _height) {
    lengthOne = _lengthOne;
    lengthTwo = _lengthTwo;
    height = _height;
}

float Trapezoid::Area() const {
    return .5*(lengthOne+lengthTwo)*height;
}

string Trapezoid::GetName2D() const {
    return "Trapezoid";
}

void Trapezoid::Scale(float scaleFactor) {
    lengthOne *= scaleFactor;
    lengthTwo *= scaleFactor;
    height *= scaleFactor;
}

void Trapezoid::Display() {
    cout << "The area of the " << GetName2D() << " is : " << Area() << endl;
    cout << "Length of side A: " << lengthOne << endl;
    cout << "Length of side B: " << lengthTwo << endl;
    cout << "Height: " << height << endl;
}

//Sector
Sector::Sector(){
    radius = 0;
    radians = 0;
}
Sector::Sector(float _radius, float _degrees) {
    radians = PI/180*_degrees;
    radius = _radius;
}

float Sector::Area() const {
    return .5f*radius*radius*radians;
}

string Sector::GetName2D() const {
    return "Sector";
}

void Sector::Scale(float scaleFactor) {
    radius *= scaleFactor;
    radians *= scaleFactor;
}

void Sector::Display() {
    cout << "The area of the " << GetName2D() << " is : " << Area() << endl;
    cout << "Radius: " << radius << endl;
    cout << "Angle in radians: " << radians << endl;
    cout << "Angle in degrees: " << radians*180.0f/PI << endl;
}

//Triangular Pyramid
TriangularPyramid::TriangularPyramid() {
    height = 0;
    base = Triangle();
}

TriangularPyramid::TriangularPyramid(float _height, float _lengthBase, float _heightBase) {
    height = _height;
    base = Triangle(_lengthBase, _heightBase);
}

float TriangularPyramid::Volume() const {
    return (1.0f/3.0f)*base.Area()*height;
}

string TriangularPyramid::GetName3D() const {
    return "Triangular Pyramid";
}

void TriangularPyramid::Scale(float scaleFactor) {
    base.Scale(scaleFactor);
    height *= scaleFactor;
}

void TriangularPyramid::Display() {
    cout << "The volume of the " << GetName3D() << " is : " << Volume() << endl;
    cout << "The height is: " << height << endl;
    base.Display();
}

//Rectangular Pyramid
RectangularPyramid::RectangularPyramid() {
    height = 0;
    base = Rectangle();
}

RectangularPyramid::RectangularPyramid(float _height, float _lengthBase, float _widthBase) {
    height = _height;
    base = Rectangle(_lengthBase, _widthBase);
}

float RectangularPyramid::Volume() const {
    return (1.0f/3.0f)*base.Area()*height;
}

string RectangularPyramid::GetName3D() const {
    return "Rectangular Pyramid";
}

void RectangularPyramid::Scale(float scaleFactor) {
    height *= scaleFactor;
    base.Scale(scaleFactor);
}

void RectangularPyramid::Display() {
    cout << "The volume of the " << GetName3D() << " is : " << Volume() << endl;
    cout << "The height is: " << height << endl;
    base.Display();
}


//Cylinder
Cylinder::Cylinder() {
    base = Circle();
    height = 0;
}

Cylinder::Cylinder(float _height, float _radius) {
    base = Circle(_radius);
    height = _height;
}

float Cylinder::Volume() const {
    return base.Area()*height;
}

string Cylinder::GetName3D() const {
    return "Cylinder";
}

void Cylinder::Scale(float scaleFactor) {
    height *= scaleFactor;
    base.Scale(scaleFactor);
}

void Cylinder::Display() {
    cout << "The volume of the " << GetName3D() << " is : " << Volume() << endl;
    cout << "The height is: " << height << endl;
    base.Display();
}

//Sphere
Sphere::Sphere() {
    base = Circle();
    radius = 0;
}

Sphere::Sphere(float _radius) {
    base = Circle(_radius);
    radius = _radius;
}

float Sphere::Volume() const {
    return (4.0f/3.0f)*base.Area()*radius;
}

string Sphere::GetName3D() const {
    return "Sphere";
}

void Sphere::Scale(float scaleFactor) {
    base.Scale(scaleFactor);
}

void Sphere::Display() {
    cout << "The volume of the " << GetName3D() << " is : " << Volume() << endl;
    base.Display();
}

Shape::~Shape() {

}
