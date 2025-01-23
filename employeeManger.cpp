#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
using namespace std;

class Employee {
private:
    std::string name;
    int idNumber;
    std::string department;
    std::string position;
    double salary;

public:
    Employee() : name(""), idNumber(0), department(""), position(""), salary(0.0) {}

    Employee(const std::string& empName, int empId)
        : name(empName), idNumber(empId), department(""), position(""), salary(0.0) {}

    Employee(const std::string& empName, int empId, const std::string& empDept, const std::string& empPos, double empSalary)
        : name(empName), idNumber(empId), department(empDept), position(empPos), salary(empSalary) {}

    void setName(const std::string& empName) { name = empName; }
    void setIdNumber(int empId) { idNumber = empId; }
    void setDepartment(const std::string& empDept) { department = empDept; }
    void setPosition(const std::string& empPos) { position = empPos; }
    void setSalary(double empSalary) { salary = empSalary; }

    std::string getName() const { return name; }
    int getIdNumber() const { return idNumber; }
    std::string getDepartment() const { return department; }
    std::string getPosition() const { return position; }
    double getSalary() const { return salary; }

    void saveToCSV(const std::string& fileName) const {
        std::ofstream outFile(fileName, std::ios::app);
        if (!outFile) {
            std::cerr << "Error opening file for writing.\n";
            return;
        }
        outFile << name << "," << idNumber << "," << department << "," << position << "," << salary << "\n";
        outFile.close();
    }

    static void printCSV(const std::string& fileName) {
        std::ifstream inFile(fileName);
        if (!inFile) {
            std::cerr << "Error opening file for reading.\n";
            return;
        }

        std::string line;
        bool isHeader = true;

        std::cout << std::left << std::setw(15) << "Name"
                  << std::setw(12) << "ID Number"
                  << std::setw(15) << "Department"
                  << std::setw(12) << "Position"
                  << std::setw(10) << "Salary" << "\n";
        std::cout << std::string(65, '-') << "\n";

        while (std::getline(inFile, line)) {
            if (isHeader) {
                isHeader = false;
                continue;
            }

            std::stringstream ss(line);
            std::string name, idNumber, department, position, salary;

            std::getline(ss, name, ',');
            std::getline(ss, idNumber, ',');
            std::getline(ss, department, ',');
            std::getline(ss, position, ',');
            std::getline(ss, salary, ',');

            std::cout << std::left << std::setw(15) << name
                      << std::setw(12) << idNumber
                      << std::setw(15) << department
                      << std::setw(12) << position
                      << std::setw(10) << salary << "\n";
        }
        inFile.close();
    }
};

void initializeCSV(const std::string& fileName) {
    std::ofstream outFile(fileName, std::ios::app);
    if (outFile.tellp() == 0) {
        outFile << "Name,ID Number,Department,Position,Salary\n";
    }
    outFile.close();
}

int main() {
    const std::string fileName = "employees.csv";
    initializeCSV(fileName);

    while (true) {
        std::cout << "\nMenu:\n";
        std::cout << "1. Add Employee\n";
        std::cout << "2. Print Employee Table\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        if (choice == 1) {
            std::cin.ignore();
            std::string name, department, position;
            int idNumber;
            double salary;

            std::cout << "Enter Employee Name: ";
            std::getline(std::cin, name);
            std::cout << "Enter Employee ID: ";
            std::cin >> idNumber;
            std::cin.ignore();
            std::cout << "Enter Employee Department: ";
            std::getline(std::cin, department);
            std::cout << "Enter Employee Position: ";
            std::getline(std::cin, position);
            std::cout << "Enter Employee Salary: ";
            std::cin >> salary;

            Employee emp(name, idNumber, department, position, salary);
            emp.saveToCSV(fileName);

            std::cout << "Employee added successfully!\n";
        } else if (choice == 2) {
            std::cout << "\nEmployee Table:\n";
            Employee::printCSV(fileName);
        } else if (choice == 3) {
            std::cout << "Exiting program.\n";
            break;
        } else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }
    return 0;
}