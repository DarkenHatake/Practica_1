#include <iostream>
#include <string>
#include <regex>

// Структура для хранения информации об объекте
struct sea {
    std::string name;
    double depth;
    double salinity;

    // Метод для вывода данных объекта
    void display() const {
        std::cout << "Name: " << name << std::endl;
        std::cout << "Depth: " << depth << std::endl;
        std::cout << "Salinity: " << salinity << std::endl;
    }
};

void building_of_the_object(std::string first, std::string second, std::string third) {
    
    std::string name = first;
    double depth = std::stod(second);
    double salinity = std::stod(third);

    sea obj{ name, depth, salinity };

    obj.display();
}

void seorch_str(std::string input) {
    
    std::regex pattern("([a-zA-z]+)([\\s]+)([-+]?\[\\d.]+)([\\s]+)([-+]?\[\\d.]+)");
    std::smatch match;
    if (std::regex_match(input, match, pattern)) {
        building_of_the_object(match[1], match[3], match[5]);
    }
    else {
        setlocale(LC_ALL, "RU");
        std::cout << "Ошибка: строка не соответствует ожидаемому формату." << std::endl;
    }
}

int main() {
    // Пример входной строки
    std::string input = "23.4  -2222.4542 2.4";
    std::string input1 = "Dark  2222.366 2.4";
    std::string input2 = "EERERvdv  2222.366 2.4";

    seorch_str(input2);
}