//
// Created by Tica Bogdan on 14/08/2017.
//

#include "ESP8266WiFi.h"
#include "WebSocketClient.h"


class Communication {

protected:

    WiFiClient *client;

    WebSocketClient *wsClient;

public:

    Communication() {

        this->client = new WiFiClient();
        this->wsClient = new WebSocketClient();

    }

    bool connect() {

        if (!this->connectWifi()) {
            return false;
        }

        if (!this->connectWebSocket()) {
            return false;
        }

        return true;

    };

    bool checkConnection() {

        return this->client->connected();

    }

    String incomingMessage() {
        String buffer;

        this->wsClient->getData(buffer);

        return buffer;
    }

    void sendMessage(String message) {
        this->wsClient->sendData(message);
    }

protected:


    bool connectWifi() {

        Serial.println();


        WiFi.begin("T_I_K", "P@r0l@123");

        int tries = 10;
        int currentTry = 0;
        while (WiFi.status() != WL_CONNECTED) {

            delay(1000);
            currentTry++;
            if (currentTry >= tries) {
                break;
            }
        }

        bool connectionStatus = WiFi.status() == WL_CONNECTED;

        Serial.println("");
        Serial.println("WiFi connected");
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());

        return connectionStatus;
    }

    bool connectWebSocket() {

        char host[20] = "unice1.tk";
        char path[20] = "/ws";

        if (!this->client->connect(host, 80)) {

            Serial.println("Unable to connect on 80 port of host:");
            Serial.print(host);
            return false;
        }

        this->wsClient->host = host;
        this->wsClient->path = path;

        bool connectionStatus = this->wsClient->handshake(*this->client);

        if (connectionStatus) {
            Serial.println("Handshake success on:");
        } else {
            Serial.println("Handshake fail on:");
        }

        Serial.print(host);
        Serial.print(path);

        return connectionStatus;

    }
};