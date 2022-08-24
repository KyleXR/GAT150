#pragma once

namespace FMOD
{
	class Channel;
}

namespace neu
{
	class AudioChannel
	{
	public:
		AudioChannel() {}
		AudioChannel(FMOD::Channel* channel); // !! set m_channel 

		bool IsPlaying();
		void Stop();

		void SetPitch(float pitch);
		void SetVolume(float volume);

		float GetPitch();
		float GetVolume();
		// !! create SetPitch/GetPitch (takes float, returns float) 
		// !! create SetVolume/GetVolume (takes float, returns float) 

	private:
		FMOD::Channel* m_channel = nullptr;
	};
}