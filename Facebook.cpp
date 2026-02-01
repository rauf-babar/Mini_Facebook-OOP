#include <iostream>
#include <fstream>
using namespace std;
 
///--------------------- CLASS DECLARATIONS ---------------------

class Helper
{
public:

    static int StringLength(const char*);
    static void StringConcatenate(char*&,const char* );
    static void StringCopy(char*&, char*&);
    static char* GetString(const char*);
    static bool StringCompare(const char*, const char* );
    static char* IntToArray(int);
    template <class identifier>
    static void DeallocateArray(identifier**);
};

class Date
{
    int date, month, year;
    friend ifstream& operator>> (ifstream& , Date& );
    static Date currentDate;

public:

    Date(int _day = 0, int _month = 0, int _year = 0);
    int DifferenceInTime();
    int DifferenceInYear();
    void PrintDifferenceInDates(Date);
    static void setCurrentDate(int, int, int);
    void displayDate();
    static void displaySystemDate();
    static void SetToCurrentDate(Date&);
};

class Post;

class Object
{
    char* ID;

protected:
    Post** Timeline;

public:

    Object();
    char*& GetID();
    void SetID(char* );
    virtual void Display() = 0;
    virtual void PrintName() = 0;
    void AddPostToTimeline(Post*);
    void ViewLatestPost();
    void ViewTimeline();
    void SeeYourMemories();
    ~Object();
};

class Pages : public Object
{
    char* pageTitle;

public:

    Pages();
    void LoadDataFromFile(ifstream& );
    bool CompareIDs(const char*& );
    void PrintName();
    void Display();
    ~Pages();
};

class User : public Object
{
private:
	char* firstName;
	char* lastName;
    User** userFriends;
    Pages** likedPages;

public:
    
    User();
    void PrintName();
    void LoadDataFromFile(ifstream& );
    bool CompareIDs(const char* );
    void AddFriend(User*& );
    void LikePage(Pages*& );
    void Display();
    void ViewFriendList();
    void ViewLikedPages();
    void ViewHome();
    ~User();
};

class Comment
{
    char* commentID;
    char* commentText;
    Object* commentPostedBy;
    static int noOfCommentsInSystem;
public:
    Comment();
    Comment(Object*,const char*,char* = 0);
    void display();
    ~Comment();
};

class PostContent
{
public:
    virtual void Display() = 0;
    virtual void ReadDataFromFile(ifstream&) = 0;
    virtual ~PostContent() {}
};

class Activity : public PostContent
{
    int typeOfActivity;
    char* valueOfActivity;
public:
    Activity();
    void Display();
    void ReadDataFromFile(ifstream&);
    ~Activity();
};

class Post
{
    char* postID;
    Date sharedDate;
    char* description;
    Object* sharedBy;
    Object** likedBy;
    Comment** comments;
    PostContent* activity;
    static int noOfPostsInSystem;

public:
    Post();
    Post(Object*, const char*);
    void LoadDataFromFile(ifstream& );
    bool CompareIDs(const char*& );
    void SetSharedBy(Object*& );
    void LikePost(Object* );
    virtual void displayPost();
    void ViewLikes();
    int GetDateDifference();
    int GetYearlyDifference();
    void PrintDifferenceInDates(Post*);
    void SetActivity(PostContent*);
    void AddComment(Comment*&);
    void PrintSharedBy();
    void PrintSharedDate();
    char*& GetDescription();
    virtual ~Post();
};


class Memories : public Post
{
    Post* originalPost;
public:

    Memories(const char*, Post* &, Object*);
    void displayPost();
    ~Memories(){}
};

class Controller
{
private:
    User* currentUser;
    User** allUsers;
    Pages** allPages;
    Post** allPosts;

public:

    Controller();
    template<class identifier>
    identifier* SearchByID(const char*, identifier**);
    void LoadUsersFromFile(const char*);
    void LoadPagesFromFile(const char*);
    void LinkUsersAndPages(const char*);
    void LoadAllPostsFromFile(const char*);
    void LoadAllCommentsFromFile(const char*);
    void LoadAllActivitiesFromFile(const char*);
    void LoadAllData();
    void Run();
    ~Controller();
};

///--------------------- CLASS METHOD'S DEFINITIONS ---------------------

//-----------------------------------
// CLASS - HELPER
//-----------------------------------

