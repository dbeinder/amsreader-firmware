/**
 * @copyright Utilitech AS 2023
 * License: Fair Source
 * 
 */

#include "DomoticzMqttHandler.h"
#include "json/domoticz_json.h"
#include "Uptime.h"

bool DomoticzMqttHandler::publish(AmsData* update, AmsData* previousState, EnergyAccounting* ea, PriceService* ps) {
    	
    return true;
}

bool DomoticzMqttHandler::publishTemperatures(AmsConfiguration* config, HwTools* hw) {
    return false;
}

bool DomoticzMqttHandler::publishPrices(PriceService* ps) {
    return false;
}

bool DomoticzMqttHandler::publishSystem(HwTools* hw, PriceService* ps, EnergyAccounting* ea) {
    return false;
}

uint8_t DomoticzMqttHandler::getFormat() {
    return 3;
}

bool DomoticzMqttHandler::publishRaw(String data) {
    return false;
}

void DomoticzMqttHandler::onMessage(String &topic, String &payload) {
}
