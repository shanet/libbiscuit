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


int biscDisconnect() {
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


int biscChangeMode(int mode) {
    if(biscSendByte(BISC_CMD_START) == -1) return BISC_ERR;
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

int biscFlashLed(int led, int numFlashes, int flashDurationMS) {
    flashDurationMS *= 1000;
    for(int i=0; i<numFlashes; i++) {
        switch(led) {
            case BISC_PLAY_LED:
                if(biscTurnOnPlayLed() == BISC_ERR) return BISC_ERR;
                usleep(flashDurationMS);
                if(biscTurnOffPlayLed() == BISC_ERR) return BISC_ERR;
                usleep(flashDurationMS);
                break;
            case BISC_ADVANCE_LED:
                if(biscTurnOnAdvanceLed() == BISC_ERR) return BISC_ERR;
                usleep(flashDurationMS);
                if(biscTurnOffAdvanceLed() == BISC_ERR) return BISC_ERR;
                usleep(flashDurationMS);
                break;
            case BISC_POWER_LED:
                if(biscSetPowerLed(ledState.powerLedColor, BISC_POWER_LED_OFF) == BISC_ERR) return BISC_ERR;
                usleep(flashDurationMS);
                if(biscSetPowerLed(ledState.powerLedColor, BISC_POWER_LED_FULL) == BISC_ERR) return BISC_ERR;
                usleep(flashDurationMS);
                break;
            default:
                return -1;
        }
    }

    return BISC_SUCCESS;
}

int biscSendLedCommand() {
    if(biscSendByte(BISC_CMD_LEDS) == -1) return BISC_ERR;
    if(biscSendByte(ledState.playAdvanceState) == -1) return BISC_ERR;
    if(biscSendByte(ledState.powerLedColor) == -1) return BISC_ERR;
    if(biscSendByte(ledState.powerLedIntensity) == -1) return BISC_ERR;

    return BISC_SUCCESS;
}



int biscSendByte(char byte) {
    if(write(deviceDescriptor, &byte, 1) != 1) {
        return BISC_ERR;
    }

    //usleep(5000);
    return BISC_SUCCESS;
}


char* biscGetVersion() {
    return VERSION;
}