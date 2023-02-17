# `goco controller`

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

## Overview

Video game controller source code for the `goco` open-source video game Godot console.

## Details

The controller supports sending key presses using the traditional W/A/S/D button configuration for digital movement and A/B/X/Y button configuration for user action types. There are additionally two more digital buttons for HOME and PAUSE interactions. 

The controller also supports an analog input via joystick that is detected by a computer as a mouse device.

## Building

A makefile is provided to aid in common development commands.

1. Compile the source code:
```
make cc
```

2. Upload the binaries to the plugged-in Arduino Leonardo board:
```
make up
```

## Dependencies

- arduino-cli (see [getting started](https://arduino.github.io/arduino-cli/0.29/getting-started/) for initial setup)
- GNU Make

