#include <iostream>
#include "./../Net/h_net.h"
#include <string>
#include<sstream>
#include <iomanip>

#pragma warning(disable : 4996)
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
	Fetchfriend,
	Finduser
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
	void Signupreq(std::string name,std::string email, std::string password,std::string username)
	{
		olc::net::message<CustomMsgTypes> msg;
		msg.header.id = CustomMsgTypes::Signup;
		std::vector<std::string> a;
		a.push_back(password);
		a.push_back(name);
		a.push_back(email);
		a.push_back(username);

		msg << a;


		Send(msg);
	}
	void Loginreq(std::string email, std::string password)
	{
		olc::net::message<CustomMsgTypes> msg;
		msg.header.id = CustomMsgTypes::Login;
		std::vector<std::string> a;
		a.push_back("Login");
		a.push_back(email);
		a.push_back(password);
		a.push_back("a");

		msg << a;


		Send(msg);
	}
	static std::string getcurrTime()
	{
		std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

		std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
		std::tm* gmTime = std::gmtime(&currentTime);

		std::ostringstream oss;
		oss << std::put_time(gmTime, "%Y-%m-%d %H:%M:%S");

		std::string formattedTime = oss.str();

		return formattedTime;
	}
	void Sendmsg(std::string senderemail,std::string receiveremail,std::string message,std::string time=getcurrTime())
	{
		olc::net::message<CustomMsgTypes> msg;
		msg.header.id = CustomMsgTypes::Sendmsg;
		std::vector<std::string> a;
		a.push_back(message);
		a.push_back(senderemail);
		a.push_back(receiveremail);
		

		

		a.push_back(time);

		msg << a;


		Send(msg);
	}
	void Fetchmessage(std::string email, std::string friendemail)
	{
		olc::net::message<CustomMsgTypes> msg;
		msg.header.id = CustomMsgTypes::Fetchmsg;

		std::vector<std::string> a;
		a.push_back("fetch message");
		a.push_back(email);
		a.push_back(friendemail);
		a.push_back("Time is to be set");
		msg << a;
		Send(msg);
	}
	void Fetchfriend(std::string email)
	{
		olc::net::message<CustomMsgTypes> msg;
		msg.header.id = CustomMsgTypes::Fetchfriend;
		std::vector<std::string> a;
		a.push_back(email);
		a.push_back("s");
		a.push_back("s");
		a.push_back("Time is to be set");
		msg << a;
		Send(msg);
	}

	void Finduser(std::string a)
	{
		olc::net::message<CustomMsgTypes> msg;
		msg.header.id = CustomMsgTypes::Finduser;
		std::vector<std::string> c;
		c.push_back(a);
		c.push_back("as");
		c.push_back("as");
		c.push_back("Time is to be set");
		msg << c;
		Send(msg);
	}

	void MessageAll()
	{
		olc::net::message<CustomMsgTypes> msg;
		msg.header.id = CustomMsgTypes::MessageAll;
		Send(msg);
	}
};
//
//int main()
//{
//	CustomClient c;
//	c.Connect("127.0.0.1", 60000);
//
//	bool key[9] = { false, false, false, false,false , false, false,false, false};
//	bool old_key[9] = { false, false, false, false ,false, false, false,false, false};
//
//	bool bQuit = false;
//	while (!bQuit)
//	{
//		
//			key[0] = GetAsyncKeyState('1') & 0x8000;
//
//			key[1] = GetAsyncKeyState('2') & 0x8000;
//			key[2] = GetAsyncKeyState('3') & 0x8000;
//			key[3] = GetAsyncKeyState('4') & 0x8000;
//			key[4] = GetAsyncKeyState('5') & 0x8000;
//			key[5] = GetAsyncKeyState('6') & 0x8000;
//			key[6] = GetAsyncKeyState('7') & 0x8000;
//			key[7] = GetAsyncKeyState('8') & 0x8000;
//			key[8] = GetAsyncKeyState('9') & 0x8000;
//		if (key[0] && !old_key[0]) c.PingServer();
//		if (key[1] && !old_key[1]) c.MessageAll();
//		
//		if (key[2] && !old_key[2]) bQuit = true;
//		if (key[3] && !old_key[3]) c.Signupreq("Nirajan","abcd@qxyz.com","122345","niru1");
//		if (key[4] && !old_key[4]) c.Loginreq("abcd@xyz.com", "122345");
//		if (key[5] && !old_key[5]) c.Sendmsg("asdfag","adhprb111@gmail.com", "trial messages6");// additional argument for time to send can be passed
//		if (key[6] && !old_key[6]) c.Fetchmessage("asdfag", "adhprb111@gmail.com");
//		if (key[7] && !old_key[7]) c.Fetchfriend("adhprb111@gmail.com");
//		if (key[8] && !old_key[8]) c.Finduser("n");
//		for (int i = 0; i < 9; i++) old_key[i] = key[i];
//
//		if (c.IsConnected())
//		{
//			if (!c.Incoming().empty())
//			{
//
//
//				auto msg = c.Incoming().pop_front().msg;
//
//				switch (msg.header.id)
//				{
//				case CustomMsgTypes::ServerAccept:
//				{
//					// Server has responded to a ping request				
//					std::cout << "Server Accepted Connection\n";
//				}
//				break;
//
//
//				case CustomMsgTypes::ServerPing:
//				{
//					// Server has responded to a ping request
//					std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();
//					std::chrono::system_clock::time_point timeThen;
//					msg >> timeThen;
//					std::cout << "Ping: " << std::chrono::duration<double>(timeNow - timeThen).count() << "\n";
//				}
//				break;
//
//				case CustomMsgTypes::ServerMessage:
//				{
//					// Server has responded to a ping request	
//					uint32_t clientID;
//					msg >> clientID;
//					std::cout << "Hello from [" << clientID << "]\n";
//				}
//				break;
//
//				case CustomMsgTypes::Signup:
//				{
//					// Server has responded to a ping request	
//					//uint32_t clientID;
//					//std::cout << msg;
//					
//						for (auto i : msg.body)
//						{
//							std::cout << i;
//						}
//					
//					//msg >> clientID;
//					//std::cout << "Signing in for you i.e. [" << clientID << "]\n";
//				}
//				break;
//				case CustomMsgTypes::Login:
//				{
//					// Server has responded to a ping request	
//					/*uint32_t clientID;
//					std::cout << msg;*/
//					for (auto i : msg.body)
//					{
//						std::cout << i;
//					}
//					
//				}
//				break;
//
//				case CustomMsgTypes::Fetchfriend:
//				{
//					std::cout << '\n';
//					for (auto i : msg.body)
//					{
//						std::cout << i;
//					}
//				}
//				break;
//
//				case CustomMsgTypes::Fetchmsg:
//				{
//					// Server has responded to a ping request	
//					/*uint32_t clientID;
//					std::cout << msg;*/
//
//					std::string sender(msg.sender.begin(), msg.sender.end());
//					std::string reciever(msg.reciever.begin(), msg.reciever.end());
//					std::string message(msg.body.begin(), msg.body.end());
//					std::cout << "\nsender: " << sender;
//					/*for (const char i : msg.sender) {
//						std::cout << i;
//					}*/
//					std::cout << "\nreciever: " << reciever;
//
//					std::cout << "\nBody: " << message;
//
//					
//				}
//				break;
//
//				case CustomMsgTypes::Finduser:
//				{
//					std::cout << '\n';
//					for (auto i : msg.body)
//					{
//						std::cout << i;
//					}
//				}
//				break;
//				}
//			}
//		}
//		else
//		{
//			std::cout << "Server Down\n";
//			bQuit = true;
//		}
//
//	}
//
//	return 0;
//}