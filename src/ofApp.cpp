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
	ofSetColor(255, 255, 255, 255); //default for images
	ofPushMatrix();
	ofMultMatrix(getTransformMatrix());
	if (haveImage) {
		// draw image centered
		//
		image.draw(-width / 2.0, -height / 2.0);
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
void Emitter::draw() {
	if (drawable) {
		ofPushMatrix();
		ofMultMatrix(getTransformMatrix());
		//similar to Sprite.draw()
		//
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
	width = 60;
	height = 80;
	child1 = new Emitter(new SpriteSystem());
	child2 = new Emitter(new SpriteSystem());
}

void Helicopter::draw() {
	ofSetColor(255, 255, 255, 255);
	ofPushMatrix();
	ofMultMatrix(getTransformMatrix());
	//	Similar to Sprite.draw()
	//
	if (haveImage) {
		image.draw(-width / 2.0, -height / 2.0);
	}
	else {
		ofSetColor(255, 0, 0);
		ofDrawRectangle(-width / 2.0, -height / 2.0, width, height); //remove trans
	}
	ofPopMatrix();
	//	Call children emitters!
	child1->draw();
	child2->draw();
}

void Helicopter::update() {
	//	Rotate offset -> affects where sprites are drawn!
	glm::vec3 pos1 = glm::vec4(20, 0, 0, 0) * glm::rotate(glm::mat4(1.0), glm::radians(rot), glm::vec3(0, 0, 1));
	//	Set pos at parent object + offset! (Reminder y is inverted on the screen!)
	child1->setPosition(glm::vec3(trans.x + pos1.x, trans.y - pos1.y, 0));
	child2->setPosition(glm::vec3(trans.x - pos1.x, trans.y + pos1.y, 0));
	//	Set rot to parent rot
	child1->rot = rot;
	child2->rot = rot;
	//	Call children update
	child1->update();
	child2->update();
}

void Helicopter::start() {
	// Start children emitters
	child1->start();
	child2->start();
}

void Helicopter::stop() {
	// Stop children emitters
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
	//load child image
	if (playerProjImage.load("images/ball.png")) {
		playerProjLoaded = true;
	}
	else {
		ofLogFatalError("can't load image: images/ball.png");
		ofExit();
	}
	//load Player image
	if (playerImage.load("images/turret.png")) {
		playerImageLoaded = true;
	}
	else {
		ofLogFatalError("can't load image: images/turret.png");
		ofExit();
	}
	//load background
	if (!background.load("images/plains.png")) {
		ofLogFatalError("can't load image: images/plains.png");
		ofExit();
	}
	//load turret sound
	playerSound.load("sounds/blast.wav");
	//	PLAYER SETUP
	//
	player.setPosition(glm::vec3(ofGetWidth() / 2.0, ofGetHeight() / 2.0, 0));
	player.child1->setPosition(glm::vec3(ofGetWidth() / 2.0 + 20, ofGetHeight() / 2.0, 0));
	player.child2->setPosition(glm::vec3(ofGetWidth() / 2.0 - 20, ofGetHeight() / 2.0, 0));
	player.start();
	
	//	GUI SETUP
	//
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
	//	CHECK IF GAME HAS STARTED
	//
	if (isGameInit) {
		player.update();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	//DRAW PLAYER
	//
	player.draw();
	
	if (!bHide) {
		gui.draw();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	case OF_KEY_UP:
		break;
	case OF_KEY_DOWN:
		break;
	case OF_KEY_RIGHT:
		player.setPosition(glm::vec3(player.trans.x - playerSpeed, player.trans.y, 0));
		break;
	case OF_KEY_LEFT:
		player.setPosition(glm::vec3(player.trans.x + playerSpeed, player.trans.y, 0));
		break;
	case 'a':
		player.rot -= playerRotate;
		break;
	case 'd':
		player.rot += playerRotate;
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
