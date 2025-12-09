#include "GameEventsManager.h"


extern std::vector<eventData> GAME_EVENTS = {
	{
		"Starosta-prvni informace",
		{
			{ eventConditions::isCollideWithNpc, "Starosta" },
		},
		{
			{ eventActions::startDialogue, "Mojí dceři někdo ukradl prsten,\nkdyž ho najdeš dobře se ti odměním." },
			{ eventActions::eventComplete, "Starosta-prvni informace" }
		},
		false
	},
	{
		"Anna-prvni informace",
		{
			{ eventConditions::isCollideWithNpc, "Anna" },
			{ eventConditions::isEventComplete, "Starosta-prvni informace"  }
		},
		{
			{ eventActions::startDialogue, "Viděla jsem někoho u rybníka, něco tam házel." },
			{ eventActions::eventComplete, "Anna-prvni informace" }
		},
		false
	},
	{
		"Helga-prvni informace",
		{
			{ eventConditions::isCollideWithNpc, "Helga" },
			{ eventConditions::isEventComplete, "Anna-prvni informace"  }
		},
		{
			{ eventActions::startDialogue, "Do rybníka pořád někdo něco hází.\n půjčím ti háček, můžeš si to také zkusit,\n ale udici si někde sežeň sám." },
			{ eventActions::eventComplete, "Helga-prvni informace" }
		},
		false
	}
};

// Správná inicializace globální proměnné
extern std::map<std::string, std::vector<std::string>> NPC_RANDOM_DIALOGUES = {
	{
		"Starosta", {
		"Starosta: Zájímá mě kdo prsten vzal.",
		"Starosta: Předpokládám, že stále pátráš po zloději.",
		"Starosta: Zatím jsem zloděje nechytil, ale až do dostanu..."
		}
	},
	{
		"Anna", {
		"Anna: Nejlepší jsou maliny z lesa.",
		"Anna: Miluji procházky po lese.",
		"Anna: Občas něco zaslechnu."
		}
	},
	{
		"Barrel", {
		"Občas sem někdo hodí odpadky.",
		"Teď tu nic tu není",
		"Jen prázdný sud, může to být bezva schovka."
		}
	},
	{
		"Helga", {
		"Jen si tu lovím ryby.",
		"Nejraději mám kapra na másle.",
		"V rybníku je spousta haraburdí."
		}
	},
	{
		"Bench", {
		"Odtud se dobře chytají ryby.",
		"Helga je tu od rána do večera.",
		"Nejlepší místo pro všechny rybáře."
		}
	}
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
					// Předpokládáme, že pokud jsme zde, kolize proběhla
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
					break; // Pokud jedna podmínka není splněna, nemusíme pokračovat
				}
			}
			// Pokud jsou všechny podmínky splněny, vykonej akce
			if (conditionsMet) {
				for (const auto& action : event.eventActions) {
					switch (action.actionType) {
					case eventActions::startDialogue:
						m_dialogueManager.setDialogueMessage(action.actionValue);
						break;
					case eventActions::startRandomDialogue:
						showRandomDialogue(action.actionValue);
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
