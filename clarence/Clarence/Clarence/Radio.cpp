#include "stdafx.h"
#include "Radio.h"

//using namespace System;
//using namespace System::IO::Ports;

Radio::Radio() {
	//int radioBaudRate = 9600;
	//String^ radioPortName;

	//Console::WriteLine("Type in a port name for the Radio and hit ENTER");
	//radioPortName = Console::ReadLine();
	//SerialPort^ radio;
	//radio = gcnew SerialPort(radioPortName, radioBaudRate);

	drawers = gcnew array<bool>(2);
	drawers[0] = drawers[1] = false;
	//These two values are arbitrary
	station = 96.3;
	//Serial radioSerial("3");
}

bool Radio::drawerStatus(int drawer) {
	if (drawer > 2) {
		//error
	}
	else {
		return drawers[drawer + 1];
	}
}

double Radio::tuner() {
	//cout << "--arduino.getStation\n";
	//while (!(cin >> station)) {
	//	cout << "Bad value!/n";
	//	cin.clear();
	//	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	//}
	return station;
}

void Radio::openDrawer(int drawer) {
	if (drawer == 1 || drawer == 2) {
		//open drawer
		drawers[drawer + 1] = true;
		//cout << "A drawer on the radio opens, revealing...\n";
		return;
	}
	else {
		//error
		return;
	}
}
