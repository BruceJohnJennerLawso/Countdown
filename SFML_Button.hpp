#pragma once
#include <SFML/Graphics.hpp>
#include "SFML_Tools.hpp"

#ifndef sf_buttonh
#define sf_buttonh

class SFML_Button
{	// ehh, I dont really want to make this a SFML_Drawable
	public:
	SFML_Button(sf::Texture * new_texture,  sf::IntRect active_tex_coordinates, sf::IntRect inactive_tex_coordinates, VectorVictor::Vector2 origin, variable height, variable width, bool active);
	
	SFML_Button(sf::Texture * new_texture,  sf::IntRect active_tex_coordinates, sf::IntRect inactive_tex_coordinates, VectorVictor::Vector2 origin, variable height, variable width,  sf::Color button_colour, bool active);
	
	bool Active;
	// Is the button basically clickable or just an inactive image on the window
	void Draw_button(SFML_Window * iwindow);
	bool Is_left_clicked(Cursor_commands * mouse_input);
	sf::Texture * Button_texture;
	VectorVictor::Vector2 Origin;
	variable Height, Width;
	sf::Sprite Active_sprite, Inactive_sprite;
	~SFML_Button();
};

#endif
