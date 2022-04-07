#include <shared_plugin_helpers/shared_plugin_helpers.h>
#include "PortManager.h"
#include "MidiProcessor.h"

class MinimalAudioPlugin : public PluginHelpers::ProcessorBase
{
public:
    MinimalAudioPlugin()
    {
        messages.reserve(100);

        portManager.onMessageChange = [&](const juce::String& m)
        {
            auto seperate = juce::StringArray::fromTokens(m, ",");

            for (int index = 0; index < seperate.size(); ++index)
                incoming[index] = seperate[index].getIntValue();

            juce::ScopedLock sl(lock);
            messages = midi.handleChange(incoming);
        };
    }

    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer& midiMessages) override
    {
        juce::ScopedLock sl(lock);

        for (auto& message: messages)
            midiMessages.addEvent(message, 0);

        messages.clear();
    }

    IncomingValuesArray incoming;
    juce::CriticalSection lock;
    PortManager portManager;
    MidiProcessor midi;

    std::vector<juce::MidiMessage> messages;
};

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MinimalAudioPlugin();
}
