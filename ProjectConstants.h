#pragma once

#include <string>

namespace ProjectConstants
{
	//The applications constants, resolution and framerate
	static const int            PROJ_WINDOW_RES_X               = 1280;
	static const int            PROJ_WINDOW_RES_Y               = 720;
	static const int            PROJ_DESIRED_FRAMERATE          = 60;



	// Constants like images and fonts
	static const std::string    IMG_PATH_SCREEN_TITLE           = "images/BG.jpg";
	static const std::string    IMG_PATH_SCREEN_WINNER1		    = "images/Winner1.png";
	static const std::string    IMG_PATH_SCREEN_WINNER2         = "images/Winner2.png";
	static const std::string    IMG_PATH_SCREEN_INGAME			= "images/InGame.png";
	static const std::string    IMG_PATH_SCREEN_FIGHTER1		= "images/BoxerLeft.png";
	static const std::string    IMG_PATH_SCREEN_FIGHTER2		= "images/BoxerRight.png";
	static const std::string    FONT_PATH_MONSTERRAT2		    = "fonts/Montserrat-Bold.otf";
	static const std::string    FONT_PATH_MONSTERRAT            = "fonts/Montserrat-Bold.otf";
}
