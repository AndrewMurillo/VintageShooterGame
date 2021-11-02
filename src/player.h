#pragma once

#include "helicopter.h"
//	Special gameplay object meant to represent a Player
//  Based on Helicopter, and has controllable player functionality.
//

//typedef enum { MoveStop, MoveLeft, MoveRight, MoveUp, MoveDown } MoveDir;

class Player{
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