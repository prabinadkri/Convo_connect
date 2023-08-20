#pragma warning(disable: 4996)
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

#include <vector>
using namespace std;


class Person
{
protected:
    string Name;
    string Username;
    string Password;
    string email;
    string UserRole;
    int age;
    public:
    Person (){}
    Person(string name_, string email_, string userRole_, string username_, string password_, int age_) {
    Name = name_;
    age = age_;
    UserRole = userRole_;
    email = email_;
    Username = username_;
    Password = password_;
}

};

class User : public Person
{
private:


public:
    User():Person(){}
    User(string name_, string email_, string userRole_, string username_, string password_, int age_): Person(name_, email_, userRole_, username_, password_,age_) {}
    void HashPassword();
    void AddUser();
    User AuthenticateUser(string username, string password);
    void SaveToFile(string filename);
    static vector<User> ReadUserFile(string filename);
    bool IsEmpty();
    void serializeString(ofstream& file, const string& data) ;

    string getUsername()
    {
        return Person::Username;
    }


private:

    void deserialize(ifstream &file)
    {
        // Read and extract each attribute from the file
        string::size_type nameSize;
        file.read(reinterpret_cast<char *>(&nameSize), sizeof(nameSize));
        Name.resize(nameSize);
        file.read(reinterpret_cast<char *>(&Name[0]), nameSize);

        string::size_type emailSize;
        file.read(reinterpret_cast<char *>(&emailSize), sizeof(emailSize));
        email.resize(emailSize);
        file.read(reinterpret_cast<char *>(&email[0]), emailSize);

        string::size_type userRoleSize;
        file.read(reinterpret_cast<char *>(&userRoleSize), sizeof(userRoleSize));
        UserRole.resize(userRoleSize);
        file.read(reinterpret_cast<char *>(&UserRole[0]), userRoleSize);

        string::size_type usernameSize;
        file.read(reinterpret_cast<char *>(&usernameSize), sizeof(usernameSize));
        Username.resize(usernameSize);
        file.read(reinterpret_cast<char *>(&Username[0]), usernameSize);

        string::size_type passwordSize;
        file.read(reinterpret_cast<char *>(&passwordSize), sizeof(passwordSize));
        Password.resize(passwordSize);
        file.read(reinterpret_cast<char *>(&Password[0]), passwordSize);
    }

};