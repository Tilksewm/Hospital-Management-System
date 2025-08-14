#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include <string>
#include <list>
#include <queue>
#include "Doctor.h"
#include "Appointment.h"

// Define a custom comparator for the appointment priority queue
struct AppointmentComparator {
    bool operator()(const Appointment& a1, const Appointment& a2) {
        return a1.priorityLevel < a2.priorityLevel;
    }
};

class Department {
public:
    std::list<Doctor> doctors;
    std::priority_queue<Appointment, std::vector<Appointment>, AppointmentComparator> appointments;

    Department() = default;
};

#endif
