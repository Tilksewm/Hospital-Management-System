#ifndef MEDICINE_H
#define MEDICINE_H

#include <string>

class Medicine {
public:
    std::string name;
    std::string expiryDate;
    int amount;
    double price;

    Medicine(const std::string& name = "", const std::string& expiryDate = "", int amount = 0, double price = 0.0)
        : name(name), expiryDate(expiryDate), amount(amount), price(price) {}
};

#endif
