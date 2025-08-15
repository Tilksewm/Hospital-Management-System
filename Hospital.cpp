#include "Hospital.h"

Hospital::Hospital() : patientIdCounter(1), doctorIdCounter(1) {}

// Helper function to generate a timestamp (for appointments)
std::string getCurrentTime() {
    std::time_t now = std::time(nullptr);
    char buf[100];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %X", std::localtime(&now));
    return buf;
}

// initializing sample Data
void Hospital::initializeData() {
    // Check if data is already loaded to avoid overwriting
    if (!departments.empty() || !patients.empty() || !preAssemblerQueue.empty() || !pharmacyQueue.empty()) {
        std::cout << "Data already exists. Skipping initialization.\n";
        return;
    }

    std::cout << "Initializing system with sample data...\n";

    // 1. Add departments
    addDepartment("Cardiology");
    addDepartment("Orthopedics");
    addDepartment("Pediatrics");

    // 2. Add doctors
    // Cardiology
    addDoctor("Cardiology", "Alemayehu Bogale", "Male", 45);
    addDoctor("Cardiology", "Aster Lema", "Female", 50);
    // Orthopedics
    addDoctor("Orthopedics", "belay Shibru", "Male", 38);
    addDoctor("Orthopedics", "Kidist Mulugeta", "Female", 42);
    // Pediatrics
    addDoctor("Pediatrics", "Chaltu Derese", "Female", 35);
    addDoctor("Pediatrics", "Abdi Mohamed", "Male", 40);

    // 3. Add patient history data
    for (int i = 1; i <= 12; ++i) {
        patients[i] = Patient(i, "Patient " + std::to_string(i), 30 + i, (i % 2 == 0 ? "Male" : "Female"), "123-456-7890");
        patients[i].addAllergy("Pollen");
        patients[i].addHistory("Initial check-up.");
        patients[i].addHistory("Follow-up visit. Diagnosed with common cold. Prescribed: Paracetamol.");
    }

    // 4. Add current appointments to the pre-assembler queue
    for (int i = 13; i <= 24; ++i) {
        patients[i] = Patient(i, "Current Patient " + std::to_string(i-12), 25 + (i-12), (i % 2 == 0 ? "Male" : "Female"), "987-654-3210");
        preAssemblerQueue.push(Appointment(i, getCurrentTime()));
    }

    // 5. Add medicine inventory
    recordNewInventory("Paracetamol", 50, 10, "2026-05-05");
    recordNewInventory("Ibuprofen", 75, 15, "2026-05-19");
    recordNewInventory("Amoxicillin", 30, 20, "2026-05-27");
    recordNewInventory("Loratadine", 100, 10, "2026-07-13");
    recordNewInventory("Metformin", 60, 25, "2026-10-22");
    recordNewInventory("Losartan", 40, 30, "2026-03-25");

    std::cout << "Initialization complete. The system is ready to use.\n";
}

// =======================================================
// Manager Functions
// =======================================================

void Hospital::addDepartment(const std::string& name) {
    if (departments.find(name) == departments.end()) {
        departments[name] = Department();
        std::cout << "Department '" << name << "' added successfully.\n";
    } else {
        std::cout << "Error: Department '" << name << "' already exists.\n";
    }
}

void Hospital::addDoctor(const std::string& departmentName, const std::string& name, const std::string& sex, int age) {
    auto it = departments.find(departmentName);
    if (it != departments.end()) {
        Doctor newDoctor(doctorIdCounter++, name, sex, age, departmentName);
        it->second.doctors.push_back(newDoctor); // Add to the Department's doctor list
        std::cout << "Doctor '" << name << "' added to department '" << departmentName << "'. ID: " << newDoctor.id << "\n";
    } else {
        std::cout << "Error: Department '" << departmentName << "' not found.\n";
    }
}

void Hospital::generatePatientLoadReport() {
    std::cout << "--- Patient Load Report (Now) ---\n";
    for (const auto& pair : departments) {
        std::cout << pair.first << ": " << pair.second.appointments.size() << " patients in queue\n";
    }
    std::cout << "-----------------------------------\n";
}

