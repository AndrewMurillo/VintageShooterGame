#pragma once

#include "ofMain.h";
#include "baseObject.h";
#include "particleSystem.h";

class Explosion: public BaseObject {
public:
	Explosion();
	Explosion(ParticleSystem *s);
	~Explosion();
	void init();
	void draw();
	void start();
	void stop();
	void setLifespan(const float life) { lifespan = life; }
	void setVelocity(const ofVec3f &vel) { velocity = vel; }
	void setRate(const float r) { rate = r; }
	void setParticleRadius(const float r) { particleRadius = r; }
	void setGroupSize(int s) { groupSize = s; }
	void setOneShot(bool s) { oneShot = s; }
	void update();
	void spawn(float time);
	ParticleSystem *sys;
	float rate;         // per sec
	bool oneShot;
	bool fired;
	ofVec3f velocity;
	float lifespan;     // sec
	bool started;
	float lastSpawned;  // ms
	float particleRadius;
	float radius;
	bool visible;
	int groupSize;      // number of particles to spawn in a group
	bool createdSys;
};
