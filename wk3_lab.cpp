#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

const int MAX_SIZE = 10;
const int MAX_ASSIGN = 5;


void determineCoursework(int assignments[MAX_SIZE][MAX_ASSIGN], int mst[], int coursework[], int size);
void determineGrade(char grades[], int coursework[], int finals[], int size);
void discardLine(ifstream &input);
int getFailed(char grades[], int students);
void printStudentCoursework(string id[], int coursework[], char grades[], int final[], int size);
int totalAssignment(int assignments[MAX_SIZE][MAX_ASSIGN], int student);

int main() {
    string student_id[MAX_SIZE];
    int student_marks[MAX_SIZE];
    int student_assignments[MAX_SIZE][MAX_ASSIGN];
    int student_mst[MAX_SIZE];
    int student_final[MAX_SIZE];
    char student_grades[MAX_SIZE];
    int student_coursework[MAX_SIZE];

    ifstream in_file;
    in_file.open("students2.txt");

    if (!in_file) {
        cerr << "FILE FAILED TO OPEN.\nCheck that file is in the same folder as source code.\n";
        return 1;
    }

    discardLine(in_file);

    int num_students;
    int i = 0;

    while(in_file >> student_id[i]) {

        for (int j = 0; j < MAX_ASSIGN; j++) {
            in_file >> student_assignments[i][j];
        }
        in_file >> student_mst[i] >> student_final[i];

        i++;
    }
    num_students = i;

    determineCoursework(student_assignments, student_mst, student_coursework, num_students);
    determineGrade(student_grades, student_coursework, student_final, num_students);

    printStudentCoursework(student_id, student_coursework, student_grades, student_final, num_students);

    cout << endl << endl;
    cout << "Number Failed = " << getFailed(student_grades, num_students) << " out of " << num_students << " students.\n\n";

    return 0;
}

void determineCoursework(int assignments[MAX_SIZE][MAX_ASSIGN], int mst[], int coursework[], int size) {
    
    for (int i = 0; i < size; i++) {
        coursework[i] = totalAssignment(assignments, i) + mst[i];
    }
}

void determineGrade(char grades[], int coursework[], int finals[], int size) {
    int total;
    for (int i = 0; i < size; i++) {
        total = coursework[i] + finals[i];

        if (total >= 80) {
            grades[i] = 'A';
        } else if (total >= 65) {
            grades[i] = 'B';
        } else if (total >= 50) {
            grades[i] = 'C';
        } else {
            grades[i] = 'D';
        }
    }
}

void discardLine(ifstream &input) {
    char c;

    while (c != '\n' && input.get(c)) {
        
    }
}

int getFailed(char grades[], int students) {
    int failed = 0;
    for (int i = 0; i < students; i++) {
        if (grades[i] == 'D') {
            failed ++;
        }
    }
    return failed;
}

void printStudentCoursework(string id[], int coursework[], char grades[], int final[], int size) {
    cout << setw(10) << left << "ID" << right << setw(10) << "COURSEWORK " << setw(6) <<"FINAL" << setw(7) << "GRADE"<< endl << endl;
    for (int i = 0; i < size; i++) {
        cout << left << setw(10) << id[i] << right << setw(11) << coursework[i] << setw(7) << final[i] << setw(7) << grades[i]<< endl << left;
    }
}

int totalAssignment(int assignments[MAX_SIZE][MAX_ASSIGN], int student) {
    int total = 0;

    for (int i = 0; i < MAX_ASSIGN; i++) {
        total += assignments[student][i];
    }
    return total;
}
