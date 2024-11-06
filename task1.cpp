#include <fstream>
#include <iostream>
#include <string>

bool isValid(const std::string& date) {
    if (date.length() != 10) {
        return false;
    }
    if (date[2] != '.' || date[5] != '.') {
        return false;
    }
    int day = std::stoi(date.substr(0, 2));
    int month = std::stoi(date.substr(3, 2));
    int year = std::stoi(date.substr(6, 4));

    if (day < 1 || day > 31 || month < 1 || month > 12 || year < 2000 || year > 2024) {
        return false;
    }
    return true;
}

int main() {
    std::string name, surname, date;
    std::cout << "Input name: ";
    std::cin >> name;
    std::cout << "Input surname: ";
    std::cin >> surname;
    std::cout << "Input date: ";
    std::cin >> date;

    if (!isValid(date)) {
        std::cerr << "Invalid data format!";
        return 1;
    }
    int amount;
    std:: cout << "Input salary amount: ";
    std:: cin >> amount;

    std::ofstream file("text.txt", std::ios::app);
    file << name << " " << surname << " " << date << " " << amount;
    file.close();
}
