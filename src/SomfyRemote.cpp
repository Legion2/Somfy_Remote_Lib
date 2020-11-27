#include "SomfyRemote.h"

#include <EEPROM.h>

#define SYMBOL 640

SomfyRemote::SomfyRemote(byte emitterPin, uint32_t remote, uint16_t eepromAddress)
	: emitterPin(emitterPin), remote(remote), eepromAddress(eepromAddress) {}

void SomfyRemote::setup() {
	pinMode(emitterPin, OUTPUT);
	digitalWrite(emitterPin, LOW);
}

void SomfyRemote::sendCommand(Command command) {
	uint16_t code;
	EEPROM.get(eepromAddress, code);

#ifdef DEBUG
	Serial.print("Rolling code: ");
	Serial.println(code);
#endif

	byte frame[7];
	buildFrame(frame, command, code);
	sendFrame(frame, 2);
	for (int i = 0; i < 4; i++) {
		sendFrame(frame, 7);
		yield();
	}

	EEPROM.put(eepromAddress, code + 1);
#ifdef ESP32 || ESP8266
	EEPROM.commit();
#endif
}

void SomfyRemote::printFrame(byte *frame) {
	for (byte i = 0; i < 7; i++) {
		if (frame[i] >> 4 == 0) {  //  Displays leading zero in case the most significant
			Serial.print("0");     // nibble is a 0.
		}
		Serial.print(frame[i], HEX);
		Serial.print(" ");
	}
	Serial.println();
}

void SomfyRemote::buildFrame(byte *frame, Command command, uint16_t code) {
	frame[0] = 0xA7;                             // Encryption key. Doesn't matter much
	frame[1] = static_cast<byte>(command) << 4;  // Which button did  you press? The 4 LSB will be the checksum
	frame[2] = code >> 8;                        // Rolling code (big endian)
	frame[3] = code;                             // Rolling code
	frame[4] = remote >> 16;                     // Remote address
	frame[5] = remote >> 8;                      // Remote address
	frame[6] = remote;                           // Remote address

#ifdef DEBUG
	Serial.print("Frame         : ");
	printFrame(frame);
#endif

	// Checksum calculation: a XOR of all the nibbles
	byte checksum = 0;
	for (byte i = 0; i < 7; i++) {
		checksum = checksum ^ frame[i] ^ (frame[i] >> 4);
	}
	checksum &= 0b1111;  // We keep the last 4 bits only

	// Checksum integration
	frame[1] |= checksum;

#ifdef DEBUG
	Serial.print("With checksum : ");
	printFrame(frame);
#endif

	// Obfuscation: a XOR of all the bytes
	for (byte i = 1; i < 7; i++) {
		frame[i] ^= frame[i - 1];
	}

#ifdef DEBUG
	Serial.print("Obfuscated    : ");
	printFrame(frame);
#endif
}

void SomfyRemote::sendFrame(byte *frame, byte sync) {
	if (sync == 2) {  // Only with the first frame.
		// Wake-up pulse & Silence
		sendHigh(9415);
		sendLow(89565);
	}

	// Hardware sync: two sync for the first frame, seven for the following ones.
	for (int i = 0; i < sync; i++) {
		sendHigh(4 * SYMBOL);
		sendLow(4 * SYMBOL);
	}

	// Software sync
	sendHigh(4550);
	sendLow(SYMBOL);

	// Data: bits are sent one by one, starting with the MSB.
	for (byte i = 0; i < 56; i++) {
		if (((frame[i / 8] >> (7 - (i % 8))) & 1) == 1) {
			sendLow(SYMBOL);
			sendHigh(SYMBOL);
		} else {
			sendHigh(SYMBOL);
			sendLow(SYMBOL);
		}
	}

	sendLow(30415);  // Inter-frame silence
}

void SomfyRemote::sendHigh(uint16_t durationInMicroseconds) {
#ifdef ESP32 || ESP8266
	digitalWrite(emitterPin, HIGH);
	delayMicroseconds(durationInMicroseconds);
#elif ARDUINO_ARCH_AVR
	// TODO fast write
	digitalWrite(emitterPin, HIGH);
	delayMicroseconds(durationInMicroseconds);
#endif
}

void SomfyRemote::sendLow(uint16_t durationInMicroseconds) {
#ifdef ESP32 || ESP8266
	digitalWrite(emitterPin, LOW);
	delayMicroseconds(durationInMicroseconds);
#elif ARDUINO_ARCH_AVR
	// TODO fast write
	digitalWrite(emitterPin, LOW);
	delayMicroseconds(durationInMicroseconds);
#endif
}
