#pragma once

#include <Arduino.h>
#include <EEPROM.h>

#include "RollingCodeStorage.h"

class EEPROMRollingCodeStorage : public RollingCodeStorage {
private:
	int address;

public:
	EEPROMRollingCodeStorage(int address);
	uint16_t nextCode() override;
};
