#include "Player1Win.h"
#include "ProjectConstants.h"

GameOverScreen::GameOverScreen() {
}

GameOverScreen::~GameOverScreen() {
}

void GameOverScreen::init() {
	m_image.load( ProjectConstants::IMG_PATH_SCREEN_WINNER1 );
}

void GameOverScreen::render() {
	ofSetRectMode( OF_RECTMODE_CORNER );

    ofFill();
    ofSetColor( ofColor::white );
    m_image.draw( 0, 0 );    
}
