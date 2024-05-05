#pragma 

#ifndef GITHUBHEADER_H
#define GITHUBHEADER_H
#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>
#include<vector>
#include<Windows.h>
#include<map>
#include<unordered_map>
#include<unordered_set>
#include<sstream>
using namespace std;

// Forward declarations
class Repository;
class User;
class Commit;
class File;
class User {
public:
    string username;
    string password;
    User() {};
    User( const string& username, const string& password) :username(username), password(password) {};

    string getPassword() {
        return this->password;
    }
    string getUsername() {
        return this->username;
    }
};
class UserRepository {
private:
    unordered_map<string, User*> users; // Hash table to store users
public:
    UserRepository();
    ~UserRepository();

    User* registerUser(const string& username, const string& password);
    User* loginUser(const string& username, const string& password);
    void logoutUser(User* user);
    User* getUserByUsername(const string& username);
    void LoadData();
    void SaveData();
    void ProfileView(const string& username);
};

class File {
public:
    string filename;
    string fileContent;
    string fileID;
    string fileOwner;
    // Constructor
    File(string filename, string fileContent, string fileID, string fileOwner)
        : filename(filename), fileContent(fileContent), fileID(fileID), fileOwner(fileOwner) {}
};
class NodeFile {
public:
    File file;
    NodeFile* next;
    NodeFile(File file) :file(file), next(nullptr) {};
};
class FileLinkedList {
private:
    NodeFile* root;

public:
    FileLinkedList() : root(nullptr) {}
    NodeFile* getHead() {
        return root;
    }
    void insertAtLast(const File& file) {
        NodeFile* newNode = new NodeFile(file);

        if (root == nullptr) {
            root = newNode;
        }
        else {
            NodeFile* temp = root;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        cout << "File '" << file.filename << "' inserted successfully." << endl;
    }

    void deleteFile(const string& fileID) {
        if (root == nullptr) {
            cout << "File with ID '" << fileID << "' not found. Deletion unsuccessful." << endl;
            return;
        }

        if (root->file.fileID == fileID) {
            NodeFile* temp = root;
            root = root->next;
            delete temp;
            cout << "File with ID '" << fileID << "' deleted successfully." << endl;
            return;
        }

        NodeFile* current = root;
        NodeFile* prev = nullptr;

        while (current != nullptr && current->file.fileID != fileID) {
            prev = current;
            current = current->next;
        }

        if (current == nullptr) {
            cout << "File with ID '" << fileID << "' not found. Deletion unsuccessful." << endl;
            return;
        }

        if (prev != nullptr && current != nullptr) {
            prev->next = current->next;
            delete current;
            cout << "File with ID '" << fileID << "' deleted successfully." << endl;
        }
        else {
            // Handle the case when either prev or current is null
            cout << "Error: One of the pointers is null." << endl;
        }

        
    }

    void update(const string& fileID, const string& newContent) {
        NodeFile* temp = root;

        while (temp != nullptr && temp->file.fileID != fileID) {
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "File with ID '" << fileID << "' not found. Update unsuccessful." << endl;
        }
        else {
            temp->file.fileContent = newContent;
            cout << "File with ID '" << fileID << "' updated successfully." << endl;
        }
    }

    void searchFile(const string& fileID) {
        NodeFile* temp = root;

        while (temp != nullptr && temp->file.fileID != fileID) {
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "File with ID '" << fileID << "' not found." << endl;
        }
        else {
            cout << "File Found:" << endl;
            cout << "Filename: " << temp->file.filename << endl;
            cout << "Content: " << temp->file.fileContent << endl;
            cout << "Owner: " << temp->file.fileOwner << endl;
        }
    }

    void displayAllFiles() {
        NodeFile* current = root;

        // Traverse the linked list and print details of each file
        while (current != nullptr) {
            cout << "File ID: " << current->file.fileID << endl;
            cout << "File Name: " << current->file.filename << endl;
            cout << "File Content: " << current->file.fileContent << endl;
            cout << "File Owner: " << current->file.fileOwner << endl;
            cout << endl;

            // Move to the next node
            current = current->next;
        }
    }
};

class Branch {
public:
    string branchOwner;
    int repoId;
    string RepoName;
    string RepoownerName;
    bool isPublic;
    string BranchID;
    Branch(string branchOwner,string BranchID, int repoId, string RepoName, string ownerName, bool isPublic)
        : branchOwner(branchOwner),BranchID(BranchID), repoId(repoId), RepoName(RepoName), RepoownerName(ownerName), isPublic(isPublic) {}

};
class BranchNode {
public:
    Branch Data;
    BranchNode* next;
    FileLinkedList newfiles;
    BranchNode(Branch data) :Data(data), next(nullptr) {};
};
class BranchLinkedList {
public:
    BranchNode* head;

