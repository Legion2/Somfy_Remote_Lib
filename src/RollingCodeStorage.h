#pragma once

#include <Arduino.h>

class RollingCodeStorage {
public:
	/**
	 * Get the next rolling code from the store. This should also increase the rolling code and store it persistently.
	 *
	 * @return next rolling code
	 */
	virtual uint16_t nextCode() = 0;

	/**
	 * Get the current rolling code from the store.
	 *
	 * @return current rolling code
	 */
    virtual uint16_t currentCode() = 0;

	
	/**
	 * Set the current rolling code to the store.
	 *
	 * @return current rolling code
	 */
    virtual uint16_t currentCode(uint16_t current) = 0;
	
};
