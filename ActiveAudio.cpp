#include "ActiveAudio.h"


ActiveAudio::ActiveAudio()
{
    this->deviceName = "none";

    //Connect to pulseaudio local server
    this->pulseAudioSpecs.format = PA_SAMPLE_S16NE;
    this->pulseAudioSpecs.channels = 2;
    this->pulseAudioSpecs.rate = 44100;

    this->simplePulseAudioConnection = pa_simple_new(NULL,
                                                    "DeskStream",
                                                    PA_STREAM_PLAYBACK,
                                                    NULL,
                                                    "Desktop Audio",
                                                    &this->pulseAudioSpecs,
                                                    NULL,
                                                    NULL,
                                                    NULL
    );
}

ActiveAudio::~ActiveAudio()
{
    pa_simple_free(this->simplePulseAudioConnection);
    return;
}