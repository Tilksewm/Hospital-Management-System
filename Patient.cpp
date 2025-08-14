#include "Patient.h"
#include <algorithm>

Patient::Patient(int id, const std::string& name, int age, const std::string& sex, const std::string& contact)
    : id(id), name(name), age(age), sex(sex), contact(contact) {}

void Patient::addAllergy(const std::string& allergy) {
    allergies.push_back(allergy);
}

void Patient::addHistory(const std::string& entry) {
    history.push_back(entry);
}

void Patient::displayInfo() const {
    std::cout << "--- Patient Details ---\n";
    std::cout << "ID: " << id << "\n";
    std::cout << "Name: " << name << "\n";
    std::cout << "Age: " << age << "\n";
    std::cout << "Sex: " << sex << "\n";
    std::cout << "Contact: " << contact << "\n";
    std::cout << "Allergies: ";
    if (allergies.empty()) {
        std::cout << "None\n";
    } else {
        for (const auto& allergy : allergies) {
            std::cout << allergy << " ";
        }
        std::cout << "\n";
    }
    std::cout << "History: ";
    if (history.empty()) {
        std::cout << "None\n";
    } else {
        for (const auto& entry : history) {
            std::cout << entry << " ";
        }
        std::cout << "\n";
    }
    std::cout << "-----------------------\n";
}

std::string Patient::serialize() const {
    std::ostringstream oss;
    oss << id << "|" << name << "|" << age << "|" << sex << "|" << contact << "|"
        << vectorToString(allergies) << "|" << vectorToString(history);
    return oss.str();
}

Patient Patient::deserialize(const std::string& data) {
    std::istringstream iss(data);
    std::string segment;
    Patient p;

    std::getline(iss, segment, '|');
    p.id = std::stoi(segment);
    std::getline(iss, p.name, '|');
    std::getline(iss, segment, '|');
    p.age = std::stoi(segment);
    std::getline(iss, p.sex, '|');
    std::getline(iss, p.contact, '|');
    std::getline(iss, segment, '|');
    p.allergies = stringToVector(segment);
    std::getline(iss, segment, '|');
    p.history = stringToVector(segment);

    return p;
}

std::string Patient::vectorToString(const std::vector<std::string>& vec) const {
    if (vec.empty()) {
        return "NULL";
    }
    std::string result;
    for (const auto& item : vec) {
        result += item + ";";
    }
    return result;
}

std::vector<std::string> Patient::stringToVector(const std::string& str) {
    std::vector<std::string> result;
    if (str == "NULL") {
        return result;
    }
    std::stringstream ss(str);
    std::string item;
    while (std::getline(ss, item, ';')) {
        result.push_back(item);
    }
    return result;
}
