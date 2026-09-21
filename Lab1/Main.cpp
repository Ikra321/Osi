#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include "employee.h"

void RunProcess(const std::string& program, const std::vector<std::string>& args) {
    std::string cmd = program;
    for (const auto& a : args) {
        cmd += " " + a;
    }
     
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if (CreateProcess(NULL, &cmd[0], NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    else {   
        std::cerr << "Не удалось запустить процесс " << program << "\n";
    }
}

void PrintBinaryFile(const std::string& binFileName) {
    std::ifstream input(binFileName, std::ios::binary);
    employee buff{};
    while (input.read(reinterpret_cast<char*>(&buff), sizeof(buff))) {
        std::cout << buff << "\n";
    }
}

void PrintTextFile(const std::string& FileName) {
    std::ifstream input(FileName);
    std::string line;
    while (std::getline(input, line)) {
        std::cout << line << "\n";
    }
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    std::string binFileName;
    int n;
    std::cout << "Введите имя бинарного файла: ";
    std::cin >> binFileName;
    std::cout << "Введите количество записей: ";
    std::cin >> n;

    RunProcess("Creator.exe", { binFileName, std::to_string(n) });

    std::cout << "\nСодержимое бинарного файла:\n";
    PrintBinaryFile(binFileName);

    std::string reportName;
    double hoursCost;
    std::cout << "\nВведите имя файла отчёта: ";
    std::cin >> reportName;
    std::cout << "Введите оплату за час: ";
    std::cin >> hoursCost;

    RunProcess("Reporter.exe", { binFileName, reportName, std::to_string(hoursCost) });

    PrintTextFile(reportName);

    return 0;
}