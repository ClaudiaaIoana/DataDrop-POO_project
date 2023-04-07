#pragma once
class Log
{
private:
	static Log*		instance;
	Log() = default;
	~Log() = default;
public:
	static void		get_instance();
	static void		destroy_instance();
};

