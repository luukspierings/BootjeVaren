#include "Sea.h"
#include "RandomGenerator.h"

#include <iostream>
#include <random>
#include <ctime>

using namespace std;

Sea::Sea(City* city)
{
	nextCity = city;
	turns = 5;
}

Sea::~Sea()
{
	delete nextCity;
}

void Sea::processState(Game* game)
{

	if (turns <= 0) {
		game->setState(new City());
		delete this;
		return;
	}
	else if(!isInBattle){

		int randomBattleChance = RandomGenerator::getInstance().generate(1,20);
		if (randomBattleChance <= 20 / (100 / 20)) {

			game->setState(new Battle(this));
			isInBattle = true;
			return;
		}
	}

	cout << "Your ship is on sea. Days left: "<< turns << endl;
	cout << "" << endl;
	
	if (isInBattle) {
		cout << lastCommandMessage << endl;
		cout << "" << endl;
		isInBattle = false;
	}

	cout << "1: Next day" << endl;
	cout << "2: Quit" << endl;

	int choice;
	cin >> choice;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore char input

	if (choice == 2) {
		game->setState(nullptr);
		delete this;
		return;
	}

	turns--;

}
