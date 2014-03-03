#include "SFML_Button.h"


box_coordinates::box_coordinates()
{	x = 0;
	y = 0;
	w = 0;
	h = 0;
}

box_coordinates::box_coordinates(unsigned int ix, unsigned int iy, unsigned int iw, unsigned int ih)
{	x = ix;
	y = iy;
	w = iw;
	h = ih;
}

box_coordinates::~box_coordinates()
{
}

SFML_Button::SFML_Button()
{
}

SFML_Button::SFML_Button(std::string texture_path, box_coordinates button_parameters, box_coordinates texture_coordinates)
{	Set_texture(texture_path, texture_coordinates);
	Set_parameters(button_parameters);
}

bool SFML_Button::Check_for_point_in_coordinates(unsigned int x, unsigned int y)
{	if(y >= Button_Coordinates.y)
	{	if(y <= (Button_Coordinates.y + Button_Coordinates.h))
		{	if(x >= Button_Coordinates.x)
			{	if(x <= (Button_Coordinates.x + Button_Coordinates.w))
				{	return true;
				}
				else
				{	return false;
				}
			}
			else
			{	return false;
			}
		}
		else
		{	return false;
		}
	}
	else
	{	return false;
	}
}

bool SFML_Button::Set_texture(std::string texture_path, box_coordinates texture_coordinates)
{	if(!Button_texture.loadFromFile(texture_path))
	{	return false;
	}
	else
	{	Set_texture_coordinates(texture_coordinates);
		return true;
	}
}

void SFML_Button::Set_texture_coordinates(box_coordinates texture_coordinates)
{	Button_sprite.setTexture(Button_texture);
	int x = texture_coordinates.x;
	int y = texture_coordinates.y;
	int h = texture_coordinates.h;
	int w = texture_coordinates.w;
	Button_sprite.setTextureRect(sf::Rect<int>(x, y, w, h));
}

void SFML_Button::Set_parameters(box_coordinates button_parameters)
{	Button_Coordinates.h = button_parameters.h;
	Button_Coordinates.w = button_parameters.w;
	Button_Coordinates.x = button_parameters.x;
	Button_Coordinates.y = button_parameters.y;
	Button_sprite.setPosition(Button_Coordinates.x, Button_Coordinates.y);
}

SFML_Button::~SFML_Button(void)
{
}
