// Countdown //////////////////////////////////////////////////////////////
// by John Lawson /////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <time.h>
#include "Time_Structure.h"
#include "Program_Elements.h"

int run_sfml(unsigned int countdown);
int run_input_window();
void Timer_Alarm();

int main()
{	// Resume the coutdown!!!
	TTxt_File Args(Cmd_dashdash::Get_directory(), "\\Countdown\\TimerArgs.txt");
	unsigned int number = std::stoi(Args.Access_data(2));
	Alarm::Play_path = Args.Access_data(3);
	Args.~TTxt_File();
	return run_sfml(number);
}	// Was yo cooler than yall, due to being a wet bag now, so they lit this candle & went to space today. Dawg.

int run_sfml(unsigned int countdown)
{	if (!(Timer::Display_font.loadFromFile(Cmd_dashdash::Get_directory().append("\\Data\\Haettenschweiler.ttf"))))
	{	std::cout << "Unable to load font" << std::endl;
		Cmd_dashdash::Log_exception("Unable to load font");
	}
	if ((!(Set_button::Set_button_tex_active.loadFromFile(Cmd_dashdash::Get_directory().append("\\Data\\Set_button_activated.png"))))||((!(Go_button::Go_button_tex_active.loadFromFile(Cmd_dashdash::Get_directory().append("\\Data\\Go_button_activated.png")))))||((!(Power_button::Power_button_tex.loadFromFile(Cmd_dashdash::Get_directory().append("\\Data\\Power_button_activated.png")))))||(!(Set_button::Set_button_tex_inactive.loadFromFile(Cmd_dashdash::Get_directory().append("\\Data\\Set_button_inactive.png"))))||((!(Go_button::Go_button_tex_inactive.loadFromFile(Cmd_dashdash::Get_directory().append("\\Data\\Go_button_inactive.png"))))))
	{	std::cout << "Unable to load texture" << std::endl;
		Cmd_dashdash::Log_exception("Unable to load button texture");
	}
	else
	{	std::cout << "Data loaded successfully" << std::endl;
		
		countdown::Timer_finished = false;
		Timer::Current_state = Timer::Paused;

		Timer::Current_time.Set_Time(countdown);		

		Timer::Display_text.setFont(Timer::Display_font);
		Timer::Display_text.setCharacterSize(80);
		Timer::Display_text.setColor(sf::Color::Green);
		Timer::Display_text.setString(Timer::Current_time.Get_time_as_string());
		Timer::Display_text.setPosition(0, -20);

		Set_button::Set_button_sprite.setTexture(Set_button::Set_button_tex_active);
		Set_button::Set_button_sprite.setPosition(215, 20);

		Go_button::Go_button_sprite.setTexture(Go_button::Go_button_tex_active);
		Go_button::Go_button_sprite.setPosition(245, 20);
		
		Power_button::Power_button_sprite.setTexture(Power_button::Power_button_tex);
		Power_button::Power_button_sprite.setPosition(275, 20);

		countdown::window_height = 70;
		countdown::window_width = 300;	

		sf::RenderWindow window(sf::VideoMode(countdown::window_width, countdown::window_height), "Countdown Timer");
		while (window.isOpen())
		{	sf::Event event;
			while (window.pollEvent(event))
			{	if(event.type == sf::Event::Closed)
				{	window.close();
					return 0;
				}	
				if(event.type == sf::Event::KeyPressed)
				{	if(event.key.code == sf::Keyboard::Q)
					{	window.close();
						return 0;
					}
				}
				if(event.type == sf::Event::MouseButtonPressed)
				{	if(event.mouseButton.button == sf::Mouse::Left)
					{	if((event.mouseButton.y >= 20)&&(event.mouseButton.y <= 60))
						{	if((event.mouseButton.x >= 215)&&(event.mouseButton.x < 235))
							{	if(Timer::Current_state == Timer::Paused)
								{	//Timer::Current_state = Timer::Input;
									//Timer::Current_time.Set_Time(SFML_numeric_input<int>("Input Timer Value" ,200, 70, Timer::Display_font));
								}
							}	// The "Set" button
							else if((event.mouseButton.x >= 245)&&(event.mouseButton.x < 265))
							{	if(Timer::Current_state == Timer::Paused)
								{	Timer::Timer.restart();
									Timer::Timer;
									Timer::Current_state = Timer::Running;
								}
							}	// The "Go" button
							else if((event.mouseButton.x >= 275)&&(event.mouseButton.x < 295))
							{	window.close();
								return 0;
							}	// The "Power off" button
						}
					}	// All left-Mouse click events
				}
			}	window.setSize(sf::Vector2u(countdown::window_width, countdown::window_height));
			if(Timer::Current_state == Timer::Running)
			{	// Update the time of the countdown accordingly
			}
			window.clear();
			switch(Timer::Current_state)
			{	case (Timer::Paused):
				{	Timer::Display_text.setString(Timer::Current_time.Get_time_as_string());
					Go_button::Go_button_sprite.setTexture(Go_button::Go_button_tex_active);
					Set_button::Set_button_sprite.setTexture(Set_button::Set_button_tex_active);
					break;
				}
				case (Timer::Input):
				{	Timer::Display_text.setString(Timer::Current_time.Get_time_as_string());
					Go_button::Go_button_sprite.setTexture(Go_button::Go_button_tex_inactive);
					Set_button::Set_button_sprite.setTexture(Set_button::Set_button_tex_inactive);
					break;
				}
				case (Timer::Running):
				{	Timer::Display_text.setString(Timer::Current_time.Get_time_as_string());
					Go_button::Go_button_sprite.setTexture(Go_button::Go_button_tex_inactive);
					Set_button::Set_button_sprite.setTexture(Set_button::Set_button_tex_inactive);
					if(Timer::Timer.getElapsedTime().asSeconds() > 1)
					{	Timer::Current_time.Change_by_dt(-(Timer::Timer.getElapsedTime().asSeconds()));
						Timer::Timer.restart();
					}
					if((Timer::Current_time.Get_time()) == 0)
					{	Timer::Current_time.Set_Time(0);
						Timer::Current_state = Timer::Paused;
						countdown::Timer_finished = true;
					}
					break;
				}
			}
			window.draw(Timer::Display_text);
			//window.draw(Set_button::Set_button_sprite);
			window.draw(Go_button::Go_button_sprite);
			window.draw(Power_button::Power_button_sprite);
			if (countdown::Timer_finished == true)
			{	Timer_Alarm();
				countdown::Timer_finished = false;
			}
			window.display();
		}
	}
}

int run_input_window()
{	return 0;
}

void Timer_Alarm()
{	Alarm::Play_path.erase(Alarm::Play_path.end() - 1);
	Cmd_dashdash::Print_line(Alarm::Play_path);
	Cmd_dashdash::Print_line((Alarm::Play_path).size());
	if (!Alarm::buffer.loadFromFile(Cmd_dashdash::Get_directory().append("\\Countdown\\Audio\\").append(Alarm::Play_path)))
	{	Cmd_dashdash::Newline();
		Cmd_dashdash::Print_line("Unable to Load Audio");
	}
	else
	{	Alarm::output.setVolume(100);
		Alarm::output.setBuffer(Alarm::buffer);
		Cmd_dashdash::Print_line("Able to Load Audio");
		Alarm::output.play();
	}
}
