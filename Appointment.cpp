#include "Appointment.h"
#include <sstream>

Appointment::Appointment(int patientId, const std::string& registrationTime)
    : patientId(patientId), registrationTime(registrationTime), priorityLevel(0), bloodPressure(0), heartRate(0) {}

void Appointment::displayDetails() const {
    std::cout << "--- Appointment Details ---\n";
    std::cout << "Patient ID: " << patientId << "\n";
    std::cout << "Registration Time: " << registrationTime << "\n";
    std::cout << "Priority Level: " << (priorityLevel > 0 ? std::to_string(priorityLevel) : "Not Set") << "\n";
    if (priorityLevel > 0) {
        std::cout << "Blood Pressure: " << bloodPressure << "\n";
        std::cout << "Heart Rate: " << heartRate << "\n";
        std::cout << "Category: " << category << "\n";
    }
    std::cout << "---------------------------\n";
}

std::string Appointment::serialize() const {
    std::ostringstream oss;
    oss << patientId << "|" << registrationTime << "|" << priorityLevel << "|"
        << bloodPressure << "|" << heartRate << "|" << category;
    return oss.str();
}

Appointment Appointment::deserialize(const std::string& data) {
    std::istringstream iss(data);
    std::string segment;
    Appointment a;

    std::getline(iss, segment, '|');
    a.patientId = std::stoi(segment);
    std::getline(iss, a.registrationTime, '|');
    std::getline(iss, segment, '|');
    a.priorityLevel = std::stoi(segment);
    std::getline(iss, segment, '|');
    a.bloodPressure = std::stoi(segment);
    std::getline(iss, segment, '|');
    a.heartRate = std::stoi(segment);
    std::getline(iss, a.category, '|');

    return a;
}
