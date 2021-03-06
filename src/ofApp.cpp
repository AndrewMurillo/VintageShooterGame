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

void Sprite::update() {
	//cout << "Sprite update()" << endl;
	trans += velocity / ofGetFrameRate();
}

//-------------------------------------------------------------
PathSprite::PathSprite() : Sprite() {
	//cout << "PathSprite made" << endl;
}

void PathSprite::update() {
	//cout << "PathSprite update()" << endl;
	float speed = glm::length(velocity);
	glm::vec3 p = trans + (getHeading() * speed);
	trans = curveEval(p.x, scale, cycles);
	//tri.pos = newPos;
	// find angle to rotate to new heading; we rotate
	// from "home" position;  (you could rotate incrementally
	// from last position as well, but you need to keep previous
	// heading;
	//
	glm::vec3 homeOrient;
	if (haveImage)
		homeOrient = glm::vec3(0, -1, 0);  // image needs to be flipped;
	else
		homeOrient = glm::vec3(0, 1, 0);


	// set rotation (angle between heading and home orientation)
	//
	rot = -glm::degrees(glm::orientedAngle(getHeading(), homeOrient, glm::vec3(0, 0, 1)));
}

glm::vec3 PathSprite::curveEval(float x, float scale, float cycles) {
	float u = (cycles * x * PI) / ofGetWidth();
	return glm::vec3(x, -scale * sin(u) + (ofGetHeight() / 2), 0);
}

//-------------------------------------------------------------

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
	haveSound = false;
	velocity = getHeading() * 100;
	//velocity = glm::vec3(0, 1000, 0);
	drawable = false;
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
			sprite.velocity = getHeading() * glm::length(velocity);
			sprite.lifespan = lifespan;
			sprite.setPosition(trans);
			sprite.birthtime = time;
			sys->add(sprite);
			lastSpawned = time;
			if(haveSound) sound.play();
		}
	}
	sys->update();
}

