#include "Stepper.h"


void Stepper::Zero() {
    unsigned int pos1 = p.getUInt("counter", 0);
    unsigned int pos2 = q.getUInt("counter", 0);
    turn1 = !turn1;
    if (pos1 > 0) {

        digitalWrite(DIR, turn1);
        for (int i = 0;i < pos1;i++) {
            digitalWrite(STEP, HIGH);
            delayMicroseconds(100);
            index1(turn1);
            digitalWrite(STEP, LOW);
            delayMicroseconds(100);
        }

    }
    pos1 = 0;
    p.putUInt("counter", pos1);
    turn1 = !turn1;
    Serial.printf("1st motor zeroed\n");
    delay(1000);

    if (pos2 > 0) {
        turn2 = !turn2;
        digitalWrite(M2DIR, turn2);
        for (int i = 0;i < pos2;i++) {
            digitalWrite(M2STEP, HIGH);
            delayMicroseconds(100);
            index2(turn2);
            digitalWrite(M2STEP, LOW);
            delayMicroseconds(100);
        }
    }
    pos2 = 0;
    q.putUInt("counter", pos2);
    turn2 = !turn2;
    Serial.printf("2nd motor zeroed");
    delay(1000);
}



void Stepper::Scan(int anglex, int angley, int interval) {
    unsigned int counter1;
    unsigned int counter2;
    Serial.printf("read values %d %d before math \n", anglex, angley);
    int stepsx = anglex / 1.8;

    int stepsy = angley / 1.8;
    Serial.printf("read values %d %d after math \n", stepsx, stepsy);

    int reset = stepsx * 8;
    turn1 = false;
    turn2 = false;
    digitalWrite(DIR, turn1);

    for (int f = 0;f < stepsy;f++) {
        for (int i = 0;i < stepsx;) {
            currentMillis = millis();
            if (currentMillis - previousMillis >= interval) {
                i++;
                previousMillis = currentMillis;
                for (int j = 0;j < 8;j++) {
                    digitalWrite(STEP, HIGH);
                    index1(turn1);
                    delayMicroseconds(100);
                    digitalWrite(STEP, LOW);
                    delayMicroseconds(100);

                }
            }
        }
        turn1 = !turn1;
        digitalWrite(DIR, turn1);
        Serial.printf("tilt %d done, resetting \n", f);
        delayMicroseconds(1000);

        for (int g = 0;g < reset;g++) {
            digitalWrite(STEP, HIGH);
            index1(turn1);
            delayMicroseconds(100);
            digitalWrite(STEP, LOW);
            delayMicroseconds(100);
        }
        turn1 = !turn1;
        digitalWrite(DIR, turn1);
        Serial.printf("reset %d done, panning \n", f);
        delayMicroseconds(1000);
        for (int l = 0;l < 50;l++) {
            digitalWrite(M2STEP, HIGH);
            index2(turn2);
            delayMicroseconds(200);
            digitalWrite(M2STEP, LOW);
            delayMicroseconds(200);

        }
        delay(500);

    }Serial.printf("Scan complete!");
}



void Stepper::Shutdown() {
    Serial.printf("Shutting down");
    delay(1000);

    p.end();
    q.end();
    delay(1000);

}




