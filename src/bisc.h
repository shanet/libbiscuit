#include <stdio.h>
#include <string.h>
#include <termios.h> 
#include <unistd.h> 
#include <errno.h>
#include <sys/file.h>

#define BISC_BAUD_RATE B57600

#define BISC_CMD_START       128

#define BISC_CmdControl      130

#define BISC_MODE_SAFE       131
#define BISC_MODE_FULL       132
#define BISC_MODE_PASSIVE    128

#define BISC_CMD_LEDS        139

#define BISC_CmdSpot         134
#define BISC_CmdClean        135
#define BISC_CmdDemo         136
#define BISC_CmdDrive        137
#define BISC_CmdMotors       138


#define BISC_CmdSong         140
#define BISC_CmdPlay         141
#define BISC_CmdSensors      142
#define BISC_CmdDock         143
#define BISC_CmdPWMMotors    144
#define BISC_CmdDriveWheels  145
#define BISC_CmdOutputs      147
#define BISC_CmdSensorList   149
#define BISC_CmdIRChar       151

// LEDs
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


typedef struct {
    char playAdvanceState;
    char powerLedColor;
    char powerLedIntensity;
} LedState;


static int deviceDescriptor;
static LedState ledState;

int biscInit(char *device);
int biscConnect(char *device);
int biscChangeMode(int mode);
int biscTurnOnAdvanceLed();
int biscTurnOffAdvanceLed();
int biscTurnOnPlayLed();
int biscTurnOffPlayLed();
int biscSetPowerLed(int color, int intensity);
int biscTurnOffPowerLed();
int biscSendLedCommand();

char* biscGetVersion();

int biscSendByte(char byte);