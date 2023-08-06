#include <iostream>
#include <h_net.h>
#include <string>
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



class CustomClient : public olc::net::client_interface<CustomMsgTypes>
{
public:
	void PingServer()
	{
		olc::net::message<CustomMsgTypes> msg;
		msg.header.id = CustomMsgTypes::ServerPing;

		// Caution with this...
		std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();

		msg << timeNow;
		Send(msg);
	}
	void Signupreq(std::string name,std::string email, std::string password)
	{
		olc::net::message<CustomMsgTypes> msg;
		msg.header.id = CustomMsgTypes::Signup;
		
		std::vector<uint8_t> n(name.begin(), name.end());
		n.push_back('|');
		n.insert(n.end(), email.begin(), email.end());
		n.push_back('|');
		n.insert(n.end(), password.begin(), password.end());

		msg << n;

		
		Send(msg);
	}
	void Loginreq(std::string email, std::string password)
	{
		olc::net::message<CustomMsgTypes> msg;
		msg.header.id = CustomMsgTypes::Login;

		std::vector<uint8_t> n(email.begin(), email.end());
		n.push_back('|');
		
		n.insert(n.end(), password.begin(), password.end());

		msg << n;


		Send(msg);
	}
	
	void Sendmsg(std::string senderemail,std::string receiveremail,std::string message)
	{
		olc::net::message<CustomMsgTypes> msg;
		msg.header.id = CustomMsgTypes::Sendmsg;

		std::vector<uint8_t> n(senderemail.begin(), senderemail.end());
		n.push_back('|');

		n.insert(n.end(), receiveremail.begin(), receiveremail.end());
		n.push_back('|');

		n.insert(n.end(), message.begin(), message.end());

		msg << n;


		Send(msg);
	}
	void Fetchmessage(std::string email, std::string friendemail)
	{
		olc::net::message<CustomMsgTypes> msg;
		msg.header.id = CustomMsgTypes::Fetchmsg;
		std::vector<uint8_t> n(email.begin(), email.end());
		n.push_back('|');
		n.insert(n.end(), friendemail.begin(), friendemail.end());
		msg << n;
		Send(msg);
	}
	void Fetchfriend(std::string email)
	{
		olc::net::message<CustomMsgTypes> msg;
		msg.header.id = CustomMsgTypes::Fetchfriend;
		std::vector<uint8_t> n(email.begin(), email.end());
		
		msg << n;
		Send(msg);
	}
	void MessageAll()
	{
		olc::net::message<CustomMsgTypes> msg;
		msg.header.id = CustomMsgTypes::MessageAll;
		Send(msg);
	}
};

int main()
{
	CustomClient c;
	c.Connect("127.0.0.1", 60000);

	bool key[4] = { false, false, false, false };
	bool old_key[4] = { false, false, false, false };

	bool bQuit = false;
	while (!bQuit)
	{
		
			key[0] = GetAsyncKeyState('1') & 0x8000;

			key[1] = GetAsyncKeyState('2') & 0x8000;
			key[2] = GetAsyncKeyState('3') & 0x8000;
			key[3] = GetAsyncKeyState('4') & 0x8000;
		
		
		if (key[0] && !old_key[0]) c.PingServer();
		if (key[1] && !old_key[1]) c.MessageAll();
		
		if (key[2] && !old_key[2]) bQuit = true;
		if (key[3] && !old_key[3]) c.Signupreq("Prabin","adhprb111@gmail.com","122345");
		for (int i = 0; i < 4; i++) old_key[i] = key[i];

		if (c.IsConnected())
		{
			if (!c.Incoming().empty())
			{


				auto msg = c.Incoming().pop_front().msg;

				switch (msg.header.id)
				{
				case CustomMsgTypes::ServerAccept:
				{
					// Server has responded to a ping request				
					std::cout << "Server Accepted Connection\n";
				}
				break;


				case CustomMsgTypes::ServerPing:
				{
					// Server has responded to a ping request
					std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();
					std::chrono::system_clock::time_point timeThen;
					msg >> timeThen;
					std::cout << "Ping: " << std::chrono::duration<double>(timeNow - timeThen).count() << "\n";
				}
				break;

				case CustomMsgTypes::ServerMessage:
				{
					// Server has responded to a ping request	
					uint32_t clientID;
					msg >> clientID;
					std::cout << "Hello from [" << clientID << "]\n";
				}
				break;

				case CustomMsgTypes::Signup:
				{
					// Server has responded to a ping request	
					uint32_t clientID;
					std::cout << msg;
					msg >> clientID;
					std::cout << "Signing in for you i.e. [" << clientID << "]\n";
				}
				break;
				}
			}
		}
		else
		{
			std::cout << "Server Down\n";
			bQuit = true;
		}

	}

	return 0;
}