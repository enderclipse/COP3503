#include <iostream>

//Standard functions
using std::cin;
using std::cout;
using std::endl;

int main(){
    //Needed variables
    int num;

    //Prompting for and storing input for number of students
    cout << "Enter the number of students: ";
    cin >> num;
    int scores[num];
    char grades[num];

    //Prompting for input of scores
    cout << "Enter " << num << " scores: ";

    int best = -1;

    //Finding the best score
    for (int i = 0; i < num; i++){
        cin >> scores[i];
        if(best < scores[i]){
            best = scores[i];
        }
    }

    //Assigning grades to each student
    for(int i = 0; i < num; i++){
        for(int i=0;i<num;i++) {
			if (scores[i] >= best - 10)
				grades[i] = 'A';
			else if (scores[i] >= best - 20)
				grades[i] = 'B';
			else if (scores[i] >= best - 30)
				grades[i] = 'C';
			else if (scores[i] >= best - 40)
				grades[i] = 'D';
			else grades[i] = 'F';
    }

        //Printing the students information
        cout << "Student " << i+1 << " - Score: " << scores[i] 
            << ", Letter: " << grades[i] << endl;
    }
}