#include "TitleScreen.h"
#include "ProjectConstants.h"

TitleScreen::TitleScreen() {
}

TitleScreen::~TitleScreen() {
}

void TitleScreen::init() {
	m_image.load( ProjectConstants::IMG_PATH_SCREEN_TITLE );
}

void TitleScreen::render() {
	ofSetRectMode( OF_RECTMODE_CORNER );

    ofFill();
    ofSetColor( ofColor::white );
    m_image.draw( 0, 0 );
}
