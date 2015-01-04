#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
//#include<GameObjects!!!!>		Theyre coming, they really are!!!
#include <math.h>
#include "SFML_Tools.hpp"








Cursor_commands::Cursor_commands()
{	position.x = 0.00;
	position.y = 0.00;
	
	Right_click = false;
	Left_click = false;
	Middle_click = false;
}

void Cursor_commands::Set_cursor_state(float x, float y, bool right, bool left, bool middle)
{	position.x = x;
	position.y = y;
	
	Right_click = right;
	Left_click = left;
	Middle_click = middle;
	
	if(Left_click == true)
	{	std::cout << "Cursor Position: (" << x << "," << y << ")" << std::endl;
	}
}

Cursor_commands::~Cursor_commands()
{
}



// this whole class is horrible, but there doesnt really seem to be any 
// alternatives that I can see at the moment. Its just too integral to how the
// engine handles inputs with regards to internal objects

key_commands::key_commands()
{	enter = false;
	space = false;
	period = false;
	left = false;
	right = false;
	up = false;
	down = false;
	tilde = false;
	v = false;
	z= false;
	x = false;
	t = false;
	r = false;
	q = false;
	w = false;
	e = false;
	a = false;
	s = false;
	d = false;
	c = false;
	l = false;
	equal = false;
	dash = false;
	plus = false;
	numpad0 = false;
	numpad1 = false;
	numpad2 = false;
	numpad3 = false;
	numpad4 = false;
	numpad5 = false;
	numpad6 = false;
	numpad7 = false;
	numpad8 = false;
	numpad9 = false;
	plus = false;
	minus = false;
}

// may cause burning in eyes, but it is useful

key_commands::~key_commands()
{
}

// the function for handling which keyboard input was sent //

