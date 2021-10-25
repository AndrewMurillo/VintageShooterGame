#pragma once

#include "helicopter.h"
//	Special gameplay object meant to represent a Player
//  Based on Helicopter, and has controllable player functionality.
//
class Player : public Helicopter {
public:
	void update();
	void move();
	void shoot();
	int lives;
	bool isLeft, isRight, isUp, isDown;
	bool isRotClockwise, isRotCClockwise;
	bool isFire;
};