#include "Game.h"
#include "ProjectConstants.h"
#include "affine.hpp"
#include "ofApp.h"

Game::Game()
	: m_state(GameState::NotInitialized)
	, m_score(200),
	m_score2(200)
{
}

Game::~Game() {
}

void Game::init() {


	time = 0;

	track1 = false;
	track2 = false;
	m_fighter1.load(ProjectConstants::IMG_PATH_SCREEN_FIGHTER1);
	m_fighter2.load(ProjectConstants::IMG_PATH_SCREEN_FIGHTER2);

	m_font.load(ProjectConstants::FONT_PATH_MONSTERRAT, 9, true);

	m_font2.load(ProjectConstants::FONT_PATH_MONSTERRAT2, 20, true);

	m_thresholdSet = 0; //how much red gets tracked (similar colour)
	m_minRadiusSet = 10.0f; //size of min track
	m_maxRadiusSet = 150.0f; //size of max track

	//Specifications of color 2 tracking set
	m_thresholdSet2 = 0; //how much blue gets tracked (similar colour)
	m_minRadiusSet2 = 10.0f; //size of min track
	m_maxRadiusSet2 = 150.0f; //size of max track

	m_colorTracking1 = ofColor::blue;
	m_colorTracking2 = ofColor::red;

	m_sound.load("song.mp3"); // Loads Music
	m_punchSound.load("punchsound.mp3"); // Loads Music
	m_sound.play();			  // Music Plays when the game is launched

	m_guiMenu.setup();
	m_player1Win = false;
	m_player2Win = false;

	m_fighter1X = 0;
	m_fighter1Y = 0;

	m_fighter2X = 0;
	m_fighter2Y = 0;

	int mouseX = 0;
	int mouseY = 0;
	
	m_inGame.load(ProjectConstants::IMG_PATH_SCREEN_INGAME);

	m_webcam.setup(1280, 720);
	m_state = GameState::Ready;

}

void Game::update() {
	// Are we playing? then update our objects
	if (m_state == GameState::Playing)
	{
		updateWin();
		colorPicker();
		updateVideo();
		//updateCollision();
		//mousePressed(2, 2, 1);

		time = ofGetElapsedTimef();



	}
}

void Game::render() {


	m_webcam.draw(0, 0);
	ofFill();
	ofSetColor(ofColor::white);
	m_inGame.draw(0, 0);

	ofFill();
	ofSetColor(255, 25, 25);
	ofDrawRectangle(80, 23, m_score, 19);
	ofDrawRectangle(707, 23, m_score2, 19);


	fighterContour1(m_fighterContour1, ofFloatColor(0, 0, 1.0f));
	fighterContour2(m_fighterContour2, ofFloatColor(1.0f, 0, 0));

	//drawing our selected color (want to give some basic user feedback)
	ofFill();

	ofSetColor(m_colorTracking1);
	ofDrawRectangle(210, 58, 30, 30);


	ofSetColor(m_colorTracking2);
	ofDrawRectangle(1050, 58, 30, 30);

	ofSetColor(ofColor::white);
	//draw our GUI (sliders for adjusting thresholds)
	m_guiMenu.begin();
		ImGui::SliderInt("Threshold", &m_thresholdSet, 0, 255);
		ImGui::SliderFloat("Min Radius", &m_minRadiusSet, 0.0f, 750.0f);
		ImGui::SliderFloat("Max Radius", &m_maxRadiusSet, 0.0f, 750.0f);
		ImGui::SliderInt("Threshold 2 ", &m_thresholdSet2, 0, 255);
		ImGui::SliderFloat("Min Radius 2", &m_minRadiusSet2, 0.0f, 750.0f);
		ImGui::SliderFloat("Max Radius 2", &m_maxRadiusSet2, 0.0f, 750.0f);
	m_guiMenu.end();

	ofSetColor(ofColor::white);

	m_font2.drawString("" + ofToString(time), 622, 40);



}

