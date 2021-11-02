#include "ofApp.h"


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
	if (playerImage.load("images/EnemyHeli.png")) {
		playerImageLoaded = true;
	}
	else {
		ofLogFatalError("can't load image: images/EnemyHeli.png");
		ofExit();
	}
	//load background
	if (!background.load("images/plains.png")) {
		ofLogFatalError("can't load image: images/plains.png");
		ofExit();
	}
	//load turret sound
	playerSound.load("sounds/blast.wav");
	//SPRITESYS SETUP
	//
	projectiles = new SpriteSystem();
	//	PLAYER SETUP
	//
	player.heli = new Helicopter(projectiles);
	player.heli->setup(glm::vec3(ofGetWidth() / 2.0, ofGetHeight() / 2.0, 0));
	player.heli->setImage(playerImage);
	player.heli->setProjImage(playerProjImage);
	player.heli->setProjSound(playerSound);

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
	numEmitters = 1;
	// create an array of emitters and set their position;
	//
	//enemySprites = new SpriteSystem(); //DELETE THIS
	for (int i = 0; i < numEmitters; i++) {
		Emitter *emit = new Emitter(projectiles);
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
	player.heli->setRate(rate);
	if (state == gamePlay) {
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
		projectiles->update();
		//CHECK FOR COLLISIONS
		//
		//checkCollisions();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	//	CHECK IF GAME HAS STARTED
	//
	if (state == gamePlay) {
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
		projectiles->draw();
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
		//player.isDown = false;
		break;
	case OF_KEY_DOWN:
		player.isDown = true;
		//player.isUp = false;
		break;
	case OF_KEY_RIGHT:
		player.isRight = true;
		//player.isLeft = false;
		break;
	case OF_KEY_LEFT:
		player.isLeft = true;
		//player.isRight = false;
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
		if (state == gamePlay) {
			//player.isFire = true;
			player.heli->start();
			//player.start();
		}
		// Check if game has not started and start game
		//
		if (state != gamePlay) {
			state = gamePlay;
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
		player.heli->stop();
		//player.isFire = false;
		//player.stop();
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
	if (state == gamePlay) {
		ofPoint mouseCur = ofPoint(x, y);
		glm::vec3 difference = mouseCur - mouseLast;
		mouseLast = mouseCur;
		newPos = player.heli->trans + difference;
		if (!(newPos.x < 0 || newPos.y < 0 || newPos.x > ofGetWidth() || newPos.y > ofGetHeight()))
			player.heli->setPosition(newPos);
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
