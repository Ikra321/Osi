#include <iostream>
#include <vector>
#include <Windows.h>
#include "Marker.h"

int* arr = nullptr;
int size = 0;
std::vector<HANDLE> hStartEvents;
std::vector<HANDLE> hPauseEvents;
std::vector<HANDLE> hContinueEvents;
std::vector<HANDLE> hEndEvents;
std::vector<HANDLE> hMarkerThread;
CRITICAL_SECTION cs;
int marker_count = 0;
std::vector<bool> threadAlive;


int main() 
{
	setlocale(LC_ALL, "Russian");
	std::cout << "Введите размер массива:";
	std::cin >> size;
	std::cout << "Введитье количество потоков:";
	std::cin >> marker_count;

	arr = new int[size];
	for (int i = 0; i < size; ++i) {
		arr[i] = 0;
	}
	InitializeCriticalSection(&cs);

	hStartEvents.resize(marker_count);
	hPauseEvents.resize(marker_count);
	hContinueEvents.resize(marker_count);
	hEndEvents.resize(marker_count);
	hMarkerThread.resize(marker_count);
	threadAlive.assign(marker_count, true);

    for (int i = 0; i < marker_count; ++i) {
        hStartEvents[i] = CreateEvent(NULL, TRUE, FALSE, NULL);
        hPauseEvents[i] = CreateEvent(NULL, FALSE, FALSE, NULL);
        hContinueEvents[i] = CreateEvent(NULL, FALSE, FALSE, NULL);
        hEndEvents[i] = CreateEvent(NULL, FALSE, FALSE, NULL);
        hMarkerThread[i] = CreateThread(NULL, 0, MarkerThread, (LPVOID)(INT_PTR)i, 0, NULL);
    }

    for (int i = 0; i < marker_count; ++i) {
        SetEvent(hStartEvents[i]);
    }

    int active = marker_count;

    while (active > 0) {
        std::vector<HANDLE> activePause;
        for (int i = 0; i < marker_count; ++i) {
            if (threadAlive[i]) {
                activePause.push_back(hPauseEvents[i]);
            }
        }

        if (activePause.empty()) break;

        WaitForMultipleObjects(activePause.size(), activePause.data(), TRUE, INFINITE);

        EnterCriticalSection(&cs);
        std::cout << "\nСодержимое массива:" << std::endl;
        for (int i = 0; i < size; ++i) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
        LeaveCriticalSection(&cs);

        int kill;
        std::cout << "Введите номер потока для завершения: ";
        std::cin >> kill;

        int idx = kill - 1;

        SetEvent(hEndEvents[idx]);

        WaitForSingleObject(hMarkerThread[idx], INFINITE);
        CloseHandle(hMarkerThread[idx]);

        threadAlive[idx] = false;
        active--;

        EnterCriticalSection(&cs);
        std::cout << "Массив после завершения потока " << kill << ":" << std::endl;
        for (int i = 0; i < size; ++i) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
        LeaveCriticalSection(&cs);

        for (int i = 0; i < marker_count; ++i) {
            if (threadAlive[i]) {
                SetEvent(hContinueEvents[i]);
            }
        }
    }

    std::cout << "\nВсе потоки завершили работу. " << std::endl;

    DeleteCriticalSection(&cs);
    delete[] arr;

    for (int i = 0; i < marker_count; ++i) {
        CloseHandle(hStartEvents[i]);
        CloseHandle(hPauseEvents[i]);
        CloseHandle(hContinueEvents[i]);
        CloseHandle(hEndEvents[i]);
    }

    return 0;
}
