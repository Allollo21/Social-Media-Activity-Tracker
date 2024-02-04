# Activity Tracker

The `ActivityTracker` class is a component of a comprehensive system designed to manage user activities. This class integrates an AVL tree data structure to efficiently organize and retrieve user information. The system records user activities such as likes, comments, and posts, providing a dynamic platform for user engagement.

## Class Overview

### Attributes
- `user_t`: AVL tree to store user information.
- `activityCounter`: Tracks the total number of activities.

### Constructors
- `ActivityTracker()`: Initializes the `activityCounter` to zero.

### Methods

#### `addActivity()`
This method facilitates the addition of user activities. Users can either be existing or new. Existing users can have their activities appended, while new users are assigned a unique ID and associated with their initial activity.

#### `removeActivity()`
Enables the removal of specific activities associated with a user. Users input their ID, view their activities, and select the activity to be deleted based on its ID.

#### `searchForUser()`
Allows users to search for a particular user by their ID. Upon identification, the system displays the user's activities.

#### `displayAll()`
Displays all users along with their associated activities.

#### `Statistics()`
Generates statistics about user activity, highlighting the most active user's ID. Additionally, it provides a comprehensive overview of user engagement through a traversal of the AVL tree.

## Usage

The `ActivityTracker` class seamlessly integrates into a larger system, providing a robust framework for tracking and managing user activities. Users interact with the system through a console interface, executing tasks such as adding activities, removing activities, searching for users, and obtaining statistical insights into user engagement.

## System Requirements

- C++ Compiler
- Standard C++ libraries
- Console-based environment

## How to Integrate

1. Include the `ActivityTracker` class in your project.
2. Ensure compatibility with a C++ compiler.
3. Integrate system dependencies as specified.

## Contributing

Contributions to enhance the functionalities of the `ActivityTracker` class are encouraged. Please follow standard software development practices and submit well-documented pull requests.

