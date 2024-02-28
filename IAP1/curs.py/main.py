#lucruri invatate la curs

# importam clasa Flask
from flask import Flask
# cream o instanta a clasei
app = Flask(__name__)
# specificam ce URL ne va apela functia
@app.route("/")
def hello_world():
 # returnam un mesaj in browser (default HTML)
 return "<p>Hello, World!</p>"
# rulam serverul de Flask
if __name__ == "__main__":
 app.run(host="0.0.0.0")

def print_hi(name):
    print(f'Hi, {name}')  # Press Ctrl+F8 to toggle the breakpoint.


# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    print_hi('Dan Coi')

# See PyCharm help at https://www.jetbrains.com/help/pycharm/

