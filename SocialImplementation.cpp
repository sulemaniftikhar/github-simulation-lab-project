#include "SocialFeature.h"

void SocialFeature::addUser(const std::string& username) {
    addUser(username);
}

void SocialFeature::follow(const std::string& follower, const std::string& followee) {
    cout << follower << " Has Follow the person " << followee;
    //follow(follower, followee);
}

void SocialFeature::unfollow(const std::string& follower, const std::string& followee) {
    cout << follower << " Has un Folllow the " << followee << endl;
    //unfollow(follower, followee);
}

void SocialFeature::displayFollowing(const std::string& username) {
    displayFollowing(username);
}