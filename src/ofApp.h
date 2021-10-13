#pragma once

#include "ofMain.h"
#include "ofxGui.h"


// This is a base object that all drawable object inherit from
// It is possible this will be replaced by ofNode when we move to 3D
//
class BaseObject {
public:
	BaseObject();
	glm::vec3 trans, scale;
	float	rot;
	bool	bSelected;
	void setPosition(glm::vec3);
	// Gets the Tranformation Matrix of the object using rotation, scale, and translation
	//
	glm::mat4 getTransformMatrix() {
		glm::mat4 T = glm::translate(glm::mat4(1.0), trans);
		T = glm::rotate(T, glm::radians(rot), glm::vec3(0, 0, 1));
		T = glm::scale(T, scale);      
		return T;
	}
	// Gets a vector representing the current heading of the object. Always of length 1, relative to y-axis
	//
	glm::vec3 getHeading() {
		return glm::normalize(glm::rotate(glm::mat4(1.0), glm::radians(rot), glm::vec3(0, 0, 1)) * glm::vec4(0, 1, 0, 0));
	}
};

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

//  Attempt at creating a PathSprite class, which would use a calculated motion path rather
//than linear velocity. SHOULD inherit all Sprite functions/variables
//
class PathSprite : public Sprite {
public:
	PathSprite();
	void update() override; //ignore this too
	glm::vec3 curveEval(float x, float scale, float cycles);
	float scale;
	float cycles;
};

//  Manages all Sprites in a system.  You can create multiple systems
//
class SpriteSystem {
public:
	void add(Sprite);
	void remove(int);
	int removeNear(glm::vec3 point, float dist);
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

//  Another Emitter class for emitting PathSprites
//  SHOULD inherit all Emitter functions/variables
//
class PathEmitter : public Emitter {
public:
	PathEmitter(SpriteSystem *);
	void update();
};

//	Special gameplay object meant to represent a Helicopter (SPRITES NOT IMPLEMENTED)
//thus the strange naming convention. Based on BaseObject, and has 2 emitters "tethered" to it. 
//
class Helicopter : public BaseObject {
public:
	Helicopter();
	void setup(glm::vec3);
	void draw();
	void update();
	void start();
	void stop();
	void setImage(ofImage);
	void setProjImage(ofImage);
	void setProjSound(ofSoundPlayer);
	void setRate(float);
	float speed;
	float rate;
	glm::vec3 velocity;
	ofImage image;
	string name;
	bool haveImage;
	bool started;
	float width, height;
	Emitter *child1;
	Emitter *child2;
	SpriteSystem *sys; //SHARED SPRITE SYSTEM IS NOT OKAY: UPDATES TWICE
	//SpriteSystem *sys2;

};

//	Special gameplay object meant to represent a Player
//  Based on Helicopter, and has controllable player functionality.
//
class Player : public Helicopter{
public:
	void update();
	void move();
	void shoot();
	int lives;
	bool isLeft, isRight, isUp, isDown;
	bool isRotClockwise, isRotCClockwise;
	bool isFire;
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
		void checkCollisions();

		// Application data
		ofImage background;
		ofTrueTypeFont score_font;
		glm::vec3 mouseLast;
		glm::vec3 newPos;
		bool isGameInit = false;
		bool isPaused;
		int score;

		// Player object
		Player player;
		ofImage playerProjImage;
		ofImage playerImage;
		ofSoundPlayer playerSound;
		bool playerImageLoaded;
		bool playerProjLoaded;
		
		// Enemy Emitters
		//
		ofImage enemyProjImage;
		ofSoundPlayer enemySound;
		vector<Emitter *> emitters;
		SpriteSystem *enemySprites;
		int numEmitters;
		//PathEmitter *emit1;
		bool enemyProjLoaded;

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
