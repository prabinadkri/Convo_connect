#include <iostream>
#include <h_net.h>
#include<sstream>
#include<ctime>
#include<iomanip>
#include "database.h"
#include <fstream>
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
struct User{
	std::string name;
	std::string email;
	std::string password;
	std::string username;
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
		{
			Database db("Convo_conn.db");
			db.filterqueue();
		}
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
			try {
				
				Database db("Convo_conn.db");
				std::string name(msg.sender.begin(), msg.sender.end());
				std::string email(msg.reciever.begin(), msg.reciever.end());
				std::string password(msg.body.begin(), msg.body.end());
				std::string username(msg.time.begin(), msg.time.end());
				db.signup(name, email, password,username);
				
			}
			catch (Exception e)
			{

				std::vector<uint8_t> error(e.error.begin(), e.error.end());
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
		/*	bool error = false;
			msg.header.id = CustomMsgTypes::Signup;
			
			std::string name(msg.sender.begin(), msg.sender.end());
			std::string email(msg.reciever.begin(), msg.reciever.end());
			std::string password(msg.body.begin(), msg.body.end());
			std::string username(msg.time.begin(), msg.time.end());

			User usr;
			std::ifstream infile("User.bin", std::ios::binary);
			while (!infile.eof())
			{
				if (infile.read(reinterpret_cast<char*>(&usr), sizeof(usr)))
				{
					if (usr.email == email)
					{
						std::vector<std::string>  m;
						m.push_back("User with email already exists!");
						m.push_back("");
						m.push_back("s");
						m.push_back("Time is to be set");
						msg << m;
						MessageClient(client, msg);
						error = true;
						break;
					}

					if (usr.username == username)
					{
						std::vector<std::string>  m;
						m.push_back("Email already exists!");
						m.push_back("");
						m.push_back("s");
						m.push_back("Time is to be set");
						msg << m;
						MessageClient(client, msg);
						error = true;
						break;
					}
				}
			}
			
			infile.close();
			if (error)
			{
				break;
			}
			User a;
			a.name = name;
			a.email = email;
			a.password = password;
			a.username = username;
			std::ofstream file("User.bin", std::ios::app | std::ios::binary);
			if (!file)
			{
				std::cout << "Error opening file" << std::endl;
				return;
			}
		
			file.write(reinterpret_cast<const char*>(&a), sizeof(a));
	

			file.close();
			std::vector<std::string>  m;
			m.push_back("Signed up");
			m.push_back("a");
			m.push_back("s");
			m.push_back("Time is to be set");
			msg << m;
		
			MessageClient(client, msg);*/

		}
		break;
		case CustomMsgTypes::Login:
		{
			std::cout << "[" << client->GetID() << "]: Logging in\n";
			try {
				//TO DO      fetch the char* data as json and code accordingly
				Database db("Convo_conn.db");
				
				std::string email(msg.sender.begin(), msg.sender.end());
				std::string password(msg.reciever.begin(), msg.reciever.end());
				
				db.login(email, password);
				std::string m = db.getName(email);
				msg.header.id = CustomMsgTypes::Login;
				std::vector<uint8_t> a(m.begin(), m.end());
				msg << a;
				MessageClient(client, msg);
				
			}
			catch (Exception e)
			{
				msg.header.id = CustomMsgTypes::Login;
				std::vector<uint8_t> error(e.error.begin(), e.error.end());
				msg << error;
				MessageClient(client, msg);
				break;
			}

			
			//std::cout << msg;

			/*for (const char i : msg.body) {
				std::cout << i;
			}*/
			

		}
		break;

		case CustomMsgTypes::Sendmsg:
		{

			Database db("Convo_conn.db");

			msg.header.id = CustomMsgTypes::Sendmsg;
			//std::cout << msg;
			std::string sender(msg.sender.begin(), msg.sender.end());
			std::string reciever(msg.reciever.begin(), msg.reciever.end());
			std::string message(msg.body.begin(), msg.body.end());
			std::string time(msg.time.begin(), msg.time.end());
			std::cout << "\nsender: " << sender;
			/*for (const char i : msg.sender) {
				std::cout << i;
			}*/
			std::cout << "\nreciever: " << reciever;

			std::cout << "\nBody: " << message;
			std::cout << "\n time: " << time ;

			std::tm tmTime = {};
			std::istringstream ss(time);
			ss >> std::get_time(&tmTime, "%Y-%m-%d %H:%M:%S");

			if (ss.fail()) {
				std::cout << "Failed to parse time." << std::endl;
				break;
			}

			std::chrono::system_clock::time_point timePoint = std::chrono::system_clock::from_time_t(std::mktime(&tmTime));

			std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

			std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
			std::tm* gmTime = std::gmtime(&currentTime);
			std::chrono::system_clock::time_point gnow = std::chrono::system_clock::from_time_t(std::mktime(gmTime));

			if (gnow >= timePoint)
			{
				db.sendmsg(sender, reciever, message, time);
			}
			else
			{
				db.queuemsg(sender, reciever, message, time);
			}
			
			//msg << "Logged in";
			//MessageClient(client, msg);

		}
		break;

		case CustomMsgTypes::Fetchmsg:
		{
			Database db("Convo_conn.db");
			std::string sender(msg.sender.begin(), msg.sender.end());
			std::string reciever(msg.reciever.begin(), msg.reciever.end());

			Msg a = db.fetchmsg(sender, reciever);
			msg.header.id = CustomMsgTypes::Fetchmsg;
			//std::cout << a.message.size();
			for (size_t i = 0;i < a.message.size();i++)
			{
				std::vector<std::string> m;
				/*std::cout << a.message[i];
				std::cout << a.sender[i];
				std::cout << a.reciever[i];*/
				m.push_back(a.message[i]);
				m.push_back(a.sender[i]);
				m.push_back(a.reciever[i]);
				m.push_back(a.time[i]);
				msg << m;
				MessageClient(client, msg);
			}



		}
		break;

		case CustomMsgTypes::Fetchfriend:
		{

			Database db("Convo_conn.db");
			std::string sender(msg.body.begin(), msg.body.end());
			std::cout << "fetching friend for "<<sender;

			std::vector<std::string> a = db.fetchfriends(sender);
			msg.header.id = CustomMsgTypes::Fetchfriend;
			
			//std::cout << a.message.size();
			for (size_t i = 0;i < a.size();i++)
			{
				std::vector<std::string> m;
				/*std::cout << a.message[i];
				std::cout << a.sender[i];
				std::cout << a.reciever[i];*/
				
				std::cout << a[i];
				m.push_back(a[i]);
				m.push_back("q");
				m.push_back("w");
				m.push_back("e");

				msg << m;
				
				MessageClient(client, msg);



				
			}
		}
		break;

		case CustomMsgTypes::Finduser:
		{

			Database db("Convo_conn.db");
			std::string user(msg.body.begin(), msg.body.end());
			
			std::vector<std::string> a = db.finduser(user);
			msg.header.id = CustomMsgTypes::Finduser;
			for (size_t i = 0;i < a.size();i++)
			{
				std::vector<uint8_t> n(a[i].begin(), a[i].end());
				msg << n;
				MessageClient(client, msg);
			}


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