// Start/Stop the emitter.
//
void Emitter::start() {
	started = true;
	//lastSpawned = ofGetElapsedTimeMillis();
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

void Emitter::setSound(ofSoundPlayer s) {
	haveSound = true;
	sound = s;
}
//--------------------------------------------------------------
//  Create a new Emitter - needs a SpriteSystem
//
PathEmitter::PathEmitter(SpriteSystem *spriteSys) : Emitter(spriteSys) {
	sys = spriteSys;
}

void PathEmitter::update() {
	//cout << "PathEmitter update()" << endl;
	if (started) {

		float time = ofGetElapsedTimeMillis();
		if ((time - lastSpawned) > (1000.0 / rate)) {
			// spawn a new sprite
			PathSprite sprite;
			if (haveChildImage) sprite.setImage(childImage);
			sprite.velocity = getHeading() * 100;
			sprite.lifespan = lifespan;
			sprite.setPosition(trans);
			sprite.birthtime = time;
			sys->add(sprite);
			lastSpawned = time;
			if (haveSound) sound.play();
		}
	}
	sys->update();
}
/**
void PathEmitter::draw() {
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

void PathEmitter::start() {
	started = true;
	//lastSpawned = ofGetElapsedTimeMillis();
}

void PathEmitter::stop() {
	started = false;
}


void PathEmitter::setLifespan(float life) {
	lifespan = life;
}

void PathEmitter::setSpeed(float s) {
	speed = s;
}

void PathEmitter::setChildImage(ofImage img) {
	childImage = img;
	haveChildImage = true;
}

void PathEmitter::setImage(ofImage img) {
	image = img;
}

void PathEmitter::setRate(float r) {
	rate = r;
}

void PathEmitter::setSound(ofSoundPlayer s) {
	haveSound = true;
	sound = s;
}
*/
//--------------------------------------------------------------
Helicopter::Helicopter() {
	speed = 0;
	velocity = glm::vec3(0, 0, 0);
	bSelected = false;
	haveImage = false;
	started = false;
	width = 60;
	height = 80;
	emitters.push_back(new Emitter(new SpriteSystem()));
	emitters.push_back(new Emitter(new SpriteSystem()));
	//sys = new SpriteSystem();
	//child1 = new Emitter(sys);
	//child2 = new Emitter(sys);
}

void Helicopter::setup(glm::vec3 pos) {
	setPosition(pos);
	emitters[0]->setPosition(glm::vec3(pos.x + 20, pos.y, 0));
	emitters[1]->setPosition(glm::vec3(pos.x - 20, pos.y, 0));
	for (auto emit : emitters) {
		emit->setVelocity(glm::vec3(0, 500, 0));
	}
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
	for (auto emit : emitters) {
		emit->draw();
	}
}

void Helicopter::update() {
	//	Rotate offset -> affects where sprites are drawn!
	glm::vec3 pos1 = glm::vec4(20, 0, 0, 0) * glm::rotate(glm::mat4(1.0), glm::radians(rot), glm::vec3(0, 0, 1));
	//	Set pos at parent object + offset! (Reminder y is inverted on the screen!)
	emitters[0]->setPosition(glm::vec3(trans.x + pos1.x, trans.y - pos1.y, 0));
	emitters[1]->setPosition(glm::vec3(trans.x - pos1.x, trans.y + pos1.y, 0));
	for (auto emit : emitters) {
		//	Set rot to parent rot
		emit->rot = rot;
		//	Call children update
		emit->update();
	}
}

void Helicopter::start() {
	// Start children emitters
	if (!started) {
		started = true;
		for (auto emit : emitters) {
			emit->start();
		}
	}
}

void Helicopter::stop() {
	// Stop children emitters
	started = false;
	for (auto emit : emitters) {
		emit->stop();
	}
}

void Helicopter::setImage(ofImage img) {
	image = img;
	haveImage = true;
	width = image.getWidth();
	height = image.getHeight();
}

void Helicopter::setRate(float r) {
	for (auto emit : emitters) {
		emit->rate = r;
	}
}

void Helicopter::setProjImage(ofImage img) {
	for (auto emit : emitters) {
		emit->setChildImage(img);
	}
}

void Helicopter::setProjSound(ofSoundPlayer sound) {
	for (auto emit : emitters) {
		emit->setSound(sound);
	}
}
//--------------------------------------------------------------
void Player::update() {
	shoot();
	move();
	Helicopter::update();
}

//	Calc movement based on booleans changed by keyboard input
//
void Player::move() {
	int newX = trans.x;
	if (isLeft) {
		newX = trans.x - 5;
		if (newX < 0) {
			newX = trans.x;
		}
	}
	if (isRight) {
		newX = trans.x + 5;
		if (newX > ofGetWindowWidth()) {
			newX = trans.x;
		}
	}
	int newY = trans.y;
	if (isUp) {
		newY = trans.y - 5;
		if (newY < 0) {
			newY = trans.y;
		}
	}
	if (isDown) {
		newY = trans.y + 5;
		if (newY > ofGetWindowHeight()) {
			newY = trans.y;
		}
	}
	setPosition(glm::vec3(newX, newY, 0));
	if (isRotCClockwise) {
		rot -= 5;
	}
	if (isRotClockwise) {
		rot += 5;
	}
}

void Player::shoot() {
	if (isFire) {
		start();
	}
	//stop();
}
//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFullscreen(true);
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
	player.setup(glm::vec3(ofGetWidth() / 2.0, ofGetHeight() / 2.0, 0));
	player.setImage(playerImage);
	player.setProjImage(playerProjImage);
	player.setProjSound(playerSound);

	//	SCORE SETUP
	//
	if (!score_font.loadFont("fonts/PressStart2P-Regular.ttf", 12)) {
		ofLogFatalError("Can't load font.");
		ofExit();
	}
	score = 0;

	//	ENEMY SETUP
	//
	if (enemyProjImage.load("images/ball2.png")) {
		enemyProjLoaded = true;
	}
	else {
		ofLogFatalError("can't load image: images/ball2.png");
		ofExit();
	}
	//load spawn sound
	enemySound.load("sounds/positiveBeep.ogg");
	/*
	emit1 = new PathEmitter(new SpriteSystem());
	emit1->setChildImage(enemyProjImage);
	emit1->setPosition(glm::vec3(0, ofGetWindowHeight() / 2.0, 0));
	emit1->rot -= 90;
	emit1->drawable = true;
	emit1->lifespan = 10000;
	*/
	numEmitters = 8;
	// create an array of emitters and set their position;
	//
	//enemySprites = new SpriteSystem(); //DELETE THIS
	for (int i = 0; i < numEmitters; i++) {
		Emitter *emit = new Emitter(new SpriteSystem());
		emit->setPosition(ofVec3f(rand() % ofGetWindowWidth(), 0, 0));
		emit->setVelocity(glm::vec3(0, rand() % 101 + 100, 0));
		emit->setRate((rand() % 9 + 1) * 0.1);
		emit->lifespan = 10000;
		//emit->drawable = true;                // make emitter itself invisible
		emit->setChildImage(enemyProjImage);
		//emit->setImage(playerImage); Only really necessary if they were stationary
		emit->setSound(enemySound);
		emitters.push_back(emit);
	}
	
	//	GUI SETUP
	//
	gui.setup();
	gui.add(rate.setup("rate", 1, 1, 10));
	/*
	gui.add(offset.setup("offset", 20, 1, 500));
	gui.add(life.setup("life", 5, .1, 10));
	gui.add(velocity.setup("velocity", glm::vec3(0, 100, 0), glm::vec3(-1000, -1000, -1000), glm::vec3(1000, 1000, 1000)));
	gui.add(playerSpeed.setup("playerSpeed", 5, 1, 20));
	gui.add(playerRotate.setup("playerRotate", 2, 1, 45));
	*/
	bHide = false;
}

