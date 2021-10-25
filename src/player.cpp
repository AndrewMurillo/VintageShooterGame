#include "player.h"

void Player::update() {
	shoot();
	move();
	Helicopter::update();
}

//	Calc movement based on booleans changed by keyboard input
//
void Player::move() {
	int newX = trans.x;
	if (isLeft) {
		newX = trans.x - 5;
		if (newX < 0) {
			newX = trans.x;
		}
	}
	if (isRight) {
		newX = trans.x + 5;
		if (newX > ofGetWindowWidth()) {
			newX = trans.x;
		}
	}
	int newY = trans.y;
	if (isUp) {
		newY = trans.y - 5;
		if (newY < 0) {
			newY = trans.y;
		}
	}
	if (isDown) {
		newY = trans.y + 5;
		if (newY > ofGetWindowHeight()) {
			newY = trans.y;
		}
	}
	setPosition(glm::vec3(newX, newY, 0));
	if (isRotCClockwise) {
		rot -= 5;
	}
	if (isRotClockwise) {
		rot += 5;
	}
}

void Player::shoot() {
	if (isFire) {
		start();
	}
	//stop();
}