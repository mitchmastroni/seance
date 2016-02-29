#pragma once
ref class hardware
{
protected:
	bool connected;
public:
	bool connect(int);
	bool isConnected();
	hardware();
};