void Hospital::removeDoctor(const std::string& departmentName, int doctorId) {
    auto it = departments.find(departmentName);
    if (it != departments.end()) {
        std::list<Doctor>& doctors = it->second.doctors; // Access the list of doctors from the Department object
        for (auto doc_it = doctors.begin(); doc_it != doctors.end(); ++doc_it) {
            if (doc_it->id == doctorId) {
                std::cout << "Doctor '" << doc_it->name << "' with ID " << doctorId << " removed from '" << departmentName << "'.\n";
                doctors.erase(doc_it);
                return;
            }
        }
        std::cout << "Error: Doctor with ID " << doctorId << " not found in department '" << departmentName << "'.\n";
    } else {
        std::cout << "Error: Department '" << departmentName << "' not found.\n";
    }
}

void Hospital::findDoctorByDepartment(const std::string& departmentName) {
    auto it = departments.find(departmentName);
    if (it != departments.end()) {
        std::cout << "Doctors in " << departmentName << " department:\n";
        std::list<Doctor>& doctors = it->second.doctors; // Access the list of doctors
        if (doctors.empty()) {
            std::cout << "  No doctors in this department.\n";
        } else {
            for (const auto& doctor : doctors) {
                doctor.displayInfo();
            }
        }
    } else {
        std::cout << "Error: Department '" << departmentName << "' not found.\n";
    }
}
// =======================================================
// Receptionist Functions
// =======================================================

void Hospital::addNewAppointment(const std::string& name, int age, const std::string& sex, const std::string& contact) {
    // Generate a unique patient ID and create a new Patient object
    int newPatientId = patientIdCounter++;
    Patient newPatient(newPatientId, name, age, sex, contact);
    patients[newPatientId] = newPatient;

    // Get current time for appointment registration
    std::time_t now = std::time(nullptr);
    std::string registrationTime = std::ctime(&now);

    // Create a new Appointment and push it to the pre-assembler queue
    Appointment newAppointment(newPatientId, registrationTime);
    preAssemblerQueue.push(newAppointment);

    std::cout << "New patient '" << name << "' registered with ID: " << newPatientId << ".\n";
    std::cout << "Appointment added to the queue for assembly.\n";
}

void Hospital::addExistingAppointment(int patientId) {
    auto it = patients.find(patientId);
    if (it != patients.end()) {
        it->second.displayInfo(); // Display patient info for confirmation
        std::cout << "Do you want to confirm this appointment? (y/n): ";
        char confirm;
        std::cin >> confirm;

        if (confirm == 'y' || confirm == 'Y') {
            std::time_t now = std::time(nullptr);
            std::string registrationTime = std::ctime(&now);

            Appointment newAppointment(patientId, registrationTime);
            preAssemblerQueue.push(newAppointment);
            std::cout << "Appointment for patient '" << it->second.name << "' confirmed and added to the queue.\n";
        } else {
            std::cout << "Appointment cancelled.\n";
        }
    } else {
        std::cout << "Error: Patient with ID " << patientId << " not found.\n";
    }
}

void Hospital::searchPatientByName(const std::string& name) {
    std::cout << "Searching for patients with name '" << name << "'...\n";
    std::vector<int> matchingIds;

    // Iterate through the unordered_map to find matching names
    for (const auto& pair : patients) {
        if (pair.second.name.find(name) != std::string::npos) {
            matchingIds.push_back(pair.first);
        }
    }

    if (matchingIds.empty()) {
        std::cout << "No patients found with that name.\n";
        return;
    }

    std::cout << "Found " << matchingIds.size() << " matching patients:\n";
    for (size_t i = 0; i < matchingIds.size(); ++i) {
        const Patient& patient = patients[matchingIds[i]];
        std::cout << i + 1 << ") ID: " << patient.id << ", Name: " << patient.name << ", Age: " << patient.age << "\n";
    }

    if (matchingIds.size() > 1) {
        int choice;
        std::cout << "Choose the correct patient by number: ";
        std::cin >> choice;
        if (choice > 0 && choice <= matchingIds.size()) {
            patients[matchingIds[choice - 1]].displayInfo();
        } else {
            std::cout << "Invalid choice.\n";
        }
    } else {
        patients[matchingIds[0]].displayInfo();
    }
}