void Log_keystroke(sf::Keyboard::Key input_event, key_commands * icommands, bool key_down)
{	// simple concept really, just pass whether the key is being held down
	// as true or false to the stored value for that key, then if it is true,
	// also call the function for that keypress (so things can be handled a bit
	// easier in the main cpp file
	
	// to be honest though, it might just be easier to directly store a copy
	// of the sf event itself
	
	// but I still want to store info about the keys that are up and those that
	// are down
	
	// maybe the best solution here is to create a vector of strings 
	// (or sf keyboard types, then let the receiving object take a look at them
	// and deal with them how it sees fit
	
	// yes, yes, I like that. The boolean wasnt really used anyways
	
	// The Enter or Return key
	if(input_event == sf::Keyboard::Return)
	{	icommands->enter = key_down;
		if(key_down == true)
		{	icommands->Enter();
		}
	}
	// Spacebar, space oddity, space pressme
	else if(input_event == sf::Keyboard::Space)
	{	icommands->space = key_down;
		if(key_down == true)
		{	icommands->Space();
		}
	}
	// The Arrow Keys
	else if(input_event == sf::Keyboard::Up)
	{	icommands->up = key_down;
		if(key_down == true)
		{	icommands->Up();
		}
	}
	else if(input_event == sf::Keyboard::Down)
	{	icommands->down = key_down;
		if(key_down == true)
		{	icommands->Down();
		}
	}
	else if(input_event == sf::Keyboard::Right)
	{	icommands->right = key_down;
		if(key_down == true)
		{	icommands->Right();
		}
	}
	else if(input_event == sf::Keyboard::Left)
	{	icommands->left = key_down;
		if(key_down == true)
		{	icommands->Left();
		}
	}
	// Tab Key
	else if(input_event == sf::Keyboard::Tab)
	{
	}
	// Tilde Key
	else if(input_event == sf::Keyboard::Tilde)
	{	icommands->tilde = key_down;
		if(key_down == true)
		{	icommands->Tilde();
		}
	}	
	// Alphabetical keys A-Z
	else if(input_event == sf::Keyboard::A)
	{	icommands->a = key_down;
		if(key_down == true)
		{	icommands->A();
		}
	}
	else if(input_event == sf::Keyboard::B)
	{
	}
	else if(input_event == sf::Keyboard::C)
	{	icommands->c = key_down;
		if(key_down == true)
		{	icommands->C();
		}
	}
	else if(input_event == sf::Keyboard::D)
	{	icommands->d = key_down;
		if(key_down == true)
		{	icommands->D();
		}
	}
	else if(input_event == sf::Keyboard::E)
	{	icommands->e = key_down;
		if(key_down == true)
		{	icommands->E();
		}
	}
	else if(input_event == sf::Keyboard::F)
	{	icommands->f = key_down;
		if(key_down == true)
		{	icommands->F();
		}
	}
	//else if(input_event == sf::Keyboard::G)
	//{
	//}
	else if(input_event == sf::Keyboard::H)
	{
	}
	else if(input_event == sf::Keyboard::I)
	{	icommands->i = key_down;
		if(key_down == true)
		{	icommands->I();
		}
	}
	else if(input_event == sf::Keyboard::J)
	{
	}
	else if(input_event == sf::Keyboard::K)
	{
	}
	else if(input_event == sf::Keyboard::L)
	{	icommands->l = key_down;
		if(key_down == true)
		{	icommands->L();
		}
	}
	else if(input_event == sf::Keyboard::M)
	{
	}
	else if(input_event == sf::Keyboard::N)
	{	icommands->n = key_down;
		if(key_down == true)
		{	icommands->N();
		}
	}
	else if(input_event == sf::Keyboard::O)
	{
	}
	else if(input_event == sf::Keyboard::P)
	{
	}
	else if(input_event == sf::Keyboard::Q)
	{	icommands->q = key_down;
		if(key_down == true)
		{	icommands->Q();
		}
	}
	else if(input_event == sf::Keyboard::R)
	{	icommands->r = key_down;
		if(key_down == true)
		{	icommands->R();
		}
	}
	else if(input_event == sf::Keyboard::S)
	{	icommands->s = key_down;
		if(key_down == true)
		{	icommands->S();
		}
	}
	else if(input_event == sf::Keyboard::T)
	{	icommands->t = key_down;
		if(key_down == true)
		{	icommands->T();
		}
	}
	else if(input_event == sf::Keyboard::U)
	{
	}
	else if(input_event == sf::Keyboard::V)
	{	icommands->v = key_down;
		if(key_down == true)
		{	icommands->V();
		}
	}
	else if(input_event == sf::Keyboard::W)
	{	icommands->w = key_down;
		if(key_down == true)
		{	icommands->W();
		}
	}
	else if(input_event == sf::Keyboard::X)
	{	icommands->x = key_down;
		if(key_down == true)
		{	icommands->X();
		}
	}
	else if(input_event == sf::Keyboard::Y)
	{
	}
	else if(input_event == sf::Keyboard::Z)
	{	icommands->z = key_down;
		if(key_down == true)
		{	icommands->Z();
		}
	}	// Assorted keys, without any real category
	else if(input_event == sf::Keyboard::Comma)
	{	icommands->comma = key_down;
		if(key_down == true)
		{	icommands->Comma();
		}
	}
	else if(input_event == sf::Keyboard::Dash)
	{	icommands->dash = key_down;
		if(key_down == true)
		{	icommands->Dash();
		}
	}
	else if(input_event == sf::Keyboard::Delete)
	{
	}
	else if(input_event == sf::Keyboard::Divide)
	{
	}
	else if(input_event == sf::Keyboard::BackSlash)
	{
	}
	else if(input_event == sf::Keyboard::BackSpace)
	{	
	}
	else if(input_event == sf::Keyboard::Equal)
	{	icommands->equal = key_down;
		if(key_down == true)
		{	icommands->Equal();
		}
	}
	else if(input_event == sf::Keyboard::Escape)
	{
	}
	else if(input_event == sf::Keyboard::LAlt)
	{
	}
	else if(input_event == sf::Keyboard::LBracket)
	{
	}
	else if(input_event == sf::Keyboard::RBracket)
	{
	}
	else if(input_event == sf::Keyboard::LControl)
	{
	}
	else if(input_event == sf::Keyboard::RControl)
	{
	}
	else if(input_event == sf::Keyboard::LShift)
	{
	}
	else if(input_event == sf::Keyboard::RShift)
	{
	}
	else if(input_event == sf::Keyboard::Menu)
	{
	}
	else if(input_event == sf::Keyboard::Multiply)
	{
	}
	else if(input_event == sf::Keyboard::Period)
	{	icommands->period = key_down;
		if(key_down == true)
		{	icommands->Period();
		}
	}
	else if(input_event == sf::Keyboard::Quote)
	{
	}
	else if(input_event == sf::Keyboard::Slash)
	{
	}	// Pageup/Pagedown
	else if(input_event == sf::Keyboard::PageDown)
	{
	}
	else if(input_event == sf::Keyboard::PageUp)
	{
	}	// Windows/OSX/Super key whatever you wanna call it
	else if(input_event == sf::Keyboard::LSystem)
	{
	}
	else if(input_event == sf::Keyboard::RSystem)
	{
	}	// Numeric inputs (row beneath the F## keys)
	else if(input_event == sf::Keyboard::Num0)
	{	
	}
	else if(input_event == sf::Keyboard::Num1)
	{
	}
	else if(input_event == sf::Keyboard::Num2)
	{
	}
	else if(input_event == sf::Keyboard::Num3)
	{
	}
	else if(input_event == sf::Keyboard::Num4)
	{
	}
	else if(input_event == sf::Keyboard::Num5)
	{
	}
	else if(input_event == sf::Keyboard::Num6)
	{
	}
	else if(input_event == sf::Keyboard::Num7)
	{
	}
	else if(input_event == sf::Keyboard::Num8)
	{
	}
	else if(input_event == sf::Keyboard::Num9)
	{
	}	// The Numpad. Beware Vaughan!!!
	else if(input_event == sf::Keyboard::Numpad0)
	{	icommands->numpad0 = key_down;
		if(key_down == true)
		{	std::cout << "numpad0 keydown" << std::endl;
			icommands->Numpad_0();
		}
	}
	else if(input_event == sf::Keyboard::Numpad1)
	{	std::cout << "numpad1 keyevent" << std::endl;
		icommands->numpad1 = key_down;
		if(key_down == true)
		{	icommands->Numpad_1();
		}
	}
	else if(input_event == sf::Keyboard::Numpad2)
	{	std::cout << "numpad1 keyevent" << std::endl;
		icommands->numpad2 = key_down;
		if(key_down == true)
		{	icommands->Numpad_2();
		}
	}
	else if(input_event == sf::Keyboard::Numpad3)
	{	icommands->numpad3 = key_down;
		if(key_down == true)
		{	icommands->Numpad_3();
		}
	}
	else if(input_event == sf::Keyboard::Numpad4)
	{	icommands->numpad4 = key_down;
		if(key_down == true)
		{	icommands->Numpad_4();
		}
	}
	else if(input_event == sf::Keyboard::Numpad5)
	{	icommands->numpad5 = key_down;
		if(key_down == true)
		{	icommands->Numpad_5();
		}
	}
	else if(input_event == sf::Keyboard::Numpad6)
	{	icommands->numpad6 = key_down;
		if(key_down == true)
		{	icommands->Numpad_6();
		}
	}
	else if(input_event == sf::Keyboard::Numpad7)
	{	icommands->numpad7 = key_down;
		if(key_down == true)
		{	icommands->Numpad_7();
		}
	}
	else if(input_event == sf::Keyboard::Numpad8)
	{	icommands->numpad8 = key_down;
		if(key_down == true)
		{	icommands->Numpad_8();
		}
	}
	else if(input_event == sf::Keyboard::Numpad9)
	{	icommands->numpad9 = key_down;
		if(key_down == true)
		{	icommands->Numpad_9();
		}
	}
	else if(input_event == sf::Keyboard::Add)
	{	icommands->plus = key_down;
		if(key_down == true)
		{	icommands->Plus();
		}
	}		// must add minus
	else if(input_event == sf::Keyboard::Subtract)
	{	icommands->minus = key_down;
		if(key_down == true)
		{	icommands->Minus();
		}
	}
}


