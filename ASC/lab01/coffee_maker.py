
"""
A command-line controlled coffee maker.
"""

import sys
from load_recipes import load_recipes

"""
Implement the coffee maker's commands. Interact with the user via stdin and print to stdout.

Requirements:
    - use functions
    - use __main__ code block
    - access and modify dicts and/or lists
    - use at least once some string formatting (e.g. functions such as strip(), lower(),
    format()) and types of printing (e.g. "%s %s" % tuple(["a", "b"]) prints "a b"
    - BONUS: read the coffee recipes from a file, put the file-handling code in another module
    and import it (see the recipes/ folder)

There's a section in the lab with syntax and examples for each requirement.

Feel free to define more commands, other coffee types, more resources if you'd like and have time.
"""

"""
Tips:
*  Start by showing a message to the user to enter a command, remove our initial messages
*  Keep types of available coffees in a data structure such as a list or dict
e.g. a dict with coffee name as a key and another dict with resource mappings (resource:percent)
as value
"""

# Commands
EXIT = "exit"
LIST_COFFEES = "list"
MAKE_COFFEE = "make"  #!!! when making coffee you must first check that you have enough resources!
HELP = "help"
REFILL = "refill"
RESOURCE_STATUS = "status"
commands = [EXIT, LIST_COFFEES, MAKE_COFFEE, REFILL, RESOURCE_STATUS, HELP]

# Coffee examples
ESPRESSO = "espresso"
AMERICANO = "americano"
CAPPUCCINO = "cappuccino"

# Resources examples
WATER = "water"
COFFEE = "coffee"
MILK = "milk"

# Coffee maker's resources - the values represent the fill percents
RESOURCES = {WATER: 100, COFFEE: 100, MILK: 100}

# Coffee recipes
recipes = load_recipes()

"""
Example result/interactions:

I'm a smart coffee maker
Enter command:
list
americano, cappuccino, espresso
Enter command:
status
water: 100%
coffee: 100%
milk: 100%
Enter command:
make
Which coffee?
espresso
Here's your espresso!
Enter command:
refill
Which resource? Type 'all' for refilling everything
water
water: 100%
coffee: 90%
milk: 100%
Enter command:
exit
"""

def refill(request):
    """ This function refills resources """
    if request == "all":
        for resource in RESOURCES:
            RESOURCES[resource] = 100
            print(f"{resource}: {RESOURCES[resource]}%")
    elif request in RESOURCES:
        RESOURCES[request] = 100
        for resource, percentage in RESOURCES.items():
            print(f"{resource}: {percentage}%")
    else:
        print("Invalid resource")

def make_coffee(coffee):
    """ This function makes coffe """
    if coffee not in [ESPRESSO, AMERICANO, CAPPUCCINO]:
        print("Invalid coffee")
        return
    if coffee == ESPRESSO:
        recipe = recipes[ESPRESSO]
    elif coffee == AMERICANO:
        recipe = recipes[AMERICANO]
    else:
        recipe = recipes[CAPPUCCINO]
    for resource, percentage in recipe.items():
        if RESOURCES[resource] < percentage:
            print("Not enough resources")
            return
        RESOURCES[resource] -= percentage
    print(f"Here's your {coffee}!")




def main():
    """ Main function """
    print("I'm a simple coffee maker")
    print("Enter command:")

    while True:
        command = sys.stdin.readline().strip().lower()
        if command not in commands:
            print("Invalid command. Type 'help' for a list of commands.")
            command = sys.stdin.readline()
            command = command.strip().lower()
        if command == EXIT:
            print("Goodbye!")
            break
        if command == LIST_COFFEES:
            print(", ".join([ESPRESSO, AMERICANO, CAPPUCCINO]))
        if command == RESOURCE_STATUS:
            for resource, fill in RESOURCES.items():
                print(f"{resource}: {fill}%")
        if command == REFILL:
            print("Which resource? Type 'all' for refilling everything")
            resource = sys.stdin.readline().strip().lower()
            refill(resource)
        if command == HELP:
            print(f"Available commands: {', '.join(commands)}")
        if command == MAKE_COFFEE:
            print("Which coffee?")
            coffee = sys.stdin.readline().strip().lower()
            make_coffee(coffee)

if __name__ == "__main__":
    main()
