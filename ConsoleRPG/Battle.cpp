#define _CRT_SECURE_NO_WARNINGS

#include "Battle.h"
#include "RandomGenerator.h"


Battle::Battle(Sea * sea)
{
	seaState = sea;
}

Battle::~Battle()
{
	delete pirate;
}

void Battle::processState(Game * game)
{
	if (pirate == nullptr) {
		pirate = new Pirate(game->shipFactory.getRandomShip(true));
	}

	cout << "You are in battle with some pirates." << endl;
	cout << "" << endl;


	
	if (lastCommandMessage && !lastCommandMessage[0]) {
		cout << "The pirates say arrr to you." << endl;
		cout << "" << endl;

	}
	else {
		cout << lastCommandMessage << endl;
		cout << "" << endl;

	}


	cout << "1: Shoot" << endl;
	cout << "2: Flight" << endl;
	cout << "3: Surrender" << endl;
	cout << "4: Quit" << endl;
	cout << "" << endl;

	int choice = 0;
	cin >> choice;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');


	switch (choice) {
	case 1:
	{
		int dmgToPirate = game->getShip()->shootCannons();

		pirate->getHit(dmgToPirate);

		int pirateHitpoints = pirate->getShip()->getHitPoints();

		sprintf(buf, "You shoot the cannons and do %s%d damage to the pirates,", "", dmgToPirate);
		sprintf(buf, "%s %d hitpoints left.", buf, pirateHitpoints);
		lastCommandMessage = buf;

		break;
	}
	case 2:
	{

		int flightRandom = RandomGenerator::getInstance().generate(0, 100);
		int flightChance = game->getShip()->getBaseFlightChance() + pirate->getShip()->getModifierFlightChance();

		if (flightRandom <= flightChance) {
			seaState->lastCommandMessage = "You successfully escaped from the pirates, hurray!";
			game->setState(seaState);
			delete this;
		}
		else {
			lastCommandMessage = "You fail escaping the pirates, they laugh at your weak attempt.";
		}

		break;
	}
	case 3:
		seaState->lastCommandMessage = "You surrender and the pirates leave you unharmed with the empty ship.";
		game->setState(seaState);
		delete this;
		break;
	case 4:
		game->setState(nullptr);
		delete seaState;
		delete this;
		break;
	}


	/*int dmgToPlayer = pirate->getShip()->shootCannons();

	sprintf(buf, "You shoot the cannons and do %s%d damage to the pirates.\n", "", dmgToPlayer);

	lastCommandMessage = buf;*/


	if (game->getShip()->getHitPoints() <= 0) {
		game->setState(nullptr);
		delete seaState;
		delete this;
	}

}

