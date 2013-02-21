#include "bisc.h"
#include "biscCore.h"


int biscDrive(int velocity, int radius) {
    assert(velocity >= -500 && velocity <= 500);
    //assert(radius >= -2000 && radius <= 2000);
    
    if(biscSendByte(BISC_CMD_DRIVE) == BISC_ERR) return BISC_ERR;

    if(biscSendInt(velocity) == BISC_ERR) return BISC_ERR;
    if(biscSendInt(radius)   == BISC_ERR) return BISC_ERR;

    // The LEDs turn off for whatever reason when a drive command is issued.
    // Resend the LED info so the LEDs stay in the same state.
    if(biscSendLedCommand() == BISC_ERR) return BISC_ERR;

    return BISC_SUCCESS;
}


int biscDirectDrive(int rightVelocity, int leftVelocity) {
    assert(rightVelocity >= -500 && rightVelocity <= 500);
    assert(leftVelocity >= -500 && leftVelocity <= 500);
    if(biscSendByte(BISC_CMD_DIRECT_DRIVE) == BISC_ERR) return BISC_ERR;

    if(biscSendInt(rightVelocity) == BISC_ERR) return BISC_ERR;
    if(biscSendInt(leftVelocity)  == BISC_ERR) return BISC_ERR;

    return BISC_SUCCESS;
}


int biscTimedDrive(int velocity, int radius, int mseconds) {
    assert(mseconds > 0);
    
    if(biscDrive(velocity, radius) == BISC_ERR) return BISC_ERR;
    if(biscWaitTime(mseconds)       == BISC_ERR) return BISC_ERR;
    if(biscDriveStop()             == BISC_ERR) return BISC_ERR;

    return BISC_SUCCESS;
}


int biscDriveDistance(int velocity, int radius, int distanceMM) {
    // If the velocity is negative, but the distance is positive, the Create will drive forever
    assert(velocity < 0 && distanceMM < 0);
    assert(velocity > 0 && distanceMM > 0);

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
    assert(mseconds > 0);

    if(biscSpin(velocity, radius) == BISC_ERR) return BISC_ERR;
    if(biscWaitTime(mseconds)     == BISC_ERR) return BISC_ERR;
    if(biscDriveStop()            == BISC_ERR) return BISC_ERR;

    return BISC_SUCCESS;
}


int biscSpinDegrees(int velocity, int radius, int degrees) {
    if(biscSpin(velocity, radius) == BISC_ERR) return BISC_ERR;
    if(biscWaitAngle(degrees)     == BISC_ERR) return BISC_ERR;
    if(biscDriveStop()            == BISC_ERR) return BISC_ERR;

    return BISC_SUCCESS;
}


int biscDriveStop(void) {
    return biscDrive(BISC_DRIVE_STOP, BISC_DRIVE_STOP);
}
