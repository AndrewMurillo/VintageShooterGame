#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){
	//Define Allied Helicopter Sprite
	AllyHeliImage = new ofImage();
	string AllyHeliFile = "images/AllyHeli.png";
	if (!AllyHeliImage->load(AllyHeliFile)) {
		ofLogFatalError("Can't Load " + AllyHeliFile);
		ofExit();
	}
	
	
	//Test

	testSprite = new Sprite(AllyHeliImage);
	//testSprite->transform->setPosition(glm::vec3(ofGetWidth() / 2.0, ofGetHeight() / 2.0, 0));
	cout << testSprite->name << endl;
	cout << testSprite->haveImage << endl;
	cout << testSprite->transform->trans << endl;
	/*
	ofSetFullscreen(true);*/
	////load child image
	//if (playerProjImage.load("images/missle.png")) {
	//	playerProjLoaded = true;
	//}
	//else {
	//	ofLogFatalError("can't load image: images/ball.png");
	//	ofExit();
	//}
	////load Player image
	//if (playerImage.load("images/EnemyHeli.png")) {
	//	playerImageLoaded = true;
	//}
	//else {
	//	ofLogFatalError("can't load image: images/EnemyHeli.png");
	//	ofExit();
	//}
	////load background
	//if (!background.load("images/plains.png")) {
	//	ofLogFatalError("can't load image: images/plains.png");
	//	ofExit();
	//}
	////load turret sound
	//playerSound.load("sounds/blast.wav");
	//playerHurtSound.load("sounds/retroHurt.mp3");
	//SPRITESYS SETUP
	////
	//playerProj = new SpriteSystem();
	//enemyProj = new SpriteSystem();
	//	PLAYER SETUP
	////
	//player.lives = 3;
	//player.heli = new AttackHeli(playerProj);
	//player.heli->setup(glm::vec3(ofGetWidth() / 2.0, ofGetHeight() / 2.0, 0));
	//player.heli->setImage(playerImage);
	//player.heli->setProjImage(playerProjImage);
	//player.heli->setProjSound(playerSound);

	//	SCORE SETUP
	//
	/*if (!score_font.loadFont("fonts/PressStart2P-Regular.ttf", 12)) {
		ofLogFatalError("Can't load font.");
		ofExit();
	}
	score = 0;*/

	//	ENEMY SETUP
	//
	/*if (enemyProjImage.load("images/missle2.png")) {
		enemyProjLoaded = true;
	}
	else {
		ofLogFatalError("can't load image: images/missle2.png");
		ofExit();
	}*/
	//load enemy death sound
	/*enemySound.load("sounds/positiveBeep.ogg");*/
	/*
	emit1 = new PathEmitter(new SpriteSystem());
	emit1->setChildImage(enemyProjImage);
	emit1->setPosition(glm::vec3(0, ofGetWindowHeight() / 2.0, 0));
	emit1->rot -= 90;
	emit1->drawable = true;
	emit1->lifespan = 10000;
	*/
	/*
	numEmitters = 8;
	// create an array of emitters and set their position;
	//
	//enemySprites = new SpriteSystem(); //DELETE THIS
	for (int i = 0; i < numEmitters; i++) {
		Emitter *emit = new Emitter(enemyProj);
		emit->setPosition(ofVec3f(rand() % ofGetWindowWidth(), 0, 0));
		emit->setVelocity(glm::vec3(0, rand() % 101 + 100, 0));
		emit->setRate((rand() % 9 + 1) * 0.1);
		emit->lifespan = 10000;
		//emit->drawable = true;                // make emitter itself invisible
		emit->setChildImage(enemyProjImage);
		//emit->setImage(playerImage); Only really necessary if they were stationary
		//emit->setSound(enemySound);
		emitters.push_back(emit);
	}
	*/
	//tForce = new TurbulenceForce(glm::vec3(minT->x, minT->y, minT->y), glm::vec3(maxT->x, maxT->y, maxT->y));
	/*expForce = new ImpulseRingForce(expMagnitude);
	e = new Explosion();
	e->setLifespan(2);
	e->setGroupSize(100);
	e->sys->addForce(expForce);
	e->setVelocity(glm::vec3(0, 0, 0));
	e->setOneShot(true);*/

	//	GUI SETUP
	//
	/*gui.setup();
	gui.add(rate.setup("rate", 3, 1, 10));
	gui.add(thrust.setup("thrust", 700, 100, 1000));
	gui.add(projSpeed.setup("projSpeed", 1000, 500, 2000));
	gui.add(heliOffset.setup("offset", 20, 0, 50));
	gui.add(expMagnitude.setup("explosion magnitude", 500, 1, 1000));*/
	//gui.add(minT.setup("Min Turb", glm::vec3(-20, -20, 0), glm::vec3(-50, -50, 0), glm::vec3(0, 0, 0)));
	//gui.add(maxT.setup("Max Turb", glm::vec3(20, 20, 0), glm::vec3(50, 50, 0), glm::vec3(0, 0, 0)));
	/*
	gui.add(velocity.setup("velocity", glm::vec3(0, 100, 0), glm::vec3(-1000, -1000, -1000), glm::vec3(1000, 1000, 1000)));
	gui.add(playerSpeed.setup("playerSpeed", 5, 1, 20));
	gui.add(playerRotate.setup("playerRotate", 2, 1, 45));
	*/
	/*bHide = true;*/
}

