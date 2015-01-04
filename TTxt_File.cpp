#include "FileParse.cpp"		
#include "Functionalize!.cpp"
#include <string>


class TTxt_File :public CFileParse
{	public:
	TTxt_File(void);
	TTxt_File(::string exe_path, ::string file_offset); 
	void Load_file(::string file_offset);
	void Process_input(::string line, unsigned int insert_location);
	void Process_input(::string line);		// Default assumed to be inserted at the end
	::string Access_data(unsigned int index);
	void Output_Data();
	void Insert_data(std::vector<std::string> i);
	void Insert_data(::string i);
	void Overwrite_data(::string i, unsigned int index);
	void Insert_blank_lines(unsigned int n);
	void Remove_line(unsigned int index);
	::string Get_path();
	unsigned int Get_file_index();
	bool Read_state();
	bool Check_file_exists();
	void Create_file();
	bool Save_file(::string file_path, bool selfdestruct);
	private:
	::string file_path;
	::vector<std::string> text_index;		// The full text of the file, including comments, read cues, etc. 
	unsigned int file_index;					// The number of elements in the file parse, regardless of whether they should be read or not
	bool is_read;								// Was the file input succesful, and is the text still loaded?
	public:
	~TTxt_File(void);
};

bool Create_text_file(::string directory, ::string file_path);
bool Check_file_exists(::string file_path);


TTxt_File::TTxt_File(void)
{	

}

TTxt_File::TTxt_File(::string exe_path, ::string file_offset)
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

void TTxt_File::Load_file(::string file_offset)
{	ifstream file (file_offset);
	if (file.is_open())
	{	is_read = true;	// Indicate that the file is now copied to memory, and all has not gone to hell in a handbasket
		file_path = file_offset;
		::string * line;
		line = new std::string(); 
		while (std::getline(file,*line))
		{	Process_input(*line);	// Nom, nom, nom, tasty bytes of data	
		}	line->clear();
		delete line;
	}	
	file.close();
}

void TTxt_File::Process_input(::string line, unsigned int insert_location)
{	::string * input_line;
	input_line = new ::string(line);
	::transform (input_line->begin (), input_line->end (), input_line->begin (), ::toupper);
	text_index.emplace((text_index.begin() + insert_location), line);
	file_index++;
	delete input_line;
}

void TTxt_File::Process_input(::string line)
{	::string * input_line;
	input_line = new std::string(line);
	::transform (input_line->begin (), input_line->end (), input_line->begin (), ::toupper);	
	text_index.emplace_back(line);
	file_index++;
	delete input_line;
}	

void TTxt_File::Insert_data(std::vector<std::string> i)
{	for(std::vector<std::string>::iterator it = i.begin(); it != i.end(); ++it)
	{	Process_input(*it);
	}
}

void TTxt_File::Insert_data(::string i)
{	Process_input(i);
}

void TTxt_File::Overwrite_data(::string i, unsigned int index)
{	unsigned int cy = 0;
	for(std::vector<std::string>::iterator it = text_index.begin(); it != text_index.end(); ++it)
	{	if (cy == index)
		{	(it)->assign(i);
		}
		else
		{	++cy;
		}
	}
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

::string TTxt_File::Get_path()
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

bool TTxt_File::Save_file(::string file_path, bool selfdestruct)
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

bool Create_text_file(::string directory, ::string file_path)
{	switch(Check_file_exists(directory.append(file_path)))	// Please note, your input has to be complete, including the .txt file extension
	{	case true:
		return false;
		case false:
		ofstream file (directory);
		if (file.is_open())
		{	file << "//File_Parse generated file created on " << Cmd_dashdash::GetDTI(); 
		}
		file.close();
		return true;
	}
	return false;
}

bool Check_file_exists(::string file_path)
{	bool Check_return = false;
	ifstream file (file_path);
	if(file.is_open())
	{	Check_return = true;
	}	file.close();
	return Check_return;
}
