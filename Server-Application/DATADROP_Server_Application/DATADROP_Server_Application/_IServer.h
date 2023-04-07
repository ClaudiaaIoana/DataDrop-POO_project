#pragma once
class _IServer
{
public:
	virtual void listen_()=0;
	virtual void send()=0;
	virtual void acceptConnection()=0;
};

