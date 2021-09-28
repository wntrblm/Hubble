/*
    Copyright (c) 2021 Alethea Katherine Flowers.
    Published under the standard MIT License.
    Full text available at: https://opensource.org/licenses/MIT
*/

#include "midi_backend.h"
#include "RtMidi.h"
#include <algorithm>

static RtMidiIn* rt_midiin = nullptr;
static RtMidiOut* rt_midiout = nullptr;
static std::vector<unsigned char> message;

bool midi_backend_init() {
    try {
        rt_midiin = new RtMidiIn();
        rt_midiout = new RtMidiOut();
    } catch (RtMidiError& error) {
        // Handle the exception here
        error.printMessage();
        return false;
    }

    auto num_ports = rt_midiin->getPortCount();
    int port_num = 0;

    if (num_ports != 1) {
        printf("There are %i MIDI input sources available.\n", num_ports);
        std::string port_name;
        for (unsigned int i = 0; i < num_ports; i++) {
            try {
                printf(" #%i: %s\n", i, rt_midiin->getPortName(i).c_str());
            } catch (RtMidiError& error) {
                error.printMessage();
                return false;
            }
        }
        printf("Which port?: ");
        std::cin >> port_num;
    }

    rt_midiin->openPort(port_num);
    // don't ignore sysex
    rt_midiin->ignoreTypes(false, true, true);

    // Assumes same number of in and out ports. Probably a bad assumption.
    // rt_midiout->openPort(port_num);

    return true;
};

bool midi_backend_receive(uint8_t* bytes) {
    rt_midiin->getMessage(&message);
    auto count = message.size();

    if (count == 0) {
        return false;
    }

    // printf("RtMIDI IN: ");
    // for (auto i = message.begin(); i != message.end(); ++i) {
    //     printf("0x%02x ", *i);
    // }
    // printf("\n");

    std::copy_n(message.begin(), count > 4 ? 4 : count, bytes);

    return true;
}
