#pragma once
#include <iostream>
#include <SFML/Audio.hpp>
#include <map>
#include "Structs.h"

class AudioManager
{
	public:
		AudioManager();
		bool playMusic(const AudioData& audioData);

		void loadSound(const AudioData& audioData);
		void playDialogueSound(const std::string& name);
		float getSoundDuration(const std::string& name);

private: 

	std::map<std::string, sf::SoundBuffer> m_buffers;
	std::map<std::string, sf::Sound> m_sounds;
	sf::Music m_backgroundMusic;
};

