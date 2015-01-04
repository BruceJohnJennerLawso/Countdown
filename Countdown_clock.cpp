// Countdown_clock.cpp /////////////////////////////////////////////////////////
// A wrapper class for the core countdown window and its internal properties ///
////////////////////////////////////////////////////////////////////////////////
//#include <std_files>
//#include "Headers.h"
//#include "Headers.hpp"
//#include "Source.cpp"
#include "Countdown_clock.hpp"
#include <time.h> 


Countdown_clock::Countdown_clock(unsigned int initial_time, sf::Color theme_colour, timer_status initial_status, std::string font_path, sf::Texture &go_texture, sf::Texture &pow_texture, std::string alert_path)
{	Mode = timer_mode;
	Countdown_window = new SFML_Window("Countdown 2.00", 70, 300);
	Current_time = new Time_Structure(initial_time);
	
	if(!Display_font.loadFromFile(font_path))
	{	// umm... we'll figure out something eventually I guess
	}	Display_text = new SFML_text(Display_font, sf::Vector2f(0, -12), Current_time->Get_time_as_string(), theme_colour, 80 , false);
	Go_button = new SFML_Button(&go_texture, sf::IntRect(0,0,20,40), sf::IntRect(20, 0, 20, 40), VectorVictor::Vector2(245, 28), 40, 20, theme_colour, true);
	Power_button = new SFML_Button(&pow_texture, sf::IntRect(0,0,20,40), sf::IntRect(20, 0, 20, 40), VectorVictor::Vector2(275, 28), 40, 20, theme_colour, true);	
	cursor_commands = new Cursor_commands();
	Countdown_status = paused;
	deltat = 0;
	
	Alert_path = alert_path;
}


Countdown_clock::Countdown_clock(sf::Color theme_colour, std::string font_path, sf::Texture &pow_texture)
{	Mode = clock_mode;
	Countdown_window = new SFML_Window("Countdown 2.00", 70, 300);
	Current_time = new Time_Structure(0.00);
	
	if(!Display_font.loadFromFile(font_path))
	{	// umm... we'll figure out something eventually I guess
	}	Display_text = new SFML_text(Display_font, sf::Vector2f(0, -12), Get_clock_time_as_string(), theme_colour, 80 , false);
	Go_button = new SFML_Button(&pow_texture, sf::IntRect(0,0,20,40), sf::IntRect(20, 0, 20, 40), VectorVictor::Vector2(245, 28), 40, 20, theme_colour, true);
	// just initialize it here so it exists, even though it shouldnt be drawn at
	// all. If we dont initialize it we'd be in trouble anyways when the
	// destructor calls delete
	Power_button = new SFML_Button(&pow_texture, sf::IntRect(0,0,20,40), sf::IntRect(20, 0, 20, 40), VectorVictor::Vector2(275, 28), 40, 20, theme_colour, true);	
	cursor_commands = new Cursor_commands();
	Countdown_status = running;
	deltat = 0;
}



int Countdown_clock::Countdown(unsigned int countdown_time)
{	Current_time->Set_Time(countdown_time);
	this->Countdown();
}

int Countdown_clock::Countdown()
{	sf::Clock countdown_timer;
	Countdown_window->window->setFramerateLimit(20);
	// this should be good enough
	while(Countdown_window->window->isOpen())
	{	deltat = countdown_timer.restart().asSeconds();
		sf::Event event;
		
		while(Countdown_window->window->pollEvent(event))
		{	if(event.type == sf::Event::Closed)
			{	Countdown_window->window->close();
				return 0;
			}
			if(event.type == sf::Event::MouseWheelMoved)
			{	// dont worry about it ;)
			}
			if(event.type == sf::Event::MouseMoved)
			{	cursor_commands->Set_cursor_state(((event.mouseMove.x)), ((event.mouseMove.y)), false, false, false);
				// now that we get the coords from mouseMove, this works just fine
			}
			if(event.type == sf::Event::MouseButtonPressed)
			{	if(event.mouseButton.button == sf::Mouse::Button::Left)
				{	cursor_commands->Set_cursor_state(event.mouseButton.x, event.mouseButton.y, false, true, false);
				}
				if(event.mouseButton.button == sf::Mouse::Button::Right)
				{	cursor_commands->Set_cursor_state(event.mouseButton.x, event.mouseButton.y, true, false, false);
				}
				if(event.mouseButton.button == sf::Mouse::Button::Middle)
				{	cursor_commands->Set_cursor_state(event.mouseButton.x, event.mouseButton.y, false, false, true);
				}
			}
			if(event.type == sf::Event::MouseButtonReleased)
			{	if(event.mouseButton.button == sf::Mouse::Button::Left)
				{	cursor_commands->Set_cursor_state(event.mouseButton.x, event.mouseButton.y, false, false, false);
				}
				if(event.mouseButton.button == sf::Mouse::Button::Right)
				{	cursor_commands->Set_cursor_state(event.mouseButton.x, event.mouseButton.y, false, false, false);
				}
				if(event.mouseButton.button == sf::Mouse::Button::Middle)
				{	cursor_commands->Set_cursor_state(event.mouseButton.x, event.mouseButton.y, false, false, false);
				}
			}
		}	
		
		if(Go_button->Active == true)
		{	if(Go_button->Is_left_clicked(cursor_commands))
			{	if(Countdown_status == paused)
				{	Go_button->Active = false;
					Countdown_status = running;
				}
			}
		}
		if(Power_button->Active == true)
		{	if(Power_button->Is_left_clicked(cursor_commands))
			{	Countdown_window->window->close();
			}
		}
		
		if(Countdown_status == running)
		{	if(Current_time->time > 0.0000)
			{	Current_time->Change_by_dt(-deltat);
			}
			else if(Current_time->time <= 0.0000)
			{	Current_time->time = 0.0000;
				Countdown_status = paused;
				std::cout << "Timer finished" << std::endl;
				this->Alert(); 
			}
		}
		Countdown_window->window->clear();
		//Countdown_window->window->draw(stuff);
		Display_text->Set_element(Current_time->Get_time_as_string());
		Display_text->Draw_element(Countdown_window);		
		Go_button->Draw_button(Countdown_window);
		Power_button->Draw_button(Countdown_window);		
		Countdown_window->window->display();
	}
	return 0;
}

