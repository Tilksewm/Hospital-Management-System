#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <string>
#include <iostream>

class Appointment {
public:
    // Properties
    int patientId;
    std::string registrationTime;
    int priorityLevel;
    int bloodPressure;
    int heartRate;
    std::string category;

    // Constructors
    Appointment() = default;
    Appointment(int patientId, const std::string& registrationTime);

    // Methods
    void displayDetails() const;

    // Custom comparator for priority queue
    bool operator<(const Appointment& other) const {
        return priorityLevel < other.priorityLevel;
    }

    // Serialization for file persistence
    std::string serialize() const;
    static Appointment deserialize(const std::string& data);
};

#endif
