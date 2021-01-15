#include "StdAfx.h"
#include "ServerExample.h"

unsigned int ServerExample::client_id;

ServerExample::ServerExample(void)
{
	// id's to assign clients for our table
	client_id = 0;

	// set up the server network to listen 
	network = new ServerNetwork();
}

ServerExample::~ServerExample(void)
{
}

void ServerExample::update()
{
	// get new clients
	if (network->acceptNewClient(client_id))
	{
		printf("client %d has been connected to the server\n", client_id);

		//increment client ID for the next client
		client_id++;
	}

	receiveFromClients();
}

void ServerExample::receiveFromClients()
{

	Packet packet;

	// go through all clients using an iterator
	std::map<unsigned int, SOCKET>::iterator iter;

	for (iter = network->sessions.begin(); iter != network->sessions.end(); iter++)
	{
		int data_length = network->receiveData(iter->first, network_data);

		if (data_length <= 0)
		{
			//no data recieved
			continue;
		}

		int i = 0;
		while (i < (unsigned int)data_length)
		{
			packet.deserialize(&(network_data[i]));
			i += sizeof(Packet);

			//switch based on packet type
			switch (packet.packet_type) {

			case INIT_CONNECTION:

				printf("server received init packet from client\n");

				sendActionPackets();

				break;

			case DATA_EVENT:

				printf("server received action event packet from client\n");
				printf("Packet contained, speed %.1f, longitude %.f, latitude %.f\n", packet.speed, packet.longitude, packet.latitude);

				sendActionPackets();

				break;

			default:

				printf("error in packet types\n");

				break;
			}
		}
	}
}


void ServerExample::sendActionPackets()
{
	// send action packet
	const unsigned int packet_size = sizeof(Packet);
	char packet_data[packet_size];

	Packet packet;
	packet.packet_type = DATA_EVENT;

	packet.serialize(packet_data);

	network->sendToAll(packet_data, packet_size);
}