//
// Created by Tica Bogdan on 14/08/2017.
//

#include <Arduino.h>
#include "Handler/Handler.cpp"

Handler *handler = new Handler();


void setup() {

    Serial.begin(115200);

    handler->setup();
}

void loop() {

    handler->loop();
}