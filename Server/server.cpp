#include <iostream>
#include <h_net.h>
#include "database.h"
enum class CustomMsgTypes : uint32_t
{
	ServerAccept,
	ServerDeny,
	ServerPing,
	MessageAll,
	ServerMessage,
	Signup,
	Login,
	Sendmsg,
	Fetchmsg,
	Fetchfriend
};



class CustomServer : public olc::net::server_interface<CustomMsgTypes>
{
private:
	
public:
	CustomServer(uint16_t nPort) : olc::net::server_interface<CustomMsgTypes>(nPort)
	{
		
	}

protected:
	virtual bool OnClientConnect(std::shared_ptr<olc::net::connection<CustomMsgTypes>> client)
	{
		olc::net::message<CustomMsgTypes> msg;
		msg.header.id = CustomMsgTypes::ServerAccept;
		client->Send(msg);
		return true;
	}


	virtual void OnClientDisconnect(std::shared_ptr<olc::net::connection<CustomMsgTypes>> client)
	{
		std::cout << "Removing client [" << client->GetID() << "]\n";
	}


	virtual void OnMessage(std::shared_ptr<olc::net::connection<CustomMsgTypes>> client, olc::net::message<CustomMsgTypes>& msg)
	{

		switch (msg.header.id)
		{
		
		case CustomMsgTypes::ServerPing:
		{
			std::cout << "[" << client->GetID() << "]: Server Ping\n";

			
			client->Send(msg);
		}
		break;

		case CustomMsgTypes::MessageAll:
		{
			std::cout << "[" << client->GetID() << "]: Message All\n";

			olc::net::message<CustomMsgTypes> msg;
			msg.header.id = CustomMsgTypes::ServerMessage;
			msg << client->GetID();
			MessageAllClients(msg, client);

		}
		break;
		case CustomMsgTypes::Signup:
		{
			std::cout << "[" << client->GetID() << "]: Signing up\n";
			try{
				//TO DO      fetch the char* data as json and code accordingly
				Database db("Convo_conn.db");
				db.signup("Prabin", "adhprb111@gmail.com", "3334");
			}
			catch (Exception e)
			{
				std::cout << e.error;
			}
	
			msg.header.id = CustomMsgTypes::Signup;
			std::cout << msg;
		
			for (const char i : msg.body) {
				std::cout << i;
			}
			msg << client->GetID();
			MessageClient(client, msg);

		}
		break;
		}
	}
};

int main()
{
	CustomServer server(60000);
	server.Start();

	while (1)
	{
		server.Update(-1, true);
	}



	return 0;
}