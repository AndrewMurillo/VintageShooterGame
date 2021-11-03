#include "helicopter.h"

Helicopter::Helicopter() {
	speed = 0;
	projSpeed = 500;
	offset = 20;
	velocity = glm::vec3(0, 0, 0);
	mass = 1;
	damping = 0.99;
	force = glm::vec3(0, 0, 0);
	acceleration = glm::vec3(0, 0, 0);
	bSelected = false;
	haveImage = false;
	started = false;
	width = 60;
	height = 80;
	emitters.push_back(new Emitter(new SpriteSystem()));
	emitters.push_back(new Emitter(new SpriteSystem()));
	behavior = doNothing;
}

Helicopter::Helicopter(SpriteSystem * SpriteSys) {
	speed = 0;
	projSpeed = 500;
	offset = 20;
	velocity = glm::vec3(0, 0, 0);
	mass = 1;
	damping = 0.99;
	force = glm::vec3(0, 0, 0);
	acceleration = glm::vec3(0, 0, 0);
	bSelected = false;
	haveImage = false;
	started = false;
	width = 60;
	height = 80;
	emitters.push_back(new Emitter(SpriteSys));
	emitters.push_back(new Emitter(SpriteSys));
	behavior = followPath;
	glm::vec2 array[] = {glm::vec2(0,0), glm::vec2(ofGetWidth(),ofGetHeight())};
	path = new Path(array);
	//sys = new SpriteSystem();
	//child1 = new Emitter(sys);
	//child2 = new Emitter(sys);
}

Helicopter::~Helicopter() {
	delete sys;
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
		image.draw(-width / 2.0, -height / 2.0 - 12);
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
	integrate();
	//	Rotate offset -> affects where sprites are drawn!
	glm::vec3 pos1 = glm::vec4(offset, 0, 0, 0) * glm::rotate(glm::mat4(1.0), glm::radians(rot), glm::vec3(0, 0, 1));
	//	Set pos at parent object + offset! (Reminder y is inverted on the screen!)
	emitters[0]->setPosition(glm::vec3(trans.x + pos1.x, trans.y - pos1.y, 0));
	emitters[1]->setPosition(glm::vec3(trans.x - pos1.x, trans.y + pos1.y, 0));
	for (auto emit : emitters) {
		//emit->setVelocity(getHeading() * projSpeed + velocity);
		emit->setVelocity(getHeading() * projSpeed);
		//	Set rot to parent rot
		emit->rot = rot;
		//	Call children update
		emit->update();
	}

	move();
	if (behavior == followPath) {
		//move from 1/4 screen to 1/3 screen, wait,  then continue forward
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

void Helicopter::setBehavior(behaviorType b) {
	behavior = b;
}

void Helicopter::move() {

}

void Helicopter::integrate() {
	double newX = trans.x + velocity.x * (1.0 / ofGetFrameRate());
	double newY = trans.y + velocity.y * (1.0 / ofGetFrameRate());
	if (newX < 0 || newX > ofGetWidth()) {
		newX = trans.x;
		velocity.x = 0;
	}
	if (newY < 0 || newY > ofGetHeight()) {
	newY = trans.y;
	velocity.y = 0;
	}
	trans = glm::vec3(newX, newY, 0);
	//trans += velocity * (1.0 / ofGetFrameRate());
	acceleration = (1 / mass) * force;
	velocity += acceleration * (1.0 / ofGetFrameRate());
	velocity *= damping;
	force = glm::vec3(0, 0, 0);
}