// =======================================================
// Assembler Functions
// =======================================================
void Hospital::getNextAppointmentForAssembly() {
    assembler:
    if (preAssemblerQueue.empty()) {
        std::cout << "No appointments in the queue for assembly.\n";
        return;
    }

    Appointment currentAppointment = preAssemblerQueue.front();

    auto patient_it = patients.find(currentAppointment.patientId);
    if (patient_it == patients.end()) {
        std::cout << "Error: Patient not found for the next appointment.\n";
        return;
    }

    Patient& currentPatient = patient_it->second;
    std::cout << "Next appointment for assembly:\n";
    currentPatient.displayInfo();
    currentAppointment.displayDetails();

    std::cout << "\n--- Action Menu ---\n";
    std::cout << "1) Take this appointment\n";
    std::cout << "2) Go back to menu\n";
    std::cout << "Enter your choice: ";
    char choice;
    std::cin >> choice;

    if (choice == '1' ) {
            std::cout << "\n--- Assembler Process ---\n";
    std::cout << "Record the following details:\n";

    int priority, bp, hr;
    std::string category;

    // Get priority and category from user
    std::cout << "Enter priority level (1=highest, 5=lowest): ";
    std::cin >> priority;
    currentAppointment.priorityLevel = priority;
    // Record Blood Pressure and Heart Rate
    std::cout << "Enter blood pressure: ";
    std::cin >> bp;
    currentAppointment.bloodPressure = bp;

    std::cout << "Enter heart rate: ";
    std::cin >> hr;
    currentAppointment.heartRate = hr;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Enter category (e.g., Cardiology, Orthopedics): ";
    std::getline(std::cin, category);
    currentAppointment.category = category;

    auto dept_it = departments.find(category);
    if (dept_it != departments.end()) {
        dept_it->second.appointments.push(currentAppointment);
        std::cout << "\nAppointment for patient '" << currentPatient.name << "' has been prioritized and moved to the '" << category << "' department queue.\n";
        preAssemblerQueue.pop();
        waitEnter();
        clearScreen();
        goto assembler;
    } else {
        std::cout << "Error: Department '" << category << "' not found. Appointment not assigned to a doctor's queue.\n";
        waitEnter();
        clearScreen();
        goto assembler;
    }
    } else if (choice == '2'){

    }else {
        std::cout << "Invalid choice. \n";
        waitEnter();
        clearScreen();
        goto assembler;
    }

}

// =======================================================
// Doctor Functions
// =======================================================
Doctor* Hospital::findDoctorById(int doctorId) {
    for (auto& deptPair : departments) {
        for (auto& doctor : deptPair.second.doctors) {
            if (doctor.id == doctorId) {
                return &doctor;
            }
        }
    }
    return nullptr;
}

void Hospital::processDoctorAppointment(int doctorId) {
    Doctor* doctor = findDoctorById(doctorId);
    if (!doctor) {
        std::cout << "Error: Doctor with ID " << doctorId << " not found.\n";
        return;
    }
    doctor:

    std::cout << "\nWelcome, Dr. " << doctor->name << " (" << doctor->department << ")!\n";

    auto dept_it = departments.find(doctor->department);
    if (dept_it == departments.end()) {
        std::cout << "Error: Doctor's department not found.\n";
        return;
    }

    Department& doctorDept = dept_it->second;
    if (doctorDept.appointments.empty()) {
        std::cout << "No appointments available in your department's queue.\n";
        return;
    }

    Appointment nextApp = doctorDept.appointments.top();
    auto patientIt = patients.find(nextApp.patientId);

    if (patientIt == patients.end()) {
        std::cout << "Error: Patient for next appointment not found. Skipping.\n";
        doctorDept.appointments.pop();// Remove the bad appointment
        return;
    }

    Patient& patient = patientIt->second;
    std::cout << "\nNext appointment details:\n";
    patient.displayInfo();
    nextApp.displayDetails();

    std::cout << "\n--- Action Menu ---\n";
    std::cout << "1) Take this appointment\n";
    std::cout << "2) Go back to menu\n";
    std::cout << "Enter your choice: ";
    char choice;
    std::cin >> choice;

    if (choice == '1' ) {

        clearScreen();
        std::cout << "\n--- Patient Consultation for Dr. " << doctor->name << " ---\n";
        patient.displayInfo();
        std::cout << "\n--- Patient History and Allergies ---\n";

        std::cout << "Allergies: ";
        if (patient.allergies.empty()) {
            std::cout << "Unknown\n";
        } else {
            for (const auto& allergy : patient.allergies) {
                std::cout << allergy << ", ";
            }
            std::cout << "\n";
        }

        std::cout << "History: ";
        if (patient.history.empty()) {
            std::cout << "Unknown\n";
        } else {
            for (const auto& entry : patient.history) {
                std::cout << entry << "; ";
            }
            std::cout << "\n";
        }

        std::cout << "\nRecord new diagnoses, treatments, and prescriptions:\n";
        std::string diagnosis, treatment, prescription;
        std::cin.ignore();
        std::cout << "Diagnosis: ";
        std::getline(std::cin, diagnosis);
        std::cout << "Treatment: ";
        std::getline(std::cin, treatment);
        std::cout << "Prescription list (comma-separated): ";
        std::getline(std::cin, prescription);

        // Add new information to patient's history
        patient.addHistory("Diagnosis: " + diagnosis + " | Treatment: " + treatment + " | Prescription: " + prescription);

        pharmacyQueue.push(nextApp);
        doctorDept.appointments.pop();
        std::cout << "\nPatient records updated. The patient has been sent to the pharmacy.\n";

        waitEnter();
        clearScreen();
        goto doctor;

    } else if (choice == '2' ) {
        std::cout << "Returning to the main menu.\n";
    } else {
        std::cout << "Invalid choice.\n";
        waitEnter();
        clearScreen();
        goto doctor;
    }
}
void Hospital::doctorLogin() {
    int doctorId;
    std::cout << "Enter doctor ID: ";
    std::cin >> doctorId;
    processDoctorAppointment(doctorId);
}
// =======================================================
// Pharmacist Functions
// =======================================================

