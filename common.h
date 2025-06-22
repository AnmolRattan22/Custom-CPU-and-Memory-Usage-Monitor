#define SHM_NAME "SystemStatsSharedMemory"
#define EVENT_NAME "SystemStatsUpdateEvent"

#include <windows.h>
#include <time.h>

struct SystemStats {
    float cpu_usage;
    float mem_usage;
    time_t timestamp;
};
