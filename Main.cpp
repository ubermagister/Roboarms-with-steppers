#include <iostream>
#include <fstream>
#include <string>
#include "kiihdyttaja.h"

using namespace std;



void sendCommandToESP(const string& command) {
    Serial.write(command);  // Send the command to the ESP board via Serial
    string response = ser.readline();  // Read response from the ESP
    cout << "ESP Response: " << response << endl;

int main() {
  
    try {
        ser.setPort("¨COM6");  
        ser.setBaudrate(115200);
        ser.setTimeout(serial::Timeout::simpleTimeout(1000));
        ser.open();
    }
    catch (Serial::IOException& e) {
        cerr << "Error: Could not open serial port!" << endl;
        return 1;
    }

    if (Serial.isOpen()) {
        cout << "Serial port initialized." << endl;
    }
    else {
        cerr << "Error: Could not open serial port!" << endl;
        return 1;
    }

    string command;

    while (true) {
        cout << "Enter command (   ): ";
        cin >> command;

        if (command == "zero") {
            sendCommandToESP("zero");
          //  aja nollaus
        }
        else if (command == "run") {
            //aja komento 
            
            sendCommandToESP("scan " + to_string(angleX) + " " + to_string(angleY) + " " + to_string(interval));
        }
        else if (command == "shutdown") {
           
         
        }
        else if (command == "speksit") {
         //printtaa speksit
        }
        else if (command == "load <nimi>") {
           // aseta käytettäviksi parametreiksi x
        }
        else if (command == "custom speksi") {
          //      kysele speksit ja tallenna uudet
        }
        else {
            cout << "Unknown command!" << endl;
        }
    }

    return 0;
}