    BranchLinkedList() : head(nullptr) {}
    BranchNode* getHeadBranch() {
        return head;
    }
    // Function to insert a branch at the end of the list
    void insertBranch(Branch branch) {
        BranchNode* newNode = new BranchNode(branch);
        if (!head) {
            head = newNode;
        }
        else {
            BranchNode* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    // Function to delete a branch by repo ID
   // Function to delete a branch by branch ID and owner name
    void deleteBranch(const string& branchID, const string& branchOwner) {
        if (!head) {
            cout << "Branch list is empty." << endl;
            return;
        }

        // Check if the head node matches the branch ID and owner name
        if (head->Data.BranchID == branchID || head->Data.branchOwner == branchOwner) {
            BranchNode* temp = head;
            head = head->next;
            delete temp;
            cout << "Branch with ID " << branchID << " and owner " << branchOwner << " deleted successfully." << endl;
            return;
        }

        // Search for the branch with the given branch ID and owner name
        BranchNode* prev = head;
        BranchNode* current = head->next;
        while (current) {
            if (current->Data.BranchID == branchID && current->Data.branchOwner == branchOwner) {
                prev->next = current->next;
                delete current;
                cout << "Branch with ID " << branchID << " and owner " << branchOwner << " deleted successfully." << endl;
                return;
            }
            prev = current;
            current = current->next;
        }

        cout << "Branch with ID " << branchID << " and owner " << branchOwner << " not found." << endl;
    }

    // Function to search for a branch by branch ID and owner name
    BranchNode* searchBranch(const string& branchID, const string& branchOwner) {
        BranchNode* current = head;
        while (current) {
            if (current->Data.BranchID == branchID || current->Data.branchOwner == branchOwner) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }


    // Function to display all branches
    void displayBranches() {
        BranchNode* current = head;
        if (!current) {
            cout << "Branch list is empty." << endl;
            return;
        }
        cout << "Branches:" << endl;
        while (current) {
            cout << "Branch Owner: " << current->Data.branchOwner << endl;
            cout << "Branch ID Is:  " << current->Data.BranchID << endl;
            cout << "Repo ID: " << current->Data.repoId << endl;
            cout << "Repo Name: " << current->Data.RepoName << endl;
            cout << "Repo Owner: " << current->Data.RepoownerName << endl;
            cout << "Is Public: " << (current->Data.isPublic ? "Yes" : "No") << endl;
            cout << endl;
            current = current->next;
        }
    }
};

class Repo : public User{
public:
    int id;
    string RepoName;
    string ownerName;
    bool isPublic;
    Repo* left;
    Repo* right;
    Repo* commits;
    Repo* commitNext;
    //BranchNode* branches; // Head of the branch linked list
    NodeFile* files; // Head of the file linked list
    int commitCount;
    int ForkCount;
    string ForkOwner;
    FileLinkedList newfiles;
    BranchLinkedList newBranches;
    Repo(string RepoName,bool isPublic,string ownerName) {
        srand(time(0));
        this->id = generateUniqueID();
        this->RepoName = RepoName;
        this->isPublic = isPublic;
        this->commitNext = nullptr;
        this->commits = nullptr;
        this->commitCount = 0;
        this->ForkCount = 0;
        this->ForkOwner = " ";
        // Set owner name when creating the repository
        this->ownerName =ownerName; // Assuming getUsername() returns the current user's name
        left = nullptr;
        right = nullptr;
    }
    string generateUniqueFileID() {
        static unordered_set<string> usedFileIDs;
        string newFileID;
        do {
            newFileID = to_string(rand() % 1000 + 1); // Generate a random ID
        } while (usedFileIDs.count(newFileID) > 0); // Keep generating until a unique ID is found
        usedFileIDs.insert(newFileID); // Insert the new ID into the set of used IDs
        return newFileID;
    }
    string generateUniqueBranchID() {
        static unordered_set<string> usedFileIDs;
        string newBranchID;
        do {
            newBranchID = to_string(rand() % 1000 + 1); // Generate a random ID
        } while (usedFileIDs.count(newBranchID) > 0); // Keep generating until a unique ID is found
        usedFileIDs.insert(newBranchID); // Insert the new ID into the set of used IDs
        return newBranchID;
    }
    BranchNode* searchBranch(const string& branchID, const string& branchOwner) {
        // Start with the head of the branch linked list
        BranchNode* current = this->newBranches.head;

        while (current) {
            if (current->Data.BranchID == branchID && current->Data.branchOwner == branchOwner) {
                return current; // Found the branch
            }
            current = current->next; // Move to the next branch
        }

        return nullptr; // Branch not found
    }


private:
    int generateUniqueID() {
        static unordered_set<int> usedIDs;
        int newID;
        do {
            newID = rand() % 100 + 1;
        } while (usedIDs.count(newID) > 0);
        usedIDs.insert(newID);
        return newID;
    }
};
class BinaryTreeRepo {
private:
    Repo* root;
    
    Repo* insertRepo(Repo* root, Repo* newNode) {
        if (root == nullptr) {
            root = newNode;
        }
        else {
            if (newNode->id < root->id) {
                root->left = insertRepo(root->left, newNode);
            }
            else {
                root->right = insertRepo(root->right, newNode);
            }
        }
        cout << "Treee insertion successfull" << endl;
        return root;
    }

    Repo* findMin(Repo* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

   

    Repo* deleteRepo(Repo* root, int id) {
        if (root == nullptr) {
            cout << "Repository with ID " << id << " not found. Deletion unsuccessful." << endl;
            return root;
        }

        if (id < root->id) {
            root->left = deleteRepo(root->left, id);
        }
        else if (id > root->id) {
            root->right = deleteRepo(root->right, id);
        }
        else {
            if (root->left == nullptr) {
                Repo* temp = root->right;
                delete root;
                cout << "Repository with ID " << id << " deleted successfully." << endl;
                return temp;
            }
            else if (root->right == nullptr) {
                Repo* temp = root->left;
                delete root;
                cout << "Repository with ID " << id << " deleted successfully." << endl;
                return temp;
            }
            // Node with two children
            Repo* temp = root->right;
            if (temp != nullptr) {
                while (temp->left != nullptr) {
                    temp = temp->left;
                }
                // Copy the minimum value to the current node
                root->id = temp->id;
                // Delete the minimum value node from the right subtree
                root->right = deleteRepo(root->right, temp->id);
            }
        }
        return root;
    }





    void loadRepo(BinaryTreeRepo& binaryTree, const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Unable to open file '" << filename << "'." << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            vector<string> tokens;
            string token;
            while (getline(ss, token, ',')) {
                tokens.push_back(token);
            }

            if (tokens.size() != 3) {
                cout << "Error: Invalid data format in file '" << filename << "'." << endl;
                continue;
            }

            string repoName = tokens[0];
            bool isPublic = (tokens[1] == "true");
            string ownerName = tokens[2];

            Repo* newRepo = new Repo(repoName, isPublic, ownerName);
            binaryTree.insertRepo(newRepo);
        }

        file.close();
    }



    Repo* searchRepo(Repo* root, int id) {
        if (root == nullptr || root->id == id) {
            return root;
        }

        if (id < root->id) {
            return searchRepo(root->left, id);
        }
        return searchRepo(root->right, id);
    }
    void displayRepoById(Repo* root, int id) {
        Repo* foundRepo = searchRepo(root, id);
        if (foundRepo != nullptr) {
            cout << "Repository Details:" << endl;
            cout << "ID: " << foundRepo->id << endl;
            cout << "Repository Name: " << foundRepo->RepoName << endl;
            cout << "Owner Name: " << foundRepo->ownerName << endl;
            cout << "Is Public: " << (foundRepo->isPublic ? "Yes" : "No") << endl;
            cout << "Fork Count: " << foundRepo->ForkCount << endl;
            cout << "Fork Owner: " << foundRepo->ForkOwner << endl;
            cout << "Commit Count: " << foundRepo->commitCount << endl;

            // Display files associated with the repository
            cout << "Files in Repository:" << endl;
            NodeFile* current = foundRepo->newfiles.getHead(); // Assuming getRoot() returns the root of the file linked list
            while (current != nullptr) {
                cout << "File ID: " << current->file.fileID << endl;
                cout << "File Name: " << current->file.filename << endl;
                cout << "File Content: " << current->file.fileContent << endl;
                cout << "File Owner: " << current->file.fileOwner << endl;
                cout << endl;
                current = current->next;
            }
            cout << "Branches Of Contributors To this Repo " << endl;
            BranchNode* newcurrent = foundRepo->newBranches.getHeadBranch();
            while (newcurrent != nullptr) {
                cout << "Branch Owner: " << newcurrent->Data.branchOwner << endl;
                cout << "Branch ID Is:  " << newcurrent->Data.BranchID << endl;
                cout << "Repo ID: " << newcurrent->Data.repoId << endl;
                cout << "Repo Name: " << newcurrent->Data.RepoName << endl;
                cout << "Repo Owner: " << newcurrent->Data.RepoownerName << endl;
                cout << "Is Public: " << (newcurrent->Data.isPublic ? "Yes" : "No") << endl;

                // Display files within the current branch
                cout << "Files in Branch:" << endl;
                newcurrent->newfiles.displayAllFiles();

                newcurrent = newcurrent->next; // Move to the next branch
            }

        }
        else {
            cout << "Repository with ID " << id << " not found." << endl;
        }
    }



    void displayAllReposHelper(Repo* root) {
        if (root != nullptr) {
            displayAllReposHelper(root->left);
            displayRepoById(root,root->id);
            cout << endl;
            cout << endl;
            displayAllReposHelper(root->right);
        }
    }

public:
    BinaryTreeRepo() : root(nullptr) {}

    void insertRepo(Repo* newNode) {
        root = insertRepo(root, newNode);
    }
    int getroot() {
        return root->id;
    }
    int getrootleft() {
        return root->left->id;
    }
    int getrootright() {
        return root->right->id;
    }
    void deleterepo(int id) {
        root = deleteRepo(root, id);
    }

    Repo* searchRepo(int id) {
        return searchRepo(root, id);
    }
    void SeeRepo(int id) {
        displayRepoById(root,id);
    }

    void displayAllRepos() {
        displayAllReposHelper(root);
    }
};


//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
////class Branch {
////public:
////    string Filename;
////    string FileData;
////    int branchID;
////    Branch* next;
////    Branch(string Filename, string FileData) :Filename(Filename), FileData(FileData),next(nullptr){};
////};
////class Repo :public User {
////public:
////    int id;
////    string RepoName;
////    string ownerName;
////    bool isPublic;
////    Repo* Contributors;
////    Repo* next;
////    Repo* commits;
////    Repo* commitNext;
////    int commitCount;
////    string ReadmeFile;
////    int ForkCount;
////    string ForkOwner;
////
////    Repo(string RepoName, bool isPublic) {
////        srand(time(0));
////        this->id = rand() % 100 + 1;
////        this->RepoName = RepoName;
////        this->isPublic = isPublic;
////        this->commitNext = nullptr;
////        this->commits = nullptr;
////        this->commitCount = 0;
////        this->ForkCount = 0;
////        this->ForkOwner = "";
////        this->ownerName = getUsername();
////    }
////    Repo() {};
////  // Methods for Repo 
////    void CreateRepo(string RepoName, bool isPublic) {
////        Repo( RepoName, isPublic);
////    }
////    void AddFileToBranch() {
////
////    }
////    void AddBranch() {
////
////    }
////    void DeleteFileToBrnach(int id) {
////
////    }
////    void deleteBranch(){
////
////    }
////    void Commit(string RepoNAme) {
////
////    }
////    void Fork(string RepoName) {
////
////    }
////};
////class FileNode {
////public:
//// 
////    string Filename;
////    FileNode* next;
////    FileNode(string Filename) :Filename(Filename), next(nullptr) {};
////};
////class FileLinkedlist {
////    FileNode* head;
////    FileLinkedlist() :head(nullptr) {};
////
////    void insertAtLast(string data) {
////
////        FileNode* newNode = new FileNode(data);
////        if (head == nullptr) {
////            head = newNode;
////        }
////        else {
////            FileNode* temp = head;
////            while (temp->next != nullptr) {
////                temp = temp->next;
////            }
////            temp->next = newNode;
////        }
////    }
////
////    void deleteFile(string name) {
////        if (head == nullptr) {
////            cout << "List is empty. Cannot delete." << endl;
////            return;
////        }
////
////        FileNode* temp = head;
////        FileNode* prev = nullptr;
////
////        // If head node itself holds the key to be deleted
////        if (temp != nullptr && temp->Filename == name) {
////            head = temp->next;
////            delete temp;
////            cout << "File with name " << name << " deleted successfully." << endl;
////            return;
////        }
////
////        // Search for the key to be deleted, keep track of the
////        // previous node as we need to change 'prev->next'
////        while (temp != nullptr && temp->Filename != name) {
////            prev = temp;
////            temp = temp->next;
////        }
////
////        // If key was not present in linked list
////        if (temp == nullptr) {
////            cout << "File with ID " << name << " not found in the list." << endl;
////            return;
////        }
////
////        // Unlink the node from linked list
////        prev->next = temp->next;
////        delete temp;
////        cout << "File with ID " << name<< " deleted successfully." << endl;
////    }
////
////    void printFiles() {
////        if (head == nullptr) {
////            cout << "No files in the list." << endl;
////            return;
////        }
////
////        FileNode* temp = head;
////        cout << "Files in the list:" << endl;
////        while (temp != nullptr) {
////            cout << "File name: " << temp->Filename << ", File Name: " << temp->Filename << endl;
////            temp = temp->next;
////        }
////    }
////
////};
////class CompleteRepoNode {
////public:
////
////    Repo data;
////    CompleteRepoNode* right;
////    CompleteRepoNode* left;
////    CompleteRepoNode(Repo data) :data(data), right(nullptr),left(nullptr) {};
////    int GetRootId() {
////        return data.id;
////    }
////};
////class BranchIngRepoTree {
////private:
////    CompleteRepoNode* root;
////    Branch* branch;
////    BranchIngRepoTree() :root(nullptr),branch(nullptr) {};
////    CompleteRepoNode* insertMainBranch(CompleteRepoNode* root, Repo data) {
////        // If the tree is empty, create a new node as root
////        if (root == nullptr)
////            return new CompleteRepoNode(data);
////
////        // Otherwise, recur down the tree
////        if (data.id < root->data.id)
////            root->left = insertMainBranch(root->left, data);
////        else if (data.id > root->data.id)
////            root->right = insertMainBranch(root->right, data);
////
////        // Return the unchanged node pointer
////        return root;
////    }
////    CompleteRepoNode* insertSubbranches(CompleteRepoNode* root, Branch data) {
////        
////        // Otherwise, recur down the tree
////        if (data.branchID < root->data.id)
////            root->left = insertSubbranches(root->left, data);
////        else if (data.branchID > root->data.id)
////            root->right = insertSubbranches(root->right, data);
////
////        // Return the unchanged node pointer
////        return root;
////    }
////    CompleteRepoNode* searchByID(CompleteRepoNode* root, int id) {
////        // Base cases: root is null or key is present at root
////        if (root == nullptr || root->data.id == id)
////            return root;
////
////        // Key is greater than root's key
////        if (root->data.id < id)
////            return searchByID(root->right, id);
////
////        // Key is smaller than root's key
////        return searchByID(root->left, id);
////    }
////    void inorderTraversal(CompleteRepoNode* root) {
////        if (root != nullptr) {
////            inorderTraversal(root->left);
////            cout << "ID: " << root->data.id << ", Repo Name: " << root->data.RepoName << endl;
////            inorderTraversal(root->right);
////        }
////    }
////public:
////    //BranchIngRepoTree() :root(nullptr) {};
////    void insertRepo(Repo data,Branch sub) {
////        if (root == nullptr) {
////            root = insertMainBranch(root, data);
////        }
////        else {
////            if (sub.branchID < root->GetRootId()) {
////                root->left = insertSubbranches(root, sub);
////            }
////            else if(sub.branchID > root->GetRootId()){
////                root->right = insertSubbranches(root, sub);
////            }
////        }
////    }
////    
////
////};
//
////class Branch {
////public:
////    string Filename;
////    string FileData;
////    int branchID;
////    Branch* next;
////    Branch(string Filename, string FileData) : Filename(Filename), FileData(FileData), next(nullptr) {};
////};
////
////class Repo : public User {
////public:
////    int id;
////    string RepoName;
////    string ownerName;
////    bool isPublic;
////    Repo* Contributors;
////    Repo* next;
////    Repo* commits;
////    Repo* commitNext;
////    int commitCount;
////    string ReadmeFile;
////    int ForkCount;
////    string ForkOwner;
////
////    Repo(string RepoName, bool isPublic) {
////        srand(time(0));
////        this->id = rand() % 100 + 1;
////        this->RepoName = RepoName;
////        this->isPublic = isPublic;
////        this->commitNext = nullptr;
////        this->commits = nullptr;
////        this->commitCount = 0;
////        this->ForkCount = 0;
////        this->ForkOwner = "";
////        this->ownerName = getUsername();
////    }
////
////    void CreateRepo(string RepoName, bool isPublic) {
////        // Repo(RepoName, isPublic); // This line doesn't actually create a repository, it should be removed.
////    }
////
////    void AddBranch(int branchID, string branchName) {
////        // Add branch functionality
////    }
////
////    void AddFileToBranch(int branchID, string Filename, string FileData) {
////        // Add file to branch functionality
////        // File handling
////        ofstream outFile(Filename);
////        if (outFile.is_open()) {
////            outFile << FileData;
////            outFile.close();
////            cout << "File " << Filename << " added to branch." << endl;
////        }
////        else {
////            cout << "Unable to open file.";
////        }
////    }
////
////    void CommitChanges(string RepoName, string commitMessage) {
////        // Commit changes functionality
////    }
////
////    void ForkRepo(string RepoName) {
////        // Fork repository functionality
////    }
////
////    void DeleteRepo(string RepoName) {
////        // Delete repository functionality
////    }
////
////    void DeleteBranch(int branchID) {
////        // Delete branch functionality
////    }
////
////    void DeleteFiles(string Filename) {
////        // Delete file functionality
////        if (remove(Filename.c_str()) == 0) {
////            cout << "File " << Filename << " deleted successfully." << endl;
////        }
////        else {
////            cout << "Error deleting file " << Filename << "." << endl;
////        }
////    }
////
////    void DisplayRepoStats() {
////        // Display repository stats functionality
////    }
////};
////
////class FileNode {
////public:
////    string Filename;
////    FileNode* next;
////    FileNode(string Filename) : Filename(Filename), next(nullptr) {};
////};
////
////class FileLinkedlist {
////    FileNode* head;
////    FileLinkedlist() : head(nullptr) {};
////
////    void insertAtLast(string data) {
////        FileNode* newNode = new FileNode(data);
////        if (head == nullptr) {
////            head = newNode;
////        }
////        else {
////            FileNode* temp = head;
////            while (temp->next != nullptr) {
////                temp = temp->next;
////            }
////            temp->next = newNode;
////        }
////    }
////    void deleteFile(string name) {
////                if (head == nullptr) {
////                    cout << "List is empty. Cannot delete." << endl;
////                    return;
////                }
////        
////                FileNode* temp = head;
////                FileNode* prev = nullptr;
////        
////                // If head node itself holds the key to be deleted
////                if (temp != nullptr && temp->Filename == name) {
////                    head = temp->next;
////                    delete temp;
////                    cout << "File with name " << name << " deleted successfully." << endl;
////                    return;
////                }
////        
////                // Search for the key to be deleted, keep track of the
////                // previous node as we need to change 'prev->next'
////                while (temp != nullptr && temp->Filename != name) {
////                    prev = temp;
////                    temp = temp->next;
////                }
////        
////                // If key was not present in linked list
////                if (temp == nullptr) {
////                    cout << "File with ID " << name << " not found in the list." << endl;
////                    return;
////                }
////        
////                // Unlink the node from linked list
////                prev->next = temp->next;
////                delete temp;
////                cout << "File with ID " << name<< " deleted successfully." << endl;
////            }
////        
////            void printFiles() {
////                if (head == nullptr) {
////                    cout << "No files in the list." << endl;
////                    return;
////                }
////        
////                FileNode* temp = head;
////                cout << "Files in the list:" << endl;
////                while (temp != nullptr) {
////                    cout << "File name: " << temp->Filename << ", File Name: " << temp->Filename << endl;
////                    temp = temp->next;
////                }
////            }
////};
////
////class CompleteRepoNode {
////public:
////    Repo data;
////    CompleteRepoNode* right;
////    CompleteRepoNode* left;
////    CompleteRepoNode(Repo data) : data(data), right(nullptr), left(nullptr) {};
////    int GetRootId() {
////        return data.id;
////    }
////};
////
////class BranchIngRepoTree {
////private:
////    CompleteRepoNode* root;
////    Branch* branch;
////    BranchIngRepoTree() : root(nullptr), branch(nullptr) {};
////
////    CompleteRepoNode* insertMainBranch(CompleteRepoNode* root, Repo data) {
////        if (root == nullptr)
////            return new CompleteRepoNode(data);
////
////        if (data.id < root->data.id)
////            root->left = insertMainBranch(root->left, data);
////        else if (data.id > root->data.id)
////            root->right = insertMainBranch(root->right, data);
////
////        return root;
////    }
////
////    CompleteRepoNode* insertSubbranches(CompleteRepoNode* root, Branch data) {
////
////        if (data.branchID < root->data.id)
////            root->left = insertSubbranches(root->left, data);
////        else if (data.branchID > root->data.id)
////            root->right = insertSubbranches(root->right, data);
////
////        return root;
////    }
////
////    CompleteRepoNode* searchByID(CompleteRepoNode* root, int id) {
////        if (root == nullptr || root->data.id == id)
////            return root;
////
////        if (root->data.id < id)
////            return searchByID(root->right, id);
////
////        return searchByID(root->left, id);
////    }
////
////    void inorderTraversal(CompleteRepoNode* root) {
////        if (root != nullptr) {
////            inorderTraversal(root->left);
////            cout << "ID: " << root->data.id << ", Repo Name: " << root->data.RepoName << endl;
////            inorderTraversal(root->right);
////        }
////    }
////
////public:
////    static BranchIngRepoTree& getInstance() {
////        static BranchIngRepoTree instance;
////        return instance;
////    }
////
////    void insertRepo(Repo data, Branch sub) {
////        if (root == nullptr) {
////            root = insertMainBranch(root, data);
////        }
////        else {
////            if (sub.branchID < root->GetRootId()) {
////                root->left = insertSubbranches(root, sub);
////            }
////            else if (sub.branchID > root->GetRootId()) {
////                root->right = insertSubbranches(root, sub);
////            }
////        }
////    }
////
////
////    CompleteRepoNode* searchRepoByID(int id) {
////        return searchByID(root, id);
////    }
////
////    void displayAllRepos() {
////        inorderTraversal(root);
////    }
////};
//
////class RepositoryManager {
////public:
////    RepositoryManager();
////    ~RepositoryManager();
////
////    Repository* createRepository(User* owner, const string& name, bool isPublic);
////    void deleteRepository(Repository* repo);
////    Repository* forkRepository(User* user, Repository* repo);
////
////    vector<Repository*> getAllRepositories();
////};
////
////class SocialManager {
////public:
////    SocialManager();
////    ~SocialManager();
////
////    void followUser(User* follower, User* followed);
////    void unfollowUser(User* follower, User* followed);
////};
////
////class User {
////private:
////    string username;
////    string password;
////    vector<User*> followers;
////    vector<User*> following;
////    vector<Repository*> repositories;
////
////public:
////    User(const string& username, const string& password);
////    ~User();
////
////    string getUsername();
////    string getPassword();
////    vector<User*> getFollowers();
////    vector<User*> getFollowing();
////    vector<Repository*> getRepositories();
////
////    void addFollower(User* follower);
////    void removeFollower(User* follower);
////    void addFollowing(User* followed);
////    void removeFollowing(User* followed);
////    void addRepository(Repository* repo);
////    void removeRepository(Repository* repo);
////};
////
////class Repository {
////private:
////    string name;
////    bool isPublic;
////    User* owner;
////    vector<File*> files;
////    vector<Commit*> commits;
////
////public:
////    Repository(User* owner, const string& name, bool isPublic);
////    ~Repository();
////
////    string getName();
////    bool getVisibility();
////    User* getOwner();
////    vector<File*> getFiles();
////    vector<Commit*> getCommits();
////
////    void addFile(File* file);
////    void deleteFile(File* file);
////    void addCommit(Commit* commit);
////};
////
////class Commit {
////private:
////    string message;
////    User* committer;
////    string timestamp;
////
////public:
////    Commit(const string& message, User* committer, const string& timestamp);
////    ~Commit();
////
////    string getMessage();
////    User* getCommitter();
////    string getTimestamp();
////};
////
////class File {
////private:
////    string name;
////    string content;
////
////public:
////    File(const string& name, const string& content);
////    ~File();
////
////    string getName();
////    string getContent();
////};
////
//
//
//
#endif // GITHUBHEADER_H