void Hospital::giveMedicine() {
    if (pharmacyQueue.empty()) {
        std::cout << "No patients waiting in the pharmacy queue.\n";
        return;
    }
    // Get the next patient from the pharmacy queue
    Appointment currentAppointment = pharmacyQueue.front();

    auto patient_it = patients.find(currentAppointment.patientId);
    if (patient_it == patients.end()) {
        std::cout << "Error: Patient for this appointment not found. Skipping.\n";
        return;
    }

    Patient& patient = patient_it->second;
    std::cout << "--- Prescription for Patient ID: " << patient.id << " ---\n";
    patient.displayInfo();
    std::cout << "Prescription List:\n";

    // Find the last history entry which should contain the prescription
    std::string lastHistoryEntry = patient.history.back();
    std::string prescriptionList;
    size_t pos = lastHistoryEntry.find("Prescription: ");
    if (pos != std::string::npos) {
        prescriptionList = lastHistoryEntry.substr(pos + 14);
        std::cout << prescriptionList << "\n";
    } else {
        std::cout << "No prescription found for this patient.\n";
        return;
    }

    std::cout << "\n1) Generate Bill\n";
    std::cout << "2) Cancel\n";
    std::cout << "Enter your choice: ";
    char choice;
    std::cin >> choice;

    if (choice == '1') {
        // Generate Bill
        double totalCost = 100.0; // Placeholder for consultancy fee
        std::cout << "\n--- Final Bill ---\n";
        std::cout << "Consultancy Fee: $100.00\n";

        std::vector<std::string> prescriptions;
        std::stringstream ss(prescriptionList);
        std::string medicineName;

        while (std::getline(ss, medicineName, ',')) {

            if (medicinePrices.find(medicineName) != medicinePrices.end()) {
                double price = medicinePrices[medicineName];
                totalCost += price;
                std::cout << medicineName << ": $" << price << "\n";
            } else {
                std::cout << "Warning: Price for '" << medicineName << "' not found in inventory.\n";
            }
        }

        std::stringstream ssPrescription(prescriptionList);

        while (std::getline(ssPrescription, medicineName, ',')) {
            Node* medicineNode = inventory.find(medicineName);
            if (medicineNode) {
                medicineNode->data.amount--;
                std::cout << "Decreased amount of '" << medicineName << "'. New amount: " << medicineNode->data.amount << "\n";
                if (medicineNode->data.amount <= 0) {
                    inventory.remove(medicineName);
                    std::cout << "'" << medicineName << "' is now out of stock and removed from inventory.\n";
                }
            }
        }


        std::cout << "--------------------\n";
        std::cout << "Total Amount Due: $" << totalCost << "\n";

        std::cout << "\nPatient process is complete. Bill generated.\n";
        pharmacyQueue.pop();
    } else if (choice == '2') {
        std::cout << "Process cancelled.\n";
    }
}
void Hospital::recordNewInventory(const std::string& medicineName, int amount, double price, std::string expiryDate) {

    Medicine newMed(medicineName, expiryDate, amount, price);
    inventory.add(newMed);
    medicinePrices[medicineName] = price;

    std::cout << amount << " units of '" << medicineName << "' added to inventory.\n";
}

