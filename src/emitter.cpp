#include "emitter.h"

//  Create a new Emitter - needs a SpriteSystem
//
Emitter::Emitter(SpriteSystem *spriteSys) {
	sys = spriteSys;
	lifespan = 3000;    // milliseconds
	started = false;
	lastSpawned = 0;
	rate = 1;    // sprites/sec
	haveChildImage = false;
	haveImage = false;
	haveSound = false;
	velocity = getHeading() * 100;
	//velocity = glm::vec3(0, 1000, 0);
	drawable = false;
	width = 50;
	height = 50;
}

Emitter::~Emitter()
{
	delete sys;
}

//  Draw the Emitter if it is drawable. In many cases you would want a hidden emitter
//
void Emitter::draw() {
	if (drawable) {
		ofPushMatrix();
		ofMultMatrix(getTransformMatrix());
		//similar to Sprite.draw()
		//
		if (haveImage) {
			image.draw(-image.getWidth() / 2.0, -image.getHeight() / 2.0);
		}
		else {
			ofSetColor(0, 0, 200);
			ofDrawRectangle(-width / 2, -height / 2, width, height);
		}
		ofPopMatrix();
	}
	//sys->draw();
}

//  Update the Emitter. If it has been started, spawn new sprites with
//  initial velocity, lifespan, birthtime.
//
void Emitter::update() {
	if (started) {

		float time = ofGetElapsedTimeMillis();
		if ((time - lastSpawned) > (1000.0 / rate)) {
			// spawn a new sprite
			Sprite sprite;
			if (haveChildImage) sprite.setImage(childImage);
			sprite.velocity = getHeading() * glm::length(velocity);
			sprite.lifespan = lifespan;
			sprite.setPosition(trans);
			sprite.rot = rot;
			sprite.birthtime = time;
			sys->add(sprite);
			lastSpawned = time;
			if (haveSound) sound.play();
		}
	}
	//sys->update();
}

// Start/Stop the emitter.
//
void Emitter::start() {
	started = true;
	//lastSpawned = ofGetElapsedTimeMillis();
}

void Emitter::stop() {
	started = false;
}


void Emitter::setLifespan(float life) {
	lifespan = life;
}

void Emitter::setVelocity(glm::vec3 v) {
	velocity = v;
}

void Emitter::setChildImage(ofImage img) {
	childImage = img;
	haveChildImage = true;
}

void Emitter::setImage(ofImage img) {
	image = img;
}

void Emitter::setRate(float r) {
	rate = r;
}

void Emitter::setSound(ofSoundPlayer s) {
	haveSound = true;
	sound = s;
}