#pragma once

#include <juce_audio_utils/juce_audio_utils.h>

using IncomingValuesArray = std::array<int, 7>;
using MidiMessages = std::vector<juce::MidiMessage>;

struct MidiProcessor
{
    MidiMessages handleChange(IncomingValuesArray& values)
    {
        DBG ("called");

        int mapped = juce::jmap(30, 0, 100, 0, 127);
        int limited = juce::jlimit(0, 100, 30);

        MidiMessages messages;

        const auto channel = 1;
        auto ccNum = 100;
        auto ccVal = 127;

        auto m = juce::MidiMessage::controllerEvent(channel, ccNum, ccVal);
        messages.push_back(m);

        return messages;
    }
};