#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
using namespace std;

class Employee {
private:
    string name;
    int idNumber;
    string department;
    string position;
    double salary;

public:
    Employee() : name(""), idNumber(0), department(""), position(""), salary(0.0) {}

    Employee(const string& empName, int empId)
        : name(empName), idNumber(empId), department(""), position(""), salary(0.0) {}

    Employee(const string& empName, int empId, const string& empDept, const string& empPos, double empSalary)
        : name(empName), idNumber(empId), department(empDept), position(empPos), salary(empSalary) {}

    void setName(const string& empName) { name = empName; }
    void setIdNumber(int empId) { idNumber = empId; }
    void setDepartment(const string& empDept) { department = empDept; }
    void setPosition(const string& empPos) { position = empPos; }
    void setSalary(double empSalary) { salary = empSalary; }

    string getName() const { return name; }
    int getIdNumber() const { return idNumber; }
    string getDepartment() const { return department; }
    string getPosition() const { return position; }
    double getSalary() const { return salary; }

    void saveToCSV(const string& fileName) const {
        ofstream outFile(fileName, ios::app);
        if (!outFile) {
            cerr << "Error opening file for writing.\n";
            return;
        }
        outFile << name << "," << idNumber << "," << department << "," << position << "," << salary << "\n";
        outFile.close();
    }

    static void printCSV(const string& fileName) {
        ifstream inFile(fileName);
        if (!inFile) {
            cerr << "Error opening file for reading.\n";
            return;
        }

        string line;
        bool isHeader = true;

        cout << left << setw(15) << "Name"
                  << setw(12) << "ID Number"
                  << setw(15) << "Department"
                  << setw(12) << "Position"
                  << setw(10) << "Salary" << "\n";
        cout << string(65, '-') << "\n";

        while (getline(inFile, line)) {
            if (isHeader) {
                isHeader = false;
                continue;
            }

            stringstream ss(line);
            string name, idNumber, department, position, salary;

            getline(ss, name, ',');
            getline(ss, idNumber, ',');
            getline(ss, department, ',');
            getline(ss, position, ',');
            getline(ss, salary, ',');

            cout << left << setw(15) << name
                      << setw(12) << idNumber
                      << setw(15) << department
                      << setw(12) << position
                      << setw(10) << salary << "\n";
        }
        inFile.close();
    }
};

void initializeCSV(const string& fileName) {
    ofstream outFile(fileName, ios::app);
    if (outFile.tellp() == 0) {
        outFile << "Name,ID Number,Department,Position,Salary\n";
    }
    outFile.close();
}

int main() {
    const string fileName = "employees.csv";
    initializeCSV(fileName);

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Add Employee\n";
        cout << "2. Print Employee Table\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            cin.ignore();
            string name, department, position;
            int idNumber;
            double salary;

            cout << "Enter Employee Name: ";
            getline(cin, name);
            cout << "Enter Employee ID: ";
            cin >> idNumber;
            cin.ignore();
            cout << "Enter Employee Department: ";
            getline(cin, department);
            cout << "Enter Employee Position: ";
            getline(cin, position);
            cout << "Enter Employee Salary: ";
            cin >> salary;

            Employee emp(name, idNumber, department, position, salary);
            emp.saveToCSV(fileName);

            cout << "Employee added successfully!\n";
        } else if (choice == 2) {
            cout << "\nEmployee Table:\n";
            Employee::printCSV(fileName);
        } else if (choice == 3) {
            cout << "Exiting program.\n";
            break;
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }
    return 0;
}
