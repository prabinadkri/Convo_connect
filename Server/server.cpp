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
				
				std::vector<uint8_t> error (e.error.begin(),e.error.end());
				for (auto i : error)
				{
					std::cout << i;
				}
				msg.header.id = CustomMsgTypes::Signup;
				msg << error;
				MessageClient(client, msg);
				break;
			}
	
			msg.header.id = CustomMsgTypes::Signup;
			msg << "Signed Up";
			MessageClient(client, msg);

		}
		break;
		case CustomMsgTypes::Login:
		{
			std::cout << "[" << client->GetID() << "]: Logging in\n";
			try {
				//TO DO      fetch the char* data as json and code accordingly
				Database db("Convo_conn.db");
				db.login("adhprb111@gmail.com", "3334");
			}
			catch (Exception e)
			{
				msg.header.id = CustomMsgTypes::Login;
				std::vector<uint8_t> error(e.error.begin(), e.error.end());
				msg << error;
				MessageClient(client, msg);
				break;
			}

			msg.header.id = CustomMsgTypes::Login;
			//std::cout << msg;

			/*for (const char i : msg.body) {
				std::cout << i;
			}*/
			msg << "Logged in";
			MessageClient(client, msg);

		}
		break;

		case CustomMsgTypes::Sendmsg:
		{
			

			msg.header.id = CustomMsgTypes::Sendmsg;
			//std::cout << msg;
			std::cout << "\nsender: ";
			for (const char i : msg.sender) {
				std::cout << i;
			}
			std::cout << "\n reciever:";
			for (const char i : msg.reciever) {
				std::cout << i;
			}
			std::cout << "\nBody: ";

			for (const char i : msg.body) {
				std::cout << i;
			}
			//msg << "Logged in";
			//MessageClient(client, msg);

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