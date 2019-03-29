#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

struct Weapon{
    bool empty;
    vector<string> weaponName;
    vector<int> weaponPower;
    vector<float> weaponEnergy;

    Weapon(){
        empty = true;
    }
};

void printShip(int index, vector<string> &shipNames, vector<string> &shipClass, vector<short> &shipLength, vector<int> &shipShield,
               vector<float> &shipSpeed, vector<Weapon> &shipWeapons);
void printShips(int numberShips, vector<string> &shipNames, vector<string> &shipClass, vector<short> &shipLength, vector<int> &shipShield,
                vector<float> &shipSpeed, vector<Weapon> &shipWeapons);
int printSingleHighest(vector<Weapon> shipWeapons);
int printMostPowerful(vector<Weapon> shipWeapons);
int printWeakest(vector<Weapon> shipWeapons);
vector<int> printUnarmed(vector<Weapon> shipWeapons);


int main()
{

	cout << "Which file(s) to open?\n";
	cout << "1. friendlyships.shp" << endl;
	cout << "2. enemyships.shp" << endl;
	cout << "3. Both files" << endl;
	int option;
	cin >> option;

	ifstream file;

	if(option == 1){
	    file.open("../friendlyships.shp", ios_base::binary);
	}
	if(option == 2){
        file.open("../enemyships.shp", ios_base::binary);
	}
	if(option == 3){
        file.open("../friendlyships.shp", ios_base::binary);
	}

	bool allFiles = false;
	vector<string> shipNames;
	vector<string> shipClass;
	vector<short> shipLength;
	vector<int> shipShield;
	vector<float> shipSpeed;
	vector<Weapon> shipWeapons;

	int fileLoad = 1;

	if(file.is_open()){
	    while(allFiles == false){
	        int numberShips;
	        file.read((char*)&numberShips, 4);

	        for(int j = 0; j < numberShips; j++){
                //Get name and class
                for(unsigned int i = 0; i < 2; i++){
                    //Get the length of the name
                    int length;
                    file.read((char*)&length, 4);

                    //Get the string data from the length
                    char* nameData = new char[length];
                    file.read(nameData, length);
                    string name(nameData);
                    delete[] nameData;

                    if(i == 0)
                        shipNames.push_back(name);
                    if(i == 1)
                        shipClass.push_back(name);
                }

                //Get ship length
                short meters = 0;
                file.read((char*)&meters, 2);
                shipLength.push_back(meters);

                //Get shield capacity
                int shield = 0;
                file.read((char*)&shield, 4);
                shipShield.push_back(shield);

                //Get speed of vehicle
                float speed = 0;
                file.read((char*)&speed, 4);
                shipSpeed.push_back(speed);

                //Get number of weapons
                int numberWeapons = 0;
                file.read((char*)&numberWeapons, 4);

                //If number of weapons is zero set the flag equal to zero
                if(numberWeapons == 0){
                    Weapon emptyWeapon;
                    emptyWeapon.empty = true;
                    shipWeapons.push_back(emptyWeapon);
                }

                //If the number of weapons is not zero, fill the shipWeapons array with them
                else{
                    Weapon weapons = Weapon();
                    weapons.empty = false;
                    for(int i = 0; i < numberWeapons; i++){

                        int weaponNameLength = 0;
                        file.read((char*) &weaponNameLength, 4);


                        char* weaponNameArray = new char[weaponNameLength];
                        file.read(weaponNameArray,weaponNameLength);
                        string weaponName(weaponNameArray);
                        weapons.weaponName.push_back(weaponName);

                        int power = 0;
                        file.read((char*) &power, 4);
                        weapons.weaponPower.push_back(power);

                        float energy = 0;
                        file.read((char*) &energy, 4);
                        weapons.weaponEnergy.push_back(energy);

                        delete[] weaponNameArray;
                    }
                    shipWeapons.push_back(weapons);
                }

	        }
	        if(option != 3 || fileLoad == 2){
	            allFiles = true;
	            file.close();
	        }
	        else{
	            file.close();
	            file.open("../enemyships.shp");
	            fileLoad++;
	        }

	    }
	}

	cout << "1. Print all ships" << endl;
	cout << "2. Starship with the strongest weapon" << endl;
	cout << "3. Strongest starship overall" << endl;
	cout << "4. Weakest ship (ignoring unarmed)" << endl;
	cout << "5. Unarmed ships" << endl;

	cin >> option;

	if(option == 1){
	    printShips(shipNames.size(), shipNames, shipClass, shipLength, shipShield, shipSpeed, shipWeapons);
	}
	if(option == 2){
        printShip(printSingleHighest(shipWeapons), shipNames, shipClass, shipLength, shipShield, shipSpeed, shipWeapons);
	}
	if(option == 3){
        printShip(printMostPowerful(shipWeapons), shipNames, shipClass, shipLength, shipShield, shipSpeed, shipWeapons);
	}
	if(option == 4){
	    printShip(printWeakest(shipWeapons), shipNames, shipClass, shipLength, shipShield, shipSpeed, shipWeapons);
	}
	if(option == 5){
        vector<int> unarmed = printUnarmed(shipWeapons);
        for(unsigned int i = 0; i < unarmed.size(); i++){
            printShip(unarmed.at(i), shipNames, shipClass, shipLength, shipShield, shipSpeed, shipWeapons);
        }
	}

   return 0;
}

