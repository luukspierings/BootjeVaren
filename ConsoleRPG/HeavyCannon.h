#pragma once

#include "Cannon.h"
#include "RandomGenerator.h"

class HeavyCannon : public Cannon
{
public:
	HeavyCannon() : Cannon("Heavy", 1000, 2 , 4) {};
	~HeavyCannon() {};

	bool isHeavy() const override { return true; }
	Cannon* Clone() const override { return new HeavyCannon(*this); };
};
