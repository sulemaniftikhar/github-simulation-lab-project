#include <iostream>
#include <string>
#include "githeader.h" // Assuming you have the header file named UserRepository.h

using namespace std;

UserRepository userRepository; // Instantiate UserRepository object globally

void displayUserPanel(const string &username)
{
    cout << "User Panel for " << username << endl;
    cout << "1. Create Repository" << endl;
    cout << "2. Commit Changes" << endl;
    cout << "3. Follow User" << endl;
    cout << "4. Contribute to Repository" << endl;
    cout << "5. Logout" << endl;
}

int main()
{
    userRepository.LoadData(); // Load user data from file or database

    int choice;
    do
    {
        cout << "GitHub Simulation" << endl;
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string username, password;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            User *newUser = userRepository.registerUser(username, password);
            if (newUser)
            {
                // Display user panel
                displayUserPanel(username);
                int userChoice;
                do
                {
                    cout << "Enter your choice: ";
                    cin >> userChoice;

                    switch (userChoice)
                    {
                    case 1:
                    {
                        cout << "Creating repository..." << endl;
                        // Call function to create repository
                        break;
                    }
                    case 2:
                    {
                        cout << "Committing changes..." << endl;
                        // Call function to commit changes
                        break;
                    }
                    case 3:
                    {
                        cout << "Following user..." << endl;
                        // Call function to follow user
                        break;
                    }
                    case 4:
                    {
                        cout << "Contributing to repository..." << endl;
                        // Call function to contribute to repository
                        break;
                    }
                    case 5:
                    {
                        userRepository.logoutUser(newUser);
                        break;
                    }
                    default:
                        cout << "Invalid choice." << endl;
                    }
                    // Add system cls or clear screen here for better readability
                } while (userChoice != 5);
            }
            break;
        }
        case 2:
        {
            string username, password;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            User *currentUser = userRepository.loginUser(username, password);
            if (currentUser)
            {
                // Display user panel
                displayUserPanel(username);
                int userChoice;
                do
                {
                    cout << "Enter your choice: ";
                    cin >> userChoice;

                    switch (userChoice)
                    {
                    case 1:
                    {
                        cout << "Creating repository..." << endl;
                        // Call function to create repository
                        break;
                    }
                    case 2:
                    {
                        cout << "Committing changes..." << endl;
                        // Call function to commit changes
                        break;
                    }
                    case 3:
                    {
                        cout << "Following user..." << endl;
                        // Call function to follow user
                        User *newUser = new User();
                        newUser->loadUsersData();

                        // newUser->loadUsersData();

                        newUser->unfollow("waleed");
                        newUser->follow("waleed");

                        break;
                    }
                    case 4:
                    {
                        cout << "Contributing to repository..." << endl;
                        // Call function to contribute to repository
                        break;
                    }
                    case 5:
                    {
                        userRepository.logoutUser(currentUser);
                        break;
                    }
                    default:
                        cout << "Invalid choice." << endl;
                    }
                    // Add system cls or clear screen here for better readability
                } while (userChoice != 5);
            }
            else
            {
                cout << "Invalid username or password." << endl;
            }
            break;
        }
        case 3:
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice." << endl;
        }
    } while (choice != 3);

    userRepository.SaveData(); // Save user data to file or database

    return 0;
}
