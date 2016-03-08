#pragma once
ref class Hardware
{
protected:
	bool connected;
public:
	bool connect(int);
	bool isConnected();
	Hardware();
};