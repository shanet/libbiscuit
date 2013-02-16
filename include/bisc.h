#ifndef BISC_H
#define BISC_H

#define BISC_SUCCESS  0
#define BISC_ERR     -1

#define BISC_BAUD_RATE       B57600

#define BISC_CMD_START         128
#define BISC_CMD_LEDS          139
#define BISC_CMD_DRIVE         137
#define BISC_CMD_DIRECT_DRIVE  145
#define BISC_CMD_WAIT_TIME     155
#define BISC_CMD_WAIT_DISTANCE 156

#define BISC_MODE_PASSIVE 128
#define BISC_MODE_SAFE    131
#define BISC_MODE_FULL    132


#define BISC_CmdControl      130
#define BISC_CmdSong         140
#define BISC_CmdPlay         141
#define BISC_CmdSensors      142
#define BISC_CmdDock         143
#define BISC_CmdPWMMotors    144
#define BISC_CmdDriveWheels  145
#define BISC_CmdOutputs      147
#define BISC_CmdSensorList   149
#define BISC_CmdIRChar       151

// Drive
#define BISC_DRIVE_FORWARD_FULL_SPEED      500
#define BISC_DRIVE_BACKWARD_FULL_SPEED    -500
#define BISC_DRIVE_FORWARD_HALF_SPEED      250
#define BISC_DRIVE_BACKWARD_HALF_SPEED    -250
#define BISC_DRIVE_FORWARD_QUARTER_SPEED   125
#define BISC_DRIVE_BACKWARD_QUARTER_SPEED -125
#define BISC_DRIVE_STRAIGHT                0x7FFF
#define BISC_SPIN_CW                       0xFFFF
#define BISC_SPIN_CCW                      0x1
#define BISC_DRIVE_STOP                    0


// LEDs
#define BISC_POWER_LED                 0
#define BISC_PLAY_LED                  1
#define BISC_ADVANCE_LED               2

#define BISC_PLAY_LED_ON               2
#define BISC_ADVANCE_LED_ON            8
#define BISC_ADVANCE_AND_PLAY_LEDS_ON  BISC_PLAY_LED | BISC_ADVANCE_LED
#define BISC_PLAY_LED_OFF              0
#define BISC_ADVANCE_LED_OFF           0
#define BISC_ADVANCE_AND_PLAY_LEDS_OFF 0

#define BISC_POWER_LED_RED             255
#define BISC_POWER_LED_ORANGE          128
#define BISC_POWER_LED_GREEN           0
#define BISC_POWER_LED_FULL            255
#define BISC_POWER_LED_HALF            128
#define BISC_POWER_LED_OFF             0

#define BISC_PLAY_LED_BIT              1
#define BISC_ADVANCE_LED_BIT           3


// Basic functions
int biscInit(char *device);
int biscConnect(char *device);
int biscDisconnect(void);
int biscChangeMode(unsigned char mode);
int biscSendByte(unsigned char byte);
char* biscGetVersion(void);
char biscHighByte(int num);
char biscLowByte(int num);

// Drive functions
int biscDrive(int velocity, int radius);
int biscDirectDrive(int rightVelocity, int leftVelocity);
int biscTimedDrive(int velocity, int radius, int mseconds);
int biscDriveDistance(int velocity, int radius, int distanceMM);
int biscDriveStraight(int velocity);
int biscTimedDriveStraight(int velocity, int mseconds);
int biscDriveDistanceStraight(int velocity, int distanceMM);
int biscSpin(int velocity, int radius);
int biscTimedSpin(int velocity, int radius, int mseconds);
int biscDriveStop(void);

// LED functions
int biscTurnOnAdvanceLed(void);
int biscTurnOffAdvanceLed(void);
int biscTurnOnPlayLed(void);
int biscTurnOffPlayLed(void);
int biscSetPowerLed(unsigned char color, unsigned char intensity);
int biscFlashLed(char led, int numFlashes, int flashDurationMS);
int biscTurnOffPowerLed(void);
int biscSendLedCommand(void);

// Wait functions
int biscWaitTime(int mseconds);
int biscWaitDistance(int distanceMM);


#endif