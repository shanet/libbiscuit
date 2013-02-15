#include "bisc.h"
#include "biscCore.h"


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