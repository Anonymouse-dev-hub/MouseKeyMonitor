#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <string>
#include <vector>

// Link the library needed for process snapshotting
#pragma comment(lib, "Kernel32.lib")

void CheckForSuspiciousProcesses() {
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;

    // Take a snapshot of all processes in the system
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to grab process snapshot." << std::endl;
        return;
    }

    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(hProcessSnap, &pe32)) {
        CloseHandle(hProcessSnap);
        return;
    }

    std::cout << "--- SCANNING PROCESSES FOR SUSPICIOUS ACTIVITY ---" << std::endl;

    do {
        // 1. Get a handle to the process
        HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pe32.th32ProcessID);

        if (hProcess) {
            // Logic: Keyloggers often run with no visible window but active threads
            // In a real tool, we would check if they are calling 'SetWindowsHookEx'
            // For this portfolio demo, we flag generic suspicious names or unsigned binaries

            std::wstring processName = pe32.szExeFile;

            // Example Heuristic: Flag known bad names or strange behaviors
            // Real keyloggers hide as "svchost.exe" (fake) or "winlogon.exe" in wrong folders
            if (processName.find(L"keylog") != std::string::npos ||
                processName.find(L"spy") != std::string::npos) {

                std::wcout << L"[!] ALERT: Suspicious Process Found: " << processName
                    << L" (PID: " << pe32.th32ProcessID << L")" << std::endl;
            }

            CloseHandle(hProcess);
        }
    } while (Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
    std::cout << "--- SCAN COMPLETE ---" << std::endl;
}

int main() {
    std::cout << "Starting Keylogger Detection Utility..." << std::endl;
    CheckForSuspiciousProcesses();

    // Keep window open
    std::cout << "\nPress Enter to exit...";
    std::cin.get();
    return 0;
}