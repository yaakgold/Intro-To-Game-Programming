#pragma once
#include <fmod.hpp>
#include <Audio/AudioSystem.h>
#include <Audio/AudioChannel.h>
#include <Resources/Resource.h>

namespace hummus
{
	class Sound : public Resource
	{
	public:
		virtual bool Create(const std::string& fileName, void* data = nullptr) override;
		virtual void Destroy() override;

		AudioChannel Play(bool loop = false);

	private:
		FMOD::System* m_system{ nullptr };
		FMOD::Sound* m_sound{ nullptr };
	};
}