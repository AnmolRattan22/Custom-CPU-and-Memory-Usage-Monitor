# Custom CPU and Memory Usage Monitor

A lightweight system resource monitor written in C using the Windows API to track real-time CPU and memory usage.

## How It Works

First, run the `monitor_window.exe` — this executable collects real-time CPU and memory usage data by making API calls to the Windows operating system.

Then, run the `viewer_win.exe` — this executable reads the data from shared memory and visually displays the CPU and memory usage statistics.

The `monitor_window.exe` must be running in the background for `viewer_win.exe` to function correctly.

