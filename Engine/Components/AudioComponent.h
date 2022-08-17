#pragma once
#include "Framework/Component.h"

namespace neu
{
	class AudioComponent : public Component
	{
	public:
		AudioComponent() = default;

		void Update() override;

		std::string m_SoundName;
		bool m_PlayOnAwake = false;
		float m_Volume = 1.0f;
		float m_Pitch = 1.0f;
		bool m_Loop = false;

		void Play();
		void Stop();


		// Inherited via Component
		virtual bool Write(const rapidjson::Value& value) const override;

		virtual bool Read(const rapidjson::Value& value) override;

	};

}