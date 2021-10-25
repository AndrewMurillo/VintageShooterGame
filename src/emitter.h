#pragma once

#include "spriteSystem.h"
//  General purpose Emitter class for emitting sprites
//  This works similar to a Particle emitter
//
class Emitter : public BaseObject {
public:
	Emitter(SpriteSystem *);
	void draw();
	void start();
	void stop();
	void setLifespan(float);
	void setVelocity(glm::vec3);
	void setChildImage(ofImage);
	void setImage(ofImage);
	void setRate(float);
	void setSound(ofSoundPlayer);
	virtual void update();
	SpriteSystem *sys;
	float rate;
	glm::vec3 velocity;
	float lifespan;
	bool started;
	float lastSpawned;
	ofImage childImage;
	ofImage image;
	ofSoundPlayer sound;
	bool drawable;
	bool haveChildImage;
	bool haveImage;
	bool haveSound;
	float width, height;
};