// SFML_Window Utility class ///////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// a really important part of the engine, because it stores data used throughout
// basically just a plain old wrapper for sf::RenderWindow, but it does store
// important info about the way that the window is related to the in game
// universe

SFML_Window::SFML_Window(std::string title, unsigned int h, unsigned int w)
{	Title = title;
	Height = h;
	Width = w;
	Aperture_height = h;
	Aperture_width = w;
	// no real rhyme or reason behind how big the aperture should be at start
	// so we just give it the same as the window itself
	
	
	// this was the reason why everything appeared 10x too big
	Set_origin();
	// make sure it has a value
	window = new sf::RenderWindow(sf::VideoMode(w, h), Title);
	// set up our RenderWindow
	window->setSize(sf::Vector2u(w, h));
	// and size it, but.. we dont need to here, cause the videomode already
	// did it.
	// What the...
	// that was weird, so the setSize call has been F******ing things up
	// #facepalm
	
	// I think this can be removed
	window->setTitle(Title);
	// again think its redundant, but its a rarely used constructor, so not too
	// concerning really
}

void SFML_Window::Set_origin()
{	origin.x = 0;
	origin.y = 0;
	// If we dont know, we just say (0,0)
}

void SFML_Window::Set_origin(variable x, variable y)
{	origin.x = x;
	origin.y = y;
	// set our VectorVictor2 to the right value
}

