#ifndef BISC_UNIT_TESTS
#define BISC_UNIT_TESTS

#include <stdio.h>
#include <string.h>
#include <CUnit/Basic.h>

#include "bisc.h"

int errAddingTestsToSuite(void);

void testBiscInitNoDevice(void);
void testBiscInitNormal(void);

void testBiscDriveUpper(void);
void testBiscDriveLower(void);
void testBiscDriveNormal(void);

void testBiscDirectDriveUpperLeft(void);
void testBiscDirectDriveLowerLeft(void);
void testBiscDirectDriveUpperRight(void);
void testBiscDirectDriveLowerRight(void);
void testBiscDirectDriveNormal(void);

void testBiscTimedDriveZero(void);
void testBiscTimedDriveNormal(void);

void testBiscDriveDistanceNegativeDistance(void);
void testBiscDriveDistanceNegativeVelocity(void);
void testBiscDriveDistanceNormal(void);

void testBiscTimedSpinZero(void);
void testBiscTimedSpinNormal(void);

void testBiscFlashLedNoFlashes(void);
void testBiscFlashLedNoDuration(void);
void testBiscFlashLedNormal(void);

void testBiscDefineSongInvalidSong(void);
void testBiscDefineSongNormal(void);

#endif
