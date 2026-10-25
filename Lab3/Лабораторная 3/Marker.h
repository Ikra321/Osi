#ifndef MARKER_H
#define MARKER_H

#include <windows.h>
#include <vector>

extern int* arr;
extern int size;
extern std::vector<HANDLE> hStartEvents;
extern std::vector<HANDLE> hPauseEvents;
extern std::vector<HANDLE> hContinueEvents;
extern std::vector<HANDLE> hEndEvents;
extern CRITICAL_SECTION cs;
DWORD WINAPI MarkerThread(LPVOID lpPar);

#endif