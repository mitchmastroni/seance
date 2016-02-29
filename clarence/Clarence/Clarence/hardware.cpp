#include "stdafx.h"
#include "hardware.h"


hardware::hardware()
{

}

bool hardware::connect(int port) {
	//initialize connection at COM-port
	return connected;
}

bool hardware::isConnected() {
	return connected;
}
