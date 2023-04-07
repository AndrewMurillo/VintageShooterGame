
//  Kevin M. Smith - CS 134 SJSU

#include "explosion.h"

Explosion::Explosion() {
	sys = new ParticleSystem();
	createdSys = true;
	init();
}

Explosion::Explosion(ParticleSystem *s) {
	if (s == NULL)
	{
		cout << "fatal error: null particle system passed to Explosion()" << endl;
		ofExit();
	}
	sys = s;
	createdSys = false;
	init();
}

Explosion::~Explosion() {

	// deallocate particle system if emitter created one internally
	//
	if (createdSys) delete sys;
}

void Explosion::init() {
	rate = 1;
	velocity = ofVec3f(0, 20, 0);
	lifespan = 3;
	started = false;
	oneShot = false;
	fired = false;
	lastSpawned = 0;
	radius = 1;
	particleRadius = .1;
	visible = true;
	groupSize = 1;
}



void Explosion::draw() {
	sys->draw();
}
void Explosion::start() {
	started = true;
	lastSpawned = ofGetElapsedTimeMillis();
}

void Explosion::stop() {
	started = false;
	fired = false;
}
void Explosion::update() {

	float time = ofGetElapsedTimeMillis();

	if (oneShot && started) {
		if (!fired) {

			// spawn a new particle(s)
			//
			for (int i = 0; i < groupSize; i++)
				spawn(time);

			lastSpawned = time;
		}
		fired = true;
		stop();
	}

	else if (((time - lastSpawned) > (1000.0 / rate)) && started) {

		// spawn a new particle(s)
		//
		for (int i = 0; i < groupSize; i++)
			spawn(time);

		lastSpawned = time;
	}

	sys->update();
}

// spawn a single particle.  time is current time of birth
//
void Explosion::spawn(float time) {

	Particle particle;

	// set initial velocity and position
	// based on emitter type
	//
	

	// other particle attributes
	//
	particle.lifespan = lifespan;
	particle.birthtime = time;
	particle.position = trans;

	// add to system
	//
	sys->add(particle);
}
