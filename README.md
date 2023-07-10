# Somfy Remote Lib [![Test](https://github.com/Legion2/Somfy_Remote_Lib/workflows/Test/badge.svg)](https://github.com/Legion2/Somfy_Remote_Lib/actions?query=event%3Apush+workflow%3Atest)

Based on [Somfy Remote](https://github.com/Nickduino/Somfy_Remote) by Nickduino.

This project is an Arduino Library able to emulate a Somfy RTS (Radio Technology Somfy) remote control on Arduino, ESP8266 and ESP32 devices.
It provides out of the box support for multiple remotes and different storage solutions for the rolling codes.
Because it is a Arduino Library it can easily included in existing projects or used standalone using one of its [included example sketches](examples/).

If you want to learn more about the Somfy RTS protocol, check out [Pushtack](https://pushstack.wordpress.com/somfy-rts-protocol/).

## Getting Started

This library was tested with ESP32 and the CC1101 transceiver module.
It should also work on any Arduino and ESP8266 Board with any *433.42 Mhz* RF transmitter.
I have not the time and resources to test them all, so please let me know (open an Issue) when you have any problem or have tested other hardware with this library.

### Hardware Requirements

For this library to work you need an *433.42 Mhz* RF transmitter.
The regular 433.92 MHz RF transmitter do not work, so watch out when buying a transmitter that you get a *433.42 Mhz* RF transmitter.
An example for such an compatible transmitter is the CC1101 module, see the [CC1101](examples/CC1101/CC1101.ino) example.
For the CC1101 module the `SmartRC-CC1101-Driver-Lib` must be installed.

### Installation

This library can be install using the Library-Manager.
Open the Library-Manager in Arduino IDE via Tools->Manage Libraries...
Search for "Somfy_Remote_Lib" and install the Somfy Remote Lib library.

### Usage

See the [SomfyRemote example](examples/SomfyRemote/SomfyRemote.ino).

All the examples can be controlled via the Serial Monitor.
Open the Serial Monitor and set the baud rate to 115200 and set line endings to `Newline` (`\n`).
You can type in the name of the command or the hexadecimal representation of it.

#### Rolling Code Storage

This library has a plugable interface for storing the rolling codes, described in [RollingCodeStorage.h](src/RollingCodeStorage.h).

Currently, there are two implementations of the storage available:

1. [EEPROM](src/EEPROMRollingCodeStorage.cpp) - should work on any device with EEPROM
2. [NVS](src/NVSRollingCodeStorage.cpp) - should work on ESP32 with [Non Volatile Storage](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/storage/nvs_flash.html)

Most [examples](examples/) use the EEPROM implementation. See the [ESP32-NVS](examples/ESP32-NVS/ESP32-NVS.ino) example for NVS.

Eventually you can pass NULL into the constructor of the SomfyRemote class in place of *rollingCodeStorage* and use external rolling code keeping logic. 
If you are not using any storage, then you have to use `sendCommandWithCode` method instead of `sendCommand`.

#### Available commands

| Name    | Description                                     | HEX code |
|---------|-------------------------------------------------|----------|
| My      | The My button pressed                           | 1        |
| Up      | The Up button pressed                           | 2        |
| MyUp    | The My and Up button pressed at the same time   | 3        |
| Down    | The Down button pressed                         | 4        |
| MyDown  | The My and Down button pressed at the same time | 5        |
| UpDown  | The Up and Down button pressed at the same time | 6        |
| Prog    | The Prog button pressed                         | 8        |
| SunFlag | Enable sun and wind detector                    | 9        |
| Flag    | Disable sun detector                            | A        |

The `sendCommand` function can be customized with a second parameter.
The parameter controlls how often the command is repeated, default is 4 times.

For remote control Telis 4 Modulis RTS5 the following applies:
When the UP command is sent once, the blinds go up (Open).
```cpp
sendCommand(Command::Up, 1);
```
When the DOWN command is sent once, the blinds go down (Close).
```cpp
sendCommand(Command::Down, 1);
```
If you want to tilt the blinds, send the Up / Down command four times.
```cpp
sendCommand(Command::Up, 4);
```
or
```cpp
sendCommand(Command::Down, 4);
```

#### Register the Somfy Remote

Before the emulated Somfy remote can control RTS devices, the remote must be registered.
Therefore you can refer to the original manual of your RTS device, the only difference is that instead of pressing buttons, the commands from above must be used.
So for example if the PROG button should be pressed, instead send the `Prog` command.

### Troubleshooting

#### Up/down commands not responsive after successful PROG

If your blinds jump to respond to the PROG command when registering the remote, but following commands like up and down do not respond, it is likely that your rolling code storage is not persisting. The result of this is that the remote will send a constant rolling code, which the blinds will ignore.

In the case of NVS storage, a possible cause for this is that the key used is too long. The key must [comform with the limitations of your microcontroller](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/storage/nvs_flash.html#keys-and-values).
