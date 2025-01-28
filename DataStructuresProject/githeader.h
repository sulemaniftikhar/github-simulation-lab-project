#ifndef GITHEADER_H
#define GITHEADER_H

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <map>
#include <unordered_map>
#include <sstream>

using namespace std;

// Forward declarations
class Repository;
class User;
class Commit;
class File;

class User
{
private:
    string username;
    string password;

    // Adjacency list representation of the follower graph
    vector<string> followers;
    // for efficient searching
    unordered_map<string, vector<string> > followersMap;

    bool userExists( string &username)
    { // Changed to const method
        return followersMap.find(username) != followersMap.end();
    }

    void saveData()
    { // Changed to const method
        ofstream file("followers.csv");
        if (file.is_open())
        {
            for ( auto &pair : followersMap)
            {
                file << pair.first << ",";
                for ( auto &follower : pair.second)
                {
                    file << follower << ",";
                }
                file << endl;
            }
            file.close();
        }
        else
        {
            cout << "Error: Unable to open followers.csv" << endl;
        }
    }

public:
    User() : username(""), password("") {}

    User(string &username,string &password)
        : username(username), password(password) {}

    string getPassword()
    {
        return password;
    }

    string getUsername()
    {
        return username;
    }

    void setCurrentUser( string &username)
    {
        ofstream current("currentUser.csv");
        if (current.is_open())
        {
            current << username;
            current.close();
        }
        else
        {
            cout << "Error: Unable to open currentUser.csv" << endl;
        }
    }

    string getCurrentUser()
    {
        ifstream file("currentUser.csv");
        string user;
        file >> user;
        return user;
    }

    bool follow( string &userToFollow)
    {
        if (followersMap.empty())
        {
            cout << "No users exist!" << endl;
            return false;
        }
        if (userExists(userToFollow))
        {
            const string currentUser = getCurrentUser();
            // Check if the currentUser is already following userToFollow
            if (find(followersMap[userToFollow].begin(), followersMap[userToFollow].end(), currentUser) != followersMap[userToFollow].end())
            {
                cout << "You are already following " << userToFollow << "!" << endl;
                return false;
            }
            followersMap[userToFollow].push_back(currentUser);
            saveData();
            cout << "You are now following " << userToFollow << "!" << endl;
            return true;
        }
        cout << "User " << userToFollow << " doesn't exist!" << endl;
        return false;
    }

    bool unfollow( string &userToUnfollow)
    {
         string currentUser = getCurrentUser();
        if (currentUser != userToUnfollow)
        {
            auto it = followersMap.find(userToUnfollow);
            if (it != followersMap.end())
            {
                auto &followers = it->second;
                auto followerPos = find(followers.begin(), followers.end(), currentUser);
                if (followerPos != followers.end())
                {
                    followers.erase(followerPos);
                    saveData();
                    cout << "You have unfollowed " << userToUnfollow << "!" << endl;
                    return true;
                }
                else
                {
                    cout << "You are not following " << userToUnfollow << "!" << endl;
                    return false;
                }
            }
            else
            {
                cout << "User " << userToUnfollow << " doesn't exist!" << endl;
                return false;
            }
        }
        else
        {
            cout << "You cannot unfollow yourself!" << endl;
            return false;
        }
    }

    vector<string> loadFollowers( string &userName)
    { // Changed to const method
        vector<string> temp;
        ifstream file("followers.csv");
        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                stringstream ss(line);
                string user, follower;
                getline(ss, user, ',');
                if (userName == user)
                {
                    while (getline(ss, follower, ','))
                    {
                        temp.push_back(follower);
                    }
                    file.close();
                    return temp;
                }
            }
            file.close();
            cout << "User doesn't exist!" << endl;
        }
        else
        {
            cout << "Error: Unable to open followers.csv" << endl;
        }
        return temp;
    }

    unordered_map<string, vector<string> > loadUsersData()
    {
        ifstream file("users.csv");
        if (!file.is_open())
        {
            cout << "Error: Unable to open users.csv" << endl;
            return followersMap;
        }

        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string user;
            getline(ss, user, ',');
            vector<string> followersVector = loadFollowers(user);
            followersMap[user] = followersVector;
        }
        file.close();

        cout << "Loaded Data:" << endl;
        for (auto pair : followersMap)
        {
            cout << "User: " << pair.first << endl
                 << " Followers: ";
            for (auto follower : pair.second)
            {
                cout << follower << " , ";
            }
            cout << endl;
        }
        return followersMap;
    }
};

class UserRepository
{
private:
    unordered_map<string, User *> users;

public:
    UserRepository();
    ~UserRepository();

    User *registerUser(const string &username, const string &password);
    User *loginUser(const string &username, const string &password);
    void logoutUser(User *user);
    User *getUserByUsername(const string &username);
    void LoadData();
    void SaveData();
    void ProfileView(const string &username);
};
class Branch
{
public:
    string Filename;
    string FileData;
    int branchID;
    Branch *next;
    Branch(string Filename, string FileData)
        : Filename(Filename), FileData(FileData), next(nullptr){};

    Branch() {}
};

