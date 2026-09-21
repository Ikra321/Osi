#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include "employee.h"

void Reporter(const std::string& binFileName, const std::string& reportName, double hoursCost) {
    std::ifstream fin(binFileName, std::ios::binary);
    std::ofstream fout(reportName);

    fout << "Отчет по файлу " << binFileName << "\n";
    fout << "Номер сотрудника, имя сотрудника, часы, зарплата\n";

    std::vector<employee> employees;
    employee buff{};
    while (fin.read(reinterpret_cast<char*>(&buff), sizeof(buff))) {
        employees.push_back(buff);
    }

    for (const auto& emp : employees) {
        fout << emp.num << " " << emp.name << " " << emp.hours << " " << emp.hours * hoursCost << "\n";
    }
}

int main(int argc, char* argv[]) {
    std::string binFileName = argv[1];
    std::string reportName = argv[2];
    double hoursCost = std::stod(argv[3]);

    Reporter(binFileName, reportName, hoursCost);
    return 0;
}