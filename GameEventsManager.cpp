#include "GameEventsManager.h"


extern std::vector<eventData> GAME_EVENTS = {
	{
		"Meet NPC",
		{
			{ eventConditions::isCollideWithNpc, "Starosta" },
		},
		{
			{ eventActions::startDialogue, "Hello, traveler! Welcome to our town." },
			{ eventActions::eventComplete, "Meet NPC" }
		},
		false
	},
	{
		"Ztraceny nahrdelnik",
		{
			{ eventConditions::isCollideWithNpc, "Anna" },
			{ eventConditions::isEventComplete, "Meet NPC"  }
		},
		{
			{ eventActions::startDialogue, "Ahoj, ztratila jsem Náhrdelník" },
			{ eventActions::eventComplete, "Ztraceny nahrdelnik" }
		},
		false
	}
};

// Správná inicializace globální promìnné
extern std::map<std::string, std::vector<std::string>> NPC_RANDOM_DIALOGUES = {
	{ "Starosta", {
		"Starosta øíká: Krásný den, že?",
		"Starosta øíká: Mìsto je v bezpeèí díky našim hrdinùm.",
		"Starosta øíká: Máte nìjaké novinky z cest?"
	} },
	{ "Anna", {
		"Anna øíká: Doufám, že najdu svùj náhrdelník brzy.",
		"Anna øíká: Miluji procházky po lese.",
		"Anna øíká: Mùj bratr je stateèný bojovník."
	} }
};

GameEventsManager::GameEventsManager(DialogueManager& dialogueManager)
	: m_dialogueManager(dialogueManager)
{

}

void GameEventsManager::checkEvent(std::string npcName)
{
	if (m_dialogueManager.isDialogueActive())
		return;

	bool conditionsMet = false;
	for (auto& event : GAME_EVENTS) {
		if (!event.eventCompleted) {
			conditionsMet = true;
			// Zkontrolovat všechny podmínky události
			for (const auto& condition : event.eventConditions) {
				switch (condition.conditionType) {
				case eventConditions::isCollideWithNpc:
					// Pøedpokládáme, že pokud jsme zde, kolize probìhla
					if (condition.conditionValue != npcName) {
						conditionsMet = false;
					}
					break;
				case eventConditions::isEventComplete:
					conditionsMet = isEventCompleted(condition.conditionValue);
					break;
				default:
					conditionsMet = false;
					break;
				}
				if (!conditionsMet) {
					break; // Pokud jedna podmínka není splnìna, nemusíme pokraèovat
				}
			}
			// Pokud jsou všechny podmínky splnìny, vykonej akce
			if (conditionsMet) {
				for (const auto& action : event.eventActions) {
					switch (action.actionType) {
					case eventActions::startDialogue:
						//std::cout << "Dialogue: " << action.actionValue << std::endl;
						m_dialogueManager.setDialogueMessage(action.actionValue);
						break;
					case eventActions::eventComplete:
						event.eventCompleted = true;
						std::cout << "Event " << action.actionValue << " completed" << std::endl;
						break;
					default:
						break;
					}
				}
			}
		}
	}
	if (!conditionsMet && NPC_RANDOM_DIALOGUES.contains(npcName)) {
		if (m_dialogueManager.isDialogueActive())
			return;
		showRandomDialogue(npcName);
	}
}

bool GameEventsManager::isEventCompleted(std::string eventName)
{
	for (const auto& event : GAME_EVENTS) {
		if (event.eventName == eventName) {
			return event.eventCompleted;
		}
	}
}

void GameEventsManager::showRandomDialogue(std::string npcName)
{
	//auto it = NPC_RANDOM_DIALOGUES[npcName];
	auto it = NPC_RANDOM_DIALOGUES.find(npcName);
	if (it != NPC_RANDOM_DIALOGUES.end()) {
		const auto& dialogues = it->second;
		if (!dialogues.empty()) {
			int randomIndex = rand() % dialogues.size();
			m_dialogueManager.setDialogueMessage(dialogues[randomIndex]);
			std::cout << dialogues[randomIndex] << std::endl;
		}
	}
}
