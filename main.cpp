
#include <iostream>
#include <string>
#include "GithubHeader.h"
#include"SocialFeature.h"
using namespace std;

UserRepository userRepository; // Instantiate UserRepository object globally

void displayUserPanel(const string& username) {
    cout << "User Panel for " << username << endl;
    cout << "1. Create Repo" << endl;
    cout << "2. View Repo" << endl;
    cout << "3. Search All Repo" << endl;
    cout << "4. Commit on Repo" << endl;
    cout << "5. Fork on Repo" << endl;
    cout << "6. Add File To Branch If you already Forked " << endl;
    cout << "7. Add File to Repo" << endl;
    cout << "8. Delete Repo" << endl;
    cout << "9. Delete Branch" << endl;
    cout << "10. Delete Files" << endl;
    cout << "11. Display Repo Stats" << endl;
    cout << "12. Update Content of Files " << endl;
    cout << "13. Follow a person " << endl;
    cout << "14. Logout" << endl;
}

int main(int argc, char* argv[])
{
    userRepository.LoadData(); // Load user data from file or database
    int userChoice;
    BinaryTreeRepo newrepo;
    int choice;
    string currentUser; // To store the username of the current user
    User* loggedInUser = nullptr; // To store the pointer to the logged-in user

    do {
        cout << "GitHub Simulation" << endl;
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string username, password;
            cout << "Enter username: ";
            cin.ignore();
            getline(cin, username);
            cout << "Enter password: ";
            getline(cin, password);
            User* newUser = userRepository.registerUser(username, password);
            if (newUser) {
                cout << "User registered successfully!" << endl;
                currentUser = username; // Store the username of the registered user
                loggedInUser = newUser; // Set the logged-in user to the newly registered user
                displayUserPanel(currentUser); // Display user panel with menu options
            }
            else {
                cout << "Registration failed. Username already exists." << endl;
            }
        }
        else if (choice == 2) {
            string username, password;
            cout << "Enter username: ";
            cin.ignore();
            getline(cin, username);
            cout << "Enter password: ";
            getline(cin, password);
            loggedInUser = userRepository.loginUser(username, password);
            if (loggedInUser) {
                currentUser = username; // Store the username of the logged-in user
                cout << "Login successful!" << endl;
                displayUserPanel(currentUser); // Display user panel with menu options
            }
            else {
                cout << "Login failed. Invalid username or password." << endl;
            }
        }
        else if (choice == 3) {
            cout << "Exiting program." << endl;
            break;
        }
        else {
            cout << "Invalid choice." << endl;
        }

        if (loggedInUser) {
            

            do {
                cout << "Enter your choice: ";
                cin >> userChoice;

                if (userChoice == 1) {
                    // Code for creating a new repository
                    string repoName;
                    bool isPublic;
                    string person = currentUser;
                    cout << "Enter Repository Name: ";
                    cin.ignore(); // Ignore the newline character in the buffer
                    getline(cin, repoName);

                    cout << "Is Repository Public? (1 for Yes, 0 for No): ";
                    cin >> isPublic;

                    // Create a new repository
                    Repo* newRepo = new Repo(repoName, isPublic, person);

                    newrepo.insertRepo(newRepo);
                    cout << "Repository created successfully:" << endl;
                    cout << "Repository Name: " << newRepo->RepoName << endl;
                    cout << "Owner Name: " << newRepo->ownerName << endl;
                    cout << "Is Public: " << (newRepo->isPublic ? "Yes" : "No") << endl;

                    // Clean up memory allocated for newRepo
                    ofstream outFile("AllRepos.csv", ios::app);
                    if (outFile.is_open()) {
                        outFile << "Repository ID: " << newRepo->id << endl;
                        outFile << "Repository Name: " << newRepo->RepoName << endl;
                        outFile << "Owner Name: " << newRepo->ownerName << endl;
                        outFile << "Is Public: " << (newRepo->isPublic ? "Yes" : "No") << endl;
                        outFile << "Fork Count: " << newRepo->ForkCount << endl;
                        outFile << "Fork Owner: " << newRepo->ForkOwner << endl;
                        outFile << "Commit Count: " << newRepo->commitCount << endl;
                        outFile << endl;
                        outFile << endl;
                        // Add more details as needed
                        outFile.close();
                        cout << "Repo details written to file." << endl;
                    }
                    else {
                        cout << "Error: Unable to open file." << endl;
                    }

                    ofstream newFile("LoadRepos.txt", ios::app);
                    if (newFile.is_open()) {
                        newFile << newRepo->id << " ";
                        newFile << newRepo->RepoName << " ";
                        newFile << newRepo->ownerName << " ";
                        newFile << (newRepo->isPublic ? "Yes" : "No") << " ";
                        newFile << newRepo->ForkCount << " ";
                        newFile << newRepo->ForkOwner << " ";
                        newFile << newRepo->commitCount << " ";
                        newFile << endl;
                        newFile << endl;
                        cout << endl;
                        // Write other details as needed
                        newFile.close();
                    }
                }
                else if (userChoice == 2) {
                    // Code for viewing a repository
                    int id;
                    cout << "Enter Repo ID : ";
                    cin >> id;
                    newrepo.SeeRepo(id);
                    cout << "Viewing repository..." << endl;
                }
                else if (userChoice == 3) {
                    // Code for searching all repositories
                    newrepo.displayAllRepos();
                    cout << "View all repositories..." << endl;
                }
                else if (userChoice == 4) {
                    int repoID = 0;
                    string branchOwner, branchID;
                    cout << "Enter the Repo ID where you want to commit : ";
                    cin >> repoID;
                    branchOwner = currentUser;
                    //cout << "Enter the Branch Owner: ";
                    cin.ignore();
                    //getline(cin, branchOwner);
                    cout << "Enter Branch ID: ";
                    getline(cin, branchID);

                    Repo* repo = newrepo.searchRepo(repoID);
                    if (repo) {
                        BranchNode* branch = repo->searchBranch(branchID, branchOwner);
                        if (branch) {
                            // Branch found, allow file insertion
                            cout << "Inititated Pull Requests For Your Files " << endl;
                            cout << "Congratualtion Commit is inititated : Now Enter Files in Your Branch " << endl;
                            string filename, fileContent;
                            cout << "Enter file name: ";
                            getline(cin, filename);
                            cout << "Enter file content: ";
                            getline(cin, fileContent);

                            string fileID = repo->generateUniqueFileID();
                            File file(filename, fileContent, fileID, currentUser);
                            branch->newfiles.insertAtLast(file);

                            cout << "File inserted successfully into Branch." << endl;
                            branch->newfiles.displayAllFiles();
                        }
                        else {
                            // Branch not found
                            cout << "Branch not found." << endl;
                        }
                    }
                    else {
                        // Repository not found
                        cout << "Repository with ID " << repoID << " not found." << endl;
                    }
                    cout << "Committing changes..." << endl;
                }
                else if (userChoice == 5) {
                    int RepoID = 0;
                    cout << "Enter the Repo ID you want to Fork: ";
                    cin >> RepoID;
                    Repo* repo = newrepo.searchRepo(RepoID);
                    if (repo) {
                        if (repo->ownerName == currentUser) {
                            cout << "You are the owner of this Repo. You can directly insert Files." << endl;
                        }
                        else {
                            string BranchID = repo->generateUniqueBranchID();
                            string BranchOwner = currentUser;

                            Branch B1(BranchOwner, BranchID, repo->id, repo->RepoName, repo->ownerName, repo->isPublic);
                            repo->newBranches.insertBranch(B1);
                            cout << "Congratulations! Fork successful. Branch has been created. Now you can insert Files." << endl;

                            cout << "Branch Added Successfully." << endl;
                            repo->newBranches.displayBranches();
                            ofstream FileSave;
                            FileSave.open("branches.csv", ios::app);
                            if (FileSave.is_open()) {
                                FileSave << "Branch ID: " << B1.BranchID << endl;
                                FileSave << "Branch Owner: " << B1.branchOwner << endl;
                                
                                // Add more data fields as needed
                            }

                            else {
                                cout << "File not opened ";
                            }
                            char choice;
                            cout << "Do you want to insert Files in this Branch? (y/n): ";
                            cin >> choice;
                            if (choice == 'y' || choice == 'Y') {
                                // Code for inserting files into the branch
                                string filename, fileContent;
                                cout << "Enter file name: ";
                                cin.ignore();
                                getline(cin, filename);
                                cout << "Enter file content: ";
                                getline(cin, fileContent);

                                string fileID = repo->generateUniqueFileID();
                                File file(filename, fileContent, fileID, currentUser);
                                BranchNode* branch = repo->newBranches.searchBranch(BranchID, BranchOwner);
                                if (branch) {
                                    branch->newfiles.insertAtLast(file);
                                    cout << "File inserted successfully into Branch." << endl;
                                    branch->newfiles.displayAllFiles();

                                }
                                else {
                                    cout << "Error: Branch not found." << endl;
                                }
                            }
                        }
                    }
                    else {
                        cout << "Repository with ID " << RepoID << " not found." << endl;
                    }
                }
                if (userChoice == 6) {
                    int repoID = 0;
                    string branchOwner, branchID;
                    cout << "Enter the Repo ID: ";
                    cin >> repoID;
                    branchOwner = currentUser;
                    //cout << "Enter the Branch Owner: ";
                    cin.ignore();
                    //getline(cin, branchOwner);
                    cout << "Enter Branch ID: ";
                    getline(cin, branchID);

                    Repo* repo = newrepo.searchRepo(repoID);
                    if (repo) {
                        BranchNode* branch = repo->searchBranch(branchID, branchOwner);
                        if (branch) {
                            // Branch found, allow file insertion
                            string filename, fileContent;
                            cout << "Enter file name: ";
                            getline(cin, filename);
                            cout << "Enter file content: ";
                            getline(cin, fileContent);

                            string fileID = repo->generateUniqueFileID();
                            File file(filename, fileContent, fileID, currentUser);
                            branch->newfiles.insertAtLast(file);

                            cout << "File inserted successfully into Branch." << endl;
                            branch->newfiles.displayAllFiles();
                        }
                        else {
                            // Branch not found
                            cout << "Branch not found." << endl;
                        }
                    }
                    else {
                        // Repository not found
                        cout << "Repository with ID " << repoID << " not found." << endl;
                    }
                }

                else if (userChoice == 7) {
                    // Prompt the user for the repository ID
                    cin.ignore();
                    int repoID;
                    cout << "Enter the repository ID: ";
                    cin >> repoID;

                    // Search for the repository by ID
                    Repo* repo = newrepo.searchRepo(repoID);
                    if (repo) {
                        cout << "Repository found. Adding files..." << endl;

                        // Add 5 different files to the repository
                        for (int i = 0; i < 5; ++i) {
                            // Generate unique file ID
                            string fileID = repo->generateUniqueFileID();

                            // Prompt user for file details
                            string filename, fileContent;
                            cout << "Enter file name for File " << i + 1 << ": ";
                            //cin.ignore();
                            getline(cin, filename);
                            cout << "Enter file content for File " << i + 1 << ": ";
                            //cin.ignore();
                            getline(cin, fileContent);

                            // Create the file object
                            File file(filename, fileContent, fileID, repo->ownerName);
                            //cin.ignore();
                            // Insert the file into the repository's file linked list
                            repo->newfiles.insertAtLast(file);
                        }

                        // Display all files in the repository
                        // You need to implement a function to display files in FileLinkedList
                        cout << "Files added to repository:" << endl;
                        //repo->files.displayFiles(); // Implement this function
                        repo->newfiles.displayAllFiles();
                    }
                    else {
                        cout << "Repository with ID " << repoID << " not found." << endl;
                    }
                    // Code for adding file to branch based on id
                    cout << "Adding file to Repo on id..." << endl;
                }
                else if (userChoice == 8) {
                    // Code for deleting repository
                    cin.ignore();
                    int newid = 0;
                    //cout << newrepo.getroot() << newrepo.getrootleft() << newrepo.getrootright() << endl;
                    cout << "Enter Your Repo ID : " << endl;
                    cin >> newid;
                    //cout << newrepo.getroot() << "  " << newrepo.getrootleft() << "  " << newrepo.getrootright() << endl;
                    newrepo.deleterepo(newid);
                    cout << "Deleting repository..." << endl;
                }
                else if (userChoice == 9) {
                    // Code for deleting branch
                    cout << "Deleting branch..." << endl;
                }
                else if (userChoice == 10) {
                    int repoId = 0;
                    cout << "Enter the Repo where File is located  ID : ";
                    cin >> repoId;
                    string FileID;
                    cout << "Enter the File ID : " << endl;
                    cin >> FileID;
                    Repo* repo = newrepo.searchRepo(repoId);
                    if (repo) {
                        cout << "Repo Found .... Searching For File : " << endl;
                        repo->newfiles.deleteFile(FileID);
                    }
                    cout << "Deleting files..." << endl;
                }
                else if (userChoice == 11) {
                    int id;
                    cout << "Enter Repo ID : ";
                    cin >> id;
                    newrepo.SeeRepo(id);
                    cout << "Viewing repository... stats of ID : " << id << endl;
                    // Code for displaying repository stats
                    cout << "Displaying repository stats..." << endl;
                }
                else if (userChoice == 12) {
                    int repoId = 0;
                    cout << "Enter Repo ID where File is Located " << endl;
                    cin >> repoId;
                    string FileId;
                    cout << "Enter the File Id you wanna update : " << endl;
                    cin >> FileId;
                    string content;
                    cout << "Enter the Updated Content of FIle " << endl;
                    cin.ignore();
                    getline(cin, content);
                    Repo* repo = newrepo.searchRepo(repoId);
                    if (repo) {
                        cout << "Repo Found .... Searching For File : " << endl;
                        repo->newfiles.update(FileId, content);
                    }
                }
                else if (userChoice == 13) {
                    SocialFeature F1;
                    string f1;
                    cout << "enter your name " << endl;
                    cin >> f1;
                    string f2;
                    cout << "Enter the name of person you want to follow ";
                    cin >> f2;
                    F1.follow(f1, f2);
                }
                else if (userChoice == 14) {

                    cout << "Logging out..." << endl;
                    loggedInUser = nullptr; // Set the logged-in user to null to log out
                }
                else {
                    cout << "Invalid choice." << endl;
                }
            } while (userChoice != 13);
        }
    } while (choice != 3);

    userRepository.SaveData(); // Save user data to file or database
    system("pause");
    return 0;
}
