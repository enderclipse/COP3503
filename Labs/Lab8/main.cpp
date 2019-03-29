#include <fstream>
#include <iostream>
#include <vector>
#include "Color.h"
using namespace std;

void ReadFile(const char *filename, vector<Color> &outVector);
void SortColors(vector<Color> &colors);
void PrintColors(const vector<Color> &colors);

//Written for us as part of the assignment specification.
int main()
{
    Color c;
    cout << "1-6: Load colors1/2/3/4/5/6.txt" << endl;
    cout << "7. Load all 6 files" << endl;
    int choice;
    cin >> choice;

    vector<Color> colors;
    // Load the selected files
    if (choice >= 1 && choice <= 6)
    {
        string file = "../colors" + to_string(choice) + ".txt";
        ReadFile(file.c_str(), colors);

    }
    else if (choice == 7)
    {
        for (int i = 1; i <= 6; i++)
        {
            string file = "../colors" + to_string(i) + ".txt";
            ReadFile(file.c_str(), colors);
        }
    }

    // Sort and print the loaded data
    SortColors(colors);
    PrintColors(colors);

    return 0;
}

void ReadFile(const char *filename, vector<Color> &outVector)
{
    fstream file(filename, ios_base::in);
    string line;

    //Each line has format "NAME VALUE\r". Read the line then split it using substr up to the first space and the \r
    while(getline(file, line)) {
        Color c;
        c.SetName(line.substr(0,line.find(" ")));
        c.SetValue(stoi(line.substr(line.find(" "),line.find("\r"))));
        outVector.push_back(c);
    }
    file.close();
}

//Used for SortColors
bool functionSort(Color A, Color B){
    return (A < B);
}
void SortColors(vector<Color> &colors)
{
    //Using algorithms::sort, sort the values lexicographically
    sort(colors.begin(), colors.end(), functionSort);
}

//Provided as part of assignment.
void PrintColors(const vector<Color> &colors)
{
    for (unsigned int i = 0; i < colors.size(); i++)
    {
        cout << colors[i].GetName();
        for (unsigned int j = 0; j < 3 - colors[i].GetName().size() / 8; j++)
            cout << "\t";
        cout << colors[i].GetHexValue() << '\t' << (int)colors[i].GetR() << "," << (int)colors[i].GetG() << "," << (int)colors[i].GetB() << endl;
    }
    cout << "Number of colors: " << colors.size() << endl;
}
