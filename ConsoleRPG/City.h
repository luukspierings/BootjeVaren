#pragma once

#include <iostream>

#include "LocationState.h"
#include "CityDestination.h"
#include "Goods.h"
#include "CustomVector.h"
#include "CustomPointerVector.h"
#include "Cannon.h"
#include "LightCannon.h"
#include "MediumCannon.h"
#include "HeavyCannon.h"
#include "Sea.h"

class Game;

class City : public LocationState
{
public:
	City();
	City(char* pName);
	City(City& otherCity);
	~City();

	void processState(Game* game) override;

	char* getName() { return name; };
	CustomVector<Goods>& getGoodsVector() { return goodsVector; };
	CustomVector<CityDestination>& getCityDestinationVector() { return cityDestinationVector; };
	CustomVector<Cannon*>& getCannonVector() { return cannonPointerVector; };

	void setGoodsVector(CustomVector<Goods>& pGoodsVector) { goodsVector = pGoodsVector; };

private:
	char name[32];

	CustomVector<Goods> goodsVector;
	CustomVector<CityDestination> cityDestinationVector;
	CustomVector<Cannon*> cannonPointerVector;

	void buyGoods(Game* game);
	void sellGoods(Game* game);
	void buyCannons(Game* game);
	void sellCannons(Game* game);

	CityDestination* sailAway(Game* game);
	void repairShip(Game* game);
	void replaceShip(Game* game);

};
