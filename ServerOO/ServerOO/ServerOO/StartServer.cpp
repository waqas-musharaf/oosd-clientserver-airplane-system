// main.cpp : Defines the entry point for the console application.
//

// may need #include "stdafx.h" in visual studio
#include "stdafx.h"
#include "ServerExample.h"
#include <WinBase.h>


void serverLoop();
ServerExample * server;

int main()
{
	// initialize the server
	server = new ServerExample();
	serverLoop();

}
void serverLoop()
{
	while (true)
	{
		server->update();
		Sleep(1000);
	}
}


