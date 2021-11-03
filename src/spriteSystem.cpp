#include "spriteSystem.h"

//  Add a Sprite to the Sprite System
//
void SpriteSystem::add(Sprite s) {
	sprites.push_back(s);
}

// Remove a sprite from the sprite system. Note that this function is not currently
// used. The typical case is that sprites automatically get removed when the reach
// their lifespan.
//
void SpriteSystem::remove(int i) {
	sprites.erase(sprites.begin() + i);
}

// remove all sprites within a given dist of point, return number removed
// Reused from Minigame Example...
//
int SpriteSystem::removeNear(glm::vec3 point, float dist) {
	vector<Sprite>::iterator s = sprites.begin();
	vector<Sprite>::iterator tmp;
	int count = 0;

	while (s != sprites.end()) {
		glm::vec3 v = s->trans - point;
		if (glm::length(v) < dist) {
			//cout << "player: " << point.x << ", " << point.y << " | emitter: " << s->trans.x << ", " << s->trans.y << endl;
			tmp = sprites.erase(s);
			count++;
			s = tmp;
		}
		else s++;
	}
	return count;
}

int SpriteSystem::removeNear(glm::vec3 point, float dist, ofSoundPlayer * sound) {
	vector<Sprite>::iterator s = sprites.begin();
	vector<Sprite>::iterator tmp;
	int count = 0;

	while (s != sprites.end()) {
		glm::vec3 v = s->trans - point;
		if (glm::length(v) < dist) {
			tmp = sprites.erase(s);
			sound->play();
			count++;
			s = tmp;
		}
		else s++;
	}
	return count;
}

//  Update the SpriteSystem by checking which sprites have exceeded their
//  lifespan (and deleting).  Also the sprite is moved to it's next
//  location based on velocity and direction.
//
void SpriteSystem::update() {

	if (sprites.size() == 0) return;
	vector<Sprite>::iterator s = sprites.begin();
	vector<Sprite>::iterator tmp;

	// check which sprites have exceed their lifespan and delete
	// from list.  When deleting multiple objects from a vector while
	// traversing at the same time, use an iterator.
	//
	while (s != sprites.end()) {
		// ADDED IF IT IS OFFSCREEN
		if ((s->lifespan != -1 && s->age() > s->lifespan) || (s->trans.x < -50 || s->trans.y < -50 || s->trans.x > ofGetWindowWidth() + 50 || s->trans.y > ofGetWindowHeight() + 50)) {
			//			cout << "deleting sprite: " << s->name << endl;
			tmp = sprites.erase(s);
			s = tmp;
		}
		else s++;
	}

	//  Move sprite
	//
	for (int i = 0; i < sprites.size(); i++) {
		sprites[i].update();
	}
}

//  Render all the sprites
//
void SpriteSystem::draw() {
	for (int i = 0; i < sprites.size(); i++) {
		sprites[i].draw();
	}
}