int Helper::StringLength(const char* str) {
    int stringLen = 0;
    if (str) {
        while (str[stringLen] != '\0')
            stringLen++;
    }
    return stringLen;
}

void Helper::StringConcatenate(char*& string1,const char* string2) {
    int size1 = StringLength(string1);
    int size2 = StringLength(string2);
    int size3 = size1 + size2 + 1;

    char* concatenatedString = new char[size3 + 1];
    int index = 0;
    for (int j = 0, k = 0; index < size3; index++) {
        if (index < size1) {
            concatenatedString[index] = string1[j];
            j++;
        }
        else {
            concatenatedString[index] = string2[k];
            k++;
        }
    }
    concatenatedString[index] = '\0';
    delete[] string1;
    string1 = concatenatedString;
}

char* Helper::IntToArray(int _number)
{
    int m = _number;
    int digit = 0;
    while (m > 0) {
        digit++;
        m /= 10;
    }
    char* arr = new char[digit + 1];
    int index = digit;
    while (_number > 0) {
        arr[--index] = (_number % 10) + '0';
        _number /= 10;
    }
    arr[digit] = '\0';
    return arr;
}

void Helper::StringCopy(char*& dest, char*& src) {
    char* tempDest = dest;
    for (char* tempSrc = src; *tempSrc != '\0'; tempSrc++, tempDest++) {
        *tempDest = *tempSrc;
    }
    *tempDest = '\0';
}

char* Helper::GetString(const char* buffer)
{
    int strLen = StringLength(buffer);
    char* str = 0;
    if (strLen > 0)
    {
        str = new char[strLen + 1];
        for (int i = 0; i < strLen; i++)
            str[i] = buffer[i];
        str[strLen] = '\0';
    }
    return str;
}

bool Helper::StringCompare(const char* alpha, const char* beta)
{
    if (strlen(alpha) != strlen(beta))
        return false;
    else
    {
        for (int i = 0; alpha[i] != '\0' && beta[i] != '\0'; i++)
        {
            if (tolower(alpha[i]) != tolower(beta[i]))
                return false;
        }
    }
    return true;
}

template <class identifier>
void Helper::DeallocateArray(identifier** myArray)
{
    if (myArray)
    {
        for (int i = 0; myArray[i] != nullptr; i++)
            delete myArray[i];
        delete[] myArray;
    }
}

//-----------------------------------
// CLASS - DATE
//-----------------------------------

Date::Date(int _day, int _month, int _year) :date(_day), month(_month), year(_year) {}

ifstream& operator>> (ifstream& in, Date& date)
{
    in >> date.date >> date.month >> date.year;
    return in;
}

Date Date::currentDate;

void Date::setCurrentDate(int _date, int _month, int _year)
{
    currentDate.date = _date;
    currentDate.month = _month;
    currentDate.year = _year;
}

int Date::DifferenceInTime()
{
    if (currentDate.year == year && currentDate.month == month && currentDate.date >= date)
        return currentDate.date - date;
    return -1;
}

int Date::DifferenceInYear()
{
    if (date == currentDate.date && month == currentDate.month)
        return currentDate.year - year;
    return -1;
}

void Date::PrintDifferenceInDates(Date rhs)
{
    cout << "\t~~~ ";
    if (date == rhs.date && month == rhs.month)
        cout << year - rhs.year << " years ago";
    else if (rhs.year == year && rhs.month == month)
        cout << date - rhs.date << " days ago";
    else
        cout << date << " / " << month << " / " << year;
    cout << "  ~~~\n";
}

void Date::displayDate()
{
    int difference = DifferenceInTime();
    cout << "( ";
    if (currentDate.date == date && currentDate.month == month && currentDate.year == year)
        cout << "1h ago";
    else if (difference == 1)
        cout << "1 day ago";
    else if (difference < 7 && difference != -1)
        cout << difference << " days ago";
    else if (difference == 7)
        cout << "1 week ago";
    else
        cout << date << " / " << month << " / " << year;
    cout << " )\n";
}

void Date::displaySystemDate()
{
    cout << "System Date :\t"<< currentDate.date << " / " << currentDate.month << " / " << currentDate.year << endl;
}

void Date::SetToCurrentDate(Date& date)
{
    date.date = currentDate.date;
    date.month = currentDate.month;
    date.year = currentDate.year;
}

