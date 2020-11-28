#pragma once

#include <Arduino.h>
#include <EEPROM.h>

#include "RollingCodeStorage.h"

/**
 * Stores the rolling codes in the EEPROM, the codes require two bytes.
 * When using with ESP32 or ESP8266 don't forget to initialize the EEPROM.
 */
class EEPROMRollingCodeStorage : public RollingCodeStorage {
private:
	int address;

public:
	EEPROMRollingCodeStorage(int address);
	uint16_t nextCode() override;
};
