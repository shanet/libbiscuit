#include "bisc_unit_tests.h"

int main(void) {
    CU_pSuite biscTestSuite = NULL;

    // Initialize CUnit test registry
    if(CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    // Add the bisc test suite to the test registry
    biscTestSuite = CU_add_suite("biscTestSuite", NULL, cleanBiscTestSuite);
    if(biscTestSuite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Add the tests to the suite
    if(CU_add_test(biscTestSuite, "test of biscInit()",          testBiscInit) == NULL          ||
       CU_add_test(biscTestSuite, "test of biscDrive()",         testBiscDrive) == NULL         ||
       CU_add_test(biscTestSuite, "test of biscDirectDrive()",   testBiscDirectDrive) == NULL   ||
       CU_add_test(biscTestSuite, "test of biscTimedDrive()",    testBiscTimedDrive) == NULL    ||
       CU_add_test(biscTestSuite, "test of biscDriveDistance()", testBiscDriveDistance) == NULL ||
       CU_add_test(biscTestSuite, "test of biscTimedSpin()",     testBiscTimedSpin) == NULL     ||
       CU_add_test(biscTestSuite, "test of biscFlashLed()",      testBiscFlashLed) == NULL      ||
       CU_add_test(biscTestSuite, "test of biscDefineSong()",    testBiscDefineSong) == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Run all the tests!
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    
    CU_cleanup_registry();

    return CU_get_error();
}


int cleanBiscTestSuite(void) {
    biscDisconnect();
    return 0;
}


void testBiscInit(void) {
    CU_ASSERT_TRUE_FATAL(biscInit("/dev/null") == BISC_SUCCESS);
}


void testBiscDrive(void) {
    CU_ASSERT_TRUE(biscDrive(501, 1)  == BISC_ERR);
    CU_ASSERT_TRUE(biscDrive(-501, 1) == BISC_ERR);
    CU_ASSERT_TRUE(biscDrive(100, 1)  == BISC_SUCCESS);
}


void testBiscDirectDrive(void) {
    CU_ASSERT_TRUE(biscDirectDrive(501, 1)   == BISC_ERR);
    CU_ASSERT_TRUE(biscDirectDrive(-501, 1)  == BISC_ERR);
    CU_ASSERT_TRUE(biscDirectDrive(1, 501)   == BISC_ERR);
    CU_ASSERT_TRUE(biscDirectDrive(1, -501)  == BISC_ERR);
    CU_ASSERT_TRUE(biscDirectDrive(100, 100) == BISC_SUCCESS);
}


void testBiscTimedDrive(void) {
    CU_ASSERT_TRUE(biscTimedDrive(1, 1, 0)   == BISC_ERR);
    CU_ASSERT_TRUE(biscTimedDrive(100, 1, 1) == BISC_SUCCESS);
}


void testBiscDriveDistance(void) {
    CU_ASSERT_TRUE(biscDriveDistance(1, 1, -1)  == BISC_ERR);
    CU_ASSERT_TRUE(biscDriveDistance(-1, 1, 1)  == BISC_ERR);
    CU_ASSERT_TRUE(biscDriveDistance(100, 1, 1) == BISC_SUCCESS);
}


void testBiscTimedSpin(void) {
    CU_ASSERT_TRUE(biscTimedSpin(1, 0) == BISC_ERR);
    CU_ASSERT_TRUE(biscTimedSpin(1, 1) == BISC_SUCCESS);
}


void testBiscFlashLed(void) {
    CU_ASSERT_TRUE(biscFlashLed(1, 0, 1) == BISC_ERR);
    CU_ASSERT_TRUE(biscFlashLed(1, 1, 0) == BISC_ERR);
    CU_ASSERT_TRUE(biscFlashLed(1, 2, 1) == BISC_SUCCESS);
}


void testBiscDefineSong(void) {
    unsigned char badNotes [] = {1};
    unsigned char badNotesDurations [] = {1};

    unsigned char goodNotes [] = {50};
    unsigned char goodNotesDurations [] = {1};
    
    CU_ASSERT_TRUE(biscDefineSong(1, badNotes, badNotesDurations, 0)   == BISC_ERR);
    CU_ASSERT_TRUE(biscDefineSong(1, goodNotes, goodNotesDurations, 1) == BISC_SUCCESS);
}
