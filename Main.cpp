#include <windows.h>
#include <iostream>
#include <string>
using namespace std;

// Function to open the serial port (COMx), configure it and return the handle
HANDLE openSerialPort(const string& portName) {
    HANDLE hSerial = CreateFile(
        portName.c_str(),  // COM port name, e.g., "COM3"
        GENERIC_READ | GENERIC_WRITE,  // Open for both read and write
        0,  // No sharing
        NULL,  // Default security attributes
        OPEN_EXISTING,  // Open the existing port
        0,  // No special attributes
        NULL);  // No template file

    if (hSerial == INVALID_HANDLE_VALUE) {
        cerr << "Error opening COM port" << endl;
        return INVALID_HANDLE_VALUE;
    }

    DCB dcbSerialParams = { 0 };
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        cerr << "Error getting current serial settings" << endl;
        CloseHandle(hSerial);
        return INVALID_HANDLE_VALUE;
    }

    dcbSerialParams.BaudRate = CBR_115200;  // 115200 baud rate
    dcbSerialParams.ByteSize = 8;  // 8 data bits
    dcbSerialParams.StopBits = ONESTOPBIT;  // 1 stop bit
    dcbSerialParams.Parity = NOPARITY;  // No parity

    if (!SetCommState(hSerial, &dcbSerialParams)) {
        cerr << "Error setting serial port parameters" << endl;
        CloseHandle(hSerial);
        return INVALID_HANDLE_VALUE;
    }

    // Set timeouts
    COMMTIMEOUTS timeouts = { 0 };
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    if (!SetCommTimeouts(hSerial, &timeouts)) {
        cerr << "Error setting timeouts" << endl;
        CloseHandle(hSerial);
        return INVALID_HANDLE_VALUE;
    }

    return hSerial;
}

// Function to send a command to the Arduino and read its response
void sendCommandToArduino(HANDLE hSerial, const string& command) {
    DWORD bytesWritten;
    if (!WriteFile(hSerial, command.c_str(), command.length(), &bytesWritten, NULL)) {
        cerr << "Error writing to serial port" << endl;
        return;
    }

    // Read the response from Arduino
    char buffer[256];
    DWORD bytesRead;
    if (!ReadFile(hSerial, buffer, sizeof(buffer), &bytesRead, NULL)) {
        cerr << "Error reading from serial port" << endl;
        return;
    }

    buffer[bytesRead] = '\0';  // Null-terminate the string
    cout << "Arduino Response: " << buffer << endl;
}

int main() {
    string portName = "COM3";  // Change to the correct COM port for your system
    HANDLE hSerial = openSerialPort(portName);
    if (hSerial == INVALID_HANDLE_VALUE) {
        return 1;  // Exit if serial port can't be opened
    }

    string command;
    while (true) {
        cout << "Enter command (zero, scan <angleX> <angleY> <interval>, shutdown): ";
        getline(cin, command);  // Use getline to capture entire command line

        if (command == "zero") {
            sendCommandToArduino(hSerial, "zero\n");
        }
        else if (command.find("scan") == 0) {
            // Format the scan command like: "scan 90 90 1000"
            sendCommandToArduino(hSerial, command + "\n");
        }
        else if (command == "shutdown") {
            sendCommandToArduino(hSerial, "shutdown\n");
        }
        else {
            cout << "Unknown command" << endl;
        }
    }

    CloseHandle(hSerial);
    return 0;
}

 /*  while (true) {
        cout << "Anna komento (speksit, load <nimi>, customspeksi, lopeta): ";
        cin >> command;

        if (command == "speksit") {
            kiihdyta.printtaaSpeksit();
        }
        else if (command == "load") {
            string nimi;
            cin >> nimi;
            if (kiihdyta.lataaSpeksitNimella(nimi)) {
                const auto& loaded = kiihdyta.haeSpeksit();
                cout << "Loaded Speksit: " << loaded.nimi << endl;
                cout << "Gear Ratio: " << loaded.GearRatio << endl;
                cout << "Step Angle: " << loaded.StepAngle << endl;
                cout << "Angle per Step: " << loaded.jaksonkulma << endl;
                cout << "Step Time: " << loaded.jaksonaika << " ms" << endl;

                cout << "Edetäänkö näillä parametreilla? (0/1): ";
                cin >> edetaan;
                if (edetaan) {
                    controlESP(hSerial);  
                }
            }
            else {
                cout << "Loadaus epäonnistui" << endl;
            }
        }
        else if (command == "customspeksi") {
            kiihdyta.kyselySpeksit();
        }
        else if (commad == "lopeta") {
            cout << "lopetetaan" << endl;
            return 0;
        }
        else {
            cout << "Tuntematon komento!" << endl;
        }
    }
    CloseHandle(hSerial);

    return 0;
}
*/