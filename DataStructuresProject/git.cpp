#include "githeader.h"

// UserRepository Implementation
UserRepository::UserRepository()
{
    LoadData();
}
UserRepository::~UserRepository()
{               // To destroy whole database of github
    SaveData(); // Save user data to file when UserRepository is destroyed
    // Deallocate memory for user objects
    for (auto &pair : users)
    {
        delete pair.second;
    }
    users.clear();
}

User *UserRepository::registerUser(const string &username, const string &password)
{
    if (users.find(username) == users.end())
    {
        User *newUser = new User(username, password);
        users[username] = newUser;
        SaveData(); // Save updated user data to file
        return newUser;
    }
    else
    {
        cout << "Username already exists. Please choose a different username." << endl;
        return nullptr;
    }
}

User *UserRepository::loginUser(const string &username, const string &password)
{
    auto it = users.find(username);
    if (it != users.end() && it->second->getPassword() == password)
    {
        User *temp;
        temp->setCurrentUser(username);
        return it->second;
    }
    else
    {
        cout << "Invalid username or password." << endl;
        return nullptr;
    }
}

void UserRepository::logoutUser(User *user)
{
    // Implementation
}
void UserRepository::LoadData()
{
    ifstream file;
    file.open("users.csv");
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string username, password;
            getline(ss, username, ',');
            getline(ss, password);
            // Check if the username already exists in memory
            users[username] = new User(username, password);
        }
        file.close();
    }
};
void UserRepository::SaveData()
{
    ofstream file;
    file.open("users.csv");
    if (file.is_open())
    {
        for (auto &pair : users)
        {
            file << pair.first << "," << pair.second->getPassword() << endl;
        }
        file.close();
    }

    // ya code na pagal kr diya tha

    // // add in followers file
    // file.open("followers.csv");
    // if (file.is_open())
    // {
    //     for (auto &pair : users)
    //     {
    //         file << pair.first << "," << endl;
    //     }
    //     file.close();
    // }
};
void UserRepository::ProfileView(const string &username)
{
    auto it = users.find(username);
    if (it != users.end())
    {
        User *user = it->second;
        // Display user profile details
        cout << "Username: " << user->getUsername() << endl;
        // Other profile details...
    }
    else
    {
        cout << "User not found." << endl;
    }
}

User *UserRepository::getUserByUsername(const string &username)
{
    auto it = users.find(username);
    if (it != users.end())
    {
        return it->second;
    }
    else
    {
        cout << "User not found." << endl;
        return nullptr;
    }
}