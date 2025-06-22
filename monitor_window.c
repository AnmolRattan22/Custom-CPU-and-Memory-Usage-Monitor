#include <windows.h>
#include <stdio.h>
#include <time.h>
#include "common.h"

int main() {
    HANDLE hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0,
        sizeof(struct SystemStats), SHM_NAME);

    if (hMapFile == NULL) {
        printf("Could not create file mapping object (%lu).\n", GetLastError());
        return 1;
    }

    struct SystemStats* stats = (struct SystemStats*)MapViewOfFile(
        hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(struct SystemStats));

    if (stats == NULL) {
        printf("Could not map view of file (%lu).\n", GetLastError());
        CloseHandle(hMapFile);
        return 1;
    }

    HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, EVENT_NAME);
    if (hEvent == NULL) {
        printf("Could not create event (%lu).\n", GetLastError());
        UnmapViewOfFile(stats);
        CloseHandle(hMapFile);
        return 1;
    }

    while (1) {
        stats->cpu_usage = (float)(rand() % 100);
        stats->mem_usage = (float)(rand() % 100);
        stats->timestamp = time(NULL);

        SetEvent(hEvent);  // Notify viewer

        Sleep(2000);
    }

    UnmapViewOfFile(stats);
    CloseHandle(hMapFile);
    CloseHandle(hEvent);
    return 0;
}
