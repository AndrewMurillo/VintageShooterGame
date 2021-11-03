#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "baseObject.h"
#include "sprite.h"
#include "spriteSystem.h"
#include "emitter.h"
#include "helicopter.h"
#include "player.h"



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

//  Another Emitter class for emitting PathSprites
//  SHOULD inherit all Emitter functions/variables
//
class PathEmitter : public Emitter {
public:
	PathEmitter(SpriteSystem *);
	void update();
};

typedef enum {gameStart, gamePlay, gameEnd} gameState;

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
		gameState state = gameStart;
		SpriteSystem *playerProj = NULL;

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
		SpriteSystem *enemyProj = NULL;
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
		ofxIntSlider heliOffset;
		ofxFloatSlider thrust;
		ofxFloatSlider projSpeed;
};
