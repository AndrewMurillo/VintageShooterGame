#include "helicopter.h"

Helicopter::Helicopter() {
	speed = 0;
	velocity = glm::vec3(0, 0, 0);
	bSelected = false;
	haveImage = false;
	started = false;
	width = 60;
	height = 80;
	emitters.push_back(new Emitter(new SpriteSystem()));
	emitters.push_back(new Emitter(new SpriteSystem()));
	//sys = new SpriteSystem();
	//child1 = new Emitter(sys);
	//child2 = new Emitter(sys);
}

void Helicopter::setup(glm::vec3 pos) {
	setPosition(pos);
	emitters[0]->setPosition(glm::vec3(pos.x + 20, pos.y, 0));
	emitters[1]->setPosition(glm::vec3(pos.x - 20, pos.y, 0));
	for (auto emit : emitters) {
		emit->setVelocity(glm::vec3(0, 500, 0));
	}
}

void Helicopter::draw() {
	ofSetColor(255, 255, 255, 255);
	ofPushMatrix();
	ofMultMatrix(getTransformMatrix());
	//	Similar to Sprite.draw()
	//
	if (haveImage) {
		image.draw(-width / 2.0, -height / 2.0);
	}
	else {
		ofSetColor(255, 0, 0);
		ofDrawRectangle(-width / 2.0, -height / 2.0, width, height); //remove trans
	}
	ofPopMatrix();
	//	Call children emitters!
	for (auto emit : emitters) {
		emit->draw();
	}
}

void Helicopter::update() {
	//	Rotate offset -> affects where sprites are drawn!
	glm::vec3 pos1 = glm::vec4(20, 0, 0, 0) * glm::rotate(glm::mat4(1.0), glm::radians(rot), glm::vec3(0, 0, 1));
	//	Set pos at parent object + offset! (Reminder y is inverted on the screen!)
	emitters[0]->setPosition(glm::vec3(trans.x + pos1.x, trans.y - pos1.y, 0));
	emitters[1]->setPosition(glm::vec3(trans.x - pos1.x, trans.y + pos1.y, 0));
	for (auto emit : emitters) {
		//	Set rot to parent rot
		emit->rot = rot;
		//	Call children update
		emit->update();
	}
}

void Helicopter::start() {
	// Start children emitters
	if (!started) {
		started = true;
		for (auto emit : emitters) {
			emit->start();
		}
	}
}

void Helicopter::stop() {
	// Stop children emitters
	started = false;
	for (auto emit : emitters) {
		emit->stop();
	}
}

void Helicopter::setImage(ofImage img) {
	image = img;
	haveImage = true;
	width = image.getWidth();
	height = image.getHeight();
}

void Helicopter::setRate(float r) {
	for (auto emit : emitters) {
		emit->rate = r;
	}
}

void Helicopter::setProjImage(ofImage img) {
	for (auto emit : emitters) {
		emit->setChildImage(img);
	}
}

void Helicopter::setProjSound(ofSoundPlayer sound) {
	for (auto emit : emitters) {
		emit->setSound(sound);
	}
}