void Game::begin() {

	track1 = false;
	track2 = false;

	time = 0;

	m_fighter1.load(ProjectConstants::IMG_PATH_SCREEN_FIGHTER1);
	m_fighter2.load(ProjectConstants::IMG_PATH_SCREEN_FIGHTER2);

	//Specifications of color 1 tracking set
	m_thresholdSet = 30; //how much red gets tracked (similar colour)
	m_minRadiusSet = 10.0f; //size of min track
	m_maxRadiusSet = 150.0f; //size of max track

	//Specifications of color 2 tracking set
	m_thresholdSet2 = 30; //how much blue gets tracked (similar colour)
	m_minRadiusSet2 = 10.0f; //size of min track
	m_maxRadiusSet2 = 150.0f; //size of max track

	m_colorTracking1 = ofColor::blue;
	m_colorTracking2 = ofColor::red;

	// reset score and number of remaining asteroids
	m_score = 490;
	m_score2 = 490;

	// We're now playing the game - set state to Playing
	m_state = GameState::Playing;
}

void Game::updateWin() {

	//For the game over screen, the respective bools for each players score which links to the proper screen display
	if (m_score <= 0)
	{

		m_state = GameState::GameWin;
		m_player1Win = false;
		m_player2Win = true;

		m_score2 = 0;
		return;
	}
	else 	if (m_score2 <= 0)
	{

		m_state = GameState::GameOver;
		m_player1Win = true;
		m_player2Win = false;
		m_score = 0;
		m_score2 = 0;
		return;
	}



}


////My old distance fucntion
//void Game::updateCollision() 
//{
//	distance = ofDist(m_fighter1X, m_fighter1Y, m_fighter2X, m_fighter2Y);
//
//	if (distance <= 10)
//	{
//		m_font.drawString("BLOCKED!!!", 700, 80);
//	}
//}


//Update the video function
void Game::updateVideo() {

	m_fighterContour1.setThreshold(m_thresholdSet); //How much of similar colour is detected
	m_fighterContour1.setMinAreaRadius(m_minRadiusSet);	 //Size of minimum area for detection
	m_fighterContour1.setMaxAreaRadius(m_maxRadiusSet); //Size of max area for detection
	m_fighterContour1.setTargetColor(m_colorTracking1, ofxCv::TRACK_COLOR_RGB);

	m_fighterContour2.setThreshold(m_thresholdSet2); //How much of similar colour is detected
	m_fighterContour2.setMinAreaRadius(m_minRadiusSet2);//Size of minimum area for detection
	m_fighterContour2.setMaxAreaRadius(m_maxRadiusSet2); //Size of max area for detection
	m_fighterContour2.setTargetColor(m_colorTracking2, ofxCv::TRACK_COLOR_RGB);

	//Update webcam
	m_webcam.update(); 
	m_webcam.isFrameNew();
	m_fighterContour1.findContours(m_webcam); //Find contours fucntion 1 for webcam call
	m_fighterContour2.findContours(m_webcam); //Find contours fucntion 2 for webcam call
}

//Fighter 1 contour fucntion
void Game::fighterContour1(ofxCv::ContourFinder & _fighterContour, ofFloatColor fighterColor1)
{
	//Set the contours variable to the fighter contour and size of it
	int numContours = _fighterContour.getContours().size();

	if (numContours > 0) {
		//Find the largest contour area if there is greater than 0 detected
		int indexLargest = 0;
		float largestArea = 0.0f;
		for (int i = 0; i < numContours; ++i)
		{
			if (_fighterContour.getContourArea(i) > largestArea) {
				indexLargest = i;
			}
		}

		ofFill();
		ofSetColor(fighterColor1);

		cv::Point2f center = _fighterContour.getCenter(indexLargest);
		m_fighter1X = center.x;
		m_fighter1Y = center.y;

		//Distance equation to track the variables of fighter 1, x and y, and fighter 2, x and y
		distance = ofDist(m_fighter1X, m_fighter1Y, m_fighter2X, m_fighter2Y);

			//If fighter 1 center of x compnenent is greater than or equal to 700 than the other fighters score is decreased by 10
			if (center.x >= 700)
			{
				//ofSetColor(trackCol);
				m_punchSound.play();
				m_score2 -= 10.0f;
			}

			//If there is a collision of distance less than 200 then it displays the text "block" showing the fighters theres been a block
			if (distance <= 200)
			{
				ofSetColor(ofColor::red);
				m_font2.drawString("BLOCKED", 400, 85); //print out blocked
				m_font2.drawString("BLOCKED", 730, 85); //print out blocked
			}

		cv::Rect rect = _fighterContour.getBoundingRect(indexLargest);
		double area = _fighterContour.getContourArea(indexLargest);
	
		//Draw the rectangle of the tracked colour
		ofSetColor(m_colorTracking1);
		ofDrawRectangle(rect.x, rect.y, rect.width, rect.height);
		ofSetColor(ofColor::white);
		//Display a text output that colour 1 has been tracked if detection is greater than 0
		m_font.drawString("TRACKED COLOUR 1", 250, 80);
		m_fighter1.draw(center.x, center.y);

		ofSetColor(fighterColor1 * 1.5f);
		const std::vector<cv::Point> contour = _fighterContour.getContour(indexLargest);

	}

	//Else if the number of contours is 0 then it indicates no colour has been tracked
	else if (numContours <= 0)
	{
		ofSetColor(ofColor::white);
		m_font.drawString("Place Mouse over COLOUR and press 1", 250, 80);
	}
}