//-----------------------------------
// CLASS - OBJECT
//-----------------------------------

 Object:: Object() : ID(nullptr), Timeline(nullptr) {};

 char*& Object::GetID()
 {
     return ID;
 }

 void  Object::SetID(char* _ID)
 {
     if (ID)
         delete[]ID;
     ID = Helper::GetString(_ID);
 }

 void  Object::AddPostToTimeline(Post* _post)
 {
     if (!Timeline )
     {
         Timeline = new Post * [10];
         for (int i = 0; i < 10; i++)
             Timeline[i] = nullptr;
     }
     for(int i =0; i < 10;i++)
     {
         if (!Timeline[i])
         {
             Timeline[i] = _post;
             return;
         }
     }
     cout << "Timeline is Fully Occupied\n";
 }

 void Object::SeeYourMemories()
 {
     cout << "\nWe hope you enjoy looking back and sharing your memories on Facebook, from the most recent to those long ago.\n\nOn this Day";
     int difference, count = 0;
     if (Timeline)
     {
         for (int i = 0; Timeline[i] != nullptr; i++)
         {
             difference = Timeline[i]->GetYearlyDifference();
             if (difference > 0)
             {
                 cout << endl << difference << " Years Ago";
                 Timeline[i]->displayPost();
                 count++;
             }
         }
     }
     if (!count)
         cout << "\nNo Memories Found\n";
 }

 void Object::ViewLatestPost()
 {
     if (Timeline) {
         for (int i = 0; Timeline[i] != nullptr; i++)
         {
             int dateDifference = Timeline[i]->GetDateDifference();
             if (dateDifference <= 2 && dateDifference != -1)
                 Timeline[i]->displayPost();
         }
     }
 }

 void Object::ViewTimeline()
 {
    if (Timeline) {
         PrintName();
         cout << "- Timeline\n";
         for (int i = 0; Timeline[i] != nullptr; i++)
             Timeline[i]->displayPost();
    }
 }

 Object:: ~Object()
 {
     if (ID)
         delete[]ID;
     Helper::DeallocateArray(Timeline);
 }

//-----------------------------------
// CLASS - USER
//-----------------------------------

 User:: User() :firstName(nullptr), lastName(nullptr), userFriends(nullptr), likedPages(nullptr) {}

 void User::PrintName()
 {
     cout << firstName << " " << lastName << " ";
 }

 void User::LoadDataFromFile(ifstream& fin)
 {
     char buffer[80];
     fin >> buffer;
     SetID(buffer);
     fin >> buffer;
     firstName = Helper::GetString(buffer);
     fin >> buffer;
     lastName = Helper::GetString(buffer);
 }

 bool User::CompareIDs(const char* ID)
 {
     return (Helper::StringCompare(GetID(), ID));
 }

 void User::AddFriend(User*& friendID)
 {
     if (userFriends == nullptr)
     {
         userFriends = new User * [10];
         for (int i = 0; i < 10; ++i) {
             userFriends[i] = nullptr;
         }
     }
     for (int i = 0; i < 10; i++)
     {
         if (userFriends[i] == nullptr)
         {
             userFriends[i] = friendID;
             return;
         }
     }
     cout << "Friend List Reached Max Limit\n";
 }

 void User::LikePage(Pages*& likePage)
 {
     if (likedPages == nullptr)
     {
         likedPages = new Pages * [10];
         for (int i = 0; i < 10; ++i) {
             likedPages[i] = nullptr;
         }
     }

     for (int i = 0; i < 10; i++)
     {
         if (likedPages[i] == nullptr)
         {
             likedPages[i] = likePage;
             return;
         }
     }
     cout << "Liked Pages Reached Max Limit\n";
 }

 void User::Display()
 {
     cout << GetID() << " - " << firstName << " " << lastName << endl;
 }

 void User::ViewFriendList()
 {
     if (userFriends)
     {
         cout << firstName << " " << lastName << " - Friend List\n\n";
         for (int i = 0; i < 10; i++)
             if (userFriends[i] != nullptr)
                 userFriends[i]->Display();
     }
     else
         cout << "No friends\n";
 }

 void User::ViewLikedPages()
 {
     if(likedPages)
     {
         cout << firstName << " " << lastName << " - Liked Pages\n\n";
         for (int i = 0; i < 10; i++)
             if (likedPages[i] != nullptr)
                 likedPages[i]->Display();
     }
     else
             cout << "No friends\n";
 }

 void User::ViewHome()
 {
     cout << firstName << " " << lastName << " - Home Page\n";
     ViewLatestPost();
     if (userFriends) {
         for (int i = 0; userFriends[i] != nullptr; i++)
             userFriends[i]->ViewLatestPost();
     }
     if (likedPages) {
         for (int i = 0; likedPages[i] != nullptr; i++)
             likedPages[i]->ViewLatestPost();
     }
 }
 User::~User()
 {
     if (firstName)
         delete[]firstName;
     if (lastName)
         delete[]lastName;
     if (userFriends)
         delete[]userFriends;
     if (likedPages)
         delete[]likedPages;
 }
 