void SFML_Window::Set_aperture_dimensions(long long unsigned int ap_w, long long unsigned int ap_h)
{	Aperture_width = ap_w;
	Aperture_height = ap_h;
	// same deal, now just for the aperture dimensions
}

SFML_Window::~SFML_Window()
{	delete window;
	//	cant forget this ;D
}






// Ignition Drawables //////////////////////////////////////////////////////////
// wrapper classes for stuff that needs to be drawn to the window like text ////
// displays & other infographics that the vessel instance draws as ui //////////
// displays and things like that ///////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////



void SFML_drawable::Draw_element(SFML_Window * iwindow)
{	
}

void SFML_drawable::Center_element()
{	
}

// Ignition Text ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

SFML_text::SFML_text(sf::Font &text_font, sf::Vector2f initial_position, std::string initial_text, sf::Color initial_colour, unsigned int character_size, bool center_origin)
{	text.setFont(text_font);
	text.setPosition(initial_position);
	text.setString(initial_text);
	text.setColor(initial_colour);
	text.setCharacterSize(character_size);
	if(center_origin == true)
	{	this->Center_element();
	}
}


void SFML_text::Set_element(std::string text_string)
{	text.setString(text_string);
}

void SFML_text::Set_element(sf::Vector2f new_position)
{	text.setPosition(new_position);
}

void SFML_text::Set_element(sf::Color new_colour)
{	text.setColor(new_colour);
}

void SFML_text::Set_element(unsigned int character_size)
{	text.setCharacterSize(character_size);
}

void SFML_text::Set_element(std::string text_string, sf::Vector2f new_position)
{	this->Set_element(text_string);
	this->Set_element(new_position);		
}

void SFML_text::Set_element(std::string text_string, sf::Vector2f new_position, sf::Color new_colour)
{	this->Set_element(text_string);
	this->Set_element(new_position);
	this->Set_element(new_colour);
}

void SFML_text::Set_element(std::string text_string, sf::Color new_colour)
{	this->Set_element(text_string);
	this->Set_element(new_colour);
}

void SFML_text::Set_element(sf::Vector2f new_position, sf::Color new_colour)
{	this->Set_element(new_position);
	this->Set_element(new_colour);
}

void SFML_text::Draw_element(SFML_Window * iwindow)
{	iwindow->window->draw(text);
}

void SFML_text::Center_element()
{	if(Centered == false)
	{	// do some centering
		// not sure how with sf::Text really
		// I mean what are the dimensions of the text strip?
		
		// important question to get answered
		Centered = true;
	}
}
	
SFML_text::~SFML_text()
{
}


// Ignition Circle /////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


