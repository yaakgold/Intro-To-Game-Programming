#pragma once
#include <Audio/AudioChannel.h>
#include <Components/Component.h>

namespace hummus
{
	class AudioComponent : public Component
	{
	public:
		virtual bool Create(void* data = nullptr) override;
		virtual void Destroy() override;
		virtual Object* Clone() const { return new AudioComponent{ *this }; }

		void Read(const rapidjson::Value& value) override;

		virtual void Update() override;

		void Play();
		void Stop();
		void SetSoundName(const std::string& soundName) { m_soundName = soundName; }

	protected:
		std::string m_soundName;
		bool m_loop{ false };
		bool m_playOnAwake{ false };

		AudioChannel m_channel;

	};
}