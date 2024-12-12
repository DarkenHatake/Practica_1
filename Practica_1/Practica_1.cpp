#include <iostream>
#include <string>
#include <regex>
#include <fstream>
#include <vector>

// Структура для хранения информации об объекте
struct Sea {
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

Sea Build_object(Sea obj, const std::string& input) {
    std::regex pattern_1("([\\w]+)");
    std::regex pattern_2("([-+]?\[\\d.]+)");
    std::smatch match;
    if (std::regex_search(input, match, pattern_1)) {
        obj.name = match.str();
    }
    std::sregex_iterator it(input.begin(), input.end(), pattern_2);
    std::sregex_iterator end;
    if (it != end) {
        obj.depth = std::stod(it->str());
        ++it;  // Переходим к следующему совпадению
    }
    if (it != end) {
        obj.salinity = std::stod(it->str());
    }
    return obj;
}

std::vector<std::string> readFileLines(const std::string& filename) {
    std::vector<std::string> lines;  // Вектор для хранения строк
    std::ifstream file(filename);     // Открываем файл

    if (!file.is_open()) {            // Проверяем, удалось ли открыть файл
        std::cerr << "Ошибка при открытии файла: " << filename << std::endl;
        return lines;                 // Возвращаем пустой вектор в случае ошибки
    }

    std::string line;
    while (std::getline(file, line)) { // Читаем файл построчно
        lines.push_back(line);          // Добавляем строку в вектор
    }

    file.close();                      // Закрываем файл
    return lines;                      // Возвращаем вектор строк
}

void writeSeasToFile(const std::vector<Sea>& sortedSeas, const std::string& filename) {
    std::ofstream file(filename); // Открываем файл для записи

    if (!file.is_open()) { // Проверяем, удалось ли открыть файл
        std::cerr << "Ошибка при открытии файла для записи: " << filename << std::endl;
        return; // Выходим из функции в случае ошибки
    }

    for (const auto& sea : sortedSeas) {
        file << sea.name << " " << sea.depth << " " << sea.salinity << "\n"; // Записываем данные объекта в файл
    }

    file.close(); // Закрываем файл
}

int main() {
    // Примеры входных строк

    std::string filename = "input.txt"; 
    std::vector<std::string> lines = readFileLines(filename);


    Sea obj;
    Build_object(obj, lines[0]).display();
    return 0;
}
