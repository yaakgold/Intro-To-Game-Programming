#pragma once
#include <fmod.hpp>
#include <Core/System.h>

namespace hummus
{
	class AudioSystem : public System
	{
	public:
		virtual bool Startup() override;
		virtual void Update() override;
		virtual void Shutdown() override;

		friend class Sound;

	protected:
		FMOD::System* m_system{ nullptr };
	};
}