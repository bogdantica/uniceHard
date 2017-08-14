//
// Created by Tica Bogdan on 14/08/2017.
//

#include "ESP8266WiFi.h"
#include "ESP8266HTTPClient.h"
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

    String getUniceData() {

        //todo update this

        Serial.println("Start to fetch");

        HTTPClient *http = new HTTPClient();

        http->begin("unice1.tk/unices/uid/rin_unice_1234");

        http->GET();
        Serial.println("After to fetch");

        String data = http->getString();

        http->end();

        Serial.println(data);

        Serial.println("End to fetch");


        return data;
    }

    bool connect() {

        if (!this->connectWifi()) {
            Serial.println("WiFi Connection Fail");
            return false;
        }

        if (!this->connectWebSocket()) {
            Serial.println("WebSocket Connection Fail");
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

        if (WiFi.status() == WL_CONNECTED) {
            return true;
        }

        WiFi.begin("T_I_K", "P@r0l@123");

        int tries = 10;
        int currentTry = 0;

        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
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