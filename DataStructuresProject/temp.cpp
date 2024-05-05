// C++ program to illustrate the begin and end iterator
#include <iostream>
#include <map>
#include <string>
using namespace std;

int main()
{
    // Create a map of strings to integers
    map<string, vector<string> > mp;

    // Insert some values into the map
    // mp["one"] = 1;
    // mp["two"] = 2;
    // mp["three"] = 3;

    string index1 = "1";

    vector<string> str;
    str.push_back("suleman");
    str.push_back("waleed");
    str.push_back("sohaib");

    mp[index1] = str;

    auto it = mp.begin();

    while (it != mp.end())
    {
        cout << "User: " << it->first << " Followers: ";
        for (auto f : it->second)
        {
            cout << f << " , ";
        }
        it++;
    }

    return 0;
}