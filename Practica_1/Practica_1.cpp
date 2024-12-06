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

int main() {
    // Пример входной строки
    std::string input = "23.4  -2222.4542 2.4";
    std::string input1 = "Dark  2222.366 2.4";
    std::string input2 = "EERERvdv  2222.366 2.4";
    // Регулярное выражение
    std::regex pattern("([a-zA-z]+)([\\s]+)([-+]?\[\\d.]+)([\\s]+)([-+]?\[\\d.]+)");
    std::smatch match;

    // Проверка строки
    if (std::regex_match(input1, match, pattern)) {
        
       
        std::string name = match[1];
        double depth = std::stod(match[3]);
        double salinity = std::stod(match[5]);

        sea obj{ name, depth, salinity };
        // Выводим данные объекта
        obj.display();
    }
    else {
        setlocale(LC_ALL, "RU");
        std::cout << "Ошибка: строка не соответствует ожидаемому формату." << std::endl;
    }
   
}