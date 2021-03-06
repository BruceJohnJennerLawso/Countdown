// SFML_Tools.h ////////////////////////////////////////////////////////////////
// A couple of sfml wrappers that  automate a few useful things ////////////////
////////////////////////////////////////////////////////////////////////////////
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "VectorVictor2.hpp"

#ifndef SFMLTools
#define SFMLTools

std::string Input_string(std::string prompt);

struct vector2
{	// old data type used by sfml tools before VV2 was available here
	// should be removed wherever possible for consistency
	
	// for all intents and purposes, this is the exact same thing as VV2,
	// but an object oriented interface is a much better idea
	long double x, y;	
};

class Program_data
{	// not actually sure what this is, think it was just a passing idea
	// that never actually got implemented
	Program_data();
	enum prog_state{Intro, Menu, Game}Game_status;
	~Program_data();
};

// Mouse_commands class ////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

class Cursor_commands
{	public:
	Cursor_commands();
	sf::Vector2f position;
	// the coordinates of the mouse relative to the window?
	
	// I dont actually know yet, so this is kinda going in blind. We'll see how
	// sfml likes to handle things
	
	// my working assumption here is that it will be in pixels, from the window origin
	bool Right_click, Left_click, Middle_click;
	// if the given mouse button is down, its true, otherwise false
	// dont want to mess about with extra buttons just yet
	
	void Set_cursor_state(float x, float y, bool right, bool left, bool middle);
	~Cursor_commands();
	// surprisingly this whole section went off without a hitch. suspicious...
};

// Key_commands class //////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

class key_commands
{	public:
	key_commands();
	// simple constructor, no params needed
	void Enter();
	void Space();
	void Period();
	void Comma();
	void Up();
	void Down();
	void Right();
	void Left();
	void Tilde();
	void Q();
	void W();
	void E();
	void A();
	void S();
	void D();
	void C();
	void N();
	void F();
	void I();
	void V();
	void Z();
	void X();
	void R();
	void T();
	void L();
	void Dash();
	void Equal();
	void Numpad_0();
	void Numpad_1();
	void Numpad_2();
	void Numpad_3();
	void Numpad_4();
	void Numpad_5();
	void Numpad_6();
	void Numpad_7();
	void Numpad_8();
	void Numpad_9();
	void Plus();				// oddly enough, this hasnt caused any errors by not being defined
	void Minus();
	// all of the functions that get called when log keystroke indicates that
	// the key in question was pressed
	bool enter, space, period, comma, up, down, right, left, tilde, v, c, q, w, e, a, s, d, f, n,  i, l, x, z, t, r, dash, equal, numpad0, numpad1, numpad2, numpad3, numpad4, numpad5, numpad6, numpad7, numpad8, numpad9, plus, minus;
	// and the booleans that are set to the key down status of the given key
	// in the same function
	~key_commands();
};	// important future idea for this is to retrieve mouse location & clickstate

void Log_keystroke(sf::Keyboard::Key input_event, key_commands * icommands, bool key_down);
void Null_queue();
// I dont think this was ever defined. Probably safe to remove


// SFML Window /////////////////////////////////////////////////////////////////
// Cause I keep getting lost every time I look for this ////////////////////////
////////////////////////////////////////////////////////////////////////////////

class SFML_Window
{	public:
	SFML_Window(std::string title, unsigned int h, unsigned int w);
	// constructor, quite simple really
	std::string Title;
	// the string that gets printed on the menubar at the top of the window
	
	// might be removable if the sf::RenderWindow already contains a string
	// for this internally
	sf::RenderWindow * window;
	// the pointer to the sfml window that the class wraps
	VectorVictor::Vector2 origin;
	// the ingame origin (top left corner) of the windows aperture
	// (the area that the window covers)
	void Set_origin();
	// if not specified, sets it to (0,0)
	void Set_origin(variable x, variable y);
	// or set the coordinates of the origin more explicitly
	long long unsigned int Width, Height;
	// the dimensions of the actual window itself, in pixels
	variable Aperture_width, Aperture_height;
	// the dimensions of what the window is currently spanning in the game
	// universe, in meters
	void Set_aperture_dimensions(long long unsigned int ap_w, long long unsigned int ap_h);
	// set those dimensions in meters
	~SFML_Window();
	// close up shop (and delete our RenderWindow)
};



