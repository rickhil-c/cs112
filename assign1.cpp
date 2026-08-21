#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

struct Medicine{
    private:
        int id;
        string name;
        int units;

        bool validateUnits(int units);

    public:
        Medicine();

        // setters
        void setId(int id);
        void setName(string name);
        void setUnits(int units);

        // getters
        int getId();
        string getName();
        int getUnits();
};

Medicine::Medicine() {
    this->id = -1;
    this->name = "No Data";
    this->units = -1;
}

void Medicine::setId(int id) {
    this->id = id;
}

void Medicine::setName(string name) {
    this->name = name;
}

void Medicine::setUnits(int units) {

    if (validateUnits(units)) {
        this->units = units;
    }
}

int Medicine::getId() {
    return this->id;
}

string Medicine::getName() {
    return this->name;
}

int Medicine::getUnits() {
    return this->units;
}

bool Medicine::validateUnits(int units) {
    
    if (units < 0) {
        return false;
    }
    
    return true;
}

bool getMedData(int &id, string &name, int &units, ifstream &file);
string getStatus(Medicine m);
bool isInArray(Medicine arr[], int size, int id, int &index);
void validateId(Medicine arr[], int size);

const int MAX_SIZE = 20;

int main() {
    Medicine medicines[MAX_SIZE];
    Medicine *med;

    // Checking constructor functioning
    // for (int i = 0; i < MAX_SIZE; i++) {
    //     med = &medicines[i];
    //     cout << med->getId() << " " << med->getName() << " " << med->getUnits() << endl;
    // }

    // temporary containers
    int tid;
    string tname;
    int tunits;

    ifstream mdata("medicines.txt");

    if (!mdata) {
        cerr << "File failed to open.\n"
            << "Ensure file exists and is same directory as program.";
        
        return -1;
    }

    int total_records = 0;

    while (getMedData(tid, tname, tunits, mdata)) {
        med = &medicines[total_records];

        med->setId(tid);
        med->setName(tname);
        med->setUnits(tunits);

        total_records++;
    }

    return 0;
}

string getStatus(Medicine m) {
    int num = m.getUnits();

    if (num == 0) {
        return "Out of Stock";
    }

    return "Available";
}


// Function that extracts data for members of medicine
// Works for line formatted as id,name,units
bool getMedData(int &id, string &name, int &units, ifstream &file) {
    string s;
    int last;
    int start = 0;
    int stop = 0;
    int range;

    if (getline(file, s)) {
        last = s.length() - 1;

        for (int i = 0; i <= last; i++) {
            if (s[i] == ',') {
                id = stoi(s.substr(0, i));
                start = i + 1;
                break;
            }
        }

        for (int i = last; i > 0; i--) {
            if (s[i] == ',') {
                units = stoi(s.substr(i + 1, last - i));
                stop = i;
                break;
            }
        }

        range = stop - start;
        name = s.substr(start, range);
        return true;
    }
    return false;
}

void updateUnits(Medicine arr[], int size) {
    int units;
    int id = -1;
    int index = validateId(arr, size, id);

    if (index == -1) {
        return;
    }
    
    cout << "Enter updated units for medicine: ID: " << id << " Name: "
        << arr[index].getName() << endl;

    while (!(cin >> units)) {
        cin.clear();
        cin.ignore(1000, '\n');

        cout << "Please enter a valid whole number for units\n";

        if (shouldExit("units")) {
            return;
        }
    }
    arr[index].setUnits(units);
}

int validateId(Medicine arr[], int size, int &id) {
    int index = 0;
    char choice;
    
    cout << "Enter the Medicince ID:\n";

    while (true) {
        cin >> id;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            
            if (shouldExit("ID")) {
                return -1;
            }

            continue;
        }

        if (isInArray(arr,size, id, index)) {
            break;
        }

        cout << "No Medicine ID matches " << id << endl;
        
        if (shouldExit("ID")) {
            return -1;
        }
    }

    return index;
}

// Function to check whether or not input id is inside Medicine array
bool isInArray(Medicine arr[], int size, int id, int &index) {

    for (int i = 0; i < size; i++) {

        if (id == arr[i].getId()) {
            index = i;
            return true;
        }
    }
    return false;
}

bool shouldExit(string item) {
    char choice = 'n';
    bool do_exit = (choice == 'N' || choice == 'n');

    cout << "Enter " << item << " again?\n Enter N to exit or any other letter to continue" << endl;
    cin >> choice;

    cin.ignore(1000, '\n');
    
    return do_exit;
}
