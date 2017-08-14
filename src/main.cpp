//
// Created by Tica Bogdan on 14/08/2017.
//

#include <Arduino.h>
#include "Handler/Handler.cpp"

Handler *handler = new Handler();

WiFiClient *client = new WiFiClient();

WebSocketClient *webSocketClient = new WebSocketClient();

char path[] = "/ws";
char host[] = "unice1.tk";


void setup() {

        handler->setup();

    return;


    Serial.begin(115200);

    WiFi.begin("T_I_K", "P@r0l@123");

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    delay(2000);

    if (client->connect("unice1.tk", 80)) {
        Serial.println("Connected");
    } else {
        Serial.println("Connection failed.");
        while (1) {
            // Hang on failure
        }
    }

    webSocketClient->path = path;
    webSocketClient->host = host;
    if (webSocketClient->handshake(*client)) {
        Serial.println("Handshake successful");
    } else {
        Serial.println("Handshake failed.");
        while (1) {
            // Hang on failure
        }
    }


}

void loop() {

//    String data;

//    if (client->connected()) {
//
//        webSocketClient->getData(data);
//        if (data.length() > 0) {
//            Serial.print("Received data: ");
//            Serial.println(data);
//        }
//
//        // capture the value of analog 1, send it along
////        pinMode(1, INPUT);
//        data = String(analogRead(1));
//
////        webSocketClient.sendData(data);
//
//    } else {
//        Serial.println("Client disconnected.");
//        while (1) {
//            // Hang on disconnect.
//        }
//    }

    // wait to fully let the client disconnect
//    delay(3000);


//    handler->loop();

}