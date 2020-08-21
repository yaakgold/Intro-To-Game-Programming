#pragma once
#include <Components/SpriteComponent.h>

namespace hummus
{
	class SpriteAnimationComponent : public SpriteComponent
	{
	public:
		virtual bool Create(void* data = nullptr) override;
		virtual void Destroy() override;
		virtual Object* Clone() override { return new SpriteAnimationComponent(*this); }

		virtual void Read(const rapidjson::Value& value);

		virtual void Update() override;

	protected:
		int m_frame{ 0 };
		float m_frameTimer{ 0 };
		float m_frameRate{ 0 };

		int m_numX{ 0 };
		int m_numY{ 0 };
		int m_numFrames{ 0 };
		int m_FPS{ 0 };
	};
}