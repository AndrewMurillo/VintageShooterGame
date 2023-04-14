#include "sprite.h"

//
// Basic Sprite Object
//
Sprite::Sprite() {
	transform = new BaseObject();
	cout << transform->trans << endl;
	cout << transform->rot << endl;
	cout << transform->scale << endl;
	speed = 0;
	velocity = glm::vec3(0, 0, 0);
	lifespan = -1;      // lifespan of -1 => immortal 
	birthtime = 0;
	haveImage = false;
	name = "UnamedSprite";
	width = 60;
	height = 80;
}

Sprite::Sprite(ofImage * img) : Sprite() {
	image = img;
	haveImage = true;
	width = image->getWidth();
	height = image->getHeight();

}

// Return a sprite's age in milliseconds
//
float Sprite::age() {
	return (ofGetElapsedTimeMillis() - birthtime);
}

//  Set an image for the sprite. If you don't set one, a rectangle
//  gets drawn.
//
void Sprite::setImage(ofImage * img) {
	image = img;
	haveImage = true;
	width = image->getWidth();
	height = image->getHeight();
}


//  Render the sprite
//
void Sprite::draw() {/*
	cout << transform->trans << endl;
	cout << transform->rot << endl;
	cout << transform->scale << endl;*/
	ofSetColor(255, 255, 255, 255); //default for images
	ofPushMatrix();
	ofMultMatrix(transform->getTransformMatrix());
	if (haveImage) {
		// draw image centered
		image->draw(-width / 2.0, -height / 2.0);
	}
	else {
		// in case no image is supplied, draw something.
		ofSetColor(255, 0, 0);
		ofDrawRectangle(-width / 2.0, -height / 2.0, width, height);
	}
	ofPopMatrix();
}

void Sprite::update() {
	//trans += velocity / ofGetFrameRate();
}

/*
void Sprite::integrate() {
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
*/


