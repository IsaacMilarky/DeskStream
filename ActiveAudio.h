#include <iostream>
#include <string>
#include <pulse/simple.h>
/*
    This class is supposed to represent the current active pulseaudio audio stream. 
    This has a simple connection to the local pulseaudio server and will need a differant 
    connection in order to mess with the volume but that can be done messily with a bash command.

*/


class ActiveAudio
{
    public:
        ActiveAudio();
        ~ActiveAudio();
    private:
        std::string deviceName;
        pa_simple * simplePulseAudioConnection;
        pa_sample_spec pulseAudioSpecs;
};