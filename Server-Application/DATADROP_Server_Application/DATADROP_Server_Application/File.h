#pragma once
#include<string.h>
#include<iostream>
class File
{
private:
	std::string sender;
	std::string receiver;
	std::string name;
	int dimension;
public:
	File(std::string sender, std::string receiver, std::string name, int dimension);
	File(const File& file);
	~File();
	std::string				get_sender();
	std::string				get_receiver();
	std::string				get_name();
	int						get_dimension();
};

