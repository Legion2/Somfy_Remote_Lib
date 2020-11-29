#include <EEPROM.h>
#include <EEPROMRollingCodeStorage.h>
#include <SomfyRemote.h>

#define EMITTER_GPIO 2
#define REMOTE1 0x65dc00
#define REMOTE2 0x25b5d5
#define REMOTE3 0xc6c78f
#define REMOTE4 0x59714b

EEPROMRollingCodeStorage rollingCodeStorage1(0);
EEPROMRollingCodeStorage rollingCodeStorage2(2);
EEPROMRollingCodeStorage rollingCodeStorage3(4);
EEPROMRollingCodeStorage rollingCodeStorage4(6);
SomfyRemote somfyRemote1(EMITTER_GPIO, REMOTE1, &rollingCodeStorage1);
SomfyRemote somfyRemote2(EMITTER_GPIO, REMOTE2, &rollingCodeStorage2);
SomfyRemote somfyRemote3(EMITTER_GPIO, REMOTE3, &rollingCodeStorage3);
SomfyRemote somfyRemote4(EMITTER_GPIO, REMOTE4, &rollingCodeStorage4);

void setup() {
	Serial.begin(115200);
	pinMode(EMITTER_GPIO, OUTPUT);
	digitalWrite(EMITTER_GPIO, LOW);

#if defined(ESP32)
	if (!EEPROM.begin(8)) {
		Serial.println("failed to initialise EEPROM");
		delay(1000);
	}
#elif defined(ESP8266)
	EEPROM.begin(8);
#endif
}

void loop() {
	if (Serial.available() > 0) {
		const String string = Serial.readStringUntil('\n');
		const Command command = getSomfyCommand(string);
		somfyRemote1.sendCommand(command);
		somfyRemote2.sendCommand(command);
		somfyRemote3.sendCommand(command);
		somfyRemote4.sendCommand(command);
	}
}
