#include "AudioChannel.h"
#include "fmod.hpp"

namespace neu
{
	bool AudioChannel::IsPlaying()
	{
		// !! if channel is null, return false 

		bool isPlaying;
		m_channel->isPlaying(&isPlaying);

		return isPlaying;
	}

	void AudioChannel::Stop()
	{
		if (IsPlaying()) m_channel->stop();
	}

	void AudioChannel::SetPitch(float pitch)
	{
		if (IsPlaying()) pitch;// !! call setPitch on channel (pass pitch) 
	}

	float AudioChannel::GetPitch()
	{
		float pitch = 0;
		if (IsPlaying()) // !! call getPitch (pass pointer to pitch &) 

			return pitch;
	}

	void AudioChannel::SetVolume(float volume)
	{
		if (IsPlaying()) volume;// !! call setVolume on channel (pass volume) 
	}

	float AudioChannel::GetVolume()
	{
		float volume = 0;
		if (IsPlaying()) // !! call getVolume (pass pointer to volume &) 

			return volume;
	}
}