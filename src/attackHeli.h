//#pragma once
//
//#include "emitter.h"
//#include "path.h"
//#include "helicopter.h"
//typedef enum { followPath, curvePath, doNothing } behaviorType;
//
////	Special gameplay object meant to represent a Helicopter (SPRITES NOT IMPLEMENTED)
////thus the strange naming convention. Based on BaseObject, and has 2 emitters "tethered" to it. 
////
//class AttackHeli : public virtual Helicopter {
//public:
//	AttackHeli();
//	AttackHeli(ofImage *, SpriteSystem *);
//	~AttackHeli();
//	void setup(glm::vec3);
//	void start();
//	void stop();
//	void setProjImage(ofImage);
//	void setProjSound(ofSoundPlayer);
//	void setRate(float);
//	//void setBehavior(behaviorType);
//	//void move();
//	void shootPrimary() override;
//	void shootSecondary() override;
//	//Path *path;
//	//behaviorType behavior;
//
//	Sprite sprite;
//	SpriteSystem *sys;
//	float rate;
//	float projSpeed;
//	int offset;
//	string name;
//	bool started;
//	vector<Emitter *> emitters;
//	//Emitter *child1;
//	//Emitter *child2;
//	//SpriteSystem *sys; //SHARED SPRITE SYSTEM IS NOT OKAY: UPDATES TWICE
//	//SpriteSystem *sys2;
//
//};