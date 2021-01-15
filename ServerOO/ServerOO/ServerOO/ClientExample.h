#pragma once
#include <winsock2.h>
#include <Windows.h>
#include "ClientNetwork.h"
#include "NetworkData.h"

class ClientExample
{
public:
	ClientExample(void);
	~ClientExample(void);

	ClientNetwork* network;

	void sendActionPackets();

	char network_data[MAX_PACKET_SIZE];

	void update();
};

