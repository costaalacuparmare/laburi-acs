# Networking Protocols - 4th Homework

### Constantinescu Vlad 324CB

The archive contains:

- `client.c` - the server implementation and the main function
- `helpers.c` - the helper functions taken from the laboratory
- `helpers'h` - the helper functions taken from the laboratory
- `requests.c` - the requests functions taken from the laboratory and modified
- `requests.h` - the requests functions taken from the laboratory and modified
- `buffer.c` - the buffer functions taken from the laboratory
- `buffer.h` - the buffer functions taken from the laboratory
- `parson.c` - the parson functions for parsing JSON recommended by the homework
- `parson.h` - the parson functions for parsing JSON recommended by the homework
- `Makefile` - the makefile used to compile the project
- `README.md` - the readme file

### Buffer Functions
Given the functions are from the laboratory and are recommended to be used for helper functions, I will
not describe them here.

### Helper Functions
Given the functions are from the laboratory and are recommended, I will
not describe them here.

### Requests Functions
- `compute_get_request`: - computes the GET request for the server
    - Adds GET to the request
    - Adds the url to the request
    - Adds the host to the request
    - Adds the connection to the request
    - Adds the content type to the request
    - Adds the content length to the request
    - Adds the cookie to the request if it is not NULL
    - Adds the JWT token for authorization to the request if it is not NULL (for all book requests)
  

- `compute_post_request`: - computes the POST request for the server
    - Adds POST to the request
    - Adds the url to the request
    - Adds the host to the request
    - Adds the connection to the request
    - Adds the content type to the request
    - Adds the content length to the request
    - Adds the cookie to the request if it is not NULL
    - Adds the JWT token for authorization to the request if it is not NULL (for all book requests)
    - Adds the payload to the request

  
- `compute_delete_request`: - computes the DELETE request for the server
    - Adds DELETE to the request
    - Adds the url to the request
    - Adds the host to the request
    - Adds the connection to the request
    - Adds the content type to the request
    - Adds the content length to the request
    - Adds the cookie to the request if it is not NULL
    - Adds the JWT token for authorization to the request if it is not NULL (for all book requests)

 
- General details: I used the helper functions to create the requests and automatically
add the "\r\n" at the end of each line.

### Parson Functions

I have decided to use the parson functions for parsing JSON because they are
recommended by the homework and are easy to use and have improved the handling
of JSON objects.

For payload creation, I used the parson functions to create the JSON object and
then convert it to a string based on the explanations provided in the GitHub
repository of the library.

### Client Functions

- `parse_command`: changes the string command to the corresponding command
in the enum list of commands and returns it for further processing.


- `get_respond`: uses parson functions to parse the response from the server
and modify it in a string format for output.


- `parse_response`: parses the response from the server and verifies if the
response is correct or not.
  - If the response is not correct, the function
  returns an error message.
  - If the response is correct, the function returns
  a success message or the data received from the server.


- `handle_register`: handles the register command and sends the request to the
server. The function also verifies if the response is correct or not.
  - Gets the username and password from stdin
  - Verifies if the username and password are correct
  - Creates the JSON payload for the request
  - Sends the request to the server
  - Parses the response from the server
  - Free the memory used for the request and response


- `handle_login`: handles the login command and sends the request to the server.
The function also verifies if the response is correct or not.
  - Gets the username and password from stdin
  - Verifies if the username and password are correct
  - Creates the JSON payload for the request
  - Sends the request to the server
  - Parses the response from the server
  - Memorizes the session cookie in a global variable
  - Frees the memory used for the request and response


- `handle_enter_library`: handles the enter_library command and sends the request
to the server. The function also verifies if the response is correct or not.
  - Checks if user is logged in by verifying the session cookie
  - Sends the request with the session cookie to the server
  - Parses the response from the server
  - Memorizes the JWT token in a global variable
  - Frees the memory used for the request and response


- `handle_get_books`: handles the get_books command and sends the request to the
server. The function also verifies if the response is correct or not.
  - Checks if user is in the library by verifying the JWT token
  - Sends the request with the JWT token to the server
  - Parses the response from the server
  - Frees the memory used for the request and response


- `handle_get_book`: handles the get_book command and sends the request to the
server. The function also verifies if the response is correct or not.
  - Checks if user is in the library by verifying the JWT token
  - Gets the id of the book from stdin, verifies if it is correct
  - Sends the request with the JWT token and the id to the server
  - Parses the response from the server
  - Frees the memory used for the request and response


- `handle_add_book`: handles the add_book command and sends the request to the
server. The function also verifies if the response is correct or not.
  - Checks if user is in the library by verifying the JWT token
  - Gets the title, author, genre, publisher and page number from stdin, verifies if they are correct
  - Creates the JSON payload for the request
  - Sends the request with the JWT token, the session cookie and the payload to the server
  - Parses the response from the server
  - Frees the memory used for the request and response


- `handle_delete_book`: handles the delete_book command and sends the request to the
server. The function also verifies if the response is correct or not.
  - Checks if user is in the library by verifying the JWT token
  - Gets the id of the book from stdin, verifies if it is correct
  - Sends the request with the JWT token, the session cookie and the id to the server
  - Parses the response from the server
  - Frees the memory used for the request and response


- `handle_logout`: handles the logout command and sends the request to the
server. The function also verifies if the response is correct or not.
  - Sends the request with the session cookie to the server
  - Parses the response from the server
  - If the response is correct, the function resets the session cookie and the JWT token
  - Frees the memory used for the request and response


### Tasks and Implementation Details
- The client is implemented in the `client.c` file.
- The client is implemented using the functions described above.
- The clients receive the commands using `fgets` from stdin.
- The commands are parsed using the `parse_command` function.
- The command codes are then used in a switch case to call the corresponding function.
- Each function is implemented as described above.
- I have decided to implement the functions in the order of the commands in the enum list.
- I have also added an error message for the case when the command is not recognized.