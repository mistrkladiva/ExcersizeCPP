#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "Structs.h"
#include "Globals.h"
#include "DialogueManager.h"


class GameEventsManager
{
public:
	GameEventsManager(DialogueManager& dialogueManager);
	void checkEvent(std::string npcName);

private:


	DialogueManager& m_dialogueManager;
	bool isEventCompleted(std::string eventName);
	void showRandomDialogue(std::string npcName);
};





