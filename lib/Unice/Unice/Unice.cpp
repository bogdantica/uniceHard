//
// Created by Tica Bogdan on 14/08/2017.
//


#include "Device/Device.cpp"

class Unice {

protected:

    Device *devices[];

public:

    void handleMessage(String message) {

    }

    void init(String message) {


        Serial.println(message);

    }

};