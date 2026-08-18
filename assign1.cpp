#include <iostream>
#include <fstream>
#include <string>

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

string getStatus(Medicine m) {
    int num = m.getUnits();

    if (num == 0) {
        return "Out of Stock";
    }

    return "Available";
}

bool getMedData(int &id, string &name, int &units, ifstream &file);

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

bool getMedData(int &id, string &name, int &units, ifstream &file) {
    string s;
    int last;
    int start;
    int stop;
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
