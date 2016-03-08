// Clarence.cpp : main project file.

#include "stdafx.h"
#include "Hardware.h"
#include "Radio.h"
//#include "fmod_studio.h"

//FMOD::Studio::System* fmodSystem;


using namespace System;
using namespace System::IO::Ports;


int main(array<System::String ^> ^args)
{
    String^ answer;
	String^ portName;
	int baudRate=9600;
	Console::WriteLine("Type in a port name and hit ENTER");
	portName=Console::ReadLine();
	// arduino settings
	SerialPort^ arduino;
	arduino = gcnew SerialPort(portName, baudRate);
	// open port
	try
	{
		arduino->Open();
		do
		{
			//Console::WriteLine("Type to talk to the arduino!");
			// get answer
			answer=Console::ReadLine();
			//send the line to the arduino
			arduino->WriteLine(answer);
			// get response
			answer = arduino->ReadLine();
			// print arduino's response to console
			Console::WriteLine(answer);
			// ask user if they want to continue
			// get answer
			//answer=Console::ReadLine();
			// clear the screen
			//Console::Clear();
		}while(true/*String::Compare(answer,"yes")==0*/);
		// close port to arduino
		arduino->Close();
	}
	catch (IO::IOException^ e  ) 
	{ 
		Console::WriteLine(e->GetType()->Name+": Port is not ready");
	}
	catch (ArgumentException^ e)
	{
		Console::WriteLine(e->GetType()->Name+": incorrect port name syntax, must start with COM/com");
	}
	// end program
	Console::Write("Press enter to close the program");
	Console::Read();
    return 0;
}
