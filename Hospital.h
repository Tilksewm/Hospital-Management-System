#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
#include <list>
#include <fstream>
#include <limits>
#include <ctime>

#include "Patient.h"
#include "Doctor.h"
#include "Appointment.h"
#include "LinkedList.h"
#include "MergeSort.h"
#include "Department.h"

class Hospital {
public:
    Hospital();
    void loadData();
    void saveData();
    void initializeData();

    // Manager Functions
    void addDepartment(const std::string& name);
    void addDoctor(const std::string& departmentName, const std::string& name, const std::string& sex, int age);
    void removeDoctor(const std::string& departmentName, int doctorId);
    void findDoctorByDepartment(const std::string& departmentName);
    void generatePatientLoadReport();

    // Receptionist Functions
    void addNewAppointment(const std::string& name, int age, const std::string& sex, const std::string& contact);
    void addExistingAppointment(int patientId);
    void searchPatientByName(const std::string& name);

    // Assembler Functions
    void getNextAppointmentForAssembly();

    // Pharmacist Functions
    void giveMedicine();
    void recordNewInventory(const std::string& medicineName, int amount, double price, std::string expiryDate);
    void getNextToExpiredMedicine();
    void displaySortedMedicineList();

    // Doctor Functions
    void doctorLogin();

    // Helpers
    void clearScreen() const;
    void waitEnter() const;

private:
    std::unordered_map<std::string, Department> departments;
    std::unordered_map<int, Patient> patients;
    std::queue<Appointment> preAssemblerQueue;
    std::priority_queue<Appointment, std::vector<Appointment>, AppointmentComparator> postAssemblerQueue;
    std::queue<Appointment> pharmacyQueue;

    LinkedList inventory;
    // Private helper for Doctor Functions
    void processDoctorAppointment(int doctorId);
    Doctor* findDoctorById(int doctorId);

    // A map to store medicine prices
    std::unordered_map<std::string, double> medicinePrices;

    // Counters for unique IDs
    int patientIdCounter;
    int doctorIdCounter;

    // Private helper for serialization/deserialization
    void savePatients();
    void loadPatients();
    void saveDepartments();
    void loadDepartments();
    void saveQueues();
    void loadQueues();
    void savePreAssemblerQueue();
    void loadPreAssemblerQueue();

};

#endif
