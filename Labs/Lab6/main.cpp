#include <iostream>
#include <fstream>
#include <istream>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;

void printSet(unsigned int index, const vector<string> &number, const vector<string> &theme, const vector<string> name,
              vector<int> &figures, vector<int> &pieces, vector<float> &price);


//Get the index of the set with the highest price
unsigned int mostExpensive(const vector<float> &price);

//Get the index of the set with the most pieces.
unsigned int mostPieces(const vector<int> &pieces);

//Print all sets with the given name
void searchName(string name, const vector<string> &names,
                const vector<string> &number,const vector<float> &price);

//Print all sets with the given theme
void searchTheme(string themeName, const vector<string> name, const vector<string> &theme,
                 const vector<string> &number, const vector<float> &price);

//Print the average parts
void printAvgParts(const vector<int> &pieces);

//Returns vector of the form <index of min, index of max>
vector<unsigned int> priceInfo(const vector<float> &price);

//Returns a max minifig index
unsigned int miniFigInformation(const vector<int> &figures);

void everythingInfo(const vector<float> &price, const vector<int> &pieces, const vector<int> &figures);





int main()
{
    cout << std::fixed << setprecision(2);
    cout << "Which file(s) to open?\n";
    cout << "1. lego1.csv" << endl;
    cout << "2. lego2.csv" << endl;
    cout << "3. lego3.csv" << endl;
    cout << "4. All 3 files" << endl;
    int option;
    cin >> option;

    ifstream legos;

    int index;

    if(option == 1 || option == 4){
        legos.open("../lego1.csv");
        index = 1;
    }
    if(option == 2){
        legos.open("../lego2.csv");
    }
    if(option == 3){
        legos.open("../lego3.csv");
    }

    unsigned int counter = 1;

    vector<string> number;
    vector<string> theme;
    vector<string> name;
    vector<int> figures;
    vector<int> pieces;
    vector<float> price;


    string line;
    getline(legos, line);

    while(getline(legos, line, ',')){
        if(counter == 1){
            number.push_back(line);
            counter++;
        }
        else if(counter == 2){
            theme.push_back(line);
            counter++;
        }
        else if(counter == 3){
            name.push_back(line);
            counter++;
        }
        else if(counter == 4){
            figures.push_back(stoi(line));
            counter++;
        }
        else if(counter == 5){
            pieces.push_back(stoi(line));
            counter++;
        }

            //This takes the end of the line which is of the form "%.2f\r\n%i" and handles it
        else if(counter == 6){

            //Find the price by taking the line's substring from 0 to the first escape char \r
            price.push_back(stof(line.substr(0,line.find("\\r"))));

            //If the character sequence is just \r\n and does not have anything after, dont' look for another int
            if(line.find("\r\n")+1 != line.size()-1){
                number.push_back(line.substr(line.find("\r\n")+2, line.size()));
            }

            //If we want to keep opening files, close the current file and open another
            if(line.find("\r\n")+1 == line.size()-1 && option == 4 && index < 3){
                index++;
                string nextFile = "./lego" + to_string(index) + ".csv";
                legos.close();
                legos.open(nextFile);
                getline(legos, line);
                counter = 1;
                continue;
            }

            counter = 2;
        }
    }

    //Since each vector is the same size, the number of sets is just the size of the vector.
    unsigned long numberSets = number.size();
    cout << "Total number of sets: " << numberSets << endl;

    int choice;
    cin >> choice;
    cin.get();

    if(choice == 1){
        unsigned int expensiveIndex = mostExpensive(price);
        cout << "The most expensive set is: " << endl;
        printSet(expensiveIndex, number, theme, name, figures, pieces, price);
    }
    if(choice == 2){
        unsigned int pieceIndex = mostPieces(pieces);
        cout << "The set with the highest parts count:" << endl;
        printSet(pieceIndex, number, theme, name, figures, pieces, price);
    }
    if(choice == 3){
        string getName;
        getline(cin >> ws,getName);
        searchName(getName, name, number, price);
    }
    if(choice == 4){
        string getName;
        getline(cin >> ws,getName);
        searchTheme(getName, name, theme, number, price);
    }
    if(choice == 5){
        printAvgParts(pieces);
    }
    if(choice == 6){
        vector<unsigned int> data = priceInfo(price);
        cout << endl << "Least expensive set: " << endl;
        printSet(data.at(0), number, theme, name, figures, pieces, price);
        cout << endl << "Most expensive set: " << endl;
        printSet(data.at(1), number, theme, name, figures, pieces, price);

    }
    if(choice == 7){
        unsigned int index = miniFigInformation(figures);
        cout << "Set with the most minifigures:\n" << endl;
        printSet(index, number, theme, name, figures, pieces, price);
    }
    if(choice == 8){
        cout << "If you bought one of everything...\n" << endl;
        everythingInfo(price, pieces, figures);
    }
    if(choice == 0){
        return 0;
    }

    /*======= Based on the choice, execute the appropriate task and show the results =======*/

    return 0;
}

