#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm> 

using namespace std;

class student {
public:
    long int reg;
    string name, branch;

    void input() {
        cout << "\nEnter name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter roll no: ";
        cin >> reg;

        cout << "Enter Branch: ";
        cin.ignore();
        getline(cin, branch);
    }

    void display() const {
        cout << "\nName - " << name;
        cout << "\nReg no. - " << reg;
        cout << "\nBranch - " << branch;
        cout << "\n";
    }

    bool operator==(const student& a) const {
        return (reg == a.reg);
    }

    // Convert student data to a string for writing to a text file
    string to_string() const {
        stringstream ss;
        ss << name << ' ' << reg << ' ' << branch;
        return ss.str();
    }

    // Initialize student data from a string read from a text file
    void from_string(const string& str) {
        stringstream ss(str);
        ss >> name >> reg >> branch;
    }
};

vector<student> v;

void get_file() {
    student x;
    ifstream file("College.txt");
    if (file.is_open()) {
        while (getline(file, x.name, ' ') && file >> x.reg >> x.branch) {
            v.push_back(x);
        }
        file.close();
    }
}

void write_to_file() {
    ofstream outFile("College.txt");
    if (outFile.is_open()) {
        for (const auto& student : v) {
            outFile << student.to_string() << '\n';
        }
        outFile.close();
        cout << "Data written to file successfully!\n";
    } else {
        cout << "Error opening file for writing!\n";
    }
}

void delete_data() {
    long int reg;
    cout << "\nEnter Reg. no.: ";
    cin >> reg;
    auto it = find(v.begin(), v.end(), student{reg, "", ""});
    if (it != v.end()) {
        v.erase(it);
        cout << "Student data deleted successfully!\n";
    } else {
        cout << "No such entry found\n";
    }
}

void edit_data() {
    long int reg;
    cout << "\nEnter Reg. no.: ";
    cin >> reg;
    auto it = find(v.begin(), v.end(), student{reg, "", ""});
    if (it != v.end()) {
        cout << "\nEnter new data:";
        it->input();
        cout << "Student data edited successfully!\n";
    } else {
        cout << "No such entry found\n";
    }
}

void search_and_show() {
    int ch;
    long int reg;
    vector<int> vi;
    vector<int> vj;

    cout << "\n1. Press to search reg no."
         << "\n2. Press to search name"
         << "\n3. Press to search branch";
    cin >> ch;

    switch (ch) 
    {
    case 1:
    {
        cout << "\nEnter reg no.: ";
        cin >> reg;
        auto it = find(v.begin(), v.end(), student{reg, "", ""});
        if (it != v.end()) {
            it->display();
        } else {
            cout << "Record NOT FOUND!!!";
        }
        break;
    }
    case 2:
    {
        string name;
        cout << "\nEnter name: ";
        cin.ignore();
        getline(cin, name);
        for (int i = 0; i < v.size(); i++) {
            if (v[i].name == name) {
                vi.push_back(i);
            }
        }
        if (!vi.empty()) {
            for (int j : vi) {
                v[j].display();
            }
        } else {
            cout << "Record NOT FOUND!!!";
        }
        break;
    }
    case 3:
    {
        string branch;
        cout << "\nEnter branch: ";
        cin.ignore();
        getline(cin, branch);
        for (int i = 0; i < v.size(); i++) {
            if (v[i].branch == branch) {
                vj.push_back(i);
            }
        }
        if (!vj.empty()) {
            for (int j : vj) {
                v[j].display();
            }
        } else {
            cout << "Record NOT FOUND!!!";
        }
        break;
    }
    default:
        cout << "Wrong CHOICE!!!";
    }
}

int main() {
    int choice;
    get_file();

    do {
        cout << "\n\t-----------------------------------------";
        cout << "\n\t     University Management System";
        cout << "\n\t-----------------------------------------";
        cout << "\n\t1. Add new student";
        cout << "\n\t2. Display student details";
        cout << "\n\t3. Remove student";
        cout << "\n\t4. Edit student details";
        cout << "\n\t5. Search student";
        cout << "\n\t6. Write data to a file";
        cout << "\n\tPress 0 to Exit\n";
        cout << "\n\t-----------------------------------------";
        cout << "\n\tEnter Your Choice: ";
        cin >> choice;

        switch (choice) 
        {
        case 1:
        {
            student newStudent;
            newStudent.input();
            v.push_back(newStudent);
            break;
        }
        case 2:
            cout << "\n\tDisplay Records";
            for (const auto& s : v) {
                s.display();
            }
            break;
        case 3:
            delete_data();
            break;
        case 4:
            edit_data();
            break;
        case 5:
            search_and_show();
            break;
        case 6:
            write_to_file();
            break;
        case 0:
            get_file();
            break;
        default:
            cout << "\nPlease enter a valid option";
        }
    } while (choice != 0);

    return 0;
}
