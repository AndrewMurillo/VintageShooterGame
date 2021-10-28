#pragma once

#include "helicopter.h"
//	Special gameplay object meant to represent a Player
//  Based on Helicopter, and has controllable player functionality.
//
class Player : public BaseObject {
public:
	void update();
	void draw();
	void move();
	//void shoot();
	Helicopter *heli;
	int lives;
	bool isLeft, isRight, isUp, isDown;
	bool isRotClockwise, isRotCClockwise;
	//bool isFire;
};