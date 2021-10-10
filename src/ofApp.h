#pragma once

#include "ofMain.h"
#include "ofxGui.h"


typedef enum { MoveStop, MoveLeft, MoveRight, MoveUp, MoveDown } MoveDir ;

// This is a base object that all drawable object inherit from
// It is possible this will be replaced by ofNode when we move to 3D
//
class BaseObject {
public:
	BaseObject();
	glm::vec3 trans, scale, center;
	float	rot;
	bool	bSelected;
	void setPosition(glm::vec3);

	glm::mat4 getTransformMatrix() {
		glm::mat4 T = glm::translate(glm::mat4(1.0), trans);
		T = glm::rotate(T, glm::radians(rot), glm::vec3(0, 0, 1));
		T = glm::scale(T, scale);      
		return T;
	}

	glm::vec3 getHeading() {
		return glm::rotate(glm::mat4(1.0), glm::radians(rot), glm::vec3(0, 0, 1)) * glm::vec4(0, 1, 0, 0);
	}
};

//  General Sprite class  (similar to a Particle)
//
class Sprite : public BaseObject {
public:
	Sprite();
	void draw();
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

//  Manages all Sprites in a system.  You can create multiple systems
//
class SpriteSystem {
public:
	void add(Sprite);
	void remove(int);
	void update();
	void draw();
	vector<Sprite> sprites;

};

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
	void update();
	SpriteSystem *sys;
	float rate;
	glm::vec3 velocity;
	float lifespan;
	bool started;
	float lastSpawned;
	ofImage childImage;
	ofImage image;
	bool drawable;
	bool haveChildImage;
	bool haveImage;
	float width, height;
};

//new class
//
class Helicopter : public BaseObject {
public:
	Helicopter();
	void draw();
	void update();
	void start();
	void stop();
	void setImage(ofImage);
	void setRate(float);
	float speed;    //   in pixels/sec
	float rate;
	glm::vec3 velocity; // in pixels/sec
	ofImage image; //  time in ms
	string name;
	bool haveImage;
	float width, height;
	Emitter *child1;
	Emitter *child2;

};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		// Application data
		ofImage playerProjImage;
		ofImage playerImage;
		ofImage background;
		ofSoundPlayer playerSound;
		glm::vec3 mouse_last;
		bool playerImageLoaded;
		bool playerProjLoaded;
		bool isPaused;

		// Player object
		Helicopter player;
		bool isGameInit = false;

		// UI
		bool bFullscreen = false;

		// GUI
		bool bHide;
		ofxFloatSlider rate;
		ofxFloatSlider life;
		ofxVec3Slider velocity;
		ofxLabel screenSize;
		ofxPanel gui;
		ofxFloatSlider playerSpeed;
		ofxFloatSlider playerRotate;
		ofxIntSlider offset;
};