//-----------------------------------
// CLASS - PAGES
//-----------------------------------
 Pages ::Pages() :pageTitle(nullptr) {}

 void Pages::LoadDataFromFile(ifstream& fin)
 {
     char buffer[80];
     fin >> buffer;
     SetID(buffer);
     fin.ignore();
     fin.getline(buffer, 100);
     pageTitle = Helper::GetString(buffer);
 }

 bool Pages::CompareIDs(const char*& ID)
 {
     return (Helper::StringCompare(GetID(), ID));
 }

 void Pages::PrintName()
 {
     cout << pageTitle << " ";
 }

 void Pages::Display()
 {
     cout << GetID() << " - " << pageTitle << endl;
 }

 Pages::~Pages()
 {
     if (pageTitle)
         delete[]pageTitle;
 }

//-----------------------------------
// CLASS - COMMENT
//-----------------------------------

 Comment::Comment() :commentID(nullptr), commentPostedBy(nullptr), commentText(nullptr) 
 { 
     noOfCommentsInSystem++;
 }
 
 int Comment::noOfCommentsInSystem = 0;

 Comment::Comment(Object* _commentPostedBy,const char* _commentText, char* ID)
 {
     if (!ID)
     {
         ID = Helper::GetString("c");
         char* IdNumber = Helper::IntToArray(noOfCommentsInSystem);
         Helper::StringConcatenate(ID, IdNumber);
         delete[]IdNumber;
     }
     commentID = Helper::GetString(ID);
     commentPostedBy = _commentPostedBy;
     commentText = Helper::GetString(_commentText);
     noOfCommentsInSystem++;
 }

 void Comment:: display()
 {
     cout << "\t\t";
     commentPostedBy->PrintName();
     cout << ": \" " << commentText << " \"\n";
 }

 Comment::~Comment()
 {
     if (commentID)
         delete[]commentID;
     if (commentText)
         delete[]commentText;
     noOfCommentsInSystem--;
 }

//-----------------------------------
// CLASS - ACTIVITY 
//-----------------------------------

 Activity::Activity() : typeOfActivity(0),valueOfActivity(0){}

 void Activity::ReadDataFromFile(ifstream& fin)
 {
     char buffer[80];
     fin >> typeOfActivity;
     fin.ignore();
     fin.getline (buffer,80);
     valueOfActivity = Helper::GetString(buffer);
 }

 void Activity::Display()
 {
     cout << "is ";
     switch (typeOfActivity)
     {
     case 1:
         cout << "feeling ";
         break;
     case 2:
         cout << "thinking about ";
         break;
     case 3:
         cout << "making ";
         break;
     case 4:
         cout << "celebrating ";
         break;
     default:
         cout << "Invalid type of Activity\n";
         break;
     }
     cout << valueOfActivity << " ";
 }
 Activity::~Activity()
 {
     if (valueOfActivity)
         delete[]valueOfActivity;
 }

//-----------------------------------
// CLASS - POST
//-----------------------------------
 
Post ::Post() :postID(nullptr), description(nullptr), sharedBy(nullptr), likedBy(nullptr),comments(nullptr),activity(nullptr) 
{ 
    noOfPostsInSystem++;
}
int Post::noOfPostsInSystem = 0;

Post::Post(Object* _sharedBy, const char* _text) :comments(nullptr), likedBy(nullptr), activity(nullptr)
{
    noOfPostsInSystem++;
    sharedBy = _sharedBy;
    description = Helper::GetString(_text);
    Date::SetToCurrentDate(sharedDate);
    char* postNumber = Helper::IntToArray(noOfPostsInSystem);
    Helper::StringConcatenate(postID, postNumber);
    delete[] postNumber;
}

