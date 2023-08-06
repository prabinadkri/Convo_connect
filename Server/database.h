#include <sqlite3.h>
#include<iostream>
#include<sstream>
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
	void signup(std::string name, std::string email, std::string password)
	{
		const char* createTableSQL = "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, name TEXT (30),email TEXT (40) UNIQUE, password TEXT (255));";
		int rc = sqlite3_exec(db, createTableSQL, 0, 0, 0);
		if (rc != SQLITE_OK) {
			throw Exception("Error in opening table");
		}
		//std::ostringstream sql;
		std::string sql = "INSERT INTO `users` (name, email, password) VALUES ('" + name + "', '" + email + "','" + password + "');";

		const char* insertSQL = sql.c_str();
		rc = sqlite3_exec(db, insertSQL, 0, 0, 0);
		if (rc != SQLITE_OK) {
			throw Exception("User already exists");
		}
		

	}
	void login(std::string email,std::string password)
	{
		std::ostringstream sqlquery;
		sqlquery << "SELECT * FROM users WHERE email = '" << email << "' AND password = '"<<password<<"';";

		const char* query = sqlquery.str().c_str();
		sqlite3_stmt* stmt;
		int rc = sqlite3_prepare_v2(db, query, -1, &stmt, nullptr);
		if (!SQLITE_OK)
		{
			throw Exception("Internal Server error");
		}
		int count = 0;
		if (sqlite3_step(stmt) == SQLITE_ROW)
		{
			count = sqlite3_column_int(stmt, 0);
		}
		if (count == 0)
		{
			throw Exception("User not found");
		}
		sqlite3_finalize(stmt);
		
	}
	bool fetchfriends()
	{

	}
	bool sendmsg()
	{

	}
	bool fetchmsg()
	{

	}
	~Database()
	{
		sqlite3_close(db);
	}
};