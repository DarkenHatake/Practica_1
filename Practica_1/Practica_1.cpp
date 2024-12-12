#include <iostream>
#include <string>
#include <regex>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

// Структура для хранения информации об объекте
struct Sea {
    std::string name;
    double depth;
    double salinity;
    // Метод для вывода данных объекта
    void display() const {
        std::cout << "Name: " << name << " Depth: " << depth << " Salinity: " << salinity << std::endl;
    }
};
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
std::vector<Sea> sortSeas(const std::vector<Sea>& seas) {
    std::map<double, Sea> seaMap;

    for (const auto& sea : seas) {
        // Если глубина еще не добавлена или текущая солёность больше, чем у уже добавленного объекта
        if (seaMap.find(sea.depth) == seaMap.end() || sea.salinity > seaMap[sea.depth].salinity) {
            seaMap[sea.depth] = sea; // Обновляем объект с максимальной солёностью для данной глубины
        }
    }

    // Создаем вектор для хранения отсортированных объектов
    std::vector<Sea> sortedSeas;
    for (const auto& pair : seaMap) {
        sortedSeas.push_back(pair.second); // Добавляем объекты в новый вектор
    }

    return sortedSeas; // Возвращаем отсортированный вектор
}

std::vector<Sea> readSeasFromFile(const std::string& filename) {
    std::vector<Sea> seas;       // Вектор для хранения объектов Sea
    std::ifstream file(filename); // Открываем файл

    if (!file.is_open()) {       // Проверяем, удалось ли открыть файл
        std::cerr << "Ошибка при открытии файла: " << filename << std::endl;
        return seas;             // Возвращаем пустой вектор в случае ошибки
    }

    std::string line;
    while (std::getline(file, line)) { // Читаем файл построчно
        Sea obj;
        obj = Build_object(obj, line);// Создаем объект Sea из строки
        seas.push_back(obj);             // Добавляем объект в вектор
    }

    file.close();                     // Закрываем файл
    return seas;                      // Возвращаем вектор объектов Sea
}


int main() {
    // Примеры входных строк
    std::string filename = "input.txt"; // Укажите имя вашего файла
    std::string outputFilename = "output.txt"; // Укажите имя вашего выходного файла
    std::vector<Sea> seas = readSeasFromFile(filename);
    for (const auto& sea : seas) {
        sea.display();
    }
    std::vector<Sea> sortedSeas = sortSeas(seas);
    std::cout << "sort: " << std::endl;
    for (const auto& sea : sortedSeas) {
        sea.display();
    }
    writeSeasToFile(sortedSeas, outputFilename);
    return 0;
}