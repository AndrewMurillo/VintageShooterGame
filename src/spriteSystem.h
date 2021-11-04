#pragma once

#include "ofMain.h"
#include "sprite.h"

//  Manages all Sprites in a system.  You can create multiple systems
//
class SpriteSystem {
public:
	void add(Sprite);
	void remove(int);
	void reset();
	int removeNear(glm::vec3 point, float dist);
	int removeNear(glm::vec3 point, float dist, ofSoundPlayer * sound);
	void update();
	void draw();
	vector<Sprite> sprites;

};