#pragma once

#include "ofMain.h"
#include "sprite.h"

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