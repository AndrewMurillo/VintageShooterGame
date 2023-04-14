#pragma once

#include "ofMain.h"
#include "ofxGui.h"
//#include "baseObject.h"
#include "sprite.h"
//#include "spriteSystem.h"
//#include "emitter.h"
//#include "helicopter.h"
//#include "attackHeli.h"
//#include "player.h"
//#include "particle.h"
//#include "particleSystem.h"
//#include "explosion.h"


//  Attempt at creating a PathSprite class, which would use a calculated motion path rather
//than linear velocity. SHOULD inherit all Sprite functions/variables
//
//class PathSprite : public Sprite {
//public:
//	PathSprite();
//	void update() override; //ignore this too
//	glm::vec3 curveEval(float x, float scale, float cycles);
//	float scale;
//	float cycles;
//};

//  Another Emitter class for emitting PathSprites
//  SHOULD inherit all Emitter functions/variables
//
//class PathEmitter : public Emitter {
//public:
//	PathEmitter(SpriteSystem *);
//	void update();
//};

//typedef enum {gameStart, gamePlay, gameEnd} gameState;

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
		void resetGame();

		////Application data
		ofImage * AllyHeliImage;

		///*Test data*/
		Sprite * testSprite;
		//ofImage background;
		//ofTrueTypeFont score_font;
		//glm::vec3 mouseLast;
		//glm::vec3 newPos;
		//bool isGameInit = false;
		//bool isPaused;
		//int score;
		////gameState state = gameStart;
		//ImpulseRingForce *expForce;
		////TurbulenceForce *tForce;
		//Explosion *e = NULL;
		////vector<Explosion *> explosions;
		////ExplosionSystem explosions;

		//// Player
		//Player player;
		//ofImage playerProjImage;
		//ofImage playerImage;
		//ofSoundPlayer playerSound;
		//ofSoundPlayer playerHurtSound;
		//bool playerImageLoaded;
		//bool playerProjLoaded;
		//SpriteSystem *playerProj = NULL;
		//
		//// Enemy Emitters
		////
		//ofImage enemyProjImage;
		//ofSoundPlayer enemySound;
		//vector<Emitter *> emitters;
		//SpriteSystem *enemyProj = NULL;
		//int numEmitters;
		////PathEmitter *emit1;
		//bool enemyProjLoaded;
		//vector<Helicopter *> enemyHelos;

		//// UI
		//bool bFullscreen = false;

		//// GUI
		//bool bHide;
		//ofxFloatSlider rate;
		//ofxVec3Slider velocity;
		//ofxLabel screenSize;
		//ofxPanel gui;
		//ofxFloatSlider playerSpeed;
		//ofxFloatSlider playerRotate;
		//ofxIntSlider heliOffset;
		//ofxFloatSlider thrust;
		//ofxFloatSlider projSpeed;
		//ofxFloatSlider expMagnitude;
		////ofxVec3Slider minT;
		////ofxVec3Slider maxT;

};
