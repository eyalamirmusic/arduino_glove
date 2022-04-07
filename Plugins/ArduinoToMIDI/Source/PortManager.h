#pragma once

#include <juce_serialport/juce_serialport.h>
#include <thread>

constexpr int sampleTimeInNS = 100;

struct PortManager
{
    PortManager()
    {
        //Debug the port list as a simple way to get the port address:
        auto portlist = SerialPort::getSerialPortPaths();

        for (int index = 0; index < portlist.size(); ++index)
            DBG(portlist.getAllKeys()[index] << ": " << portlist.getAllValues()[index]);

        port = std::make_unique<SerialPort>(
            "/dev/tty.usbserial-10", config, DebugFunction());

        stream = std::make_unique<SerialPortInputStream>(port.get());
        thread = std::make_unique<std::thread>(
            [&]
            {
                while (isRunning.load())
                {
                    while (stream->canReadLine())
                    {
                        auto current = stream->readNextLine();

                        if (current != oldMessage)
                        {
                            oldMessage = current;
                            onMessageChange(current);
                        }
                    }

                    std::this_thread::sleep_for(std::chrono::nanoseconds(sampleTimeInNS));
                }
            });
    }

    ~PortManager()
    {
        isRunning.store(false);
        thread->join();
    }

    SerialPortConfig config {9600,
                             8,
                             SerialPortConfig::SERIALPORT_PARITY_NONE,
                             SerialPortConfig::STOPBITS_1,
                             SerialPortConfig::FLOWCONTROL_NONE};

    std::unique_ptr<SerialPort> port;
    std::unique_ptr<SerialPortInputStream> stream;
    std::unique_ptr<std::thread> thread;
    std::atomic<bool> isRunning {true};
    juce::String oldMessage;
    std::function<void(const juce::String&)> onMessageChange;
};
