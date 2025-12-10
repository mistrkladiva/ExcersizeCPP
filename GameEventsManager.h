#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "Structs.h"
#include "Globals.h"
#include "AudioManager.h"
#include "DialogueManager.h"


class GameEventsManager
{
public:
	GameEventsManager(DialogueManager& dialogueManager, AudioManager& audioManager);
	void checkEvent(std::string npcName);

private:


	DialogueManager& m_dialogueManager;
	AudioManager& m_audioManager;
	float m_dialogueDuration = 1.f;

	bool isEventCompleted(std::string eventName);
	void showRandomDialogue(std::string npcName);

	void playDialogueSound(const std::string& name);
	void showDialogue(const std::string& message);

};





