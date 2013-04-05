libBiscuit
=======

#### Shane Tully (shanetully.com)
##### shane@shanetully.com

libBiscuit is a simple iRobot Create API written in C for Linux.

## Compiling

The provided Makefile builds libbiscuit into a shared object and static archive that you can use in your own projects. To build the libbiscuit just run `make all`. The compiled files will be in the bin directory.

## Usage

To use libbiscuit in your project, link against the static library or shared object compiled as outlined in the compiling section and include `bisc.h` (in the include directory) in your header(s).

To use the library, you must first connect to the iRobot Create with the `bisc_init([device])` function, where `device` is the block device of the Create (this is usually `/dev/ttyUSB0`). After `bisc_init()`, you'll be connected to the Create and ready to call any other function to control it.

A brief outline of interesting functions follows. When in doubt, look at the source--it's very straightforward. At the very least, take a look at `bisc.h`; a lot of helpful macros are defined in there.

### Core functions
`int biscInit(char *device);`
* Connect to the Create

`int biscDisconnect(void);`
* Disconnect from the Create

`int biscChangeMode(unsigned char mode);`
* Change the mode of the create. Available modes:
    * `BISC_MODE_PASSIVE`
    * `BISC_MODE_SAFE`
    * `BISC_MODE_FULL`

`int biscSendByte(unsigned char byte);`
* Send a given byte directly to the Create

`int biscSendInt(int num);`
* Send a given int directly to the Create

`char* biscGetVersion(void);`
* Get the version of libbiscuit

### Drive functions
`int biscDrive(int velocity, int radius);`
* Drive the Create at the given velocity and radius.

`int biscDirectDrive(int rightVelocity, int leftVelocity);`
* Control the Create's wheels independently of one another.

`int biscTimedDrive(int velocity, int radius, int mseconds);`
* Drive at the given velocity and radius for the given number of milliseconds.

`int biscDriveDistance(int velocity, int radius, int distanceMM);`
* Drive at the given velocity and radius for the given number of millimeters. Note that distance is actually a displacement; that is, if the velocity of negative, the distance is measured as negative distance.

`int biscDriveStraight(int velocity);`
* Drive straight at the given velocity.

`int biscTimedDriveStraight(int velocity, int mseconds);`
* Drive straight at the given velocity for the given number of milliseconds.

`int biscDriveDistanceStraight(int velocity, int distanceMM);`
* Drive straight at the given velocity for the given number of millimeters.

`int biscSpin(int velocity);`
* Spin in place at the given velocity.

`int biscTimedSpin(int velocity, int mseconds);`
* Spin in place at the given velocity for the given number of milliseconds.

`int biscSpinAngle(int velocity, int degrees);`
* Spin in place at the given velocity for the given number of degrees.

`int biscDriveStop(void);`
* Stop the Create.

### LED functions
`int biscTurnOnAdvanceLed(void);`
* Turn on the advance LED.

`int biscTurnOffAdvanceLed(void);`
* Turn off the advance LED.

`int biscTurnOnPlayLed(void);`
* Turn on the play LED.

`int biscTurnOffPlayLed(void);`
* Turn off the play LED.

`int biscSetPowerLed(unsigned char color, unsigned char intensity);`
* Set the power LED to the given color and intensity. Both color and intensity are values between 0-255, where 0 is green, red is 255 and 0 is off, and 255 is highest full brightness. Macros are defined in `bisc.h` to help with this.

`int biscTurnOffPowerLed(void);`
* Turn off the power LED.

`int biscFlashLed(char led, int numFlashes, int flashDurationMS);`
* Flash the given LED a number of times for a number of milliseconds. Valid LEDS:
    * `BISC_POWER_LED`
    * `BISC_PLAY_LED`
    * `BISC_ADVANCE_LED`

### Wait functions
`int biscWaitTime(int mseconds);`
* Wait a given time in milliseconds.

`int biscWaitDistance(int distanceMM);`
* Wait for the Create to travel a given distance. Note that despite the name, this is actually a displacement measurement. If the velocity of the Create is negative, the distance traveled is measured as negative.

`int biscWaitAngle(int degrees);`
* Wait for the Create to rotate a given number of degrees.

`int biscWaitEvent(int eventCode);`
* Wait for an event to happen as defined by the Open Interface.

### Song functions
`int biscDefineSong(unsigned char songNum, unsigned char *notes, unsigned char *notesDurations, unsigned int notesLen);`
* Define a given song number. `notes` is an array of notes as defined by the Open Interface.

`int biscPlaySong(unsigned char songNum);`
* Play a previously defined song

`int biscBeep(void);`
* Play a short beep.

`int biscPlayFireflies(void);`
* Play a song the resembles Fireflies by Owl City


## License
Copyright (C) 2013 Shane Tully

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
