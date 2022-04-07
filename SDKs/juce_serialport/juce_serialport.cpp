#include "juce_serialport.h"

#if JUCE_MAC
#include "juce_serialport_OSX.cpp"
#else
#include "juce_serialport_Windows.cpp"
#endif
