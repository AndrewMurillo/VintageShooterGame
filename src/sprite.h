#pragma once

#include "ofMain.h"
#include "baseObject.h"

//  General Sprite class  (similar to a Particle)
//
class Sprite : public BaseObject {
public:
	Sprite();
	virtual ~Sprite() = default; //Ignore this
	void draw();
	virtual void update();
	float age();
	void setImage(ofImage);
	float speed;    //   in pixels/sec
	glm::vec3 velocity; // in pixels/sec
	ofImage image;
	float birthtime; // elapsed time in ms
	float lifespan;  //  time in ms
	string name;
	bool haveImage;
	float width, height;
};