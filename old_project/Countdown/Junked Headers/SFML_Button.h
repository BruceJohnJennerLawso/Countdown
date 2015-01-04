#pragma once
#include <SFML/Graphics.hpp>


class box_coordinates
{	public:
	box_coordinates::box_coordinates();
	box_coordinates::box_coordinates(unsigned int ix, unsigned int iy, unsigned int iw, unsigned int ih);
	unsigned int x, y;	// Cartesian coordinates of the upper left corner of the box
	unsigned int w, h;	// width, height of the box
	box_coordinates::~box_coordinates();
};

class SFML_Button
{	public:
	SFML_Button();
	SFML_Button(std::string texture_path, box_coordinates button_parameters, box_coordinates texture_coordinates);
	sf::Texture Button_texture;
	sf::Sprite Button_sprite;
	box_coordinates Button_Coordinates;
	bool Check_for_point_in_coordinates(unsigned int x, unsigned int y);
	bool Set_texture(std::string texture, box_coordinates texture_coordinates);
	void Set_texture_coordinates(box_coordinates texture_coordinates);
	void Set_parameters(box_coordinates button_parameters);
	~SFML_Button(void);
};

