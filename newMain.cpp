//#include <iostream>
//#include <unordered_set>
//#include <ctime>
//using namespace std;
//
//class Repo {
//public:
//    int id;
//    string RepoName;
//    string ownerName;
//    bool isPublic;
//    Repo* left;
//    Repo* right;
//
//    Repo(string RepoName, bool isPublic, string ownerName) {
//        srand(time(0));
//        this->id = generateUniqueID();
//        this->RepoName = RepoName;
//        this->isPublic = isPublic;
//        this->ownerName = ownerName;
//        left = nullptr;
//        right = nullptr;
//    }
//
//private:
//    int generateUniqueID() {
//        static unordered_set<int> usedIDs;
//        int newID;
//        do {
//            newID = rand() % 100 + 1;
//        } while (usedIDs.count(newID) > 0);
//        usedIDs.insert(newID);
//        return newID;
//    }
//};
//
//class BinaryTreeRepo {
//private:
//    Repo* root;
//
//    Repo* insertRepo(Repo* root, Repo* newNode) {
//        if (root == nullptr) {
//            root = newNode;
//        }
//        else {
//            if (newNode->id < root->id) {
//                root->left = insertRepo(root->left, newNode);
//            }
//            else {
//                root->right = insertRepo(root->right, newNode);
//            }
//        }
//        cout << "Tree insertion successful" << endl;
//        return root;
//    }
//
//    Repo* deleteRepo(Repo* root, int id) {
//        if (root == nullptr) {
//            cout << "Repository with ID " << id << " not found. Deletion unsuccessful." << endl;
//            return root;
//        }
//
//        if (id < root->id) {
//            root->left = deleteRepo(root->left, id);
//        }
//        else if (id > root->id) {
//            root->right = deleteRepo(root->right, id);
//        }
//        else {
//            if (root->left == nullptr) {
//                Repo* temp = root->right;
//                delete root;
//                cout << "Repository with ID " << id << " deleted successfully." << endl;
//                return temp;
//            }
//            else if (root->right == nullptr) {
//                Repo* temp = root->left;
//                delete root;
//                cout << "Repository with ID " << id << " deleted successfully." << endl;
//                return temp;
//            }
//            Repo* temp = findMin(root->right);
//            root->id = temp->id;
//            root->right = deleteRepo(root->right, temp->id);
//        }
//        return root;
//    }
//
//    Repo* findMin(Repo* node) {
//        while (node->left != nullptr) {
//            node = node->left;
//        }
//        return node;
//    }
//
//public:
//    BinaryTreeRepo() : root(nullptr) {}
//
//    void insertRepo(Repo* newNode) {
//        root = insertRepo(root, newNode);
//    }
//
//    void deleteRepo(int id) {
//        root = deleteRepo(root, id);
//    }
//    void inorderHelper(Repo* root) {
//        if (root != nullptr) {
//            inorderHelper(root->left);
//            cout << "Repository ID: " << root->id << ", Name: " << root->RepoName << endl;
//            inorderHelper(root->right);
//        }
//    }
//    void inorder() {
//        inorderHelper(root);
//    }
//    // Other member functions...
//};
//
//int main() {
//    BinaryTreeRepo repoTree;
//
//    // Inserting some repositories
//    Repo* repo1 = new Repo("Project A", true, "John");
//    Repo* repo2 = new Repo("Project B", false, "Alice");
//    Repo* repo3 = new Repo("Project C", true, "Bob");
//
//    repoTree.insertRepo(repo1);
//    repoTree.insertRepo(repo2);
//    repoTree.insertRepo(repo3);
//    repoTree.inorder();
//    // Deleting a repository
//    repoTree.deleteRepo(repo2->id);
//    repoTree.inorder();
//    Repo* repo4 = new Repo("Project d", true, "Bsdob");
//    Repo* repo5 = new Repo("Project e", true, "Bsob");
//    repoTree.insertRepo(repo4);
//    repoTree.insertRepo(repo5);
//    int id;
//    cin >> id;
//    repoTree.inorder();
//    repoTree.deleteRepo(id);
//    repoTree.inorder();
//    system("pause");
//    return 0;
//}