void Hospital::getNextToExpiredMedicine() {
    // Traverse the linked list to find the next expiring medicine
    std::string nextToExpireDate = "9999-99-99";
    std::string nextToExpireName;
    Node* current = inventory.head; // Assuming head is public or we add a getter
    if (!current) {
        std::cout << "Inventory is empty.\n";
        return;
    }

    while (current) {
        if (current->data.expiryDate < nextToExpireDate) {
            nextToExpireDate = current->data.expiryDate;
            nextToExpireName = current->data.name;
        }
        current = current->next;
    }

    if (!nextToExpireName.empty()) {
        std::cout << "The next medicine to expire is '" << nextToExpireName << "' with expiry date " << nextToExpireDate << ".\n";
    } else {
        std::cout << "Inventory is empty.\n";
    }
}

void Hospital::displaySortedMedicineList() {
    std::vector<Medicine> medicineVector = inventory.toVector();
    if (medicineVector.empty()) {
        std::cout << "Inventory is empty. No list to display.\n";
        return;
    }

    mergeSort(medicineVector, 0, medicineVector.size() - 1);

    std::cout << "--- Medicine Inventory (Sorted by Name) ---\n";
    for (const auto& med : medicineVector) {
        std::cout << "Name: " << med.name << ", Amount: " << med.amount << ", Expiry: " << med.expiryDate << ", Price: $" << med.price << "\n";
    }
    std::cout << "------------------------------------------\n";
}

// for better usage
void Hospital::clearScreen() const {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void Hospital::waitEnter() const {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

// =======================================================
// File Persistence Functions
// =======================================================
/*
void Hospital::loadData() {
    std::cout << "Loading data from files...\n";
    loadPatients();
    loadDepartments();
    std::cout << "Data loaded successfully.\n";
    waitEnter();
}

void Hospital::saveData() {
    std::cout << "Saving data to files...\n";
    savePatients();
    saveDepartments();
    std::cout << "Data saved successfully.\n";
    waitEnter();
}

void Hospital::savePatients() {
    std::ofstream file("patients.txt");
    if (!file.is_open()) {
        std::cerr << "Error: Could not open patients.txt for writing.\n";
        return;
    }
    for (const auto& pair : patients) {
        file << pair.second.serialize() << "\n";
    }
    file.close();
}

void Hospital::loadPatients() {
    std::ifstream file("patients.txt");
    if (!file.is_open()) {
        std::cout << "patients.txt not found. Starting with no patient data.\n";
        return;
    }
    std::string line;
    int maxId = 0;
    while (std::getline(file, line)) {
        Patient p = Patient::deserialize(line);
        patients[p.id] = p;
        if (p.id > maxId) {
            maxId = p.id;
        }
    }
    file.close();
    patientIdCounter = maxId + 1;
}

void Hospital::saveDepartments() {
    std::ofstream deptFile("departments.txt");
    std::ofstream docFile("doctors.txt");

    if (!deptFile.is_open() || !docFile.is_open()) {
        std::cerr << "Error: Could not open files for writing departments/doctors.\n";
        return;
    }

    for (const auto& pair : departments) {
        // Save department names
        deptFile << pair.first << "\n";

        // Save doctors belonging to each department
        for (const auto& doctor : pair.second) {
            docFile << doctor.serialize() << "\n";
        }
    }
    deptFile.close();
    docFile.close();
}


void Hospital::loadDepartments() {
    std::ifstream deptFile("departments.txt");
    if (!deptFile.is_open()) {
        std::cout << "departments.txt not found. Starting with no departments.\n";
        return;
    }
    std::string deptName;
    while (std::getline(deptFile, deptName)) {
        departments[deptName] = std::list<Doctor>();
    }
    deptFile.close();

    std::ifstream docFile("doctors.txt");
    if (!docFile.is_open()) {
        std::cout << "doctors.txt not found. No doctors to load.\n";
        return;
    }
    std::string line;
    int maxId = 0;
    while (std::getline(docFile, line)) {
        Doctor d = Doctor::deserialize(line);
        departments[d.department].push_back(d);
        if (d.id > maxId) {
            maxId = d.id;
        }
    }
    docFile.close();
    doctorIdCounter = maxId + 1;
}
*/
