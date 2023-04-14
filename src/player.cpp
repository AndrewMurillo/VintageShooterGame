//#include "player.h"
//
//void Player::update() {
//	heli->update();
//}
//
//void Player::draw() {
//	heli->draw();
//}
//
////	Calc movement based on booleans changed by keyboard input
////
//void Player::move() {
//	//int newX = heli->trans.x;
//	//int newY = heli->trans.y;
//	if (isLeft) {
//		heli->force = glm::vec3(-thrust,0,0);
//	}
//	else if (isRight) {
//		heli->force = glm::vec3(thrust, 0, 0);
//	}
//	else if (isUp) {
//		heli->force = glm::vec3(0, -thrust, 0);
//	}
//	else if (isDown) {
//		heli->force = glm::vec3(0, thrust, 0);
//	}
//	//heli->setPosition(glm::vec3(newX, newY, 0));
//	if (isRotCClockwise) {
//		heli->rot -= 5;
//	}
//	if (isRotClockwise) {
//		heli->rot += 5;
//	}
//}
///*
//void Player::shoot() {
//	if (isFire) {
//		start();
//	}
//	//stop();
//}
//*/