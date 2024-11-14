#include "kiihdyttaja.h"

void kiihdyttaja::printtaaSpeksit(const Speksit& speksi) const {



};

bool kiihdyttaja::lataaSpeksit(const string& filename){
    ifstream file(filename);
    if (file.is_open()) {
        string nimi;
        Speksit speksi;
        while (getline(file, nimi)) {
            file >> speksi.GearRatio >> speksi.StepAngle >> speksi.jaksonkulma >> speksi.jaksonaika;
            file.ignore();
            speksi.nimi = nimi;
            speksiMap[nimi] = speksi;
        }
        file.close();
        return true;
    }
    return false;


}


void kiihdyttaja::tallennaSpeksit(const string& filename) const{}


void kiihdyttaja::kyselySpeksit(){
}

void kiihdyttaja::teecustomSpeksit(const string& nimi) {
    Speksit uusispeksi;
    uusispeksi.nimi = nimi;
    double driver, driven;
    cout << "Anna Gear ratio:n antamalla ensiksi ajuri rattaan hammasluku:";
    cin >> driver;
    cout << "Anna ajettavan rattaan hammasluku";
    cin >> driven;
    uusispeksi.GearRatio = driver / driven;
    cout << "Anna steppikulma <asteina>:";
    cin >> uusispeksi.StepAngle;
    cout << "Enter motor torque:";
    cin >> uusispeksi.jaksonkulma;
    cout << "Anna jaksonaika <millisekunttia>:";
    cin >> uusispeksi.jaksonaika;

    speksiMap[nimi] = uusispeksi;
    cout << "New motor specifications saved with name "<<nimi<<endl;

};
