#pragma once

#include <juce_audio_utils/juce_audio_utils.h>

using IncomingValuesArray = std::array<int, 7>;
using MidiMessages = std::vector<juce::MidiMessage>;

struct MidiProcessor
{
    MidiMessages handleChange(IncomingValuesArray& values)
    {
        DBG ("called");

        MidiMessages messages;

        const auto channel = 1;
        auto ccNum = 100;
        auto ccVal = 127;

        auto m = juce::MidiMessage::controllerEvent(channel, ccNum, ccVal);
        messages.push_back(m);

        return messages;
    }
};