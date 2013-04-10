#include "bisc.h"
#include "biscCore.h"


int biscTurnOnAdvanceLed(void) {
    ledState.playAdvanceState |= BISC_ADVANCE_LED_ON;
    return biscSendLedCommand();
}


int biscTurnOffAdvanceLed(void) {
    ledState.playAdvanceState ^= 1 << BISC_ADVANCE_LED_BIT;
    return biscSendLedCommand();
}


int biscTurnOnPlayLed(void) {
    ledState.playAdvanceState |= BISC_PLAY_LED_ON;
    return biscSendLedCommand();
}


int biscTurnOffPlayLed(void) {
    ledState.playAdvanceState ^= 1 << BISC_PLAY_LED_BIT;
    return biscSendLedCommand();
}


int biscSetPowerLed(unsigned char color, unsigned char intensity) {
    ledState.powerLedColor = color;
    ledState.powerLedIntensity = intensity;

    return biscSendLedCommand();
}


int biscTurnOffPowerLed(void) {
    ledState.powerLedIntensity = BISC_POWER_LED_OFF;
    return biscSendLedCommand();
}


int biscFlashLed(char led, int numFlashes, int flashDurationMS) {
    if(led < BISC_POWER_LED || led > BISC_ADVANCE_LED) return BISC_ERR;
    if(numFlashes <= 0)                                return BISC_ERR;
    if(flashDurationMS <= 0)                           return BISC_ERR;

    // Keep a backup of the LED state so it can be restored after flashing
    LedState stateBackup = ledState;

    for(int i=0; i<numFlashes; i++) {
        switch(led) {
            case BISC_PLAY_LED:
                if(biscTurnOnPlayLed() == BISC_ERR) return BISC_ERR;
                break;
            case BISC_ADVANCE_LED:
                if(biscTurnOnAdvanceLed() == BISC_ERR) return BISC_ERR;
                break;
            case BISC_POWER_LED:
                if(biscSetPowerLed(ledState.powerLedColor, BISC_POWER_LED_FULL) == BISC_ERR) return BISC_ERR;
                break;
            default:
                return -1;
        }

        if(biscWaitTime(flashDurationMS) == BISC_ERR) return BISC_ERR;

        switch(led) {
            case BISC_PLAY_LED:
                if(biscTurnOffPlayLed() == BISC_ERR) return BISC_ERR;
                break;
            case BISC_ADVANCE_LED:
                if(biscTurnOffAdvanceLed() == BISC_ERR) return BISC_ERR;
                break;
            case BISC_POWER_LED:
                if(biscSetPowerLed(ledState.powerLedColor, BISC_POWER_LED_OFF) == BISC_ERR) return BISC_ERR;
                break;
            default:
                return -1;
        }

        if(biscWaitTime(flashDurationMS) == BISC_ERR) return BISC_ERR;
    }

    // Restore the LED state
    ledState = stateBackup;
    if(biscSendLedCommand() == BISC_ERR) return BISC_ERR;

    return BISC_SUCCESS;
}


int biscSendLedCommand(void) {
    if(biscSendByte(BISC_CMD_LEDS)              == BISC_ERR) return BISC_ERR;
    if(biscSendByte(ledState.playAdvanceState)  == BISC_ERR) return BISC_ERR;
    if(biscSendByte(ledState.powerLedColor)     == BISC_ERR) return BISC_ERR;
    if(biscSendByte(ledState.powerLedIntensity) == BISC_ERR) return BISC_ERR;

    return BISC_SUCCESS;
}