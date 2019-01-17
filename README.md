# Leonardo-Switch-Controller
Using Arduino Leonardo as a Pokken Tournament Pro Pad Wii U Controller that also works on Nintendo Switch as an almost Pro controller. Transfers input from a Wii Classic Controller.

# Current Status
- [x] Working on Switch, suitable for playing Super Smash Bros. Ultimate.
- [x] Remapped Home to Home and Plus
- [x] Remapped Capture to Home and Minus
- [x] Added toggle for mashing joystick down (for SSBU coin farming) with Home+A (on) or Home+B (off).
- [ ] Untested on Wii U for Pokken
- [ ] Does not work Windows without changing part of Arduino Joystick Library back to how it should be.

# Equipment and Setup
* Arduino Leonardo with an altered boards.txt
* [Nunchucky](https://www.adafruit.com/product/345) or [WiiChuck Adapter](https://www.sparkfun.com/products/retired/9281)
* Wii Classic Controller

As the WiiChuck Adapter was designed for Uno which has different I2C pins, rather than plugging into A2-A5 you must connect it to the Leonardo as follows:
* i2c **d**ata to D2
* i2c **c**lock to D3
* Negative to GND
* Positive to 3.3V

# Derived From
* https://github.com/MHeironimus/ArduinoJoystickLibrary (Version 1.0)
* https://github.com/dmadison/NintendoExtensionCtrl
* Reference: https://github.com/progmem/Switch-Fightstick
