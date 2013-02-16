#include "bisc.h"


int biscDrive(int velocity, int radius) {
    if(biscSendByte(BISC_CMD_DRIVE) == BISC_ERR) return BISC_ERR;

    if(biscSendByte(biscHighByte(velocity)) == BISC_ERR) return BISC_ERR;
    if(biscSendByte(biscLowByte(velocity))  == BISC_ERR) return BISC_ERR;
    if(biscSendByte(biscHighByte(radius))   == BISC_ERR) return BISC_ERR;
    if(biscSendByte(biscLowByte(radius))    == BISC_ERR) return BISC_ERR;

    // The LEDs turn off for whatever reason when a drive command is issued.
    // Resend the LED info so the LEDs stay in the same state.
    if(biscSendLedCommand() == BISC_ERR) return BISC_ERR;

    return BISC_SUCCESS;
}


int biscDirectDrive(int rightVelocity, int leftVelocity) {
    if(biscSendByte(BISC_CMD_DIRECT_DRIVE) == BISC_ERR) return BISC_ERR;

    if(biscSendByte(biscHighByte(rightVelocity)) == BISC_ERR) return BISC_ERR;
    if(biscSendByte(biscLowByte(rightVelocity))  == BISC_ERR) return BISC_ERR;
    if(biscSendByte(biscHighByte(leftVelocity))  == BISC_ERR) return BISC_ERR;
    if(biscSendByte(biscLowByte(leftVelocity))   == BISC_ERR) return BISC_ERR;

    return BISC_SUCCESS;
}


int biscTimedDrive(int velocity, int radius, int seconds) {
    if(biscDrive(velocity, radius) == BISC_ERR) return BISC_ERR;
    if(biscWaitTime(seconds)       == BISC_ERR) return BISC_ERR;
    if(biscDriveStop()             == BISC_ERR) return BISC_ERR;

    return BISC_SUCCESS;
}


int biscDriveDistance(int velocity, int radius, int distanceMM) {
    if(biscDrive(velocity, radius)  == BISC_ERR) return BISC_ERR;
    if(biscWaitDistance(distanceMM) == BISC_ERR) return BISC_ERR;
    if(biscDriveStop()              == BISC_ERR) return BISC_ERR;

    return BISC_SUCCESS;
}


int biscDriveStraight(int velocity) {
    return biscDrive(velocity, BISC_DRIVE_STRAIGHT);
}


int biscTimedDriveStraight(int velocity, int mseconds) {
    return biscTimedDrive(velocity, BISC_DRIVE_STRAIGHT, mseconds);
}


int biscDriveDistanceStraight(int velocity, int distanceMM) {
    return biscDriveDistance(velocity, BISC_DRIVE_STRAIGHT, distanceMM);
}


int biscSpin(int velocity, int radius) {
    return biscDrive(velocity, radius);
}


int biscTimedSpin(int velocity, int radius, int mseconds) {
    if(biscSpin(velocity, radius) == BISC_ERR) return BISC_ERR;
    if(biscWaitTime(mseconds)     == BISC_ERR) return BISC_ERR;
    if(biscDriveStop()            == BISC_ERR) return BISC_ERR;

    return BISC_SUCCESS;
}


int biscDriveStop(void) {
    return biscDrive(BISC_DRIVE_STOP, BISC_DRIVE_STOP);
}
