# Object-Oriented Programming - 1st Homework

### Constantinescu Vlad 324CB

The source folder contains:

- App.java: contains custom general methods and the main method
- Comment.java: contains the Comment class and its variables and methods
- Followable.java: contains the Followable interface and methods declarations
- Likeable.java: contains the Likeable interface and methods declarations
- Output.java: contains the Output class and its variables for JSON type output
- Post.java: contains the Post class and its variables and methods
- User.java: contains the User class and its variables and methods

## General Implementation
```     
- Read the main method arguments and check credentials validity. If the
  credentials are valid, the program continues, otherwise it exits with
  an error message.
- App data is contained in arraylists of users, posts and comments to increase
  the efficiency of the program, while also keeping the data intact between
  commands.
- Implemented a custom command to reset the password of a user. 
- Used 3 interfaces: Followable, Likeable and Output for app abstraction.
- Used switch case to implement the commands.
```

## Classes and Methods

- `App` contains users,posts and comments arraylists, as well as the methods:
  `checkCredentials`,`authenticate`, `login`, `getID`, `getString`, `getData`


- `User` contains the user's ID, username, password, followers and following
  arraylists and the total number of likes and implements Followable while also
  containing the methods `getID`, `getPassword`, `setUserID`, `setPassword`,
  `setLikes`, `checkDuplicateUser`, `checkUsername`, `checkPassword`,
  `checkFollow`, `toStringFollowers`, `toStringLikes`, `compareToFollowers`,
  `compareToLikes`


- `Post` contains the post's ID, text, date, likes and comments arraylists and
  implements Likeable while also containing the methods `getID`, `getLikes`,
  `getID`, `setPostID`, `checkText`, `toStringUser`, `toStringFollow`,
  `toStringLikes`, `toStringComments`, `toStringDetails`, `compareToByID`,
  `compareToByLikes`, `compareToByComments`


- `Comment` contains the comment's ID, text, date and likes arraylists and
  implements Likeable while also containing the methods
  `getID`, `setCommentID`, `checkText`, `toStringUser`, `compareToByID`

## Command List and Implementation Details

- `-create-user` creates a new user with the given credentials and adds it to
  the users arraylist


- `-change-password` changes the password of the given user if the old password
  is correct and the new password is valid


- `-follow-user-by-username` adds the user to the followers list of the given
  user if the user exists and is not already followed


- `-unfollow-user-by-username` removes the user from the followers list of the
  given user


- `-get-following` prints the list of users followed by the given user


- `-get-followers` prints the list of users following the given user


- `-create-post` creates a new post with the given text and adds it to the
  posts arraylist


- `delete-post-by-id` deletes the post with the given ID if it exists


- `-like-post` adds a like to the post with the given ID if it exists and is
  not already liked by the user


- `-unlike-post` removes a like from the post with the given ID if it exists


- `-comment-post` adds a comment to the post with the given ID if it exists


- `-delete-comment-by-id` deletes the comment with the given ID if it exists


- `-like-comment` adds a like to the comment with the given ID if it exists and
  is not already liked by the user


- `-unlike-comment` removes a like from the comment with the given ID if it

All "-get" commands use individual created methods to sort the data and print,
by implementing distinct compareTo and toString methods for each command.

- `-get-most-followed-users` prints the list of users with the most followers
  in descending order


- `-get-most-liked-users` prints the list of users with the most likes in
  descending order


- `-get-post-details` prints the details of the post with the given ID if it
  exists


- `-get-most-like-posts` prints the list of posts with the most likes in
  descending order


- `-get-most-commented-posts` prints the list of posts with the most comments
  in descending order


- `-get-user-posts` prints the list of posts of the given user in descending
  order by date, if the user is followed by the authenticated user


- `-get-following-posts` prints the list of posts of the users followed by the
  authenticated user in descending order by date


- `-cleanup-all` deletes all the data from the app and resets the ids to 0

## Bonus

### Limit cases
1. Implement a custom command to reset the password of a user
2. Deletion makes the ID of the deleted object available for the next object
   created
3. Number of likes and comments is updated when a post/comment is deleted
### Commands Refactoring
1. Change IDs allocation for posts and comments to be done individually for each
   user, instead of globally for the app, therefore increasing the efficiency
2. Change the way the data is stored from arraylists to hashmaps, to increase
   the efficiency of the program
3. Change output message for invalid commands to be more explicit