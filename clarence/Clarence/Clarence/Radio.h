#pragma once
#include "hardware.h"
ref class Radio : public hardware {
private:
	array<bool> ^drawers;
	double station;
public:
	Radio();
	bool drawerStatus(int);
	double tuner();
	void openDrawer(int);
};

