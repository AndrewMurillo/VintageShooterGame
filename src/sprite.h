#pragma once

#include "ofMain.h"
#include "baseObject.h"

//  General Sprite class  (similar to a Particle)
//
class Sprite{
public:
	Sprite();
	Sprite(ofImage *);
	void draw();
	void update();
	void setImage(ofImage *);
	float age();
	BaseObject * transform;
	float speed;    //   in pixels/sec
	glm::vec3 velocity; // in pixels/sec
	ofImage *image;
	float birthtime; // elapsed time in ms
	float lifespan;  //  time in ms
	string name;
	bool haveImage;
	float width, height;
	float mass;
	float damping;
	glm::vec3 force;
	glm::vec3 acceleration;
};