#include "pch.h"
#include "average_dll.h"

extern "C" {
    __declspec(dllexport) double average(int* arr, int size) {
        if (size <= 0) return 0.0;
        long long sum = 0;
        for (int i = 0; i < size; ++i) {
            sum += arr[i];
        }
        return (double)sum / size;
    }
}