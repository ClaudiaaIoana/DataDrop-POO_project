#define _CRT_SECURE_NO_WARNINGS

#include "File.h"

File::File(std::string sender, std::string receiver, std::string name, int dimension)
{
	this->sender = sender;
	this->receiver = receiver;
	this->name = name;
	this->dimension = dimension;

}

File::File(const File& file)
{
	this->sender = file.sender;
	this->receiver = file.receiver;
	this->name = file.name;
	this->dimension = file.dimension;
}

File::~File()
{
	
}

std::string File::get_sender()
{
	return this->sender;
}

std::string File::get_receiver()
{
	return this->receiver;
}

std::string File::get_name()
{
	return this->name;
}

int File::get_dimension()
{
	return this->dimension;
}

