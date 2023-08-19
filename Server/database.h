#include <sqlite3.h>
#include<iostream>
#include<vector>
#include<sstream>
#include<chrono>
#include<ctime>
#include<iomanip>
#pragma warning(disable : 4996)
struct Msg
{
	std::vector<std::string> sender;
	std::vector<std::string> reciever;
    std::vector<std::string> message;
	std::vector<std::string> time;
};
class Exception
{

	
public:
	std::string error;
	Exception()
	{

	}
	Exception(std::string e)
	{
		error = e;
	}
};
class Database
{
private:
	sqlite3* db;
public:
	Database(std::string a)
	{
		int rc = sqlite3_open(a.c_str(), &db);
		if (rc != SQLITE_OK) {
			
			throw Exception("Error in opening in database");
		}
	}
	void signup(std::string name, std::string email, std::string password,std::string username)
	{
		const char* createTableSQL = "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, name TEXT (30),email TEXT (40) UNIQUE, password TEXT (255), username TEXT (40) UNIQUE);";
		int rc = sqlite3_exec(db, createTableSQL, 0, 0, 0);
		if (rc != SQLITE_OK) {
			throw Exception("Error in opening table");
		}
		//std::ostringstream sql;
		std::string sql = "INSERT INTO `users` (name, email, password, username) VALUES ('" + name + "', '" + email + "','" + password + "','"+ username +"');";

		const char* insertSQL = sql.c_str();
		rc = sqlite3_exec(db, insertSQL, 0, 0, 0);
		if (rc != SQLITE_OK) {
			throw Exception("User already exists");
			
		}
		

	}
	void login(std::string email,std::string password)
	{
		//std::ostringstream sqlquery;
		std::string sqlquery = "SELECT * FROM users WHERE email = '"+ email +"' AND password = '"+password+"';";

		const char* query = sqlquery.c_str();
		sqlite3_stmt* stmt;
		int rc = sqlite3_prepare_v2(db, query, -1, &stmt, nullptr);
		if (rc!=SQLITE_OK)
		{
			
			throw Exception("Internal Server error");
			return;
		}
		rc = sqlite3_step(stmt);

		if (rc == SQLITE_DONE) {
			throw Exception("Invalid credentials");

		}
		
		sqlite3_finalize(stmt);
		
	}

	std::vector<std::string> finduser(std::string s)
	{

		std::vector<std::string> usrs;

		std::string sql = "SELECT name from users WHERE name LIKE '"+s+"%';";
		sqlite3_stmt* stmt;
		int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
		if (rc != SQLITE_OK) {
			throw Exception("Error occured");

		}

		while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
			std::string s;
			s = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
			usrs.push_back(s);

		}

		if (rc != SQLITE_DONE) {
			throw Exception("Couldnot fetch all messages");
		}