//Fighter 2 contour fucntion
void Game::fighterContour2(ofxCv::ContourFinder & _fighterContour2, ofFloatColor fighterColor2)
{
	//Set the contours variable to the fighter contour and size of it
	int numContours2 = _fighterContour2.getContours().size();

	if (numContours2 > 0) 
	{
		//Find the largest contour area if there is greater than 0 detected
		int indexLargest = 0;
		float largestArea = 0.0f;
		for (int i = 0; i < numContours2; ++i)
		{
			if (_fighterContour2.getContourArea(i) > largestArea) {
				indexLargest = i;
			}
		}
		ofFill();
		ofSetColor(fighterColor2);

		cv::Point2f center2 = _fighterContour2.getCenter(indexLargest);
		m_fighter2X = center2.x;
		m_fighter2Y = center2.y;	
		
		//Player 1 score decreases.
		//If fighter 2 center of x compnenent is greater less or equal to 700 than the other fighters score is decreased by 10
		if (center2.x <= 700)
		{
				//ofSetColor(trackCol2);
				m_punchSound.play();
				m_score -= 10.0f;
				m_fighter2.draw(m_fighter2X, m_fighter2Y);
		}	
		
		
		cv::Rect rect = _fighterContour2.getBoundingRect(indexLargest);
		double area = _fighterContour2.getContourArea(indexLargest);

		//Draw the rectangle of the tracked colour
		ofSetColor(m_colorTracking2);
		ofDrawRectangle(rect.x, rect.y, rect.width, rect.height);
		ofSetColor(ofColor::white);
		//Display a text output that colour 1 has been tracked if detection is greater than 0
		m_font.drawString("TRACKED COLOUR 2", 900, 80);

	ofSetColor(fighterColor2 * 1.5f);

		const std::vector<cv::Point> contour = _fighterContour2.getContour(indexLargest);

	}

	//Else if the number of contours is 0 then it indicates no colour has been tracked
	else if (numContours2 <= 0)
	{
			ofSetColor(ofColor::white);
			m_font.drawString("Place Mouse over COLOUR and press 2", 780, 80);
	}
}

void Game::colorPicker()
{
	//If player presses 1 then it stores the colour of the r g and b values at that given mouse position x and y 
	if (ofGetKeyPressed('1'))
	{
		//Used get mouse x and y to find mouse position
		int index = (ofGetMouseX() + ofGetMouseY() * m_webcam.getWidth()) * m_webcam.getPixels().getBytesPerPixel();
		m_colorTracking1.r = m_webcam.getPixels()[index];
		m_colorTracking1.g = m_webcam.getPixels()[index + 1];
		m_colorTracking1.b = m_webcam.getPixels()[index + 2];
	
		track1 = true;
	}


	//If player presses 2 then it stores the colour of the r g and b values at that given mouse position x and y 
	if (ofGetKeyPressed('2'))
	{
		//Used get mouse x and y to find mouse position
		int index = (ofGetMouseX() + ofGetMouseY() * m_webcam.getWidth()) * m_webcam.getPixels().getBytesPerPixel();
		m_colorTracking2.r = m_webcam.getPixels()[index];
		m_colorTracking2.g = m_webcam.getPixels()[index + 1];
		m_colorTracking2.b = m_webcam.getPixels()[index + 2];

		track2 = true;
	}

	else {
		ofSetColor(ofColor::white);
		m_font.drawString("Place Mouse over COLOUR and press 2", 1950, 58);

		ofSetColor(ofColor::white);
		m_font.drawString("Place Mouse over COLOUR and press 1", 220, 58);
	}
}

//Get the games current state to be updated based on actions in game
Game::GameState Game::getGameState() {
	return m_state;
}