//--------------------------------------------------------------
void ofApp::update(){
	//	CHECK IF GAME HAS STARTED
	//
	player.setRate(rate);
	if (isGameInit) {
		//	UPDATE PLAYER
		//
		player.update();
		//	UPDATE ENEMYS
		//
		//emit1->update();
		for (int i = 0; i < emitters.size(); i++) {
			emitters[i]->setPosition(ofVec3f(rand() % ofGetWindowWidth(), 0, 0));
			emitters[i]->setVelocity(glm::vec3(0, rand() % 101 + 100, 0));
			emitters[i]->setRate((rand() % 9 + 1) * 0.1);
			emitters[i]->update();
		}
		//CHECK FOR COLLISIONS
		//
		//checkCollisions();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	//	CHECK IF GAME HAS STARTED
	//
	if (isGameInit) {
		//	DRAW BACKGROUND
		//
		ofSetColor(255, 255, 255, 255);
		background.draw(0, 0);
		//	DRAW PLAYER
		//
		player.draw();
		//	DRAW ENEMIES
		//
		//emit1->draw();
		for (int i = 0; i < emitters.size(); i++) {
			emitters[i]->draw();
		}
		//	DRAW SCORE
		//
		score_font.drawString(ofToString(score), 30, 72);
	}
	else { //	DRAW START SCREEN
		ofDrawBitmapString("PRESS SPACE TO START", ofPoint(ofGetWindowWidth() / 2 - 90, ofGetWindowHeight() / 2));
	}

	if (!bHide) {
		gui.draw();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	case OF_KEY_UP:
		player.isUp = true;
		player.isDown = false;
		break;
	case OF_KEY_DOWN:
		player.isDown = true;
		player.isUp = false;
		break;
	case OF_KEY_RIGHT:
		player.isRight = true;
		player.isLeft = false;
		break;
	case OF_KEY_LEFT:
		player.isLeft = true;
		player.isRight = false;
		break;
	case 'a':
		player.isRotCClockwise = true;
		player.isRotClockwise = false;
		break;
	case 'd':
		player.isRotClockwise = true;
		player.isRotCClockwise = false;
		break;
	case 'h':
		bHide = !bHide;
		break;
	case 'f':
		//bFullscreen = !bFullscreen;
		//ofSetFullscreen(bFullscreen);
		break;
	case ' ':
		// Don't fire until game started
		//
		if (isGameInit) {
			player.isFire = true;
			//player.start();
		}
		// Check if game has not started and start game
		//
		if (!isGameInit) {
			isGameInit = true;
			//START ENEMY SPAWNERS
			//
			//emit1->start();
			for (int i = 0; i < emitters.size(); i++) {
				emitters[i]->start();
			}
		}
		break;
	case 'p': //UNIMPLEMENTED
		isPaused = !isPaused;
		break;
	default:
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	switch (key) {
	case OF_KEY_UP:
		player.isUp = false;
		break;
	case OF_KEY_DOWN:
		player.isDown = false;
		break;
	case OF_KEY_RIGHT:
		player.isRight = false;
		break;
	case OF_KEY_LEFT:
		player.isLeft = false;
		break;
	case 'a':
		player.isRotCClockwise = false;
		break;
	case 'd':
		player.isRotClockwise = false;
		break;
	case ' ':
		player.isFire = false;
		player.stop();
		break;
	default:
		break;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
	if (isGameInit) {
		ofPoint mouseCur = ofPoint(x, y);
		glm::vec3 difference = mouseCur - mouseLast;
		mouseLast = mouseCur;
		newPos = player.trans + difference;
		if (!(newPos.x < 0 || newPos.y < 0 || newPos.x > ofGetWidth() || newPos.y > ofGetHeight()))
			player.setPosition(newPos);
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	mouseLast = ofPoint(x, y);
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

// Mostly reused from Minigame example... Hahaha
//
/*
void ofApp::checkCollisions() {

	// find the distance at which the two sprites (missles and invaders) will collide
	// detect a collision when we are within that distance.
	//
	float collisionDist = playerProjImage.getHeight() / 2 + enemyProjImage.getHeight() / 2;

	// Loop through all the missiles, then remove any invaders that are within
	// "collisionDist" of the missiles.  the removeNear() function returns the
	// number of missiles removed.
	//
	for (int i = 0; i < player.sys->sprites.size(); i++) {
		//THERES AN ISSUE HERE... But at least it runs right?
		score += enemySprites->removeNear(player.sys->sprites[i].trans, collisionDist);
		//for (int j = 0; j < numEmitters; j++) {
		//	cout << emitters[i]->sys->sprites.size() << endl;
		//	score += emitters[i]->sys->removeNear(player.sys->sprites[i].trans, collisionDist);
		//}
	}
}
*/
