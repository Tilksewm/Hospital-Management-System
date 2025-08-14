
#ifndef PATIENT_H
#define PATIENT_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

class Patient {
public:
    // Properties
    int id;
    std::string name;
    int age;
    std::string sex;
    std::string contact;
    std::vector<std::string> allergies;
    std::vector<std::string> history;

    // Constructors
    Patient() = default;
    Patient(int id, const std::string& name, int age, const std::string& sex, const std::string& contact);

    // Methods
    void addAllergy(const std::string& allergy);
    void addHistory(const std::string& entry);
    void displayInfo() const;

    // Serialization for file persistence
    std::string serialize() const;
    static Patient deserialize(const std::string& data);

private:
    // Helper function for serialization
    std::string vectorToString(const std::vector<std::string>& vec) const;
    static std::vector<std::string> stringToVector(const std::string& str);
};

#endif
