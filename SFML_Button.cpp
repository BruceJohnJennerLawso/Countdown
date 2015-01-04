#include <SFML/Graphics.hpp>
#include "SFML_Button.hpp"



SFML_Button::SFML_Button(sf::Texture * new_texture,  sf::IntRect active_tex_coordinates, sf::IntRect inactive_tex_coordinates, VectorVictor::Vector2 origin, variable height, variable width, bool active)
{	Button_texture = new_texture;
	Active_sprite.setTexture(*Button_texture);
	Active_sprite.setTextureRect(active_tex_coordinates);
	Active_sprite.setPosition(sf::Vector2f(origin.Get_x(), origin.Get_y()));
	
	Inactive_sprite.setTexture(*Button_texture);
	Inactive_sprite.setTextureRect(inactive_tex_coordinates);
	Inactive_sprite.setPosition(sf::Vector2f(origin.Get_x(), origin.Get_y()));
	
	Height = height;
	Width = width;	
	
	Origin = origin;
	
	Active = active;
}


SFML_Button::SFML_Button(sf::Texture * new_texture,  sf::IntRect active_tex_coordinates, sf::IntRect inactive_tex_coordinates, VectorVictor::Vector2 origin, variable height, variable width,  sf::Color button_colour, bool active)
{	Button_texture = new_texture;
	Active_sprite.setTexture(*Button_texture);
	Active_sprite.setTextureRect(active_tex_coordinates);
	Active_sprite.setPosition(sf::Vector2f(origin.Get_x(), origin.Get_y()));
	Active_sprite.setColor(button_colour);
	
	Inactive_sprite.setTexture(*Button_texture);
	Inactive_sprite.setTextureRect(inactive_tex_coordinates);
	Inactive_sprite.setPosition(sf::Vector2f(origin.Get_x(), origin.Get_y()));
	Inactive_sprite.setColor(button_colour);
	
	Height = height;
	Width = width;	
	
	Origin = origin;
	
	Active = active;
}

void SFML_Button::Draw_button(SFML_Window * iwindow)
{	if(Active == true)
	{	iwindow->window->draw(Active_sprite);
	}
	else if(Active == false)
	{	iwindow->window->draw(Inactive_sprite);
	}
}

bool SFML_Button::Is_left_clicked(Cursor_commands * mouse_input)
{	if(mouse_input->Left_click == true)
	{	//VectorVictor::Vector2 offset = mouse_input->position;
		// dont wanna bother with writing a conversion operator here, sooo
		VectorVictor::Vector2 offset(mouse_input->position.x, mouse_input->position.y);
		//offset.x = mouse_input->position.x;
		//offset.y = mouse_input->position.y;
		offset -= Origin;
		if((offset.Get_x() <= Width)&&(offset.Get_x() >= 0))
		{	if((offset.Get_y() <= Height)&&(offset.Get_y() >= 0))
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


SFML_Button::~SFML_Button()
{
}
