#pragma once
#include "hardware.h"

//using namespace System;
//using namespace System::IO::Ports;

ref class Radio : public Hardware {
private:
	array<bool> ^drawers;
	double station;
public:
	Radio();
	bool drawerStatus(int drawer);
	double tuner();
	void openDrawer(int drawer);
};

