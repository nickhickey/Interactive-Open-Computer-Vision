#pragma once

#include "ofMain.h"
#include "ProjectConstants.h"
#include "ofxImGui.h"
#include "ofxCv.h"



class Game
{
public:
	enum GameState
	{
		NotInitialized,
		Ready,
		Playing,
		GameWin,
		GameOver
	};

	Game();
	~Game();

	void init();
	void update();
	void render();

	void begin();

	GameState getGameState();


	bool				  m_player1Win;
	bool				  m_player2Win;



private:
	
	//Who has won the game
	void updateWin();

	//Update the webcam video 
	void updateVideo();
	 
//	void updateCollision(); OLD FUNCTION FOR COLLISIONS, had problems
	
	//Color selector fucntion
	void colorPicker();
	//void mousePressed(int x, int y, int button);

	//The two contour finder functions to be used to find the positions and contours
	void fighterContour1(ofxCv::ContourFinder & _fighterContour, ofFloatColor fighterColor1);
	void fighterContour2(ofxCv::ContourFinder & _fighterContour2, ofFloatColor fighterColor2);


	//contour finders for each fighter
	ofxCv::ContourFinder	m_fighterContour1;
	ofxCv::ContourFinder	m_fighterContour2;


	//set up the game state
	GameState             m_state;

	//initialize the video grabber, sound players for the various sounds and the gui for the menu.
	ofVideoGrabber		  m_webcam;
	ofSoundPlayer		  m_sound;
	ofSoundPlayer		  m_punchSound;
	ofxImGui			  m_guiMenu;

	//initialize the two fighters scores
	float                 m_score;
	float                 m_score2;

	//initialize the two fighters x and y coordinates and create the distance fucntions to track the blocking
	float				 m_fighter1X;
	float				 m_fighter1Y;
	float				 m_fighter2X;
	float				 m_fighter2Y;
	float				 distance; // distance to be used to compare values
	float				 distance2;
	int				     time; //timer for the gameplay

	//Fighter 1 colour data
	int  				  m_thresholdSet;
	float				  m_minRadiusSet;
	float				  m_maxRadiusSet;


	//Fighter 2 colour data
	int  				  m_thresholdSet2;
	float				  m_minRadiusSet2;
	float				  m_maxRadiusSet2;


	//Tracking two colours
	ofColor				  m_colorTracking1;
	ofColor				  m_colorTracking2;

	//Set up the images
	ofImage				  m_fighter1;
	ofImage				  m_fighter2;
	ofImage				  m_inGame;

	bool track1; 
	bool track2;

	//Set up the font
	ofTrueTypeFont	      m_font;
	ofTrueTypeFont	      m_font2;
};
