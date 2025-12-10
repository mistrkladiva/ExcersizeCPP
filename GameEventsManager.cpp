#include "GameEventsManager.h"


extern std::vector<eventData> GAME_EVENTS = {
	{
		"Starosta-konec",
		{
			{ eventConditions::isCollideWithNpc, "Starosta" },
			{ eventConditions::isEventComplete, "Starosta-zaver"  }
		},
		{
			{ eventActions::playDialogueSound, "starosta-end"},
			{ eventActions::startDialogue, "Už opravdu nemusíš pátrat, To je konec tohoto příběhu." }
		},
		false
	},
	{
		"Starosta-prvni informace",
		{
			{ eventConditions::isCollideWithNpc, "Starosta" },
		},
		{
			{ eventActions::playDialogueSound, "starosta-1"},
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
			{ eventActions::playDialogueSound, "anna-1"},
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
			{ eventActions::playDialogueSound, "helga-1"},
			{ eventActions::startDialogue, "Do rybníka pořád někdo něco hází.\npůjčím ti háček, můžeš si to také zkusit,\nale udici si někde sežeň sám." },
			{ eventActions::eventComplete, "Helga-prvni informace" }
		},
		false
	},
	{
		"sud-s-udici",
		{
			{ eventConditions::isCollideWithNpc, "Barrel-interactive" },
			{ eventConditions::isEventComplete, "Helga-prvni informace"  }
		},
		{
			{ eventActions::playDialogueSound, "narrator-2"},
			{ eventActions::startDialogue, "A hele. Někdo si tu schoval udici\nMůžu se dát do výlovu rybníka." },
			{ eventActions::eventComplete, "sud-s-udici" }
		},
		false
	},
	{
		"vylov-rybnika-1",
		{
			{ eventConditions::isCollideWithNpc, "Bench" },
			{ eventConditions::isEventComplete, "sud-s-udici"  }
		},
		{
			{ eventActions::playDialogueSound, "narrator-3"},
			{ eventActions::startDialogue, "Už jsem něco zachytil..Sakra jen starý hrnec." },
			{ eventActions::eventComplete, "vylov-rybnika-1" }
		},
		false
	},
	{
		"Helga-pokracuj-vylov",
		{
			{ eventConditions::isCollideWithNpc, "Helga" },
			{ eventConditions::isEventComplete, "vylov-rybnika-1"  }
		},
		{
			{ eventActions::playDialogueSound, "helga-2"},
			{ eventActions::startDialogue, "Jo to víš, v rybníku je toho spousta. Zkuz to znova." },
			{ eventActions::eventComplete, "Helga-pokracuj-vylov" }
		},
		false
	},
	{
		"vylov-rybnika-2",
		{
			{ eventConditions::isCollideWithNpc, "Bench" },
			{ eventConditions::isEventComplete, "Helga-pokracuj-vylov"  }
		},
		{
			{ eventActions::playDialogueSound, "narrator-4"},
			{ eventActions::startDialogue, "Zkusím to ještě jednou, snad budu mít štěstí.\nZas nějaké odpadky." },
			{ eventActions::eventComplete, "vylov-rybnika-2" }
		},
		false
	},
	{
		"Starosta-zaver",
		{
			{ eventConditions::isCollideWithNpc, "Starosta" },
			{ eventConditions::isEventComplete, "vylov-rybnika-2"  }
		},
		{
			{ eventActions::playDialogueSound, "starosta-2"},
			{ eventActions::startDialogue, "Tak dcera se mi přiznala, že prsten dala svému příteli.\nTakže je vše v pořádku.\nJo a dík za vyčištění rybníka." },
			{ eventActions::eventComplete, "Starosta-prvni informace" }
		},
		false
	},
};

// Správná inicializace globální proměnné
extern std::map<std::string, std::vector<RandomDialogueData>> NPC_RANDOM_DIALOGUES = {
	{
		"Starosta", 
		{
			{"rnd-starosta-1", "Zajímá mě kdo prsten vzal."},
			{"rnd-starosta-2", "Předpokládám, že stále pátráš po zloději."},
			{"rnd-starosta-3", "Zatím jsem zloděje nechytil, ale až do dostanu..."}
		}
		
	},
	{
		"Anna",
		{
			{"rnd-anna-1", "Nejlepší jsou maliny z lesa."},
			{"rnd-anna-2", "Miluji procházky po lese."},
			{"rnd-anna-3", "Občas něco zaslechnu."}
		}
	},
	{
		"Barrel",
		{
			{"rnd-barrel-1", "Občas sem někdo hodí odpadky."},
			{"rnd-barrel-2", "Teď tu nic tu není."},
			{"rnd-barrel-3", "Jen prázdný sud, může to být bezva schovka."}
		}
	},
	{
		"Barrel-interactive",
		{
			{"rnd-barrel-1", "Občas sem někdo hodí odpadky."},
			{"rnd-barrel-2", "Teď tu nic tu není"},
			{"rnd-barrel-3", "Jen prázdný sud, může to být bezva schovka."}
		}
	},
	{
		"Helga",
		{
			{"rnd-helga-1", "Jen si tu lovím ryby."},
			{"rnd-helga-2", "Nejraději mám kapra na másle."},
			{"rnd-helga-3", "V rybníku je spousta haraburdí."}
		}
	},
	{
		"Bench",
		{
			{"rnd-bench-1", "Odtud se dobře chytají ryby."},
			{"rnd-bench-2", "Helga je tu od rána do večera."},
			{"rnd-bench-3", "Nejlepší místo pro všechny rybáře."}
		}
	}
};

GameEventsManager::GameEventsManager(DialogueManager& dialogueManager, AudioManager& audioManager)
	: m_dialogueManager(dialogueManager)
	, m_audioManager(audioManager)
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
						showDialogue(action.actionValue);
						break;
					case eventActions::playDialogueSound:
						playDialogueSound(action.actionValue);
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



void GameEventsManager::playDialogueSound(const std::string& name)
{
	m_dialogueDuration = m_audioManager.getSoundDuration(name);
	m_audioManager.playDialogueSound(name);
}

void GameEventsManager::showDialogue(const std::string& message)
{
	m_dialogueManager.setDialogueMessage(message, m_dialogueDuration);
}

void GameEventsManager::showRandomDialogue(std::string npcName)
{
	//auto it = NPC_RANDOM_DIALOGUES[npcName];
	auto it = NPC_RANDOM_DIALOGUES.find(npcName);
	if (it != NPC_RANDOM_DIALOGUES.end()) {
		const auto& dialogues = it->second;
		if (!dialogues.empty()) {
			int randomIndex = rand() % dialogues.size();
			
			playDialogueSound(dialogues[randomIndex].soundName);
			showDialogue(dialogues[randomIndex].message);
		}
	}
}