//--------------------------------------------------------------
void ofApp::update(){
	testSprite->update();
	//	CHECK IF GAME HAS STARTED
	////
	//player.heli->setRate(rate);
	//player.thrust = thrust;
	//player.heli->projSpeed = projSpeed;
	//player.heli->offset = heliOffset;
	//expForce->setMagnitude(expMagnitude);
	//tForce->setMagnitude(glm::vec3(minT->x, minT->y, minT->y), glm::vec3(maxT->x, maxT->y, maxT->y));
	//if (state == gamePlay) {
	//	//	UPDATE PLAYER
	//	//
	//	player.update();
	//	//	UPDATE ENEMYS
	//	//
	//	//emit1->update();
	//	for (int i = 0; i < emitters.size(); i++) {
	//		emitters[i]->setPosition(ofVec3f(rand() % ofGetWindowWidth(), 0, 0));
	//		emitters[i]->setVelocity(glm::vec3(0, rand() % 101 + 100, 0));
	//		emitters[i]->setRate((rand() % 9 + 1) * 0.1);
	//		emitters[i]->update();
	//	}
	//	//	UPDATE EXPLOSIONS
	//	//
	//	e->update();
	//	playerProj->update();
	//	enemyProj->update();
	//	//CHECK FOR COLLISIONS
	//	//
	//	checkCollisions();
	//	if (player.lives <= 0)
	//		state = gameEnd;

	//}
}

