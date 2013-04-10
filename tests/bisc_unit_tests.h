#ifndef BISC_UNIT_TESTS
#define BISC_UNIT_TESTS

#include <stdio.h>
#include <string.h>
#include <CUnit/Basic.h>

#include "bisc.h"

int cleanBiscTestSuite(void);

void testBiscInit(void);
void testBiscDrive(void);
void testBiscDirectDrive(void);
void testBiscTimedDrive(void);
void testBiscDriveDistance(void);
void testBiscTimedSpin(void);
void testBiscFlashLed(void);
void testBiscDefineSong(void);

#endif
