#include "AudioManager.h"

AudioManager::AudioManager()
{
}

bool AudioManager::playMusic(const AudioData& audioData)
{
    if (!m_backgroundMusic.openFromFile(audioData.audioFilePath)) {
		std::cerr << "Error loading background music!" << std::endl;
        return false;
    }

    m_backgroundMusic.setLoop(true);
    m_backgroundMusic.setVolume(10);
    m_backgroundMusic.play();
	return true;
}

void AudioManager::loadSound(const AudioData& audioData)
{
    sf::SoundBuffer buffer;
    buffer.loadFromFile(audioData.audioFilePath);
    m_buffers[audioData.audioName] = buffer;

    sf::Sound sound;
    sound.setBuffer(m_buffers[audioData.audioName]);
    m_sounds[audioData.audioName] = sound;
}

void AudioManager::playDialogueSound(const std::string& name)
{
    m_sounds[name].play();
    float seconds = m_buffers[name].getDuration().asSeconds();
}

float AudioManager::getSoundDuration(const std::string& name) {
    return m_buffers[name].getDuration().asSeconds();
}