#include "player.h"

void Player::update() {
	//shoot();
	move();
	//heli->setPosition(trans);
	//heli->rot = rot;
	//heli->scale = scale;
	heli->update();
	//Helicopter::update();
}

void Player::draw() {
	heli->draw();
}

//	Calc movement based on booleans changed by keyboard input
//
void Player::move() {
	int newX = heli->trans.x;
	int newY = heli->trans.y;
	if (isLeft) {
		newX = heli->trans.x - 5;
		if (newX < 0) {
			newX = heli->trans.x;
		}
	}
	else if (isRight) {
		newX = heli->trans.x + 5;
		if (newX > ofGetWindowWidth()) {
			newX = heli->trans.x;
		}
	}
	else if (isUp) {
		newY = heli->trans.y - 5;
		if (newY < 0) {
			newY = heli->trans.y;
		}
	}
	else if (isDown) {
		newY = heli->trans.y + 5;
		if (newY > ofGetWindowHeight()) {
			newY = heli->trans.y;
		}
	}
	heli->setPosition(glm::vec3(newX, newY, 0));
	if (isRotCClockwise) {
		heli->rot -= 5;
	}
	if (isRotClockwise) {
		heli->rot += 5;
	}
}
/*
void Player::shoot() {
	if (isFire) {
		start();
	}
	//stop();
}
*/