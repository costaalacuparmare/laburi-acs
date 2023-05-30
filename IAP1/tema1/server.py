from flask import Flask, request

# Note: static folder means all files from there will be automatically served over HTTP
app = Flask(__name__, static_folder="public")

# TODO Task 03: you can use a global variable for storing the auth session
# e.g., add the "authenticated" (boolean) and "username" (string) keys.
session = {}

# you can use a dict as user/pass database
ALLOWED_USERS = { "admin": "n0h4x0rz-plz" }

# Task 04: database filename
DATABASE_FILE = "database.txt"

@app.route("/")
def index():
    # TODO Task 02: render the index page using our template
    return "TODO"

# TODO Task 03: Authentication
@app.route("/login.html")
def login():
    error_msg = ""
    if request.method == "POST":
        username = request.form.get("username", "")
        password = request.form.get("password", "")
        # TODO: verify credentials and set the session dict
        pass
    # return render_template("login.html", error_msg=error_msg)
    return "TODO"

@app.route("/logout.html")
def logout():
    # TODO Task 03: clear authentication status
    #session["authenticated"] = 0;
    #return redirect("/index.html")
    return "TODO"

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

# TODO Task 04: Save Account Details
@app.route("/account-details")
def upload():
    # Hint: if method == "GET", read the data from the database and pass it to the template
    # otherwise (when POST), replace the database with the user-provided data.
    return "TODO"

# Run the webserver (port 5000 - the default Flask port)
if __name__ == "__main__":
    app.run(debug=True, port=5000)

