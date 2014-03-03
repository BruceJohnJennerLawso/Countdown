#include "TTxt_File.h"
#include "SFML_Button.h"



namespace countdown
{	bool Update_window;
	unsigned int window_height, window_width;
	enum status{paused, running, zeroed, setting}Countdown_status;
	enum output_stat{countdown, clock}Output_status;
	sf::Color  Countdown_colour;
};

namespace Timer
{	std::string font_path;
	sf::Clock Timer;
	sf::Font Display_font;
	sf::Text Display_text;	
	Time_Structure Current_time(45);
};

namespace Alarm
{	std::string Play_path;
	sf::SoundBuffer buffer;
	sf::Sound output;	
};

enum Button_status{active, inactive};

namespace Go_Button
{	SFML_Button Go_button;
	Button_status status;
	void Switch_status();
	void Left_click();
};

namespace Power_Button
{	SFML_Button Power_button;
	Button_status status;
	void Switch_status();
	void Left_click();
};