void printShip(int index, vector<string> &shipNames, vector<string> &shipClass, vector<short> &shipLength, vector<int> &shipShield,
               vector<float> &shipSpeed, vector<Weapon> &shipWeapons){
    cout << "Name: " << shipNames.at(index) << endl;
    cout << "Class: " << shipClass.at(index) << endl;
    cout << "Length: " << shipLength.at(index) << endl;
    cout << "Shield capacity: " << shipShield.at(index) << endl;
    cout << "Maximum Warp: " << setprecision(1) << shipSpeed.at(index);
    cout << "Armaments: " << endl;
    int firepower = 0;
    if(shipWeapons.at(index).empty)
        cout << "Unarmed" << endl << endl;
    else{
        for(unsigned int i = 0; i < shipWeapons.at(index).weaponName.size(); i++){

            cout << shipWeapons.at(index).weaponName.at(i) << ", " << shipWeapons.at(index).weaponPower.at(i) << ", "
                 << shipWeapons.at(index).weaponEnergy.at(i) << endl;
            firepower += shipWeapons.at(index).weaponPower.at(i);
        }
        cout << "Total firepower: " << firepower << endl <<endl;
    }

}


void printShips(int numberShips, vector<string> &shipNames, vector<string> &shipClass, vector<short> &shipLength, vector<int> &shipShield,
                vector<float> &shipSpeed, vector<Weapon> &shipWeapons){
    for(int i = 0; i < numberShips; i++){
        printShip(i, shipNames, shipClass, shipLength, shipShield,shipSpeed, shipWeapons);
    }
}
int printSingleHighest(vector<Weapon> shipWeapons){
    int highestIndex = 0;
    int highestPower = 0;
    for(unsigned int i = 0; i < shipWeapons.size(); i++){
        if(shipWeapons.at(i).empty)
            continue;

        for(unsigned int j = 0; j < shipWeapons.at(i).weaponPower.size(); j++){
            if(shipWeapons.at(i).weaponPower.at(j) > highestPower){
                highestIndex = i;
                highestPower = shipWeapons.at(i).weaponPower.at(j);
            }
        }
    }
    return highestIndex;
}
int printMostPowerful(vector<Weapon> shipWeapons){
    int mostPowerful = 0;
    int mostPowerIndex = 0;
    int firepower = 0;
    for(unsigned int i = 0; i < shipWeapons.size(); i++){
        for(unsigned int j = 0; j < shipWeapons.at(i).weaponPower.size(); j++){
            firepower+= shipWeapons.at(i).weaponPower.at(j);
        }
        if(firepower > mostPowerful){
            mostPowerful = firepower;
            mostPowerIndex = i;
        }

        firepower = 0;
    }
    return mostPowerIndex;
}
int printWeakest(vector<Weapon> shipWeapons){
    int leastPowerful = 0;
    int leastPowerIndex = 0;
    int firepower = 0;
    bool firstShip = true;
    for(unsigned int i = 0; i < shipWeapons.size(); i++){
        if(shipWeapons.at(i).empty){
            continue;
        }

        for(unsigned int j = 0; j < shipWeapons.at(i).weaponPower.size(); j++){
            firepower+= shipWeapons.at(i).weaponPower.at(j);
        }
        if(firepower < leastPowerful || firstShip){
            leastPowerful = firepower;
            leastPowerIndex = i;
            firstShip = false;
        }

        firepower = 0;
    }
    return leastPowerIndex;
}
vector<int> printUnarmed(vector<Weapon> shipWeapons){
    vector<int> unarmedShips;
    for(unsigned int i = 0; i < shipWeapons.size(); i++){
        if(shipWeapons.at(i).empty){
            unarmedShips.push_back(i);
        }
    }

    return unarmedShips;
}