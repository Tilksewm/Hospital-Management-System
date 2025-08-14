#include "Doctor.h"
#include <sstream>

Doctor::Doctor(int id, const std::string& name, const std::string& sex, int age, const std::string& department)
    : id(id), name(name), sex(sex), age(age), department(department) {}

void Doctor::addAppointment(const Appointment& app) {
    appointments.push(app);
}

Appointment Doctor::getNextAppointment() {
    if (appointments.empty()) {
        return Appointment();
    }
    Appointment nextApp = appointments.top();
    appointments.pop();
    return nextApp;
}

void Doctor::displayInfo() const {
    std::cout << "--- Doctor Details ---\n";
    std::cout << "ID: " << id << "\n";
    std::cout << "Name: " << name << "\n";
    std::cout << "Sex: " << sex << "\n";
    std::cout << "Age: " << age << "\n";
    std::cout << "Department: " << department << "\n";
    std::cout << "-----------------------\n";
}

std::string Doctor::serialize() const {
    std::ostringstream oss;
    oss << id << "|" << name << "|" << sex << "|" << age << "|" << department;
    return oss.str();
}

Doctor Doctor::deserialize(const std::string& data) {
    std::istringstream iss(data);
    std::string segment;
    Doctor d;

    std::getline(iss, segment, '|');
    d.id = std::stoi(segment);
    std::getline(iss, d.name, '|');
    std::getline(iss, d.sex, '|');
    std::getline(iss, segment, '|');
    d.age = std::stoi(segment);
    std::getline(iss, d.department, '|');

    return d;
}
