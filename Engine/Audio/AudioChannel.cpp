#include "pch.h"
#include "AudioChannel.h"

namespace hummus
{
    bool AudioChannel::isPlaying()
    {
        bool isPlaying = false;

        if (m_channel)
        {
            m_channel->isPlaying(&isPlaying);
        }

        return isPlaying;
    }

    void AudioChannel::Stop()
    {
        if (isPlaying())
        {
            m_channel->stop();
        }
    }
}
