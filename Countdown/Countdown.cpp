// Countdown //////////////////////////////////////////////////////////////
// by John Lawson /////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
#include <SFML/Audio.hpp>
#include <iostream>
#include <time.h>
#include <algorithm>
#include "Time_Structure.h"
#include "Program_Elements.h"

#define version "1.104"

int Countdown_clock(unsigned int countdown);
void Timer_Alarm();
void Init_program_stuff(unsigned int countdown);
void Set_colour(int red, int green, int blue);
std::string Play_path_at_mode(std::string mode, std::string Alarm_path, std::string Timer_path);
int Load_program_assets();

int main()
{	// Resume the coutdown!!!
	TTxt_File Arguments(Cmd_dashdash::Get_directory(), "\\Countdown\\CountdownArguments.cfg");
	if(Arguments.Get_file_index() < 8)
	{	Cmd_dashdash::Log_exception("Error 5: Incomplete Config file.");
		return 5;
	}
	else
	{	unsigned int number = std::stoi(Arguments.Access_data(1));
		std::string mode = Arguments.Access_data(2);
		Alarm::Play_path = Play_path_at_mode(mode, Arguments.Access_data(4), Arguments.Access_data(3));
		Timer::font_path = Arguments.Access_data(5);
		int red = std::stoi(Arguments.Access_data(6));
		int green = std::stoi(Arguments.Access_data(7));
		int blue = std::stoi(Arguments.Access_data(8));
		Set_colour(red, green, blue);
		Arguments.~TTxt_File();
		return Countdown_clock(number);
	}
}	// Was yo cooler than yall, due to being a wet bag now, so they lit this candle & went to space today. Dawg.

void Init_program_stuff(unsigned int countdown)
{		countdown::Update_window = true;
		countdown::Countdown_status = countdown::status::paused;
		countdown::Output_status = countdown::output_stat::countdown;
		Timer::Current_time.Set_Time(countdown);		
		Timer::Display_text.setFont(Timer::Display_font);
		Timer::Display_text.setCharacterSize(80);
		Timer::Display_text.setColor(countdown::Countdown_colour);
		Timer::Display_text.setString(Timer::Current_time.Get_time_as_string());
		Timer::Display_text.setPosition(0, -12);
		countdown::window_height = 86;
		countdown::window_width = 400;	
}

std::string Play_path_at_mode(std::string mode, std::string Alarm_path, std::string Timer_path)
{	std::transform(mode.begin (), mode.end (), mode.begin (), toupper);
	if(mode == "ALARM")
	{	return Alarm_path;
	}
	else if(mode == "TIMER")
	{	return Timer_path;
	}
}

void Set_colour(int red, int green, int blue)
{	countdown::Countdown_colour = sf::Color(red, green, blue, 255);
	Timer::Display_text.setColor(countdown::Countdown_colour);
	Go_Button::Go_button.Button_sprite.setColor(countdown::Countdown_colour);
	Power_Button::Power_button.Button_sprite.setColor(countdown::Countdown_colour);
}

int Load_program_assets()
{	std::string Offset = "\\Data\\Assets\\UI\\";
	if (!(Timer::Display_font.loadFromFile(Cmd_dashdash::Get_directory().append("\\Data\\" + Timer::font_path))))
	{	std::cout << "Unable to load font" << std::endl;
		Cmd_dashdash::Log_exception("Error 1: Unable to load font");
		return 1;
	}
	else
	{	if(!Go_Button::Go_button.Set_texture((Cmd_dashdash::Get_directory().append(Offset + ("Go_button.png"))), box_coordinates(0, 0, (20), 40)))
		{	Cmd_dashdash::Log_exception(("Error 2: Unable to load go button texture"));
			return 2;
		}
		else
		{	Go_Button::Go_button.Set_parameters(box_coordinates(245, 28, 20, 40));
			if(!Power_Button::Power_button.Set_texture((Cmd_dashdash::Get_directory().append(Offset + ("Power_button.png"))), box_coordinates(0, 0, 20, 40)))
			{	Cmd_dashdash::Log_exception(("Error 3: Unable to load Power button texture"));
				return 3;
			}
			else
			{	Power_Button::Power_button.Set_parameters(box_coordinates(275, 28, 20, 40));
				if (!Alarm::buffer.loadFromFile(Cmd_dashdash::Get_directory().append("\\Countdown\\Audio\\").append(Alarm::Play_path)))
				{	Cmd_dashdash::Log_exception(("Error 4: Unable to load Audio file"));
					return 4;
				}
				else
				{	return 0;
				}
			}
		}
	}
}

