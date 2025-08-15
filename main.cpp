#include <iostream>
#include "Hospital.h"

void displayMainMenu() {
    std::cout << "\n--- Hospital Management System ---\n";
    std::cout << "1) Manager\n";
    std::cout << "2) Receptionist\n";
    std::cout << "3) Assembler\n";
    std::cout << "4) Doctor\n";
    std::cout << "5) Pharmacist\n";
    std::cout << "6) Exit\n";
    std::cout << "Enter your choice: ";
}

void displayManagerMenu() {
    std::cout << "\n--- Manager Menu ---\n";
    std::cout << "1) Add a department\n";
    std::cout << "2) Add a doctor\n";
    std::cout << "3) Remove a doctor\n";
    std::cout << "4) Find a doctor\n";
    std::cout << "5) Generate a report\n";
    std::cout << "6) Back to Main Menu\n";
    std::cout << "Enter your choice: ";
}

void displayReceptionistMenu() {
    std::cout << "\n--- Receptionist Menu ---\n";
    std::cout << "1) Add New Appointment\n";
    std::cout << "2) Add Appointment for Existing Patient\n";
    std::cout << "3) Search by name\n";
    std::cout << "4) Back to Main Menu\n";
    std::cout << "Enter your choice: ";
}

void displayPharmacistMenu() {
    std::cout << "\n--- Pharmacist Menu ---\n";
    std::cout << "1) Give medicine\n";
    std::cout << "2) Record new inventory\n";
    std::cout << "3) Get next to expired medicine\n";
    std::cout << "4) Display Medicine sorted by name\n";
    std::cout << "5) Back to Main Menu\n";
    std::cout << "Enter your choice: ";
}
int main() {
    Hospital hospital;
    //hospital.loadData();
    hospital.initializeData();
    hospital.waitEnter();

    char choice;
    while (true) {
        hospital.clearScreen();
        displayMainMenu();
        std::cin >> choice;
        hospital.clearScreen();

        switch (choice) {
            case '1': { // Manager
                managerMenu:
                hospital.clearScreen();
                char subChoice;
                std::cout << "Manager Menu\n";
                displayManagerMenu();
                std::cin >> subChoice;
                hospital.clearScreen();

                if (subChoice == '1') {
                    std::string deptName;
                    std::cout << "Enter department name: ";
                    std::cin >> deptName;
                    hospital.addDepartment(deptName);
                    hospital.waitEnter();
                    hospital.clearScreen();
                    goto managerMenu;
                } else if (subChoice == '2') {
                    std::string deptName, docName, sex;
                    int age;
                    std::cout << "Enter department name: ";
                    std::cin >> deptName;
                    std::cout << "Enter doctor's name: ";
                    std::cin.ignore();
                    std::getline(std::cin, docName);
                    std::cout << "Enter doctor's sex (male/female: ";
                    std::cin >> sex;
                    std::cout << "Enter doctor's age: ";
                    std::cin >> age;
                    hospital.addDoctor(deptName, docName, sex, age);
                    hospital.waitEnter();
                    hospital.clearScreen();
                    goto managerMenu;
                } else if (subChoice == '3') {
                    std::string deptName;
                    int docId;
                    std::cout << "Enter department name: ";
                    std::cin >> deptName;
                    std::cout << "Enter doctor ID to remove: ";
                    std::cin >> docId;
                    hospital.removeDoctor(deptName, docId);
                    hospital.waitEnter();
                    hospital.clearScreen();
                    goto managerMenu;
                } else if (subChoice == '4') {
                    std::string deptName;
                    std::cout << "Enter department name to find doctors: ";
                    std::cin >> deptName;
                    hospital.findDoctorByDepartment(deptName);
                    hospital.waitEnter();
                    hospital.clearScreen();
                    goto managerMenu;
                } else if (subChoice == '5') {
                    hospital.generatePatientLoadReport();
                    hospital.waitEnter();
                    hospital.clearScreen();
                    goto managerMenu;
                } else if (subChoice == '6') {
                    // Back to main menu
                    continue;
                } else {
                    std::cout << "Invalid choice.\n";
                    hospital.waitEnter();
                    hospital.clearScreen();
                    goto managerMenu;
                }
                hospital.waitEnter();
                break;
            }
            case '2': { // Receptionist
                receptionistMenu:
                char subChoice;
                displayReceptionistMenu();
                std::cin >> subChoice;
                hospital.clearScreen();

                if (subChoice == '1') {
                    std::string name, sex, contact;
                    int age;
                    std::cout << "Enter new patient's name: ";
                    std::cin.ignore();
                    std::getline(std::cin, name);
                    std::cout << "Enter age: ";
                    std::cin >> age;
                    std::cout << "Enter sex: ";
                    std::cin >> sex;
                    std::cout << "Enter contact number: ";
                    std::cin.ignore();
                    std::getline(std::cin, contact);
                    hospital.addNewAppointment(name, age, sex, contact);
                    hospital.waitEnter();
                    hospital.clearScreen();
                    goto receptionistMenu;
                } else if (subChoice == '2') {
                    int patientId;
                    std::cout << "Enter existing patient ID: ";
                    std::cin >> patientId;
                    hospital.addExistingAppointment(patientId);
                    hospital.waitEnter();
                    hospital.clearScreen();
                    goto receptionistMenu;
                } else if (subChoice == '3') {
                    std::string name;
                    std::cout << "Enter patient name to search: ";
                    std::cin.ignore();
                    std::getline(std::cin, name);
                    hospital.searchPatientByName(name);
                    hospital.waitEnter();
                    hospital.clearScreen();
                    goto receptionistMenu;
                } else if (subChoice == '4') {
                    // Back to main menu
                    continue;
                } else {
                    std::cout << "Invalid choice.\n";
                    hospital.waitEnter();
                    hospital.clearScreen();
                    goto receptionistMenu;
                }
                hospital.waitEnter();
                break;
            }
            case '3': { // Assembler
                hospital.getNextAppointmentForAssembly();
                hospital.waitEnter();
                break;
            }
            case '4': { // Doctors
                hospital.doctorLogin();
                hospital.waitEnter();
                break;
            }
            case '5': { // Pharmacist
                pharmacistMenu:
                char subChoice;
                displayPharmacistMenu();
                std::cin >> subChoice;
                hospital.clearScreen();

                if (subChoice == '1') {
                    hospital.giveMedicine();
                    hospital.waitEnter();
                    hospital.clearScreen();
                    goto pharmacistMenu;
                } else if (subChoice == '2') {
                    std::string medicineName, expiryDate;
                    int amount;
                    double price;
                    std::cout << "Enter medicine name: ";
                    std::cin.ignore();
                    std::getline(std::cin, medicineName);
                    std::cout << "Enter amount: ";
                    std::cin >> amount;
                    std::cout << "Enter price per unit: ";
                    std::cin >> price;
                    std::cout << "Enter expiry date (YYYY-MM-DD): ";
                    std::cin >> expiryDate;

                    hospital.recordNewInventory(medicineName, amount, price, expiryDate);
                    hospital.waitEnter();
                    hospital.clearScreen();
                    goto pharmacistMenu;
                } else if (subChoice == '3') {
                    hospital.getNextToExpiredMedicine();
                    hospital.waitEnter();
                    hospital.clearScreen();
                    goto pharmacistMenu;
                }else if (subChoice == '4') {
                    hospital.displaySortedMedicineList();
                    hospital.waitEnter();
                    hospital.clearScreen();
                    goto pharmacistMenu;
                } else if (subChoice == '5') {
                    continue;
                } else {
                    std::cout << "Invalid choice.\n";
                    hospital.waitEnter();
                    hospital.clearScreen();
                    goto pharmacistMenu;
                }
                hospital.waitEnter();
                break;
            }
            case '6':
                std::cout << "Exiting system...\n";
                //hospital.saveData();
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                hospital.waitEnter();
                break;
        }
    }
    return 0;
}