void Post::LoadDataFromFile(ifstream& fin)
{
    char buffer[100];
    fin >> buffer;
    postID = Helper::GetString(buffer);
    fin >> sharedDate;
    fin.ignore();
    fin.getline(buffer, 100);
    description = Helper::GetString(buffer);
}

bool Post::CompareIDs(const char*& _postID)
{
    return(Helper::StringCompare(postID, _postID));
}

void Post::SetSharedBy(Object*& _sharedBy)
{
    sharedBy = _sharedBy;
}

void Post::LikePost(Object* _likedBy)
{
    if (likedBy == nullptr)
    {
        likedBy = new Object * [10];
        for (int i = 0; i < 10; ++i) {
            likedBy[i] = nullptr;
        }
    }

    for (int i = 0; i < 10; i++)
    {
        if (likedBy[i] == nullptr)
        {
            likedBy[i] = _likedBy;
            return;
        }
    }
    cout << "Likes Reached Max Limit\n";
}

void Post::displayPost()
{

    cout << "\n--- ";
    sharedBy->PrintName();
    if (activity)
        activity->Display();
    sharedDate.displayDate();
    cout << "\t\" " << description << " \"\n";
    if (comments)
        for (int i = 0; comments[i] != nullptr; i++)
            comments[i]->display();
}

void Post::ViewLikes()
{
    cout << "Post Liked By: \n";
    if (likedBy)
    {
        for (int i = 0; likedBy[i] != nullptr; i++)
            likedBy[i]->Display();
    }
}

int Post::GetDateDifference()
{
    return sharedDate.DifferenceInTime();
}

int Post::GetYearlyDifference()
{
    return sharedDate.DifferenceInYear();
}

void Post::PrintDifferenceInDates(Post* rhs)
{
    sharedDate.PrintDifferenceInDates(rhs->sharedDate);
}

char*& Post::GetDescription()
{
    return description;
}

void Post::AddComment(Comment*& _comment)
{
    if (comments == nullptr) 
    {
        comments = new Comment * [10];
        for (int i = 0; i < 10; i++)
            comments[i] = nullptr;
    }
    for (int i = 0; i < 10; i++)
        if (comments[i] == nullptr)
        {
            comments[i] = _comment;
            return;
        }
    cout << "Comments Reached Max Limit\n";
}

void Post::SetActivity(PostContent* content)
{
    activity = content;
}

void Post::PrintSharedBy()
{
    sharedBy->PrintName();
}

void Post::PrintSharedDate()
{
    sharedDate.displayDate();
}

Post::~Post()
{
    if (postID)
        delete[]postID;
    if (description)
        delete[]description;
    if (likedBy)
        delete[]likedBy;
    if (activity)
        delete activity;
    Helper::DeallocateArray(comments);
    noOfPostsInSystem--;
}

//-----------------------------------
// CLASS - MEMORIES
//-----------------------------------

Memories::Memories(const char* _text, Post*& _originalPost, Object* _user) : Post(_user,_text)
{
    originalPost = _originalPost;
}


void Memories::displayPost()
{
    cout << "\n~~~ ";
    PrintSharedBy();
    cout << "shared a memory ~~~ ";
    PrintSharedDate();
    cout << "\t\t\" " << GetDescription() << "\"\n";
    PrintDifferenceInDates(originalPost);
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n--";
    originalPost->PrintSharedBy();
    originalPost->PrintSharedDate();
    cout << "\t\t\" " << originalPost->GetDescription() << "\"\n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
}

//-----------------------------------
// CLASS - CONTROLLER
//-----------------------------------

Controller::Controller() : currentUser(nullptr), allUsers(nullptr), allPages(nullptr), allPosts(nullptr) {}

template <class indentifier>
indentifier* Controller::SearchByID(const char* ID, indentifier** list)
{
    for (int i = 0; list[i] != nullptr; i++)
    {
        if (list[i]->CompareIDs(ID))
            return list[i];
    }
    return nullptr;
}

