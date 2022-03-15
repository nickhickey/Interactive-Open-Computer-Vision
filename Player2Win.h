#pragma once

#include "Game.h"
#include "ofMain.h"


class GameWinScreen
{
public:
    GameWinScreen();
    ~GameWinScreen();

    void init();
    void render();

private:
    
	
	ofImage				  m_image;
	
	ofTrueTypeFont	      m_font;
};
