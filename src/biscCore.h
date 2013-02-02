typedef struct {
    char playAdvanceState;
    char powerLedColor;
    char powerLedIntensity;
} LedState;


static int deviceDescriptor;
static LedState ledState;