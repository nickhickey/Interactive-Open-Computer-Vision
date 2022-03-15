#include "Player2Win.h"
#include "ProjectConstants.h"
#include "ofMain.h"

GameWinScreen::GameWinScreen() {
}

GameWinScreen::~GameWinScreen() {
}

void GameWinScreen::init() {
	m_image.load( ProjectConstants::IMG_PATH_SCREEN_WINNER2 );
	m_font.load(ProjectConstants::FONT_PATH_MONSTERRAT, 20, true);
}

void GameWinScreen::render() {
	ofSetRectMode( OF_RECTMODE_CORNER );

    ofFill();
    ofSetColor( ofColor::white );
    m_image.draw( 0, 0 );    

	//if (m_player1Win == true) {


	//}
	//m_font.drawString("Boxing 2016: ", 40, 40);
}