SFML_circle::SFML_circle(sf::Vector2f initial_position, sf::Color initial_colour, float initial_radius, bool center_origin)
{	circle_shape.setPosition(initial_position);
	circle_shape.setFillColor(initial_colour);
	circle_shape.setRadius(initial_radius);
	if(center_origin == true)
	{	this->Center_element();
	}
}

void SFML_circle::Set_element(float new_radius)
{	circle_shape.setRadius(new_radius);
}

void SFML_circle::Set_element(sf::Vector2f new_position)
{	circle_shape.setPosition(new_position);
}

void SFML_circle::Set_element(sf::Color new_colour)
{	circle_shape.setFillColor(new_colour);
}

void SFML_circle::Set_element(float new_radius, sf::Vector2f new_position)
{	this->Set_element(new_radius);
	this->Set_element(new_position);
}

void SFML_circle::Set_element(float new_radius, sf::Vector2f new_position, sf::Color new_colour)
{	this->Set_element(new_radius);
	this->Set_element(new_position);
	this->Set_element(new_colour);
}

void SFML_circle::Set_element(float new_radius, sf::Color new_colour)
{	this->Set_element(new_radius);
	this->Set_element(new_colour);
}

void SFML_circle::Set_element(sf::Vector2f new_position, sf::Color new_colour)
{	this->Set_element(new_position);
	this->Set_element(new_colour);
}

void SFML_circle::Draw_element(SFML_Window * iwindow)
{	iwindow->window->draw(circle_shape);
}

void SFML_circle::Center_element()
{	if(Centered == false)
	{	// do some centering stuffz
		circle_shape.setOrigin(sf::Vector2f(circle_shape.getRadius(), circle_shape.getRadius()));
		Centered = true;
	}
}

SFML_circle::~SFML_circle()
{	// no pointers, no problems
}


SFML_rectangle::SFML_rectangle(sf::Vector2f initial_position, sf::Color initial_colour, float width, float height, bool center_origin)
{	rect_shape.setPosition(initial_position);
	rect_shape.setFillColor(initial_colour);
	rect_shape.setSize(sf::Vector2f(width, height));
	if(center_origin == true)
	{	Center_element();
	}
}

void SFML_rectangle::Set_element(float new_width, float new_height)
{	rect_shape.setSize(sf::Vector2f(new_width, new_height));
}

void SFML_rectangle::Set_element(sf::Vector2f new_position)
{	rect_shape.setPosition(new_position);
}

void SFML_rectangle::Set_element(sf::Color new_colour)
{	rect_shape.setFillColor(new_colour);
}

void SFML_rectangle::Set_element(float new_width, float new_height, sf::Vector2f new_position)
{	this->Set_element(new_width, new_height);
	this->Set_element(new_position);	
}

void SFML_rectangle::Set_element(float new_width, float new_height, sf::Vector2f new_position, sf::Color new_colour)
{	this->Set_element(new_width, new_height);
	this->Set_element(new_position);
	this->Set_element(new_colour);
}

void SFML_rectangle::Set_element(float new_width, float new_height, sf::Color new_colour)
{	this->Set_element(new_width, new_height);
	this->Set_element(new_colour);
}

void SFML_rectangle::Set_element(sf::Vector2f new_position, sf::Color new_colour)
{	this->Set_element(new_position);
	this->Set_element(new_colour);
}	
	
void SFML_rectangle::Draw_element(SFML_Window * iwindow)
{	iwindow->window->draw(rect_shape);
}

void SFML_rectangle::Center_element()
{	if(Centered == false)
	{	rect_shape.setOrigin(sf::Vector2f((rect_shape.getSize().x)/2, (rect_shape.getSize().y)/2));
		// looks good
		Centered = true;
	}
}

SFML_rectangle::~SFML_rectangle()
{
}







std::string Input_string(std::string prompt)		// this should go, not
{	std::string data = "";	// a great idea in a project primarily focused
	while(true)				// on gui
	{	std::cout << std::endl;
		std::cout << prompt;
		while(std::getline(std::cin, data))
		{	if (data.size() == 0)
			{	continue;	
			}	
			else
			{	return data;
			}	
		}
	}
}
