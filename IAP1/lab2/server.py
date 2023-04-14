from flask import Flask, request, render_template

# Note: static folder means all files from there will be automatically served over HTTP
app = Flask(__name__, static_folder="public")

# TODO Task 03: you can use a global variable for storing the auth session
# e.g., add the "authenticated" (boolean) and "username" (string) keys.
session = {}

# you can use a dict as user/pass database
ALLOWED_USERS = { "admin": "n0h4x0rz-plz" }

# Task 04: database filename
DATABASE_FILE = "database.txt"

@app.route("/index.html")
def index():
    # TODO Task 02: render the index page using our template
    return render_template("index.html")
@app.route("/about.html")
def about():
    return render_template("about.html")

# TODO Task 03: Authentication
@app.route("/login.html")
def login():
    error_msg = ""
    if request.method == "POST":
        username = request.form.get("username", "")
        password = request.form.get("password", "")
        if username in ALLOWED_USERS and ALLOWED_USERS[username] == password:
            session["authenticated"] = True
            session["username"] = username
            return "Authenticated"
        else:
            error_msg = "Invalid username or password"
    return render_template("login.html", error_msg=error_msg)

@app.route("/logout.html")
def logout():
    session.pop('authenticated', None)
    session.pop('username', None)
    return "Logged out"

# You can use this as a starting point for Task 04
# (note: you need a "write" counterpart)
def read_database(filename):
    """ Reads the user account details database file (line by line). """
    with open(filename, "rt") as f:
        line1 = f.readline()
        line2 = f.readline()
        age = int(f.readline())
        return {
            "first_name": line1,
            "last_name": line2,
            "age": age,
        }

@app.route("/account-details", methods=["GET", "POST"])
def account_details():
    if request.method == "POST":
        first_name = request.form['first_name']
        last_name = request.form['last_name']
        age = request.form['age']

        # Write the user's details to the database file
        with open('database.txt', 'w') as f:
            f.write(f"{first_name},{last_name},{age}\n")
    data = read_database(DATABASE_FILE)
    return render_template("account-details.html", data=data)

# Run the webserver (port 5000 - the default Flask port)
if __name__ == "__main__":
    app.run(debug=True, port=5000)