void printSet(unsigned int i, const vector<string> &number, const vector<string> &theme, const vector<string> name,
              vector<int> &figures, vector<int> &pieces, vector<float> &price){

    cout << "Name: " << name[i] << endl;
    cout << "Number: " << number[i] << endl;
    cout << "Theme: " << theme[i] << endl;
    cout << "Price: $" << price[i] << endl;
    cout << "Minifigures: " <<figures[i] << endl;
    cout << "Piece count: " <<pieces[i] << endl;
}

unsigned int mostExpensive(const vector<float> &price){
    unsigned int highestIndex = 0;
    float highestPrice = 0;
    for(unsigned int i = 0; i < price.size(); i++){
        if(price.at(i) > highestPrice){
            highestPrice = price.at(i);
            highestIndex = i;
        }
    }
    return highestIndex;
}

//Get the index of the set with the most pieces.
unsigned int mostPieces(const vector<int> &pieces){
    unsigned int highestIndex = 0;
    float highestPrice = 0;
    for(unsigned int i = 0; i < pieces.size(); i++){
        if(pieces.at(i) > highestPrice){
            highestPrice = pieces.at(i);
            highestIndex = i;
        }
    }
    return highestIndex;
}

//Print all sets with the given name
void searchName(string setName, const vector<string> &names,
                const vector<string> &number, const vector<float> &price){

    bool firstPrint = true;
    bool found = false;

    for(unsigned int i = 0; i < names.size(); i++){
        if(names.at(i).find(setName) < names.at(i).size()){
            if(firstPrint){
                cout << "Sets matching \"" << setName << "\":" << endl;
                firstPrint = false;
            }
            cout << number.at(i) << " " << names.at(i) << " $" << price.at(i) << endl;
            found = true;
        }
    }
    if(!found){
        cout << "No sets found matching that search term" << endl;
    }

}

//Print all sets with the given theme
void searchTheme(string themeName, const vector<string> name, const vector<string> &theme,
                 const vector<string> &number, const vector<float> &price){

    bool found = false;
    bool firstPrint = true;
    for(unsigned int i = 0; i < theme.size(); i++){
        if(theme.at(i).find(themeName) < theme.at(i).size()){
            if(firstPrint){
                cout << "Sets matching \"" << themeName << "\":" << endl;
                firstPrint = false;
            }
            cout << number.at(i) << " " << name.at(i) << " $" << price.at(i) << endl;
            found = true;
        }
    }

    if(!found){
        cout << "No sets found matching that search term" << endl;
    }
}

//Print the average parts
void printAvgParts(const vector<int> &pieces){
    int sum = 0;
    for(unsigned int i = 0; i < pieces.size(); i++){
        sum += pieces.at(i);
    }
    cout << "Average part count for " << pieces.size() << "sets: " << sum/pieces.size() << endl;
}

//Returns vector of the form <min price, highest price>
vector<unsigned int> priceInfo(const vector<float> &price){
    float sum = 0;
    vector<unsigned int> minMax;
    unsigned int min = 0;
    unsigned int max = 0;
    unsigned int size = price.size();
    for(unsigned int i = 0; i < size; i++){
        if(price.at(min) > price.at(i)){
            min = i;
        }
        if(price.at(max) < price.at(i)){
            max = i;
        }
        sum += price.at(i);
    }

    cout << "Average price for " << size << " sets: $" << sum/size << endl;
    minMax.push_back(min);
    minMax.push_back(max);

    return minMax;

}

//Returns a vector of the form <avg figures, index of highest minifigs>
unsigned int miniFigInformation(const vector<int> &figures){
    unsigned int max = 0;
    unsigned int sum = 0;
    for(unsigned int i = 0; i < figures.size(); i++){
        if(figures.at(max) < figures.at(i))
            max = i;

        sum += figures.at(i);
    }

    cout << "Average number of minifigures: " << sum/figures.size() << endl;
    return max;
}

void everythingInfo(const vector<float> &price, const vector<int> &pieces, const vector<int> &figures){
    float sumPrice = 0;
    unsigned int sumPieces = 0 ;
    unsigned int sumFigures = 0;

    for(unsigned int i = 0; i < price.size(); i++){
        sumPrice += price.at(i);
        sumPieces += pieces.at(i);
        sumFigures += figures.at(i);
    }
    cout << "It would cost: $" << sumPrice << endl;
    cout << "You would have " << sumPieces << " pieces in your collection" << endl;
    cout << "You would have an army of " << sumFigures << " minifigures!" << endl;

}