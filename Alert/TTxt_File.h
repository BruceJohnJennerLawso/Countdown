#pragma once
#include "fileparse.h"						

class TTxt_File :public CFileParse
{	public:
	TTxt_File(void);
	TTxt_File(std::string exe_path, std::string file_offset); 
	void Load_file(std::string file_offset);
	void Process_input(std::string line, unsigned int insert_location);
	void Process_input(std::string line);		// Default assumed to be inserted at the end
	std::string Access_data(unsigned int index);
	void Output_Data();
	void Insert_data(std::vector<std::string> i);
	void Insert_data(std::string i);
	void Overwrite_data(std::string i, unsigned int index);
	void Insert_blank_lines(unsigned int n);
	void Remove_line(unsigned int index);
	std::string Get_path();
	unsigned int Get_file_index();
	bool Read_state();
	bool Check_file_exists();
	void Create_file();
	bool Save_file(std::string file_path, bool selfdestruct);
	private:
	std::string file_path;
	std::vector<std::string> text_index;		// The full text of the file, including comments, read cues, etc. 
	unsigned int file_index;					// The number of elements in the file parse, regardless of whether they should be read or not
	bool is_read;								// Was the file input succesful, and is the text still loaded?
	public:
	~TTxt_File(void);
};

bool Create_text_file(std::string directory, std::string file_path);
bool Check_file_exists(std::string file_path);
unsigned int GetDTI ();


