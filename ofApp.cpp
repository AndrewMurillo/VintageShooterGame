#include "ofApp.h"

BaseObject::BaseObject() {
	trans = glm::vec3(0, 0, 0);
	scale = glm::vec3(1, 1, 1);
	rot = 0;
}

void BaseObject::setPosition(glm::vec3 pos) {
	trans = pos;
}

//
// Basic Sprite Object
//
Sprite::Sprite() {
	speed = 0;
	velocity = glm::vec3(0, 0, 0);
	lifespan = -1;      // lifespan of -1 => immortal 
	birthtime = 0;
	bSelected = false;
	haveImage = false;
	name = "UnamedSprite";
	width = 60;
	height = 80;
}

// Return a sprite's age in milliseconds
//
float Sprite::age() {
	return (ofGetElapsedTimeMillis() - birthtime);
}

//  Set an image for the sprite. If you don't set one, a rectangle
//  gets drawn.
//
void Sprite::setImage(ofImage img) {
	image = img;
	haveImage = true;
	width = image.getWidth();
	height = image.getHeight();
}


//  Render the sprite
//
void Sprite::draw() {

	ofSetColor(255, 255, 255, 255);

	// draw image centered and add in translation amount
	//
	ofPushMatrix();
	ofMultMatrix(getTransformMatrix());
	if (haveImage) {
		image.draw(-width / 2.0, -height / 2.0); //ditto as below
	}
	else {
		// in case no image is supplied, draw something.
		// 
		ofSetColor(255, 0, 0);
		ofDrawRectangle(-width / 2.0, -height / 2.0, width, height); //remove trans
	}
	ofPopMatrix();
}

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
		if (s->lifespan != -1 && s->age() > s->lifespan) {
			//			cout << "deleting sprite: " << s->name << endl;
			tmp = sprites.erase(s);
			s = tmp;
		}
		else s++;
	}

	//  Move sprite
	//
	for (int i = 0; i < sprites.size(); i++) {
		sprites[i].trans += sprites[i].velocity / ofGetFrameRate();
	}
}

//  Render all the sprites
//
void SpriteSystem::draw() {
	for (int i = 0; i < sprites.size(); i++) {
		sprites[i].draw();
	}
}
//  Create a new Emitter - needs a SpriteSystem
//
Emitter::Emitter(SpriteSystem *spriteSys) {
	sys = spriteSys;
	lifespan = 3000;    // milliseconds
	started = false;

	lastSpawned = 0;
	rate = 1;    // sprites/sec
	haveChildImage = false;
	haveImage = false;
	velocity = getHeading() * 100;
	//velocity = glm::vec3(0, 1000, 0);
	drawable = true;
	width = 50;
	height = 50;
}

//  Draw the Emitter if it is drawable. In many cases you would want a hidden emitter
//
//
void Emitter::draw() {
	if (drawable) {
		ofPushMatrix();
		ofMultMatrix(getTransformMatrix());
		if (haveImage) {
			image.draw(-image.getWidth() / 2.0, -image.getHeight() / 2.0);
		}
		else {
			ofSetColor(0, 0, 200);
			ofDrawRectangle(-width / 2, -height / 2, width, height);
		}
		ofPopMatrix();
	}
	sys->draw();
}

//  Update the Emitter. If it has been started, spawn new sprites with
//  initial velocity, lifespan, birthtime.
//
void Emitter::update() {
	if (started) {

		float time = ofGetElapsedTimeMillis();
		if ((time - lastSpawned) > (1000.0 / rate)) {
			// spawn a new sprite
			Sprite sprite;
			if (haveChildImage) sprite.setImage(childImage);
			sprite.velocity = velocity;
			sprite.lifespan = lifespan;
			sprite.setPosition(trans);
			sprite.birthtime = time;
			sys->add(sprite);
			lastSpawned = time;
		}
	}
	sys->update();
}

// Start/Stop the emitter.
//
void Emitter::start() {
	started = true;
	lastSpawned = ofGetElapsedTimeMillis();
}

void Emitter::stop() {
	started = false;
}


void Emitter::setLifespan(float life) {
	lifespan = life;
}

void Emitter::setVelocity(glm::vec3 v) {
	velocity = v;
}

void Emitter::setChildImage(ofImage img) {
	childImage = img;
	haveChildImage = true;
}

void Emitter::setImage(ofImage img) {
	image = img;
}

void Emitter::setRate(float r) {
	rate = r;
}

//--------------------------------------------------------------
Helicopter::Helicopter() {
	speed = 0;
	velocity = glm::vec3(0, 0, 0);
	bSelected = false;
	haveImage = false;
	name = "UnamedSprite";
	width = 60;
	height = 80;
	child1 = new Emitter(new SpriteSystem());
	child2 = new Emitter(new SpriteSystem());
}

void Helicopter::draw() {

	ofSetColor(255, 255, 255, 255);

	// draw image centered and add in translation amount
	//
	ofPushMatrix();
	ofMultMatrix(getTransformMatrix());
	if (haveImage) {
		image.draw(-width / 2.0, -height / 2.0); //ditto as below
	}
	else {
		// in case no image is supplied, draw something.
		// 
		ofSetColor(255, 0, 0);
		ofDrawRectangle(-width / 2.0, -height / 2.0, width, height); //remove trans
	}

	ofPopMatrix();
	child1->draw();
	child2->draw();
}

