#include "ofApp.h"
#include "ProjectConstants.h"
#include "affine.hpp"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetWindowShape( 
        ProjectConstants::PROJ_WINDOW_RES_X, 
        ProjectConstants::PROJ_WINDOW_RES_Y );

    ofSetFrameRate( ProjectConstants::PROJ_DESIRED_FRAMERATE );


    m_titleScreen.init();
    m_gameOverScreen.init();
    m_winScreen.init();

    m_game.init();

    m_appState = AppState::ScreenTitle;
}

void ofApp::beginGame()
{
    m_game.begin();
    m_appState = AppState::GamePlaying;
}

void ofApp::update()
{

    switch( m_appState )
    {
        case AppState::ScreenTitle:
            if ( ofGetKeyPressed( 's' ) )
            {
                beginGame();
            }
        break;

        case AppState::GamePlaying:
            m_game.update();

            if ( m_game.getGameState() == Game::GameState::GameOver )
            {
                m_appState = AppState::ScreenGameOver;
            }
            else if ( m_game.getGameState() == Game::GameState::GameWin )
            {
                m_appState = AppState::ScreenGameWin;
            }
        break;

        case AppState::ScreenGameOver:
            if ( ofGetKeyPressed( 's' ) )
            {
                beginGame();
            }
        break;

        case AppState::ScreenGameWin:
            if ( ofGetKeyPressed( 's' ) )
            {
                beginGame();
            }
        break;

        default:
            break;
    }
}

void ofApp::draw()
{
	ofClear( ofFloatColor( 0.0f, 0.0f, 0.0f, 1.0f ) );

    switch( m_appState )
    {
        case AppState::ScreenTitle:
            m_titleScreen.render();
        break;

        case AppState::GamePlaying:
            m_game.render();
        break;

        case AppState::ScreenGameOver:
            m_game.render();    
            m_gameOverScreen.render();
        break;

        case AppState::ScreenGameWin:
            m_game.render();    
            m_winScreen.render();
        break;

        default:
            break;
    }
}