		sqlite3_finalize(stmt);
		return usrs;
	}

	std::vector<std::string> fetchfriends(std::string user)
	{
		std::vector<std::string> frnds;

		std::string sql = "SELECT username from users";
		sqlite3_stmt* stmt;
		int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
		if (rc != SQLITE_OK) {
			throw Exception("Error occured");

		}

		while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
			std::string s;
			s = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
			if ((isFriend(user, s) || isFriend(s, user)))
			{
				frnds.push_back(s);
			}

		}

		if (rc != SQLITE_DONE) {
			throw Exception("Couldnot fetch all messages");
		}

		sqlite3_finalize(stmt);
		return frnds;
	}
	void sendmsg(std::string sender,std::string reciever,std::string msgs ,std::string time)
	{
		if (!(isFriend(sender, reciever) || isFriend(reciever, sender)))
		{
			std::string query = "CREATE TABLE IF NOT EXISTS `"+sender+"~"+reciever+"` (id INTEGER PRIMARY KEY, sender TEXT (60),reciever TEXT (60) , message TEXT (1000),time TEXT (60));";
			int rc = sqlite3_exec(db, query.c_str(), 0, 0, 0);
			if (rc != SQLITE_OK) {
				throw Exception("Error in opening table");
			}
		}
		
		//std::ostringstream sql;
		std::string sql;
		if(isFriend(sender,reciever))
		{
		
			 sql = "INSERT INTO `" + sender + "~" + reciever + "` (sender, reciever, message, time) VALUES('" + sender + "', '" + reciever + "', '" + msgs + "', '" + time + "');";
		}
		else
		{
			sql = "INSERT INTO `" + reciever + "~" + sender + "` (sender, reciever, message, time) VALUES('" + sender + "', '" + reciever + "', '" + msgs + "', '" + time + "');";
		}
		const char* insertSQL = sql.c_str();
		int rc = sqlite3_exec(db, insertSQL, 0, 0, 0);
		if (rc != SQLITE_OK) {
			throw Exception("Couldnot send message");
		}

	}
	Msg fetchmsg(std::string user1,std::string user2)
	{
		Msg a;
		std::string sql;
		if (isFriend(user1, user2))
		{
			sql = "SELECT sender,reciever,message,time From `" + user1 + "~" + user2 + "` ;";
		}
		if (isFriend(user2, user1))
		{
			sql = "SELECT sender,reciever,message,time From `" + user2 + "~" + user1 + "` ;";
		}
		sqlite3_stmt* stmt;
		int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
		if (rc != SQLITE_OK) {
			throw Exception("Error occured");
			
		}

		while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
			std::string s;
			s = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
			a.sender.push_back(s);
			s = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
			a.reciever.push_back(s);
			s = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
			a.message.push_back(s);
			s = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
			a.time.push_back(s);

		}

		if (rc != SQLITE_DONE) {
			throw Exception("Couldnot fetch all messages");
		}

		sqlite3_finalize(stmt);
		return a;
	}

	bool isFriend(std::string sender,std::string reciever)
	{
		const std::string query = "SELECT name FROM sqlite_master WHERE type='table' AND name='" + sender+"~"+reciever + "';";
		sqlite3_stmt* stmt;

		int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
		if (rc != SQLITE_OK) {
			//std::cerr << "Error preparing the statement: " << sqlite3_errmsg(db) << std::endl;
			return false;
		}

		rc = sqlite3_step(stmt);
		bool tableExists = rc == SQLITE_ROW;

		sqlite3_finalize(stmt);
		return tableExists;
	}

	std::string getName(std::string emails)
	{


	
		std::string name;
		std::string sqlquery = "SELECT * FROM users WHERE email ='"+emails+"';";

		const char* aquery = sqlquery.c_str();
		sqlite3_stmt* tmt;
		int rc = sqlite3_prepare_v2(db, aquery, -1, &tmt, nullptr);
		if (rc != SQLITE_OK)
		{

			throw Exception(sqlite3_errmsg(db));
			
		}
		while ((rc = sqlite3_step(tmt)) == SQLITE_ROW) {
			std::string s;
			s = reinterpret_cast<const char*>(sqlite3_column_text(tmt, 1));
			name = s;

		}

		if (rc != SQLITE_DONE) {
			throw Exception("No user with given email exist");
		}

		sqlite3_finalize(tmt);
		return name;
	}
	
	void queuemsg(std::string sender, std::string reciever, std::string msgs, std::string time)
	{
	
			std::string query = "CREATE TABLE IF NOT EXISTS `queuemsgs` (id INTEGER PRIMARY KEY, sender TEXT (60),reciever TEXT (60) , message TEXT (1000),time TEXT (60));";
			int rc = sqlite3_exec(db, query.c_str(), 0, 0, 0);
			if (rc != SQLITE_OK) {
				throw Exception("Error in opening table");
			}
	
		//std::ostringstream sql;
		std::string sql;
	

			sql = "INSERT INTO `queuemsgs` (sender, reciever, message, time) VALUES('" + sender + "', '" + reciever + "', '" + msgs + "', '" + time + "');";
		
		
		const char* insertSQL = sql.c_str();
		 rc = sqlite3_exec(db, insertSQL, 0, 0, 0);
		if (rc != SQLITE_OK) {
			throw Exception("Couldnot send message");
		}

	}


	void filterqueue()
	{

		Msg a;
		std::string sql;
		
		sql = "SELECT id,sender,reciever,message,time From `queuemsgs` ;";
		
		sqlite3_stmt* stmt;
		int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
		if (rc != SQLITE_OK) {
			throw Exception("Error occured");

		}

		while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
			std::string id = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
			std::string sender = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
	
			std::string reciever = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
			
			std::string message = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
			
			std::string time = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
			


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

				std::string query = "DELETE FROM `queuemsgs` WHERE id ='" + id + "';";
				int ac = sqlite3_exec(db, query.c_str(), 0, 0, 0);
				if (ac != SQLITE_OK) {
					throw Exception("Error in opening table");
				}
				sendmsg(sender, reciever, message, time);



			}



		}

		if (rc != SQLITE_DONE) {
			throw Exception("Couldnot fetch all messages");
		}

		sqlite3_finalize(stmt);
		


	}


	~Database()
	{
		sqlite3_close(db);
	}
};