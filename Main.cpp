#include <iostream>
#include <string>
#include "kiihdyttaja.h"
using namespace std;




void sendCommandToESP(const string& command) {
    Serial.write(command);  // Send the command to the ESP board via Serial
    string response = ser.readline();  // Read response from the ESP
    cout << "ESP Response: " << response << endl;

void controlESP();



int main() {
    kiihdyttaja kiihdyta;

    if (kiihdyta.lataaSpeksit("stepksit.txt")) {
        cout << "Speksit loadattu" << endl;
    }

    string command;
    bool edetaan=false;
    while (true) {
        cout << "Anna komento (speksit, load <nimi>, customspeksi): ";
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

                cout << "Edetäänkö näillä parametreilla? (0/1)";
                    cin >> edetaan;
                if (edetaan) {
                    controlESP();
                }
                
            }
            else {
                cout << "loadaus epäonnistui" << endl;
            }
        }
        else if (command == "customspeksi") {
            kiihdyta.kyselySpeksit();
        }else{
            cout 





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