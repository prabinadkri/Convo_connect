
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "main.h"
//#include "bcrypt/bcrypt.h"
#include "./client.h"
using namespace std;

void User::HashPassword() {
   // Password = bcrypt::generateHash(Password);
}
void User::AddUser(){
    this->HashPassword();
    client.Signupreq(Name, email, Password, Username);
    //if (this->UserRole == "Admin")
    //    // SaveToFile("Admin.txt");
    //    SaveToFile("Admin.bin");

    //else if (this->UserRole == "User")

    //    SaveToFile("User.bin");
    // else{
    //     cout << "Invalid User Role" << endl;// Error throwing exception left
    //     return;
    //     }
}
User User::AuthenticateUser(string username_, string password_)
{
    User user;
    vector<User> users = User::ReadUserFile("Admin.txt");
    for (User user : users)
    {
        if(user.Password==Password){
         //if (bcrypt::validatePassword(password_,user.Password)) {
            if (user.Username == username_)
            {
                return user;
            }
        }
    }
    users = User::ReadUserFile("User.txt");
    for (User user : users)
    {
               if(user.Password==Password){

         //if (bcrypt::validatePassword(password_, user.Password)) {
            if (user.Username == username_)
            {
                return user;
            }
        }
        
    }
    User Nirajan ("Nirajan","nirajansah1111@gmail.com","User","nirajan11", "123456789",19);
  
    return Nirajan;
}
void User::SaveToFile(string filename)
{
    ofstream file(filename, ios::app | ios::binary);
    if (!file)
    {
        cout << "Error opening file" << endl;
        return;
    }

    string::size_type nameSize = Name.size();
    file.write(reinterpret_cast<const char *>(&nameSize), sizeof(nameSize));
    file.write(reinterpret_cast<const char *>(&Name[0]), nameSize);

    string::size_type emailSize = email.size();
    file.write(reinterpret_cast<const char *>(&emailSize), sizeof(emailSize));
    file.write(reinterpret_cast<const char *>(&email[0]), emailSize);

    string::size_type userRoleSize = UserRole.size();
    file.write(reinterpret_cast<const char *>(&userRoleSize), sizeof(userRoleSize));
    file.write(reinterpret_cast<const char *>(&UserRole[0]), userRoleSize);

    string::size_type usernameSize = Username.size();
    file.write(reinterpret_cast<const char *>(&usernameSize), sizeof(usernameSize));
    file.write(reinterpret_cast<const char *>(&Username[0]), usernameSize);

    string::size_type passwordSize = Password.size();
    file.write(reinterpret_cast<const char *>(&passwordSize), sizeof(passwordSize));
    file.write(reinterpret_cast<const char *>(&Password[0]), passwordSize);

    file.close();
}
// void User:: SaveToFile(string filename){
//         std::fstream userfile;
//         userfile.open(filename,  std::ios::app);
//         if (!userfile.is_open())
//         {
//             cout<<"Error: Could not open"<<endl;
//         }
//         userfile.open(filename, std::ios::app);
//         userfile.write((char *)this, sizeof(User));
// }

vector<User> User::ReadUserFile(string filename)
{
    vector<User> users;
    ifstream file(filename, ios::binary);
    if (!file)
    {
        cout << "Error opening file" << endl;
        return users;
    }

    while (file.peek() != EOF)
    {
        User user;
        user.deserialize(file);
        users.push_back(user);
    }

    file.close();
    return users;
}

bool User::IsEmpty()
{
    if (this->Name.length() != 0)
        return false;
    return true;
}