void Helicopter::update() {
	glm::vec3 pos1 = glm::vec4(20, 0, 0, 0) * glm::rotate(glm::mat4(1.0), glm::radians(rot), glm::vec3(0, 0, 1));
	cout << "x: " << pos1.x << " y: " << pos1.y << endl;
	child1->setPosition(glm::vec3(trans.x + pos1.x, trans.y - pos1.y, 0));
	child2->setPosition(glm::vec3(trans.x - pos1.x, trans.y + pos1.y, 0));
	child1->rot = rot;
	child2->rot = rot;
	child1->update();
	child2->update();
}

void Helicopter::start() {
	child1->start();
	child2->start();
}

void Helicopter::stop() {
	child1->stop();
	child2->stop();
}

void Helicopter::setImage(ofImage img) {
	image = img;
	haveImage = true;
	width = image.getWidth();
	height = image.getHeight();
}

//--------------------------------------------------------------
void ofApp::setup(){
	/*
	playerSprite.setPosition(glm::vec3(ofGetWidth() / 2.0, ofGetHeight() / 2.0, 0));
	
	
	launcherLeft = new Emitter(new SpriteSystem());
	launcherLeft->setPosition(glm::vec3(playerSprite.trans.x + 20, playerSprite.trans.y, 0));
	launcherLeft->drawable = true;
	launcherLeft->start();
	launcherRight = new Emitter(new SpriteSystem());
	launcherRight->setPosition(glm::vec3(playerSprite.trans.x - 20, playerSprite.trans.y, 0));
	launcherRight->drawable = true;
	launcherRight->start();
	*/
	player.setPosition(glm::vec3(ofGetWidth() / 2.0, ofGetHeight() / 2.0, 0));
	player.child1->setPosition(glm::vec3(ofGetWidth() / 2.0 + 20, ofGetHeight() / 2.0, 0));
	player.child2->setPosition(glm::vec3(ofGetWidth() / 2.0 - 20, ofGetHeight() / 2.0, 0));
	player.start();
	
	

	gui.setup();
	gui.add(rate.setup("rate", 1, 1, 10));
	gui.add(life.setup("life", 5, .1, 10));
	gui.add(velocity.setup("velocity", glm::vec3(0, 100, 0), glm::vec3(-1000, -1000, -1000), glm::vec3(1000, 1000, 1000)));
	gui.add(playerSpeed.setup("playerSpeed", 2, 1, 10));
	gui.add(playerRotate.setup("playerRotate", 2, 1, 45));
	bHide = false;
}

//--------------------------------------------------------------
void ofApp::update(){
	//launcherLeft->setPosition(glm::vec3(playerSprite.trans.x + 20, playerSprite.trans.y, 0));
	//launcherRight->setPosition(glm::vec3(playerSprite.trans.x - 20, playerSprite.trans.y, 0));
	//launcherLeft->rot = playerSprite.rot;
	//cout << "dfjk: " << player.child1->trans.x<< endl;
	//launcherRight->rot = playerSprite.rot;
	if (isGameInit) {
		//launcherLeft->setRate(rate);
		//launcherLeft->setLifespan(life * 1000);    // convert to milliseconds 
		//launcherLeft->setVelocity(glm::vec3(velocity->x, velocity->y, velocity->z));
		//launcherLeft->update();
		//launcherRight->setRate(rate);
		//launcherRight->setLifespan(life * 1000);    
		//launcherRight->setVelocity(glm::vec3(velocity->x, velocity->y, velocity->z));
		//launcherRight->update();
		player.update();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	player.draw();
	/*
	playerSprite.draw();
	launcherLeft->draw();
	launcherRight->draw();
	*/

	if (!bHide) {
		gui.draw();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	case OF_KEY_UP:
		playerSprite.setPosition(glm::vec3(playerSprite.trans.x, playerSprite.trans.y + playerSpeed, 0));
		break;
	case OF_KEY_DOWN:
		playerSprite.setPosition(glm::vec3(playerSprite.trans.x, playerSprite.trans.y - playerSpeed, 0));
		break;
	case OF_KEY_RIGHT:
		player.setPosition(glm::vec3(player.trans.x - playerSpeed, player.trans.y, 0));
		playerSprite.setPosition(glm::vec3(playerSprite.trans.x - playerSpeed, playerSprite.trans.y, 0));
		break;
	case OF_KEY_LEFT:
		player.setPosition(glm::vec3(player.trans.x + playerSpeed, player.trans.y, 0));
		playerSprite.setPosition(glm::vec3(playerSprite.trans.x + playerSpeed, playerSprite.trans.y, 0));
		break;
	case 'a':
		player.rot -= playerRotate;
		playerSprite.rot -= playerRotate;
		break;
	case 'd':
		player.rot += playerRotate;
		playerSprite.rot += playerRotate;
		break;
	case 'h':
		bHide = !bHide;
		break;
	case 'f':
		bFullscreen = !bFullscreen;
		ofSetFullscreen(bFullscreen);
		break;
	case ' ':
	{
		if (!isGameInit) {
			isGameInit = true;
		}
		isFire = !isFire;
		if (isFire) {
			//launcherLeft->start();
			//launcherRight->start();
		}
		else {
			//launcherLeft->stop();
			//launcherRight->stop();
		}
		break;
	}
	case 'p':
		isPaused = !isPaused;
		break;
	default:
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