void Controller::LoadUsersFromFile(const char* fileName)
{
    ifstream fin(fileName);
    if (fin.is_open())
    {
        int noOfUsers;
        fin >> noOfUsers;
        allUsers = new User * [noOfUsers + 1];
        for (int i = 0; i < noOfUsers; i++)
        {
            allUsers[i] = new User;
            allUsers[i]->LoadDataFromFile(fin);
        }
        allUsers[noOfUsers] = nullptr;
        fin.close();
    }
    else
        cout << "Error Opening File\n";
}
void Controller::LoadPagesFromFile(const char* fileName)
{
    ifstream fin(fileName);
    if (fin.is_open())
    {
        int noOfPages;
        fin >> noOfPages;
        allPages = new Pages * [noOfPages + 1];
        for (int i = 0; i < noOfPages; i++)
        {
            allPages[i] = new Pages;
            allPages[i]->LoadDataFromFile(fin);
        }
        allPages[noOfPages] = nullptr;
        fin.close();
    }
    else
        cout << "Error Opening File\n";
}

void Controller::LinkUsersAndPages(const char* fileName)
{
    ifstream fin(fileName);
    if (fin.is_open())
    {
        char userID[80];
        fin >> userID;
        User* tempUser = nullptr;
        while (!(Helper::StringCompare(userID, "-1")))
        {
            tempUser = SearchByID(userID, allUsers);
            char friendID[20];
            fin >> friendID;
            while (!(Helper::StringCompare(friendID, "-1")))
            {
                User* tempFriendID = SearchByID(friendID,allUsers);
                tempUser->AddFriend(tempFriendID);
                fin >> friendID;
            }
            char likePageID[10];
            fin >> likePageID;
            while (!(Helper::StringCompare(likePageID, "-1")))
            {
                Pages* tempLikedPage = SearchByID(likePageID, allPages);
                tempUser->LikePage(tempLikedPage);
                fin >> likePageID;
            }
            fin >> userID;
        }
        fin.close();
    }
    else
        cout << "Error Opening File\n";
}

void Controller::LoadAllPostsFromFile(const char* fileName)
{
    ifstream fin(fileName);
    if (fin.is_open())
    {
        int noOfPosts;
        fin >> noOfPosts;
        char buffer[80];
        allPosts = new Post * [noOfPosts + 1];
        allPosts[noOfPosts] = nullptr;
        for (int i = 0; i < noOfPosts; i++)
        {
            allPosts[i] = new Post;
            allPosts[i]->LoadDataFromFile(fin);
            fin >> buffer;
            if (buffer[0] == 'u')
            {
                Object* sharedBy = SearchByID(buffer,allUsers);
                allPosts[i]->SetSharedBy(sharedBy);
                sharedBy->AddPostToTimeline(allPosts[i]);
            }
            else if (buffer[0] == 'p')
            {
                Object* sharedBy = SearchByID(buffer,allPages);
                allPosts[i]->SetSharedBy(sharedBy);
                sharedBy->AddPostToTimeline(allPosts[i]);
            }
            fin >> buffer;
            while (!(Helper::StringCompare(buffer, "-1")))
            {
                if (buffer[0] == 'u')
                {
                    Object* likedBy = SearchByID(buffer,allUsers);
                    allPosts[i]->LikePost(likedBy);
                }
                else if (buffer[0] == 'p')
                {
                    Object* likedBy = SearchByID(buffer,allPages);
                    allPosts[i]->LikePost(likedBy);
                }
                fin >> buffer;
            }
        }
    }
    else
        cout << "Error Opening File\n";
}

void Controller::LoadAllCommentsFromFile(const char* fileName)
{
    ifstream fin(fileName);
    if (fin.is_open())
    {
        int noOfComments;
        fin >> noOfComments;
        char buffer[80];
        for (int i = 0; i < noOfComments; i++)
        {
            char ID[10];
            fin >> ID;
            fin >> buffer;
            Post* post = SearchByID(buffer,allPosts);
            fin >> buffer;
            Object* commentedBy;
            if (buffer[0] == 'u')
                commentedBy = SearchByID(buffer,allUsers);
            else
                commentedBy = SearchByID(buffer,allPages);
            fin.ignore();
            fin.getline(buffer, 80);
            Comment* comment = new Comment(commentedBy, buffer, ID);
            post->AddComment(comment);
        }
    }
    else
        cout << "Error Opening File\n";
}

void Controller::LoadAllActivitiesFromFile(const char* fileName)
{
    ifstream fin(fileName);
    if (fin.is_open())
    {
        int totalNoOfActivites;
        fin >> totalNoOfActivites;
        char buffer[80];
        for (int i = 0; i < totalNoOfActivites; i++)
        {
            fin >> buffer;
            Post* post = SearchByID(buffer, allPosts);
            Activity* postContentPtr = new Activity;
            postContentPtr->ReadDataFromFile(fin);
            post->SetActivity(postContentPtr);
        }
    }
    else
        cout << "Error Opening File\n";
}

