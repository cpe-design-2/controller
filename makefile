# File: makefile
# Description:
# 	Compiles the C code for the targeted Arduino microcontroller.

# to see the desired port and board-id run: `arduino-cli board list`
PORT=COM9
BOARD_ID=arduino:avr:leonardo

.PHONY: cc
cc:
	arduino-cli compile --fqbn arduino:avr:leonardo . --build-path build --output-dir build/out 

.PHONY: up
up:
	arduino-cli upload --fqbn arduino-cli compile --fqbn arduino:avr:leonardo -p COM9 --input-dir build/out

.PHONY: clean
clean:
	rm -Rf build