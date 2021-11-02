#pragma once

#include "emitter.h"
#include "path.h"
typedef enum { followPath, curvePath, doNothing } behaviorType;

//	Special gameplay object meant to represent a Helicopter (SPRITES NOT IMPLEMENTED)
//thus the strange naming convention. Based on BaseObject, and has 2 emitters "tethered" to it. 
//
class Helicopter : public BaseObject {
public:
	Helicopter();
	Helicopter(SpriteSystem *);
	~Helicopter();
	void setup(glm::vec3);
	void draw();
	void update();
	void start();
	void stop();
	void setImage(ofImage);
	void setProjImage(ofImage);
	void setProjSound(ofSoundPlayer);
	void setRate(float);
	void setBehavior(behaviorType);
	void move();
	void integrate();
	Path *path;
	behaviorType behavior;
	SpriteSystem *sys;
	float speed;
	float rate;
	glm::vec3 velocity;
	ofImage image;
	string name;
	bool haveImage;
	bool started;
	float width, height;
	float mass;
	float damping;
	glm::vec3 force;
	glm::vec3 acceleration;
	vector<Emitter *> emitters;
	//Emitter *child1;
	//Emitter *child2;
	//SpriteSystem *sys; //SHARED SPRITE SYSTEM IS NOT OKAY: UPDATES TWICE
	//SpriteSystem *sys2;

};