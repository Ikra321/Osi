#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include "employee.h"

void Creator(const std::string& binFileName, int n) {
    std::ofstream file(binFileName, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось создать бинарный файл\n";
        return;
    }

    std::cout << "Введите пожалуйста данные о " << n << " сотрудниках( id, имя, и колличество часов)\n";
    for (int i = 0; i < n; i++) {
        employee buff{};
        std::cin >> buff;
        file.write(reinterpret_cast<const char*>(&buff), sizeof(buff));
    }
}  

int main(int argc, char* argv[]) {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    std::string binFileName = argv[1];
    int n = std::stoi(argv[2]);
    Creator(binFileName, n); 
    return 0;
}