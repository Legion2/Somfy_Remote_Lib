#include <EEPROM.h>
#include <ELECHOUSE_CC1101_SRC_DRV.h>
#include <SomfyRemote.h>

#define EMITTER_GPIO 2
#define EEPROM_ADDRESS 0
#define REMOTE 0x5184c8

#define CC1101_FREQUENCY 433.42

SomfyRemote somfyRemote(EEPROM_ADDRESS, REMOTE, EMITTER_GPIO);

void setup() {
	Serial.begin(115200);
	ELECHOUSE_cc1101.Init();
	ELECHOUSE_cc1101.setMHZ(CC1101_FREQUENCY);
	ELECHOUSE_cc1101.SetTx();

#ifdef ESP32 || ESP8266
	EEPROM.begin(4);
#endif

	somfyRemote.setup();
}

void loop() {
	if (Serial.available() > 0) {
		char serie = (char)Serial.read();
		Command command = static_cast<Command>(serie - '0');
		somfyRemote.sendCommand(command);
		Serial.println("finished sending");
	}
}
