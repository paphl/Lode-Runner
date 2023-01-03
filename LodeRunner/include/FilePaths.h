#pragma once
#include <iostream>
namespace Texture_Paths
{
    const std::string Characters = "assets/Units/Characters.png";
	const std::string Tileset = "assets/Tile//Tileset.png";
	const std::string Menu_Buttons = "assets/Menu/Button.png";
	const std::string Menu_Background = "assets/Menu/lode_runner_menu_bg.jpg";
	const std::string My_Logo = "assets/Logo/logo.png";
	const std::string Menu_Selector = "assets/Menu/menu-selector.png";
	const std::string Buttons = "assets/Menu/Button.png";

}

namespace Other_Directories
{
	const std::string Level_Directory = "levels";

}

namespace Constants
{
	const int Unit_Size = 16;
	const float Splash_State_Show_Time = 0.5f;
	static const float VIEW_HEIGHT = 720.0f;
	static const float WINDOW_SIZE_X_1200 = 1200.0f;
	static const float WINDOW_SIZE_Y_800 = 800.0f;
	const float POSITION_450 = 450.0f;
	const float POSITION_75 = 75.0f;
	static const int I_16 = 16;

	#define Max_main_menu 3
	#define MENU_POS_X 300
	#define MENU_POS_Y_Play 200
	#define MENU_POS_Y_About 300
	#define MENU_POS_Y_Exit 400
	#define MENU_POS_X_Selector 200
	#define MENU_POS_Y_Selector 210
	#define MENU_Size 70
	const float SIZE_OF_TILE = I_16*4;
	enum DIG_DIRECTION
	{
		LEFT = 0,
		RIGHT
	};
}