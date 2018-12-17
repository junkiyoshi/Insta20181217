#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofSetColor(239);

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	int font_size = 150;
	this->font.loadFont("fonts/Kazesawa-Bold.ttf", font_size, true, true, true);

	ofFbo fbo;
	fbo.allocate(ofGetWidth(), ofGetHeight());
	fbo.begin();
	ofClear(0);

	string word = "Daily";
	font.drawString(word, ofGetWidth() * 0.5 - font.stringWidth(word) * 0.5, ofGetHeight() * 0.5 - font_size * 0.5);

	word = "Coding";
	font.drawString(word, ofGetWidth() * 0.5 - font.stringWidth(word) * 0.5, ofGetHeight() * 0.5 + font_size * 1.5);

	fbo.end();

	ofPixels pixels;
	fbo.readToPixels(pixels);

	font_size = 10;
	for (int x = 0; x < fbo.getWidth(); x += font_size) {

		for (int y = 0; y < fbo.getHeight(); y += font_size) {

			if (pixels.getColor(x, y) != ofColor(0, 0)) {

				this->locations.push_back(ofPoint(x, y));
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	for (int i = 0; i < this->locations.size(); i++) {

		glm::vec2 noise_point = glm::vec2(
			ofMap(ofNoise(this->locations[i].x * 0.01, this->locations[i].y * 0.01, ofGetFrameNum() * 0.03), 0, 1, -20, 20),
			0);

		ofDrawCircle(this->locations[i], 1);
		ofDrawCircle(this->locations[i] + noise_point, 3);
		ofDrawLine(this->locations[i], this->locations[i] + noise_point);
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}