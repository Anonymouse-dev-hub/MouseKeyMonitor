# MouseKeyMonitor
# 🛡️ Heuristic Keylogger Detector (C++)

![Language](https://img.shields.io/badge/Language-C%2B%2B-blue)
![Platform](https://img.shields.io/badge/Platform-Windows-0078D6)
![License](https://img.shields.io/badge/License-MIT-green)

## 📖 Overview
The **Keylogger Detector** is a Windows-based security utility designed to identify potential malicious processes. Unlike signature-based antiviruses, this tool uses **Heuristic Analysis** to scan active processes for suspicious behaviors often exhibited by spyware and keyloggers.

I built this project to deepen my understanding of **Windows Internals**, the **Win32 API**, and how malware persists in memory.

## ⚙️ Technical Architecture
The tool operates by interacting directly with the Windows Kernel via the **WinAPI**:
1.  **Process Snapshotting:** Uses `CreateToolhelp32Snapshot` to capture the state of all system processes in real-time.
2.  **Process Iteration:** Traverses the process list using `Process32First` and `Process32Next`.
3.  **Heuristic Scanning:** Analyzes process attributes (Name, PID, Visibility) to flag anomalies such as:
    * Unsigned binaries masquerading as system files.
    * Processes attempting to hide from the Task Manager.
    * Known malicious naming conventions.

## 🚀 Features
* **Real-time Process Enumeration:** Instant snapshot of all running tasks.
* **Low-Level System Access:** Direct interaction with `Kernel32.dll`.
* **Lightweight:** zero external dependencies; runs natively on Windows.

## 🛠️ Installation & Usage

### Prerequisites
* Windows 10/11
* Visual Studio 2022 (or any C++ Compiler supporting WinAPI)

### Build Instructions
1.  Clone the repository:
    ```bash
    git clone [https://github.com/YourUsername/Keylogger-Detector.git](https://github.com/YourUsername/Keylogger-Detector.git)
    ```
2.  Open the project in **Visual Studio**.
3.  Ensure the target is set to **Release** and **x64**.
4.  Build the solution (`Ctrl + Shift + B`).

### Running the Tool
Run the executable via Command Prompt as Administrator (required for full process visibility):

```bash
cd x64/Release
KeyloggerDetector.exe
