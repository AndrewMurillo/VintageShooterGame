//#include "attackheli.h"
//
////AttackHeli::AttackHeli() {
////	speed = 0;
////	projSpeed = 500;
////	offset = 20;
////	velocity = glm::vec3(0, 0, 0);
////	mass = 1;
////	damping = 0.99;
////	force = glm::vec3(0, 0, 0);
////	acceleration = glm::vec3(0, 0, 0);
////	bSelected = false;
////	haveImage = false;
////	started = false;
////	width = 60;
////	height = 80;
////	emitters.push_back(new Emitter(new SpriteSystem()));
////	emitters.push_back(new Emitter(new SpriteSystem()));
////	//behavior = doNothing;
////}
//
//AttackHeli::AttackHeli(ofImage * heli, SpriteSystem * SpriteSys) {
//	speed = 0;
//	projSpeed = 500;
//	offset = 20;
//	velocity = glm::vec3(0, 0, 0);
//	mass = 1;
//	damping = 0.99;
//	force = glm::vec3(0, 0, 0);
//	acceleration = glm::vec3(0, 0, 0);
//	bSelected = false;
//	haveImage = false;
//	started = false;
//	width = 60;
//	height = 80;
//	sprite = new Sprite(heli);
//	emitters.push_back(new Emitter(SpriteSys));
//	emitters.push_back(new Emitter(SpriteSys));
//	//behavior = doNothing;
//	glm::vec2 array[] = {glm::vec2(0,0), glm::vec2(ofGetWidth(),ofGetHeight())};
//	//path = new Path(array);
//	//sys = new SpriteSystem();
//	//child1 = new Emitter(sys);
//	//child2 = new Emitter(sys);
//}
//
//AttackHeli::~AttackHeli() {
//	delete sys;
//}
//
//void AttackHeli::setup(glm::vec3 pos) {
//	setPosition(pos);
//	emitters[0]->setPosition(glm::vec3(pos.x + 20, pos.y, 0));
//	emitters[1]->setPosition(glm::vec3(pos.x - 20, pos.y, 0));
//	for (auto emit : emitters) {
//		emit->setSpriteVelocity(glm::vec3(0, 500, 0));
//	}
//}
//
//void AttackHeli::draw() {
//	Sprite::draw();
//	//	Call children emitters!
//	for (auto emit : emitters) {
//		emit->draw();
//	}
//}
//
//void AttackHeli::update() {
//	//integrate();
//	//	Rotate offset -> affects where sprites are drawn!
//	glm::vec3 pos1 = glm::vec4(offset, 0, 0, 0) * glm::rotate(glm::mat4(1.0), glm::radians(rot), glm::vec3(0, 0, 1));
//	//	Set pos at parent object + offset! (Reminder y is inverted on the screen!)
//	emitters[0]->setPosition(glm::vec3(trans.x + pos1.x, trans.y - pos1.y, 0));
//	emitters[1]->setPosition(glm::vec3(trans.x - pos1.x, trans.y + pos1.y, 0));
//	for (auto emit : emitters) {
//		//emit->setVelocity(getHeading() * projSpeed + velocity);
//		emit->setSpriteVelocity(getHeading() * projSpeed);
//		//	Set rot to parent rot
//		emit->rot = rot;
//		//	Call children update
//		emit->update();
//	}
//
//	//move();
//}
//
//void AttackHeli::start() {
//	// Start children emitters
//	if (!started) {
//		started = true;
//		for (auto emit : emitters) {
//			emit->start();
//		}
//	}
//}
//
//void AttackHeli::stop() {
//	// Stop children emitters
//	started = false;
//	for (auto emit : emitters) {
//		emit->stop();
//	}
//}
//
//void AttackHeli::setRate(float r) {
//	for (auto emit : emitters) {
//		emit->rate = r;
//	}
//}
//
//void AttackHeli::setProjImage(ofImage img) {
//	for (auto emit : emitters) {
//		emit->setChildImage(img);
//	}
//}
//
//void AttackHeli::setProjSound(ofSoundPlayer sound) {
//	for (auto emit : emitters) {
//		emit->setSound(sound);
//	}
//}
//
////void AttackHeli::setBehavior(behaviorType b) {
////	behavior = b;
////}
///*
//void AttackHeli::move() {
//	if (behavior == doNothing)
//		return;
//	if (behavior == followPath) {
//		float cycles = 4;
//		float scale = 200;
//		//cout << "PathSprite update()" << endl;
//		float speed = glm::length(velocity);
//		glm::vec3 p = trans + (getHeading() * speed);
//		float u = (cycles * p.x * PI) / ofGetWidth();
//		trans = glm::vec3(p.x, -scale * sin(u) + (ofGetHeight() / 2), 0);
//		// find angle to rotate to new heading; we rotate
//		// from "home" position;  (you could rotate incrementally
//		// from last position as well, but you need to keep previous
//		// heading;
//		//
//		glm::vec3 homeOrient;
//		if (haveImage)
//			homeOrient = glm::vec3(0, -1, 0);  // image needs to be flipped;
//		else
//			homeOrient = glm::vec3(0, 1, 0);
//
//
//		// set rotation (angle between heading and home orientation)
//		//
//		rot = -glm::degrees(glm::orientedAngle(getHeading(), homeOrient, glm::vec3(0, 0, 1)));
//	}
//
//}
//*/
//
//void AttackHeli::shootPrimary() {
//	//implement main cannon code
//}
//
//
//void AttackHeli::shootSecondary() {
//	//implement main cannon code
//}