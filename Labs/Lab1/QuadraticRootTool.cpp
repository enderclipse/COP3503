#include <iostream>
#include <cmath> //Used for sqrt

//Common functions called
using std::cout;
using std::cin;
using std::endl;

int main(){

    //Defining variables needed
    double a;
    double b;
    double c;

    //Prompting for and gathering input
    cout << "Enter a, b, c: ";
    cin >> a >> b >> c;

    //Calculating discriminate
    double discrim = b*b - 4*a*c;

    //If discrim is less than 0
    if(discrim < 0){
        cout << "The equation has no real roots." << endl;
    }

    //If discrim is greater than 0
    else if (discrim > 0){
        double r1 = (-b + sqrt(discrim))/(2*a);
        double r2 = (-b - sqrt(discrim))/(2*a);
        cout << "The equation has two roots: " << r1 << " and " << r2 << endl;
    }

    //If discrim is 0
    else{
        double r = -b/(2*a);
        cout << "The equation has one root: " << r << endl;
    }
    return 0;

}