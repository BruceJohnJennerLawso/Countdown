#include "TTxt_File.h"
using namespace std;


TTxt_File::TTxt_File(void)
{	

}

TTxt_File::TTxt_File(std::string exe_path, std::string file_offset)
{	file_index = 0;
	is_read = false;
	file_path = "NULL";
	switch(this->Check_file_exists())
	{	case false:
		Create_text_file(exe_path, file_offset);
		case true:
		Load_file(exe_path.append(file_offset));
	}
}

void TTxt_File::Load_file(std::string file_offset)
{	ifstream file (file_offset);
	if (file.is_open())
	{	is_read = true;	// Indicate that the file is now copied to memory, and all has not gone to hell in a handbasket
		file_path = file_offset;
		std::string * line;
		line = new std::string(); 
		while (std::getline(file,*line))
		{	Process_input(*line);	// Nom, nom, nom, tasty bytes of data	
		}	line->clear();
		delete line;
	}	
	file.close();
}

void TTxt_File::Process_input(std::string line, unsigned int insert_location)
{	std::string * input_line;
	input_line = new std::string(line);
	transform (input_line->begin (), input_line->end (), input_line->begin (), toupper);
	text_index.emplace((text_index.begin() + insert_location), line);
	file_index++;
	delete input_line;
}

void TTxt_File::Process_input(std::string line)
{	std::string * input_line;
	input_line = new std::string(line);
	transform (input_line->begin (), input_line->end (), input_line->begin (), toupper);	
	text_index.emplace_back(line);
	file_index++;
	delete input_line;
}	

void TTxt_File::Insert_data(std::vector<std::string> i)
{	for(std::vector<std::string>::iterator it = i.begin(); it != i.end(); ++it)
	{	Process_input(*it);
	}
}

void TTxt_File::Insert_data(std::string i)
{	Process_input(i);
}

bool TTxt_File::Overwrite_data(std::string i, unsigned int index)
{	unsigned int cy = 0;
	for(std::vector<std::string>::iterator it = text_index.begin(); it != text_index.end(); ++it)
	{	if (cy == index)
		{	(it)->assign(i);
			return true;
		}
		else
		{	++cy;
		}
	}	return false;
}

void TTxt_File::Insert_blank_lines(unsigned int n)
{	for (unsigned int cy = 0; cy != n; ++cy)
	{	Process_input("");
	}
}

void TTxt_File::Remove_line(unsigned int index)
{	std::vector<std::string>::iterator it = text_index.begin()+index;
	if(index <= file_index)
	{	text_index.erase(it);
		file_index--;
	}	
	else
	{	// ??? I dunno, maybe tell the user not to do that?
	}
}

std::string TTxt_File::Access_data(unsigned int index)
{	unsigned int cy = 0;
	for(std::vector<std::string>::iterator it = text_index.begin(); it != text_index.end(); ++it)
	{	if (cy == index)
		{	return *it;
		}
		else
		{	++cy;
		}
	}
	return "BAD_INDEX";	
}

void TTxt_File::Output_Data()
{	for(unsigned int cy = 0; cy != text_index.size(); ++cy)
	{	cout << cy << "	" << text_index.at(cy) << endl;
	}
}

std::string TTxt_File::Get_path()
{	return file_path;
}

unsigned int TTxt_File::Get_file_index()
{	return file_index;
}	// Pretty much what it says on the llama

bool TTxt_File::Read_state()
{	return is_read;
}	// A check on whether the read was successful

bool TTxt_File::Check_file_exists()
{	bool Check_return = false;
	ifstream file (file_path);
	if(file.is_open())
	{	Check_return = true;
	}	file.close();
	return Check_return;
}

bool TTxt_File::Save_file(std::string file_path, bool selfdestruct)
{	switch(Check_file_exists())
	{	case true:
		{	std::remove(file_path.c_str());
			ofstream file (file_path);
			if (file.is_open())
			{	for (std::vector<std::string>::iterator it = text_index.begin(); it != text_index.end(); ++it)
				{	file << ((*it).append("\n"));	
				}
			}
			file.close();
			// It read funny without a comment in here.
			if (selfdestruct == true)
			{	this->~TTxt_File();
			}
			else
			{	return true;
			}
		}
		case false:
		{	return false;
		}
	}
}

TTxt_File::~TTxt_File(void)
{	text_index.clear();
	is_read = false;
}


// Non-member function to remove the Cmd_dashdash dependency ///////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Create_text_file(std::string directory, std::string file_path)
{	switch(Check_file_exists(directory.append(file_path)))	// Please note, your input has to be complete, including the .txt file extension
	{	case true:
		return false;
		case false:
		ofstream file (directory);
		if (file.is_open())
		{	file << "//File_Parse generated file created on " << GetDTI(); 
		}
		file.close();
		return true;
	}
	return false;
}

bool Check_file_exists(std::string file_path)
{	bool Check_return = false;
	ifstream file (file_path);
	if(file.is_open())
	{	Check_return = true;
	}	file.close();
	return Check_return;
}

unsigned int GetDTI ()
{	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];	
	time (&rawtime);
	timeinfo = localtime(&rawtime);
	strftime (buffer, 80, "%d%m%y", timeinfo);	
	std::string number = buffer;	
	unsigned int DTI = std::stoi(number);
	return DTI;	// Need to convert string to integer... yeah... This was finished sometime... Apparently...
}