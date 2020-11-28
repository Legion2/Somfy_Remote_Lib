#include <EEPROM.h>
#include <ELECHOUSE_CC1101_SRC_DRV.h>
#include <SomfyRemote.h>

#define EMITTER_GPIO 2
#define EEPROM_ADDRESS 0
#define REMOTE 0x5184c8

#define CC1101_FREQUENCY 433.42

SomfyRemote somfyRemote(EMITTER_GPIO, REMOTE, EEPROM_ADDRESS);

void setup() {
	Serial.begin(115200);

	somfyRemote.setup();

	ELECHOUSE_cc1101.Init();
	ELECHOUSE_cc1101.setMHZ(CC1101_FREQUENCY);
	ELECHOUSE_cc1101.SetTx();

#if defined(ESP32) || defined(ESP8266)
	if (!EEPROM.begin(4)) {
		Serial.println("failed to initialise EEPROM");
		delay(1000);
	}
#endif
}

void loop() {
	if (Serial.available() > 0) {
		char serie = (char)Serial.read();
		Command command = static_cast<Command>(serie - '0');
		sendCommandWithRollingCode(command);
#ifdef DEBUG
		Serial.println("finished sending");
#endif
	}
}

void sendCommandWithRollingCode(Command command) {
	uint16_t code;
	EEPROM.get(EEPROM_ADDRESS, code);
#ifdef DEBUG
	Serial.print("Rolling code: ");
	Serial.println(code);
#endif

	somfyRemote.sendCommand(command, code);
	EEPROM.put(EEPROM_ADDRESS, code + 1);
#if defined(ESP32) || defined(ESP8266)
	EEPROM.commit();
#endif
}
