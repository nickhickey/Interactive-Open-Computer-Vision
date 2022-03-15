#pragma once

#include "ofMain.h"

#include "Game.h"

#include "TitleScreen.h"
#include "Player2Win.h"
#include "Player1Win.h"

class ofApp : public ofBaseApp
{
	bool				  m_player1Win = false;
	bool				  m_player2Win = false;
    enum AppState
    {
        Uninitialized,
        ScreenTitle,
        GamePlaying,
        ScreenGameOver,
        ScreenGameWin
    };

public:
    void setup();
    void update();
    void draw();

    void beginGame();


    AppState              m_appState;

    Game                  m_game;

    TitleScreen           m_titleScreen;
    GameOverScreen        m_gameOverScreen;
    GameWinScreen         m_winScreen;
};