//--------------------------------------------------------------
void ofApp::draw(){
	testSprite->draw();
	//	CHECK IF GAME HAS STARTED
	//
	//if (state == gamePlay) {
	//	//	DRAW BACKGROUND
	//	//
	//	ofSetColor(255, 255, 255, 255);
	//	background.draw(0, 0);
	//	//	DRAW PLAYER
	//	//
	//	player.draw();
	//	//	DRAW ENEMIES
	//	//
	//	//emit1->draw();
	//	for (int i = 0; i < emitters.size(); i++) {
	//		emitters[i]->draw();
	//	}
	//	//for (int i = 0; i < explosions.size(); i++) {
	//	//	explosions[i]->draw();
	//	//}
	//	e->draw();
	//	playerProj->draw();
	//	enemyProj->draw();
	//	//	DRAW SCORE
	//	//
	//	score_font.drawString("SCORE: " + ofToString(score), 30, 72);
	//	//  DRAW LIVES
	//	score_font.drawString("HEALTH: " + ofToString(player.lives), ofGetWindowWidth() - 200, 72);
	//}

	//else if(state == gameStart){ //	DRAW START SCREEN
	//	ofDrawBitmapString("PRESS SPACE TO START", ofPoint(ofGetWindowWidth() / 2 - 90, ofGetWindowHeight() / 2));
	//}

	//else {
	//	score_font.drawString("Final Score: " + ofToString(score), ofGetWindowWidth() / 2 - 90, ofGetWindowHeight() / 2);
	//}

	//if (!bHide) {
	//	gui.draw();
	//}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	case OF_KEY_UP:
		//player.isUp = true;
		break;
	case OF_KEY_DOWN:
		//player.isDown = true;
		break;
	case OF_KEY_RIGHT:
		//player.isRight = true;
		break;
	case OF_KEY_LEFT:
		//player.isLeft = true;
		break;
	case 'a':
		//player.isRotCClockwise = true;
		//player.isRotClockwise = false;
		break;
	case 'd':
		//player.isRotClockwise = true;
		//player.isRotCClockwise = false;
		break;
	case 'h':
		//bHide = !bHide;
		break;
	case 'f':
		//bFullscreen = !bFullscreen;
		//ofSetFullscreen(bFullscreen);
		break;
	case ' ':
		// Don't fire until game started
		//
		//if (state == gamePlay) {
		//	//player.isFire = true;
		//	player.heli->start();
		//	//player.start();
		//}
		// Check if game has not started and start game
		//
		/*if (state != gamePlay) {
			state = gamePlay;
			resetGame();
		}*/
		break;
	case 'p': //UNIMPLEMENTED
		//isPaused = !isPaused;
		break;
	default:
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	switch (key) {
	case OF_KEY_UP:
		//player.isUp = false;
		break;
	case OF_KEY_DOWN:
		//player.isDown = false;
		break;
	case OF_KEY_RIGHT:
		//player.isRight = false;
		break;
	case OF_KEY_LEFT:
		//player.isLeft = false;
		break;
	case 'a':
		//player.isRotCClockwise = false;
		break;
	case 'd':
		//player.isRotClockwise = false;
		break;
	case ' ':
		//player.heli->stop();
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
	/*if (state == gamePlay) {
		ofPoint mouseCur = ofPoint(x, y);
		glm::vec3 difference = mouseCur - mouseLast;
		mouseLast = mouseCur;
		newPos = player.heli->trans + difference;
		if (!(newPos.x < 0 || newPos.y < 0 || newPos.x > ofGetWidth() || newPos.y > ofGetHeight()))
			player.heli->setPosition(newPos);
	}*/
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	//mouseLast = ofPoint(x, y);
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

void ofApp::checkCollisions() {

	// find the distance at which the two sprites (missles and invaders) will collide
	// detect a collision when we are within that distance.
	//
	//float collisionDist = playerProjImage.getHeight() / 2 + enemyProjImage.getHeight() / 2;

	// Loop through all the missiles, then remove any invaders that are within
	// "collisionDist" of the missiles.  the removeNear() function returns the
	// number of missiles removed.
	//
	//!for (int i = 0; i < playerProj->sprites.size(); i++) {
	//!	score += enemyProj->removeNear(playerProj->sprites[i].trans, collisionDist, &enemySound);
	//!}
	//vector<Sprite>::iterator s = playerProj->sprites.begin();
	//bool erase = false;
	//while (s != playerProj->sprites.end()) {
	//	erase = false;
	//	for (int j = 0; j < enemyProj->sprites.size() && s != playerProj->sprites.end(); j++) {
	//		glm::vec3 length = enemyProj->sprites[j].trans - s->trans;
	//		if (glm::length(length) < collisionDist) {
	//			enemyProj->sprites.erase(enemyProj->sprites.begin() + j);
	//			e->setPosition(s->trans);
	//			s = playerProj->sprites.erase(s);
	//			score += 1;
	//			enemySound.play();
	//			//trigger explosion
	//			e->sys->reset();
	//			e->start();
	//			erase = true;
	//		}
	//	}
	//	if (!erase)
	//		s++;
	//}

	//!player.lives -= enemyProj->removeNear(player.heli->trans, collisionDist); //add hurt sound?
	/*for (int i = 0; i < enemyProj->sprites.size(); i++) {
		if ( glm::length(enemyProj->sprites[i].trans - player.heli->trans)< collisionDist) {
			enemyProj->sprites.erase(enemyProj->sprites.begin() + i);
			player.lives--;
			playerHurtSound.play();
		}
	}*/
}

void ofApp::resetGame() {
	//playerProj->reset();
	//for (int i = 0; i < emitters.size(); i++) {
	//	emitters[i]->stop();
	//}
	//enemyProj->reset();
	//player.lives = 3;
	//player.heli->rot = 0;
	//player.heli->velocity = glm::vec3(0, 0, 0);
	//player.heli->setup(glm::vec3(ofGetWidth() / 2.0, ofGetHeight() / 2.0, 0));
	//score = 0;
	////START ENEMY SPAWNERS
	////
	//for (int i = 0; i < emitters.size(); i++) {
	//	emitters[i]->start();
	//}
}