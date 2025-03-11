
"""
    Read the recipe files and stores the recipes in a dictionary.
"""

import os

"""
	Bonus task: load all the available coffee recipes from the folder 'recipes/'
	File format:
		first line: coffee name
		next lines: resource=percentage

	info and examples for handling files:
		http://cs.curs.pub.ro/wiki/asc/asc:lab1:index#operatii_cu_fisiere
		https://docs.python.org/3/library/io.html
		https://docs.python.org/3/library/os.path.html
"""

RECIPES_FOLDER = "recipes"

def load_recipes():
    """ The function loads all the available coffee recipes from the folder 'recipes/'"""
    recipes = {}
    for filename in os.listdir(RECIPES_FOLDER):
        with open(os.path.join(RECIPES_FOLDER, filename), 'r', encoding="utf-8") as file:
            coffee_name = file.readline().strip()
            recipe = {}
            for line in file:
                resource, percentage = line.strip().split("=")
                recipe[resource] = int(percentage)
            recipes[coffee_name] = recipe
    return recipes

def main():
    """ Main function """
    # recipes = load_recipes()
    # for coffee, recipe in recipes.items():
    #     print(coffee)
    #     for resource, percentage in recipe.items():
    #         print(f"{resource}: {percentage}%")
    #     print()
    print(load_recipes())

if __name__ == "__main__":
    main()
