#include "bisc.h"
#include "biscCore.h"


int biscInit(char *device) {
    // Open a serial connection with the Create
    if(biscConnect(device) == -1) return -1;

    // Put the Create in safe mode
    if(biscSendByte(BISC_CMD_START) == -1) return -1;
    if(biscSendByte(BISC_MODE_SAFE) == -1) return -1;

    ledState.playAdvanceState = BISC_ADVANCE_AND_PLAY_LEDS_OFF;
    ledState.powerLedColor = BISC_POWER_LED_GREEN;
    ledState.powerLedIntensity = BISC_POWER_LED_FULL;

    return 0;
}


int biscConnect(char *device) {
    int deviceDescriptor = -1;
    struct termios tty;

    // Try to open the device
    if((deviceDescriptor = open(device, O_RDWR | O_NOCTTY | O_NONBLOCK)) == -1) {
        return -1;
    }

    tcgetattr(deviceDescriptor, &tty);
    tty.c_iflag     = IGNBRK | IGNPAR;
    tty.c_lflag     = 0;
    tty.c_oflag     = 0;
    tty.c_cflag     = CREAD | CS8 | CLOCAL;
    cfsetispeed(&tty, BISC_BAUD_RATE);
    cfsetospeed(&tty, BISC_BAUD_RATE);
    tcsetattr(deviceDescriptor, TCSANOW, &tty);

    return deviceDescriptor;
}


int biscChangeMode(int mode) {
    if(biscSendByte(BISC_CMD_START) == -1) return -1;
    return biscSendByte(mode);
}


int biscTurnOnAdvanceLed() {
    ledState.playAdvanceState |= BISC_ADVANCE_LED_ON;
    return biscSendLedCommand();
}

int biscTurnOffAdvanceLed() {
    ledState.playAdvanceState ^= 1 << BISC_ADVANCE_LED_BIT;
    return biscSendLedCommand();
}

int biscTurnOnPlayLed() {
    ledState.playAdvanceState |= BISC_PLAY_LED_ON;
    return biscSendLedCommand();
}

int biscTurnOffPlayLed() {
    ledState.playAdvanceState ^= 1 << BISC_PLAY_LED_BIT;
    return biscSendLedCommand();
}

int biscSetPowerLed(int color, int intensity) {
    ledState.powerLedColor = color;
    ledState.powerLedIntensity = intensity;
    return biscSendLedCommand();
}

int biscTurnOffPowerLed() {
    ledState.powerLedIntensity = BISC_POWER_LED_OFF;
    return biscSendLedCommand();
}

int biscSendLedCommand() {
    if(biscSendByte(BISC_CMD_LEDS) == -1) return -1;
    if(biscSendByte(ledState.playAdvanceState) == -1) return -1;
    if(biscSendByte(ledState.powerLedColor) == -1) return -1;
    if(biscSendByte(ledState.powerLedIntensity) == -1) return -1;

    return 0;
}



int biscSendByte(char byte) {
    if(write(deviceDescriptor, &byte, 1) == -1) {
        return -1;
    }

    usleep(5000);
    return 0;
}


char* biscGetVersion() {
    return VERSION;
}