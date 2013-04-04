#include "bisc.h"
#include "biscCore.h"


int biscDrive(int velocity, int radius) {
    #ifndef NDEBUG
        assert(velocity >= -500 && velocity <= 500);
        //assert(radius >= -2000 && radius <= 2000);
    #elif
        if(velocity < -500 || velocity < 500) return BISC_ERR;
        //if(radius < -2000 || radius > 2000) return BISC_ERR;
    #endif

        

    if(biscSendByte(BISC_CMD_DRIVE) == BISC_ERR) return BISC_ERR;

    if(biscSendInt(velocity) == BISC_ERR) return BISC_ERR;
    if(biscSendInt(radius)   == BISC_ERR) return BISC_ERR;

    // The LEDs turn off for whatever reason when a drive command is issued.
    // Resend the LED info so the LEDs stay in the same state.
    if(biscSendLedCommand() == BISC_ERR) return BISC_ERR;

    return BISC_SUCCESS;
}


int biscDirectDrive(int rightVelocity, int leftVelocity) {
    #ifndef NDEBUG
        assert(rightVelocity >= -500 && rightVelocity <= 500);
        assert(leftVelocity >= -500 && leftVelocity <= 500);
    #elif
        if(rightVelocity < -500 || rightVelocity > 500) return BISC_ERR;
        if(leftVelocity < -500 || leftVelocity > 500) return BISC_ERR;
    #endif

    if(biscSendByte(BISC_CMD_DIRECT_DRIVE) == BISC_ERR) return BISC_ERR;

    if(biscSendInt(rightVelocity) == BISC_ERR) return BISC_ERR;
    if(biscSendInt(leftVelocity)  == BISC_ERR) return BISC_ERR;

    return BISC_SUCCESS;
}


int biscTimedDrive(int velocity, int radius, int mseconds) {
    #ifndef NDEBUG
        assert(mseconds > 0);
    #elif
        if(mseconds <= 0) return BISC_ERR;
    #endif
    
    if(biscDrive(velocity, radius) == BISC_ERR) return BISC_ERR;
    if(biscWaitTime(mseconds)      == BISC_ERR) return BISC_ERR;
    if(biscDriveStop()             == BISC_ERR) return BISC_ERR;

    return BISC_SUCCESS;
}


int biscDriveDistance(int velocity, int radius, int distanceMM) {
    // If the velocity is negative, but the distance is positive, the Create will drive forever
    #ifndef NDEBUG
        assert(velocity < 0 && distanceMM < 0);
        assert(velocity > 0 && distanceMM > 0);
    #elif
        if(velocity > 0 && distanceMM < 0) return BISC_ERR;
        if(velocity < 0 && distanceMM > 0) return BISC_ERR;
    #endif

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


int biscSpin(int velocity) {
    return biscDrive(velocity, BISC_SPIN_CW);
}


int biscTimedSpin(int velocity, int mseconds) {
    #ifndef NDEBUG
        assert(mseconds > 0);
    #elif
        if(mseconds <= 0) return BISC_ERR;
    #endif

    if(biscSpin(velocity)     == BISC_ERR) return BISC_ERR;
    if(biscWaitTime(mseconds) == BISC_ERR) return BISC_ERR;
    if(biscDriveStop()        == BISC_ERR) return BISC_ERR;

    return BISC_SUCCESS;
}


int biscSpinAngle(int velocity, int degrees) {
    if(biscSpin(velocity)     == BISC_ERR) return BISC_ERR;
    if(biscWaitAngle(degrees) == BISC_ERR) return BISC_ERR;
    if(biscDriveStop()        == BISC_ERR) return BISC_ERR;

    return BISC_SUCCESS;
}


int biscDriveStop(void) {
    return biscDrive(BISC_DRIVE_STOP, BISC_DRIVE_STOP);
}
