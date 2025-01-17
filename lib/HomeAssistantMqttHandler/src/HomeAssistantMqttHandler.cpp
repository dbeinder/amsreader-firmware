/**
 * @copyright Utilitech AS 2023
 * License: Fair Source
 * 
 */

#include "HomeAssistantMqttHandler.h"
#include "hexutils.h"
#include "Uptime.h"
#include "FirmwareVersion.h"
#include "json/ha1_json.h"
#include "json/ha2_json.h"
#include "json/ha3_json.h"
#include "json/ha4_json.h"
#include "json/hadiscover_json.h"
#include "FirmwareVersion.h"

#if defined(ESP32)
#include <esp_task_wdt.h>
#endif

void HomeAssistantMqttHandler::setHomeAssistantConfig(HomeAssistantConfig config) {
    l1Init = l2Init = l2eInit = l3Init = l3eInit = l4Init = l4eInit = rtInit = rteInit = pInit = sInit = rInit = false;

    topic = String(mqttConfig.publishTopic);

    if(strlen(config.discoveryNameTag) > 0) {
        snprintf_P(json, 128, PSTR("AMS reader (%s)"), config.discoveryNameTag);
        deviceName = String(json);
        snprintf_P(json, 128, PSTR("[%s] "), config.discoveryNameTag);
        sensorNamePrefix = String(json);
    } else {
        deviceName = F("AMS reader");
        sensorNamePrefix = "";
    }
    deviceModel = boardTypeToString(boardType);
    manufacturer = boardManufacturerToString(boardType);

    char hostname[32];
    #if defined(ESP8266)
        strcpy(hostname, WiFi.hostname().c_str());
    #elif defined(ESP32)
        strcpy(hostname, WiFi.getHostname());
    #endif

    stripNonAscii((uint8_t*) hostname, 32, false);
    deviceUid = String(hostname); // Maybe configurable in the future?

    if(strlen(config.discoveryHostname) > 0) {
        if(strncmp_P(config.discoveryHostname, PSTR("http"), 4) == 0) {
            deviceUrl = String(config.discoveryHostname);
        } else {
            snprintf_P(json, 128, PSTR("http://%s/"), config.discoveryHostname);
            deviceUrl = String(json);
        }
    } else {
        snprintf_P(json, 128, PSTR("http://%s.local/"), hostname);
        deviceUrl = String(json);
    }

    if(strlen(config.discoveryPrefix) > 0) {
        snprintf_P(json, 128, PSTR("%s/status"), config.discoveryPrefix);
        statusTopic = String(json);

        snprintf_P(json, 128, PSTR("%s/sensor/"), config.discoveryPrefix);
        discoveryTopic = String(json);
    } else {
        statusTopic = F("homeassistant/status");
        discoveryTopic = F("homeassistant/sensor/");
    }
    strcpy(this->mqttConfig.subscribeTopic, statusTopic.c_str());
}

bool HomeAssistantMqttHandler::publish(AmsData* update, AmsData* previousState, EnergyAccounting* ea, PriceService* ps) {
    return false;
}

bool HomeAssistantMqttHandler::publishList1(AmsData* data, EnergyAccounting* ea) {
    return false;
}

bool HomeAssistantMqttHandler::publishList2(AmsData* data, EnergyAccounting* ea) {
    return false;
}

bool HomeAssistantMqttHandler::publishList3(AmsData* data, EnergyAccounting* ea) {
    return false;
}

bool HomeAssistantMqttHandler::publishList4(AmsData* data, EnergyAccounting* ea) {
    return false;
}

String HomeAssistantMqttHandler::getMeterModel(AmsData* data) {
    return "1";
}

bool HomeAssistantMqttHandler::publishRealtime(AmsData* data, EnergyAccounting* ea, PriceService* ps) {
    return false;
}

bool HomeAssistantMqttHandler::publishTemperatures(AmsConfiguration* config, HwTools* hw) {
    return false;
}

bool HomeAssistantMqttHandler::publishPrices(PriceService* ps) {
    return false;
}

bool HomeAssistantMqttHandler::publishSystem(HwTools* hw, PriceService* ps, EnergyAccounting* ea) {
	return false;
}

void HomeAssistantMqttHandler::publishSensor(const HomeAssistantSensor sensor) {

}

void HomeAssistantMqttHandler::publishList1Sensors() {
}

void HomeAssistantMqttHandler::publishList2Sensors() {
}

void HomeAssistantMqttHandler::publishList2ExportSensors() {
}

void HomeAssistantMqttHandler::publishList3Sensors() {
}

void HomeAssistantMqttHandler::publishList3ExportSensors() {
}

void HomeAssistantMqttHandler::publishList4Sensors() {
}

void HomeAssistantMqttHandler::publishList4ExportSensors() {
}

void HomeAssistantMqttHandler::publishRealtimeSensors(EnergyAccounting* ea, PriceService* ps) {
}

void HomeAssistantMqttHandler::publishRealtimeExportSensors(EnergyAccounting* ea, PriceService* ps) {
}

void HomeAssistantMqttHandler::publishTemperatureSensor(uint8_t index, String id) {
}

void HomeAssistantMqttHandler::publishPriceSensors(PriceService* ps) {
}

void HomeAssistantMqttHandler::publishSystemSensors() {
}

void HomeAssistantMqttHandler::publishThresholdSensors() {
}

uint8_t HomeAssistantMqttHandler::getFormat() {
    return 4;
}

bool HomeAssistantMqttHandler::publishRaw(String data) {
    return false;
}

void HomeAssistantMqttHandler::onMessage(String &topic, String &payload) {
}
