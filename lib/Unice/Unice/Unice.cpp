//
// Created by Tica Bogdan on 14/08/2017.
//


#include "Device/Device.cpp"

class Unice {

protected:

    Device *devices[];


public:

    Unice(unsigned int uniceType) {

        switch (uniceType) {

            case 1000:

                break;

            case 2000:

                break;

            default:

                break;
        }
    }

    void handleMessage(String message) {

    }

};