int Countdown_clock(unsigned int countdown)
{	Go_Button::status = active;
	Power_Button::status = active;
	int load;
	if((load = Load_program_assets()) != 0)
	{	return load;
	}
	else
	{	Init_program_stuff(countdown);
		std::string title = ("Countdown ");
		title.append(version);
		sf::RenderWindow window(sf::VideoMode(countdown::window_width, countdown::window_height), title);
		while (window.isOpen())
		{	sf::Event event;
			// Event Handling ///////////////////////////////////////////////////////////////////////////////////////////
			while (window.pollEvent(event))
			{	if(event.type == sf::Event::Closed)
				{	window.close();
					return 0;
				}	// General SFML Events
				else if(event.type == sf::Event::KeyPressed)
				{	if(event.key.code == sf::Keyboard::Q)
					{	window.close();
						return 0;
					}
					if(event.key.code == sf::Keyboard::Z)
					{	countdown::Countdown_status = countdown::status::zeroed;
						Timer::Current_time.Set_Time(0);
					}
					if(event.key.code == sf::Keyboard::R)
					{	countdown::Countdown_status = countdown::status::running;
					}
					if(event.key.code == sf::Keyboard::P)
					{	countdown::Countdown_status = countdown::status::paused;
					}
				}	// Keypress Events
				else if(event.type == sf::Event::MouseButtonPressed)
				{	if(event.mouseButton.button == sf::Mouse::Left)
					{	if(Go_Button::Go_button.Check_for_point_in_coordinates(event.mouseButton.x, event.mouseButton.y) == true)
						{	Go_Button::Left_click();	
						}	// The "Go" button
						else if(Power_Button::Power_button.Check_for_point_in_coordinates(event.mouseButton.x, event.mouseButton.y) == true)
						{	Power_Button::Left_click();
							window.close();
							return 0;
						}	// The "Power off" button	
					}	// All left-Mouse click events
				}
			}	// All events in the main window
			// Timer State Updates //////////////////////////////////////////////////////////////////////////////////////
			switch(countdown::Countdown_status)
			{	case (countdown::status::paused):
				{	break;
					// Nothing to do here
				}
				case (countdown::status::running):
				{	if(Timer::Timer.getElapsedTime().asMilliseconds() >= 1000)
					{	Timer::Current_time.Change_by_dt(-(Timer::Timer.getElapsedTime().asSeconds()));
						countdown::Update_window = true;
						Timer::Timer.restart();
					}
					else if((Timer::Current_time.Get_time()) == 0)
					{	Timer::Current_time.Set_Time(0);
						Timer_Alarm();
						countdown::Countdown_status = countdown::status::zeroed;
					}	break;
				}
				case (countdown::status::setting):
				{	break;
					// Nothing to do here
				}
				case (countdown::status::zeroed):
				{	break;
					// Nothing to do here
				}
			}
			switch(countdown::Output_status)
			{	case (countdown::output_stat::clock):
				{	Timer::Display_text.setString("");	// Need the time sheet in binder for this
					break;
				}
				case (countdown::output_stat::countdown):
				{	Timer::Display_text.setString(Timer::Current_time.Get_time_as_string());
					break;
				}
			}
			// Window Redrawing /////////////////////////////////////////////////////////////////////////////////////////
			if(countdown::Update_window == true)
			{	window.clear();
				window.setSize(sf::Vector2u(countdown::window_width, countdown::window_height));
				window.draw(Timer::Display_text);
				window.draw(Go_Button::Go_button.Button_sprite);
				window.draw(Power_Button::Power_button.Button_sprite);
				countdown::Update_window = false;
				window.display();
			}
		}
	}
}

void Go_Button::Left_click()
{	switch(countdown::Countdown_status)
	{	case countdown::status::paused:
		{	Timer::Timer.restart();
			Timer::Timer;
			countdown::Countdown_status = countdown::status::running;
			Go_Button::Switch_status();
			countdown::Update_window = true;
			break;
		}
		case countdown::status::zeroed:
		{	Timer_Alarm();
			break;
		}
		case countdown::status::running:
		{	// Do nothing for now
			break;
		}
		case countdown::status::setting:
		{	// Do nothing for now
			break;
		}
	}
}

void Go_Button::Switch_status()
{	switch(Go_Button::status)
	{	case active:
		{	Go_Button::status = Button_status::inactive;
			Go_Button::Go_button.Set_texture_coordinates(box_coordinates(20, 0, 20, 40));
			break;
		}
		case inactive:
		{	Go_Button::status = Button_status::active;
			Go_Button::Go_button.Set_texture_coordinates(box_coordinates(0, 0, 20, 40));
			break;
		}
	}	
}

void Power_Button::Left_click()
{
}

void Power_Button::Switch_status()
{	switch(Power_Button::status)
	{	case active:
		{	Power_Button::status = Button_status::inactive;
			Power_Button::Power_button.Set_texture_coordinates(box_coordinates(20, 0, 20, 40));
			break;
		}
		case inactive:
		{	Power_Button::status = Button_status::active;
			Power_Button::Power_button.Set_texture_coordinates(box_coordinates(0, 0, 20, 40));
			break;
		}
	}	
}

void Timer_Alarm()
{	Alarm::output.setVolume(100);
	Alarm::output.setBuffer(Alarm::buffer);
	Alarm::output.play();
}