int Countdown_clock::Clock()
{	sf::Clock countdown_timer;
	Countdown_window->window->setFramerateLimit(20);
	// this should be good enough
	while(Countdown_window->window->isOpen())
	{	sf::Event event;
		
		while(Countdown_window->window->pollEvent(event))
		{	if(event.type == sf::Event::Closed)
			{	Countdown_window->window->close();
				return 0;
			}
			if(event.type == sf::Event::MouseWheelMoved)
			{	// dont worry about it ;)
			}
			if(event.type == sf::Event::MouseMoved)
			{	cursor_commands->Set_cursor_state(((event.mouseMove.x)), ((event.mouseMove.y)), false, false, false);
				// now that we get the coords from mouseMove, this works just fine
			}
			if(event.type == sf::Event::MouseButtonPressed)
			{	if(event.mouseButton.button == sf::Mouse::Button::Left)
				{	cursor_commands->Set_cursor_state(event.mouseButton.x, event.mouseButton.y, false, true, false);
				}
				if(event.mouseButton.button == sf::Mouse::Button::Right)
				{	cursor_commands->Set_cursor_state(event.mouseButton.x, event.mouseButton.y, true, false, false);
				}
				if(event.mouseButton.button == sf::Mouse::Button::Middle)
				{	cursor_commands->Set_cursor_state(event.mouseButton.x, event.mouseButton.y, false, false, true);
				}
			}
			if(event.type == sf::Event::MouseButtonReleased)
			{	if(event.mouseButton.button == sf::Mouse::Button::Left)
				{	cursor_commands->Set_cursor_state(event.mouseButton.x, event.mouseButton.y, false, false, false);
				}
				if(event.mouseButton.button == sf::Mouse::Button::Right)
				{	cursor_commands->Set_cursor_state(event.mouseButton.x, event.mouseButton.y, false, false, false);
				}
				if(event.mouseButton.button == sf::Mouse::Button::Middle)
				{	cursor_commands->Set_cursor_state(event.mouseButton.x, event.mouseButton.y, false, false, false);
				}
			}
		}	
		
		if(Power_button->Active == true)
		{	if(Power_button->Is_left_clicked(cursor_commands))
			{	Countdown_window->window->close();
			}
		}
		
		
		Countdown_window->window->clear();
		//Countdown_window->window->draw(stuff);
		Display_text->Set_element(Get_clock_time_as_string());
		Display_text->Draw_element(Countdown_window);		
		Power_button->Draw_button(Countdown_window);		
		Countdown_window->window->display();
	}
	return 0;
}

void Countdown_clock::Alert()
{	//sf::Music music;
	if(!music.openFromFile(Alert_path))
	{	// uhh, cover your eyes and hope for the best???
		std::cout << "Unable to open music located at " << Alert_path << std::endl;
	}
	music.setLoop(false);
	music.play();
}

Countdown_clock::~Countdown_clock()
{	delete Countdown_window;
	delete Current_time;
	delete Display_text;
	delete Go_button;
	delete Power_button;
	delete cursor_commands;
}


std::string Get_clock_time_as_string()
{	time_t rawtime;
	struct tm * timeinfo;
	char buffer [80];
	time (&rawtime);
	timeinfo = localtime (&rawtime);
	strftime(buffer,80,"%T",timeinfo);
	std::string clock_time = buffer;
	// I think we are safe to not delete the timeinfo pointer, since it doesnt
	// actually new anything here, just gets a reference from localtime()
	return clock_time;
}
