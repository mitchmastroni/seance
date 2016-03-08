#include "stdafx.h"
#include "Hardware.h"


Hardware::Hardware()
{

}

bool Hardware::connect(int port) {
	//initialize connection at COM-port
	return connected;
}

bool Hardware::isConnected() {
	return connected;
}
