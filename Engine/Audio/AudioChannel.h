#pragma once
#include <fmod.hpp>

namespace hummus
{
	class AudioChannel
	{
	public:
		AudioChannel() = default;
		AudioChannel(FMOD::Channel* channel) : m_channel{ channel } {}

		bool isPlaying();
		void Stop();

	protected:
		FMOD::Channel* m_channel{ nullptr };
	};
}