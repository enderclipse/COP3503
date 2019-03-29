//
// Created by JOSHUA HADDAD on 2019-03-28.
//

#include <iostream>
#define PI 3.14159f

using namespace std;

class Shape {
public:
    virtual void Scale(float scaleFactor) = 0;
    virtual void Display() = 0;
    virtual ~Shape();

};

class Shape2D : virtual public Shape{
public:
    virtual float Area() const = 0;
    void ShowArea() const;
    virtual string GetName2D() const = 0;
    bool operator>(const Shape2D &rhs) const;
    bool operator<(const Shape2D &rhs) const;
    bool operator==(const Shape2D &rhs) const;
    ~Shape2D() = default;
};

class Shape3D : virtual public Shape{
public:
    virtual float Volume() const = 0;
    void ShowVolume() const;
    virtual string GetName3D() const = 0;
    bool operator>(const Shape3D &rhs) const;
    bool operator<(const Shape3D &rhs) const;
    bool operator==(const Shape3D &rhs) const;
    ~Shape3D() = default;
};

class Square : public Shape2D{
private:
    float side;

public:
    Square();
    Square(float _side);
    float Area() const;
    string GetName2D() const;
    void Scale(float scaleFactor);
    void Display();
    ~Square() = default;
};
class Triangle : public Shape2D{
private:
    float base, height;

public:
    Triangle();
    Triangle(float _base, float _height);
    float Area() const;
    string GetName2D() const;
    void Scale(float scaleFactor);
    void Display();
    ~Triangle() = default;
};
class Rectangle : public Shape2D{
private:
    float width, length;

public:
    Rectangle();
    Rectangle(float _width, float _height);
    float Area() const;
    string GetName2D() const;
    void Scale(float scaleFactor);
    void Display();
    ~Rectangle() = default;
};
class Circle : public Shape2D{
private:
    float radius;

public:
    Circle();
    Circle(float _radius);
    float Area() const;
    string GetName2D() const;
    void Scale(float scaleFactor);
    void Display();
    ~Circle() = default;
};
class Ellipse : public Shape2D{
private:
    float major, minor;

public:
    Ellipse();
    Ellipse(float _major, float _minor);
    float Area() const;
    string GetName2D() const;
    void Scale(float scaleFactor);
    void Display();
    ~Ellipse() = default;
};
class Trapezoid : public Shape2D{
private:
    float lengthOne ,lengthTwo, height;

public:
    Trapezoid();
    Trapezoid(float _lengthOne, float _lengthTwo, float _height);
    float Area() const;
    string GetName2D() const;
    void Scale(float scaleFactor);
    void Display();
    ~Trapezoid() = default;
};
class Sector : public Shape2D{
private:
    float radius, radians;

public:
    Sector();
    Sector(float _radius, float _degrees);
    float Area() const;
    string GetName2D() const;
    void Scale(float scaleFactor);
    void Display();
    ~Sector() = default;
};

class TriangularPyramid : public Shape3D, private Triangle{
private:
    float height;
    Triangle base;

public:
    TriangularPyramid();
    TriangularPyramid(float _height, float _lengthBase, float _heightBase);
    float Volume() const;
    string GetName3D() const;
    void Scale(float scaleFactor);
    void Display();
    ~TriangularPyramid() = default;
};

class RectangularPyramid : public Shape3D, private Triangle, private Square{
private:
    float height;
    Rectangle base;
public:
    RectangularPyramid();
    RectangularPyramid(float _height, float _lengthBase, float _widthBase);
    float Volume() const;
    string GetName3D() const;
    void Scale(float scaleFactor);
    void Display();
    ~RectangularPyramid() = default;
};

class Cylinder : public Shape3D, private Circle{
private:
    float height;
    Circle base;

public:
    Cylinder();
    Cylinder(float _height, float radius);
    float Volume() const;
    string GetName3D() const;
    void Scale(float scaleFactor);
    void Display();
    ~Cylinder() = default;
};
class Sphere : public Shape3D{
private:
    Circle base;
    float radius;

public:
    Sphere();
    Sphere(float _radius);
    float Volume() const;
    string GetName3D() const;
    void Scale(float scaleFactor);
    void Display();
    ~Sphere() = default;
};