class Repo : public User
{
public:
    int id;
    string RepoName;
    string ownerName;
    bool isPublic;
    Repo *Contributors;
    Repo *next;
    Repo *commits;
    Repo *commitNext;
    int commitCount;
    string ReadmeFile;
    int ForkCount;
    string ForkOwner;

    Repo(string RepoName, bool isPublic)
    {
        srand(time(0));
        this->id = rand() % 100 + 1;
        this->RepoName = RepoName;
        this->isPublic = isPublic;
        this->commitNext = nullptr;
        this->commits = nullptr;
        this->commitCount = 0;
        this->ForkCount = 0;
        this->ForkOwner = "";
        this->ownerName = getUsername();
    }

    Repo() {}

    // Methods for Repo
    void CreateRepo(string RepoName, bool isPublic)
    {
        Repo(RepoName, isPublic);
    }
    void AddFileToBranch()
    {
    }
    void AddBranch()
    {
    }
    void DeleteFileToBrnach(int id)
    {
    }
    void deleteBranch()
    {
    }
    void Commit(string RepoNAme)
    {
    }
    void Fork(string RepoName)
    {
    }
};
class FileNode
{
public:
    string Filename;
    FileNode *next;
    FileNode(string Filename) : Filename(Filename), next(nullptr){};
};
class FileLinkedlist
{
    FileNode *head;
    FileLinkedlist() : head(nullptr){};

    void insertAtLast(string data)
    {

        FileNode *newNode = new FileNode(data);
        if (head == nullptr)
        {
            head = newNode;
        }
        else
        {
            FileNode *temp = head;
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void deleteFile(string name)
    {
        if (head == nullptr)
        {
            cout << "List is empty. Cannot delete." << endl;
            return;
        }

        FileNode *temp = head;
        FileNode *prev = nullptr;

        // If head node itself holds the key to be deleted
        if (temp != nullptr && temp->Filename == name)
        {
            head = temp->next;
            delete temp;
            cout << "File with name " << name << " deleted successfully." << endl;
            return;
        }

        // Search for the key to be deleted, keep track of the
        // previous node as we need to change 'prev->next'
        while (temp != nullptr && temp->Filename != name)
        {
            prev = temp;
            temp = temp->next;
        }

        // If key was not present in linked list
        if (temp == nullptr)
        {
            cout << "File with ID " << name << " not found in the list." << endl;
            return;
        }

        // Unlink the node from linked list
        prev->next = temp->next;
        delete temp;
        cout << "File with ID " << name << " deleted successfully." << endl;
    }

    void printFiles()
    {
        if (head == nullptr)
        {
            cout << "No files in the list." << endl;
            return;
        }

        FileNode *temp = head;
        cout << "Files in the list:" << endl;
        while (temp != nullptr)
        {
            cout << "File name: " << temp->Filename << ", File Name: " << temp->Filename << endl;
            temp = temp->next;
        }
    }
};

class CompleteRepoNode
{
public:
    Repo data;
    CompleteRepoNode *right;
    CompleteRepoNode *left;
    CompleteRepoNode(Repo data)
        : data(data), right(nullptr), left(nullptr){};
    int GetRootId()
    {
        return data.id;
    }
};

class BranchIngRepoTree
{
private:
    CompleteRepoNode *root;
    Branch *branch;

    CompleteRepoNode *insertMainBranch(CompleteRepoNode *root, Repo data)
    {
        // If the tree is empty, create a new node as root
        if (root == nullptr)
            return new CompleteRepoNode(data);

        // Otherwise, recur down the tree
        if (data.id < root->data.id)
            root->left = insertMainBranch(root->left, data);
        else if (data.id > root->data.id)
            root->right = insertMainBranch(root->right, data);

        // Return the unchanged node pointer
        return root;
    }

    CompleteRepoNode *insertSubbranches(CompleteRepoNode *root, Branch data)
    {

        // Otherwise, recur down the tree
        if (data.branchID < root->data.id)
            root->left = insertSubbranches(root->left, data);
        else if (data.branchID > root->data.id)
            root->right = insertSubbranches(root->right, data);

        // Return the unchanged node pointer
        return root;
    }

    CompleteRepoNode *searchByID(CompleteRepoNode *root, int id)
    {
        // Base cases: root is null or key is present at root
        if (root == nullptr || root->data.id == id)
            return root;

        // Key is greater than root's key
        if (root->data.id < id)
            return searchByID(root->right, id);

        // Key is smaller than root's key
        return searchByID(root->left, id);
    }

    void inorderTraversal(CompleteRepoNode *root)
    {
        if (root != nullptr)
        {
            inorderTraversal(root->left);
            cout << "ID: " << root->data.id << ", Repo Name: " << root->data.RepoName << endl;
            inorderTraversal(root->right);
        }
    }

public:
    BranchIngRepoTree()
        : root(nullptr) {}
    void insertRepo(Repo data, Branch sub)
    {
        if (root == nullptr)
        {
            root = insertMainBranch(root, data);
        }
        else
        {
            if (sub.branchID < root->GetRootId())
            {
                root->left = insertSubbranches(root, sub);
            }
            else if (sub.branchID > root->GetRootId())
            {
                root->right = insertSubbranches(root, sub);
            }
        }
    }
};

#endif