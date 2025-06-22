#include <windows.h>
#include <stdio.h>
#include <time.h>
#include "common.h"

int main() {
    HANDLE hMapFile = OpenFileMapping(FILE_MAP_READ, FALSE, SHM_NAME);
    if (hMapFile == NULL) {
        printf("Could not open file mapping object (%lu).\n", GetLastError());
        return 1;
    }

    struct SystemStats* stats = (struct SystemStats*)MapViewOfFile(
        hMapFile, FILE_MAP_READ, 0, 0, sizeof(struct SystemStats));

    if (stats == NULL) {
        printf("Could not map view of file (%lu).\n", GetLastError());
        CloseHandle(hMapFile);
        return 1;
    }

    HANDLE hEvent = OpenEvent(EVENT_MODIFY_STATE | SYNCHRONIZE, FALSE, EVENT_NAME);
    if (hEvent == NULL) {
        printf("Could not open event (%lu).\n", GetLastError());
        UnmapViewOfFile(stats);
        CloseHandle(hMapFile);
        return 1;
    }

    printf("Viewer started. Waiting for updates...\n");

    while (1) {
        WaitForSingleObject(hEvent, INFINITE);  // Wait for monitor signal

        printf("Updated at: %s", ctime(&stats->timestamp));
        printf("CPU Usage: %.2f%%\n", stats->cpu_usage);
        printf("Memory Usage: %.2f%%\n\n", stats->mem_usage);
    }

    UnmapViewOfFile(stats);
    CloseHandle(hMapFile);
    CloseHandle(hEvent);
    return 0;
}
