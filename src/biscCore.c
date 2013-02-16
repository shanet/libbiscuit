#include "bisc.h"
#include "biscCore.h"


int biscInit(char *device) {
    // Open a serial connection with the Create
    if(biscConnect(device) == -1) return BISC_ERR;

    // Put the Create in safe mode
    if(biscSendByte(BISC_CMD_START) == -1) return BISC_ERR;
    if(biscSendByte(BISC_MODE_SAFE) == -1) return BISC_ERR;

    ledState.playAdvanceState = BISC_ADVANCE_AND_PLAY_LEDS_OFF;
    ledState.powerLedColor = BISC_POWER_LED_GREEN;
    ledState.powerLedIntensity = BISC_POWER_LED_FULL;

    return BISC_SUCCESS;
}


int biscConnect(char *device) {
    struct termios tty;

    // Try to open the device
    if((deviceDescriptor = open(device, O_RDWR | O_NOCTTY | O_NONBLOCK)) == -1) {
        return BISC_ERR;
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


int biscDisconnect(void) {
    // Check if not connected
    if(deviceDescriptor == 0) {
        return BISC_ERR;
    }

    if(close(deviceDescriptor) == -1) {
        return BISC_ERR;
    }

    deviceDescriptor = 0;
    return BISC_SUCCESS;
}


int biscChangeMode(char mode) {
    if(biscSendByte(BISC_CMD_START) == -1) return BISC_ERR;
    return biscSendByte(mode);
}


int biscSendByte(char byte) {
    usleep(10000);
    return (write(deviceDescriptor, &byte, 1) == 1 ? BISC_SUCCESS : BISC_ERR);
}


char biscHighByte(int num) {
    return (num >> 8) & 0xff;
}


char biscLowByte(int num) {
    return num & 0xff;
}


char* biscGetVersion(void) {
    return VERSION;
}


int biscWaitTime(int mseconds) {
    if(biscSendByte(BISC_CMD_WAIT_TIME) == BISC_ERR) return BISC_ERR;
    if(biscSendByte(mseconds / 100)     == BISC_ERR) return BISC_ERR;

    return BISC_SUCCESS;
}


int biscWaitDistance(int distanceMM) {
    if(biscSendByte(BISC_CMD_WAIT_DISTANCE)   == BISC_ERR) return BISC_ERR;
    if(biscSendByte(biscHighByte(distanceMM)) == BISC_ERR) return BISC_ERR;
    if(biscSendByte(biscLowByte(distanceMM))  == BISC_ERR) return BISC_ERR;

    return BISC_SUCCESS;
}