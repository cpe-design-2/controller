# File: makefile
# Description:
# 	Compiles the C code for the targeted Arduino microcontroller.

# to see the desired port and board-id run: `arduino-cli board list`
PORT=/dev/cu.usbmodem14101
BOARD_ID=arduino:avr:pro

.PHONY: cc
cc:
	arduino-cli compile --fqbn $(BOARD_ID) . --build-path build --output-dir build/out

.PHONY: up
up:
	arduino-cli upload --fqbn $(BOARD_ID) -p /dev/cu.usbmodem14101 . --input-dir build/out

.PHONY: clean
clean:
	rm -Rf build