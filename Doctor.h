#ifndef DOCTOR_H
#define DOCTOR_H

#include <iostream>
#include <string>
#include <queue>
#include "Appointment.h"

class Doctor {
public:
    // Properties
    int id;
    std::string name;
    std::string sex;
    int age;
    std::string department;
    std::priority_queue<Appointment> appointments;

    // Constructors
    Doctor() = default;
    Doctor(int id, const std::string& name, const std::string& sex, int age, const std::string& department);

    // Methods
    void addAppointment(const Appointment& app);
    Appointment getNextAppointment();
    void displayInfo() const;

    // Serialization for file persistence
    std::string serialize() const;
    static Doctor deserialize(const std::string& data);
};

#endif
