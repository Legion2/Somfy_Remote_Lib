# Somfy Remote Lib [![Test](https://github.com/Legion2/Somfy_Remote_Lib/workflows/Test/badge.svg)](https://github.com/Legion2/Somfy_Remote_Lib/actions?query=event%3Apush+workflow%3Atest)

Based on [Somfy Remote](https://github.com/Nickduino/Somfy_Remote) by Nickduino.

This project is an Arduino Library able to emulate a Somfy remote control on Arduino, ESP8266 and ESP32 devices.
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

### Installation

This library can be install using the Library-Manager.
Open the Library-Manager in Arduino IDE via Tools->Manage Libraries...
Search for "Somfy_Remote_Lib" and install the Somfy Remote Lib library.

### Usage

See the [SomfyRemote example](examples/SomfyRemote/SomfyRemote.ino).
