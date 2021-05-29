#include <NVSRollingCodeStorage.h>
#include <SomfyRemote.h>

#define EMITTER_GPIO 2
#define NVS_NAME "somfy"
#define NVS_KEY "remote_1"
#define REMOTE 0x5184c8

NVSRollingCodeStorage rollingCodeStorage(NVS_NAME, NVS_KEY);
SomfyRemote somfyRemote(EMITTER_GPIO, REMOTE, &rollingCodeStorage);

void setup() {
	Serial.begin(115200);

	somfyRemote.setup();
}

void loop() {
	if (Serial.available() > 0) {
		const String string = Serial.readStringUntil('\n');
		const Command command = getSomfyCommand(string);
		somfyRemote.sendCommand(command);
#ifdef DEBUG
		Serial.println("finished sending");
#endif
	}
}
