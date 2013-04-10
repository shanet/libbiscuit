#ifndef BISC_CORE_H
#define BISC_CORE_H

#include <termios.h> 
#include <unistd.h> 
#include <errno.h>
#include <sys/file.h>

typedef struct {
    char playAdvanceState;
    char powerLedColor;
    char powerLedIntensity;
} LedState;

int deviceDescriptor;
LedState ledState;

#endif