void Controller::LoadAllData()
{
    LoadUsersFromFile("SocialNetworkUsers.txt");
    LoadPagesFromFile("SocialNetworkPages.txt");
    LinkUsersAndPages("UsersFriendsAndLikedPages.txt");
    LoadAllPostsFromFile("SocialNetworkPosts.txt");
    LoadAllCommentsFromFile("SocialNetworksComments.txt");
    LoadAllActivitiesFromFile("SocialNetworkActivities.txt");
}

void Controller::Run()
{
    char dottedLine[] = "-------------------------------------------------------------------------------------------------------------\n";

    cout << dottedLine << "Command :\tSet current Date to 17 4 2024 \n" << dottedLine;
    Date::setCurrentDate(17, 4, 2024);
    Date::displaySystemDate();

    cout << endl << dottedLine << "Command :\tSet current user \"u1\"\n" << dottedLine;
    currentUser = SearchByID("u1",allUsers);
    if (currentUser)
    {
        currentUser->PrintName();
        cout << "successfully set as Current user\n\n";
    }

    cout << dottedLine << "Command:\tView Friend List\n" << dottedLine;
    currentUser->ViewFriendList();

    cout << endl << dottedLine << "Command:\tView Liked Pages\n" << dottedLine;
    currentUser->ViewLikedPages();

    cout << endl << dottedLine << "Command:\tView TimeLine\n" << dottedLine;
    currentUser->ViewTimeline();

    cout << endl << dottedLine << "Command:\tView Liked List (post5)\n" << dottedLine;
    Post* postPtr = SearchByID("post5",allPosts);
    if (postPtr)
        postPtr->ViewLikes();

    cout << endl << dottedLine << "Command:\tLike Post (post5)\n";
    postPtr = SearchByID("post5",allPosts);
    if (postPtr)
        postPtr->LikePost(currentUser);

    cout << dottedLine << "Command:\tView Liked List (post5)\n" << dottedLine;
    postPtr = SearchByID("post5",allPosts);
    if (postPtr)
        postPtr->ViewLikes();

    cout << endl << dottedLine << "Command:\tView Page (p1)\n" << dottedLine;
    Pages* page = SearchByID("p1",allPages);
    if (page)
        page->ViewTimeline();

    cout << endl << dottedLine << "Command:\tView Home\n" << dottedLine;
    currentUser->ViewHome();

    cout << endl << dottedLine << "Command:\tPost Comment (post4, Good Luck For your Result)\n" << dottedLine;
    Comment* newComment1 = new Comment(currentUser, "Good Luck For your Result");
    postPtr = SearchByID("post4",allPosts);
    postPtr->AddComment(newComment1);

    cout << "Command:\tView Post (post4)\n" << dottedLine;
    postPtr = SearchByID("post4",allPosts);
    if (postPtr)
        postPtr->displayPost();

    cout << endl << dottedLine << "Command:\tPost Comment (post8, Thanks for the wishes)\n" << dottedLine;
    Comment* newComment2 = new Comment(currentUser, "Thanks for the wishes");
    postPtr = SearchByID("post8",allPosts);
    postPtr->AddComment(newComment2);

    cout << "Command:\tView Post (post8)\n" << dottedLine;
    postPtr = SearchByID("post8",allPosts);
    if (postPtr)
        postPtr->displayPost();
    cout << endl << dottedLine << "Command:\tSee Your Memories\n" << dottedLine;
    currentUser->SeeYourMemories();

    cout << endl << dottedLine << "Command:\tShare Memory (post10, \"Never thought I will be specialist in this field...\")\n";
    postPtr = SearchByID("post10",allPosts);
    Memories* memoryPtr = new Memories("Never thought I will be specialist in this field...", postPtr, currentUser);
    currentUser->AddPostToTimeline(memoryPtr);

    cout << dottedLine << "Command:\tView TimeLine\n" << dottedLine;
    currentUser->ViewTimeline();
}

Controller::~Controller()
{
    Helper::DeallocateArray(allUsers);
    Helper::DeallocateArray(allPages);
    if (allPosts)
        delete[] allPosts;
}

/// ------------------------- DRIVER FUNCTION ------------------------
int main() 
{
	Controller my_Application;
	my_Application.LoadAllData();
    my_Application.Run();
}
