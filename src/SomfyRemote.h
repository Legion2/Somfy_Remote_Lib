#pragma once

#include <Arduino.h>

#include "RollingCodeStorage.h"

enum class Command : byte {
	My = 0x1,
	Up = 0x2,
	MyUp = 0x3,
	Down = 0x4,
	MyDown = 0x5,
	UpDown = 0x6,
	Prog = 0x8,
	SunFlag = 0x9,
	Flag = 0xA
};

class SomfyRemote {
private:
	byte emitterPin;
	uint32_t remote;
	RollingCodeStorage *const rollingCodeStorage;

	void buildFrame(byte *frame, Command command, uint16_t code);
	void sendFrame(byte *frame, byte sync);
	void printFrame(byte *frame);

	void sendHigh(uint16_t durationInMicroseconds);
	void sendLow(uint16_t durationInMicroseconds);

public:
	SomfyRemote(byte emitterPin, uint32_t remote, RollingCodeStorage *rollingCodeStorage);
	void setup();
	/**
	 * Send a command with this SomfyRemote.
	 *
	 * @param command the command to send
	 * @param repeat the number how often the command should be repeated, default 4. Should
	 * 				 only be used when simulating holding a button.
	 */
	void sendCommand(Command command, int repeat = 4);
	/**
	 * Send a command with this SomfyRemote.
	 *
	 * @param command the command to send
	 * @param rollingCode the rolling code to use. Should only be used with external storage.
	 * @param repeat the number how often the command should be repeated, default 4. Should
	 * 				 only be used when simulating holding a button.
	 */
	void sendCommandWithCode(Command command, uint16_t rollingCode, int repeat = 4);
};

Command getSomfyCommand(const String &string);
