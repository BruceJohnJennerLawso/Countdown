#include "TTxt_File.h"


namespace countdown
{	unsigned int window_height, window_width;
	bool Timer_finished;
};

namespace Timer
{	sf::Clock Timer;
	enum Timer_state{Running, Paused, Input}Current_state;
	sf::Font Display_font;
	sf::Text Display_text;	
	Time_Structure Current_time(45);
};

namespace Go_button
{	sf::Texture Go_button_tex_active;
	sf::Texture Go_button_tex_inactive;
	sf::Sprite Go_button_sprite;
};

namespace Power_button
{	sf::Texture Power_button_tex;
	sf::Sprite Power_button_sprite;
};

namespace Set_button
{	sf::Texture Set_button_tex_active;
	sf::Texture Set_button_tex_inactive;
	sf::Sprite Set_button_sprite;
};

namespace Alarm
{	std::string Play_path;
	sf::SoundBuffer buffer;
	sf::Sound output;	
};