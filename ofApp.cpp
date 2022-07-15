#include "ofApp.h"	
//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetColor(255);
	ofNoFill();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	ofMesh location_list;
	location_list.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
	for (int i = 0; i < 10; i++) {

		auto noise_seed = glm::vec2(ofRandom(1000), ofRandom(1000));
		ofMesh mesh;
		mesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
		for (int k = 0; k < 40; k++) {

			mesh.addVertex(glm::vec3(
				ofMap(ofNoise(noise_seed.x, k * 0.005 + ofGetFrameNum() * 0.005), 0, 1, -350, 350),
				ofMap(ofNoise(noise_seed.y, k * 0.005 + ofGetFrameNum() * 0.005), 0, 1, -350, 350),
				0));

			if (k > 0) {

				mesh.addIndex(k);
				mesh.addIndex(k - 1);
			}

			if (k % 10 == 0) {

				location_list.addVertex(mesh.getVertices().back());
			}
		}

		//mesh.drawWireframe();
	}

	for (int i = 0; i < location_list.getNumVertices(); i++) {

		ofNoFill();
		ofDrawCircle(location_list.getVertex(i), 5);

		for (int k = i + 1; k < location_list.getNumVertices(); k++) {

			auto distance = glm::distance(location_list.getVertex(i), location_list.getVertex(k));
			if (distance < 60) {

				location_list.addIndex(i);
				location_list.addIndex(k);

				ofFill();
				ofDrawCircle(location_list.getVertex(i), 2);
				ofDrawCircle(location_list.getVertex(k), 2);
			}
		}
	}

	location_list.drawWireframe();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}