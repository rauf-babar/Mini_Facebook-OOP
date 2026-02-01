
# ⓕ Facebook - Object Oriented Programming Project

A simplified Facebook clone implemented in C++ to demonstrate core Object-Oriented Programming (OOP) concepts.  
The project simulates key social networking features such as users, pages, posts, comments, likes, activities, timelines, and memories using a console-based interface.

---

## Project Overview

This project models a miniature social networking system inspired by Facebook.  
All system data is loaded from text files, and predefined commands are executed to demonstrate platform functionality.

The primary goal of the project is to apply and showcase strong OOP design principles, manual memory management, and real-world entity relationships in C++.

---

## Object-Oriented Concepts Used

- **Encapsulation**
  - Data members are kept private or protected and accessed through member functions.

- **Inheritance**
  - Common base class used for shared attributes and behavior.
  - Specialized classes inherit and extend base functionality.

- **Polymorphism**
  - Virtual functions enable runtime binding.
  - Objects are accessed through base-class pointers where appropriate.

- **Abstraction**
  - Abstract base classes define common interfaces for derived classes.

- **Dynamic Memory Management**
  - Extensive use of dynamic allocation and deallocation.
  - Custom handling of dynamic arrays and strings without STL containers.

---

## Features Implemented

### Users
- Unique user identification
- Friend lists
- Liked pages
- Personal timeline
- Home feed combining posts from friends and liked pages

### Pages
- Page creation with titles
- Page timelines
- Page posts and likes

### Posts
- Unique post IDs
- Text content
- Date and time tracking
- Likes from users and pages
- Comments
- Associated activities

### Comments
- Auto-generated comment IDs
- Linked to specific posts
- Commented by users or pages

### Likes
- Users and pages can like posts
- View list of entities who liked a post

### Activities
- Activity-based post content (e.g., feeling, thinking, celebrating)
- Implemented using polymorphic behavior

### Date, Time, and Memories
- Custom date handling
- Relative time display
- Detection of posts from previous years
- Ability to share posts as memories

---

## Project Structure

```

Facebook-OOP-CPP/
│
├── Facebook.cpp
│   └── Main source file containing all class definitions and logic
│
├── Project - Facebook.sln
│   └── Visual Studio solution file
│
├── SocialNetworkUsers.txt
│   └── User data
│
├── SocialNetworkPages.txt
│   └── Page data
│
├── UsersFriendsAndLikedPages.txt
│   └── User friendships and liked pages
│
├── SocialNetworkPosts.txt
│   └── Posts data
│
├── SocialNetworksComments.txt
│   └── Comments data
│
├── SocialNetworkActivities.txt
    └── Activity data linked to posts

```

---

## How to Run

1. Clone the repository.
2. Open `Project - Facebook.sln` in Visual Studio.
3. Ensure all `.txt` files are placed in the executable directory.
4. Build and run the project.
5. Observe the console output demonstrating Facebook-like operations.

---

## Demonstrated Functionality

- Setting system date
- Selecting current user
- Viewing friends and liked pages
- Viewing timelines
- Liking posts
- Viewing post likes
- Commenting on posts
- Viewing home feed
- Viewing and sharing memories

---

## Educational Purpose

This project is intended for:
- Learning and practicing Object-Oriented Programming in C++
- Understanding class relationships and polymorphism
- Manual memory management
- File handling and data-driven execution
- Academic coursework and lab assignments

