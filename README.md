# Somfy Remote Lib
Based on [Somfy Remote](https://github.com/Nickduino/Somfy_Remote) by Nickduino.

An Arduino Library able to emulate a Somfy remote control on Arduino, ESP8266 and ESP32 devices.

If you want to learn more about the Somfy RTS protocol, check out [Pushtack](https://pushstack.wordpress.com/somfy-rts-protocol/).

## Requirements

For this library to work you need an *433.42 Mhz* RF transmitter.
The regular 433.92 MHz RF transmitter do not work, so watch out when buying a transmitter that you get a *433.42 Mhz* RF transmitter.
An example for such an compatible transmitter is the CC1101 module, see the [CC1101](examples/CC1101/CC1101.ino) example.
