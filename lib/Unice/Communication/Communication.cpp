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

        return "{\"name\":\"Rin Unice\",\"uid\":\"rin_unice_1234\",\"devices\":[{\"name\":\"Temperature\",\"device_type\":60,\"type\":{\"name\":\"Sensor\",\"device_type\":60},\"state\":{\"state\":\"0\",\"target\":\"0\"}},{\"name\":\"living_light\",\"device_type\":50,\"type\":{\"name\":\"Percentage\",\"device_type\":50},\"state\":{\"state\":\"0\",\"target\":\"58\"}},{\"name\":\"Heating HVAC\",\"device_type\":20,\"type\":{\"name\":\"Triple\",\"device_type\":20},\"state\":{\"state\":\"0\",\"target\":\"0\"}},{\"name\":\"Bedroom Light\",\"device_type\":10,\"type\":{\"name\":\"Double\",\"device_type\":10},\"state\":{\"state\":\"0\",\"target\":\"0\"}}]}";

        this->connectWifi();

        Serial.println("Start to fetch");

        HTTPClient *http = new HTTPClient();

        http->begin("unice1.tk/unices/uid/rin_unice_1234");

        int code = http->GET();


        Serial.println("HTTP Code:");
        Serial.println(code);

        String data = http->getString();

        http->end();

        if (code > 0) {
            Serial.println(data);

        } else {
            Serial.println(http->errorToString(code));
        }


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