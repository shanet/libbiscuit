#ifndef BISC_CORE_H
#define BISC_CORE_H

typedef struct {
    char playAdvanceState;
    char powerLedColor;
    char powerLedIntensity;
} LedState;

int deviceDescriptor;
LedState ledState;

#endif