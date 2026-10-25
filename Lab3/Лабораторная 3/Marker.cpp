#include <iostream>
#include <cstdlib>
#include "Marker.h"

DWORD WINAPI MarkerThread(LPVOID lpPar) {
    int id = (INT)(INT_PTR)lpPar;

    WaitForSingleObject(hStartEvents[id], INFINITE);

    std::srand(id);

    while (true) {
        int ind = std::rand() % size;

        EnterCriticalSection(&cs);
        if (arr[ind] == 0) {
            LeaveCriticalSection(&cs);
            Sleep(5);
            EnterCriticalSection(&cs);
            arr[ind] = id + 1;
            LeaveCriticalSection(&cs);
            Sleep(5);
        }
        else {
            int countner = 0;
            for (int i = 0; i < size; ++i) {
                if (arr[i] == id + 1) {
                    ++countner;
                }
            }

            std::cout << "Маркер с индексом " << id + 1 << " ,пометил " << countner << " элементов и остановился на " << ind << "\n";
            LeaveCriticalSection(&cs);

            SetEvent(hPauseEvents[id]);

            HANDLE waitHandles[2] = { hContinueEvents[id], hEndEvents[id] };
            DWORD result = WaitForMultipleObjects(2, waitHandles, FALSE, INFINITE);

            if (result == WAIT_OBJECT_0 + 1) {
                EnterCriticalSection(&cs);
                for (int i = 0; i < size; ++i) {
                    if (arr[i] == id + 1) {
                        arr[i] = 0;
                    }
                }
                LeaveCriticalSection(&cs);
                break;
            }
        }
    }
    return 0;
}