// Generic displays ////////////////////////////////////////////////////////////
// This whole section is kinda hazy. Basically, the idea is that we wrap ///////
// anything that is sf::Drawable into a wrapper class with some useful /////////
// methods so that working with it is much easier //////////////////////////////
////////////////////////////////////////////////////////////////////////////////

class SFML_drawable
{	public:
	virtual void Draw_element(SFML_Window * iwindow);
	
	bool Centered;
	virtual void Center_element();
	//std::vector<std::vector<*Ignition_drawable>> idrawable_pointers;
	//std::vector<Ignition_handle<Ignition_drawable>
	//bool Clean_drawable_references();
	// this idea must wait for now
};

// next thing to implement is rotation, since pretty much everything here is
// sf::Transformable

class SFML_text: public SFML_drawable
{	public:
	SFML_text(sf::Font &text_font, sf::Vector2f initial_position, std::string initial_text, sf::Color initial_colour, unsigned int character_size, bool center_origin);
	// should receive a sf::Font by reference
	void Set_element(std::string text_string);
	void Set_element(sf::Vector2f new_position);
	void Set_element(sf::Color new_colour);	
	void Set_element(unsigned int character_size);
	//	size is in pixels, although I dont know if this is height or width
	void Set_element(std::string text_string, sf::Vector2f new_position);
	void Set_element(std::string text_string, sf::Vector2f new_position, sf::Color new_colour);
	void Set_element(std::string text_string, sf::Color new_colour);
	void Set_element(sf::Vector2f new_position, sf::Color new_colour);
	// 
	void Draw_element(SFML_Window * iwindow);
	void Center_element();
	sf::Text text;
	
	~SFML_text();
	// later on this destructor will use info stored about the stored references
	// to this object to clean up all of said references so that null pointers
	// arent laying around like landmines
};

class SFML_circle: public SFML_drawable
{	public:
	SFML_circle(sf::Vector2f initial_position, sf::Color initial_colour, float initial_radius, bool center_origin);
	// later this will have a second constructor to texture it with a passed
	// sf::Texture reference
	void Set_element(float new_radius);
	void Set_element(sf::Vector2f new_position);	
	void Set_element(sf::Color new_colour);	
	void Set_element(float new_radius, sf::Vector2f new_position);
	void Set_element(float new_radius, sf::Vector2f new_position, sf::Color new_colour);
	void Set_element(float new_radius, sf::Color new_colour);
	void Set_element(sf::Vector2f new_position, sf::Color new_colour);	
	// all of the given setters, applied directly to our sf::CircleShape,
	// instead of holding internal variables. There could be a lot of displays
	// in sim, so we want to keep memory usage to a bare minimum
	void Draw_element(SFML_Window * iwindow);
	void Center_element();
	sf::CircleShape circle_shape;
	// oddly, sfml seems to automatically pick a point count for circles by
	// default, so that the given circle looks halfway decent. oh well...
	~SFML_circle();
};

class SFML_rectangle: public SFML_drawable
{	public:
	SFML_rectangle(sf::Vector2f initial_position, sf::Color initial_colour, float width, float height, bool center_origin);
	// later this will have a second constructor to texture it with a passed
	// sf::Texture reference
	void Set_element(float new_width, float new_height);
	void Set_element(sf::Vector2f new_position);	
	void Set_element(sf::Color new_colour);	
	void Set_element(float new_width, float new_height, sf::Vector2f new_position);
	void Set_element(float new_width, float new_height, sf::Vector2f new_position, sf::Color new_colour);
	void Set_element(float new_width, float new_height, sf::Color new_colour);
	void Set_element(sf::Vector2f new_position, sf::Color new_colour);	
	void Center_element();
	void Draw_element(SFML_Window * iwindow);
	sf::RectangleShape rect_shape;
	~SFML_rectangle();
};



#endif
