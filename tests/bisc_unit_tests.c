#include "bisc_unit_tests.h"


int main(void) {
    CU_pSuite biscInitSuite;
    CU_pSuite biscDriveSuite;
    CU_pSuite biscDirectDriveSuite;
    CU_pSuite biscTimedDriveSuite;
    CU_pSuite biscDriveDistanceSuite;
    CU_pSuite biscTimedSpinSuite;
    CU_pSuite biscFlashLedSuite;
    CU_pSuite biscDefineSongSuite;

    // Initialize CUnit test registry
    if(CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    // Add the bisc test suite to the test registry
    biscInitSuite          = CU_add_suite("biscInitSuite",          NULL, NULL);
    biscDriveSuite         = CU_add_suite("biscDriveSuite",         NULL, NULL);
    biscDirectDriveSuite   = CU_add_suite("biscDirectDriveSuite",   NULL, NULL);
    biscTimedDriveSuite    = CU_add_suite("biscTimedDriveSuite",    NULL, NULL);
    biscDriveDistanceSuite = CU_add_suite("biscDriveDistanceSuite", NULL, NULL);
    biscTimedSpinSuite     = CU_add_suite("biscTimedSpinSuite",     NULL, NULL);
    biscFlashLedSuite      = CU_add_suite("biscFlashLedSuite",      NULL, NULL);
    biscDefineSongSuite    = CU_add_suite("biscDefineSongSuite",    NULL, NULL);

    if(biscInitSuite          == NULL ||
       biscDriveSuite         == NULL ||
       biscDirectDriveSuite   == NULL ||
       biscTimedDriveSuite    == NULL ||
       biscDriveDistanceSuite == NULL ||
       biscTimedSpinSuite     == NULL ||
       biscFlashLedSuite      == NULL ||
       biscDefineSongSuite    == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Add the tests to the suites
    if(CU_add_test(biscInitSuite, "test of biscInit() no device", testBiscInitNoDevice) == NULL ||
       CU_add_test(biscInitSuite, "test of biscInit() normal",    testBiscInitNormal) == NULL) {
        return errAddingTestsToSuite();
    }

    if(CU_add_test(biscDriveSuite, "test of biscDrive() upper bound", testBiscDriveUpper) == NULL ||
       CU_add_test(biscDriveSuite, "test of biscDrive() lower bound", testBiscDriveLower) == NULL ||
       CU_add_test(biscDriveSuite, "test of biscDrive() normal",      testBiscDriveNormal) == NULL) {
        return errAddingTestsToSuite();
    }

    if(CU_add_test(biscDirectDriveSuite, "test of biscDirectDrive() upper left bound",  testBiscDirectDriveUpperLeft) == NULL  ||
       CU_add_test(biscDirectDriveSuite, "test of biscDirectDrive() lower left bound",  testBiscDirectDriveLowerLeft) == NULL  ||
       CU_add_test(biscDirectDriveSuite, "test of biscDirectDrive() upper right bound", testBiscDirectDriveUpperRight) == NULL ||
       CU_add_test(biscDirectDriveSuite, "test of biscDirectDrive() lower right bound", testBiscDirectDriveLowerRight) == NULL ||
       CU_add_test(biscDirectDriveSuite, "test of biscDirectDrive() normal",            testBiscDirectDriveNormal) == NULL) {
        return errAddingTestsToSuite();
    }

    if(CU_add_test(biscTimedDriveSuite, "test of biscTimedDrive() lower bound", testBiscTimedDriveZero) == NULL ||
       CU_add_test(biscTimedDriveSuite, "test of biscTimedDrive() normal",      testBiscTimedDriveNormal) == NULL) {
        return errAddingTestsToSuite();
    }

    if(CU_add_test(biscDriveDistanceSuite, "test of biscDriveDistance() negative distance", testBiscDriveDistanceNegativeDistance) == NULL ||
       CU_add_test(biscDriveDistanceSuite, "test of biscDriveDistance() negative velocity", testBiscDriveDistanceNegativeVelocity) == NULL ||
       CU_add_test(biscDriveDistanceSuite, "test of biscDriveDistance() normal",            testBiscDriveDistanceNormal) == NULL) {
        return errAddingTestsToSuite();
    }

    if(CU_add_test(biscTimedSpinSuite, "test of biscTimedSpin() no time", testBiscTimedSpinZero)   == NULL ||
       CU_add_test(biscTimedSpinSuite, "test of biscTimedSpin() normal",  testBiscTimedSpinNormal) == NULL) {
        return errAddingTestsToSuite();
    }

    if(CU_add_test(biscFlashLedSuite, "test of biscFlashLed() no flashes",  testBiscFlashLedNoFlashes)  == NULL ||
       CU_add_test(biscFlashLedSuite, "test of biscFlashLed() no duration", testBiscFlashLedNoDuration) == NULL ||
       CU_add_test(biscFlashLedSuite, "test of biscFlashLed() normal",      testBiscFlashLedNormal)     == NULL) {
        return errAddingTestsToSuite();
    }

    if(CU_add_test(biscDefineSongSuite, "test of biscDefineSong() invalid song", testBiscDefineSongInvalidSong) == NULL ||
       CU_add_test(biscDefineSongSuite, "test of biscDefineSong() normal",       testBiscDefineSongNormal) == NULL) {
        return errAddingTestsToSuite();
    }

    // Run all the tests!
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    
    CU_cleanup_registry();
    biscDisconnect();

    return CU_get_error();
}


int errAddingTestsToSuite(void) {
    CU_cleanup_registry();
    return CU_get_error();
}


// Init tests
void testBiscInitNoDevice(void) {
    CU_ASSERT_TRUE_FATAL(biscInit(NULL) == BISC_ERR);
}

void testBiscInitNormal(void) {
    CU_ASSERT_TRUE_FATAL(biscInit("/dev/null") == BISC_SUCCESS);
}


// Drive tests
void testBiscDriveUpper(void) {
    CU_ASSERT_TRUE(biscDrive(501, 1) == BISC_ERR);
}

void testBiscDriveLower(void) {
    CU_ASSERT_TRUE(biscDrive(-501, 1) == BISC_ERR);
}

void testBiscDriveNormal(void) {
    CU_ASSERT_TRUE(biscDrive(100, 1) == BISC_SUCCESS);
}


// Drive direct tests
void testBiscDirectDriveUpperLeft(void) {
    CU_ASSERT_TRUE(biscDirectDrive(501, 1) == BISC_ERR);
}

void testBiscDirectDriveLowerLeft(void) {
    CU_ASSERT_TRUE(biscDirectDrive(-501, 1) == BISC_ERR);
}

void testBiscDirectDriveUpperRight(void) {
    CU_ASSERT_TRUE(biscDirectDrive(1, 501) == BISC_ERR);
}

void testBiscDirectDriveLowerRight(void) {
    CU_ASSERT_TRUE(biscDirectDrive(1, -501) == BISC_ERR);
}

void testBiscDirectDriveNormal(void) {
    CU_ASSERT_TRUE(biscDirectDrive(100, 100) == BISC_SUCCESS);
}


// Timed drive tests
void testBiscTimedDriveZero(void) {
    CU_ASSERT_TRUE(biscTimedDrive(1, 1, 0) == BISC_ERR);
}

void testBiscTimedDriveNormal(void) {
    CU_ASSERT_TRUE(biscTimedDrive(100, 1, 1) == BISC_SUCCESS);
}


// Drive distance tests
void testBiscDriveDistanceNegativeDistance(void) {
    CU_ASSERT_TRUE(biscDriveDistance(1, 1, -1) == BISC_ERR);
}

void testBiscDriveDistanceNegativeVelocity(void) {
    CU_ASSERT_TRUE(biscDriveDistance(-1, 1, 1) == BISC_ERR);
}

void testBiscDriveDistanceNormal(void) {
    CU_ASSERT_TRUE(biscDriveDistance(100, 1, 1) == BISC_SUCCESS);
}


// Timed spin tests
void testBiscTimedSpinZero(void) {
    CU_ASSERT_TRUE(biscTimedSpin(1, 0) == BISC_ERR);
}

void testBiscTimedSpinNormal(void) {
    CU_ASSERT_TRUE(biscTimedSpin(1, 1) == BISC_SUCCESS);
}


// Flash led tests
void testBiscFlashLedNoFlashes(void) {
    CU_ASSERT_TRUE(biscFlashLed(1, 0, 1) == BISC_ERR);
}

void testBiscFlashLedNoDuration(void) {
    CU_ASSERT_TRUE(biscFlashLed(1, 1, 0) == BISC_ERR);
}

void testBiscFlashLedNormal(void) {
    CU_ASSERT_TRUE(biscFlashLed(1, 2, 1) == BISC_SUCCESS);
}

// Define song tests
void testBiscDefineSongInvalidSong(void) {
    unsigned char badNotes [] = {1};
    unsigned char badNotesDurations [] = {1};

    CU_ASSERT_TRUE(biscDefineSong(1, badNotes, badNotesDurations, 0)   == BISC_ERR);
}

void testBiscDefineSongNormal(void) {
    unsigned char goodNotes [] = {50};
    unsigned char goodNotesDurations [] = {1};
    
    CU_ASSERT_TRUE(biscDefineSong(1, goodNotes, goodNotesDurations, 1) == BISC_SUCCESS);
}
