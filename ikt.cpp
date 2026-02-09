#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>

using namespace std;

vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        if (!token.empty()) {
            token.erase(0, token.find_first_not_of(' '));
            token.erase(token.find_last_not_of(' ') + 1);
            tokens.push_back(token);
        }
    }
    return tokens;
}

class Recipe {
private:
    string name;
    vector<string> ingredients;
    string instructions;
    int difficulty;

public:
    Recipe(string n, vector<string> ingr, string instr, int diff) 
        : name(n), ingredients(ingr), instructions(instr), difficulty(diff) {}

    string getName() const { return name; }
    string getInstructions() const { return instructions; }
    
    double calculateMatch(const vector<string>& userFridge) const {
        if (ingredients.empty()) return 0.0;
        
        int matchCount = 0;
        for (const auto& recipeItem : ingredients) {
            if (find(userFridge.begin(), userFridge.end(), recipeItem) != userFridge.end()) {
                matchCount++;
            }
        }
        return (static_cast<double>(matchCount) / ingredients.size()) * 100.0;
    }
};

class Cookbook {
private:
    vector<Recipe> recipes;
    string dbFileName;

    void generateDefaultDatabase() {
        ofstream file(dbFileName);
        
        file << "Classic Omelette|eggs,salt,oil|Whisk eggs with salt, fry in oil|1" << endl;
        file << "Cheese Omelette|eggs,cheese,salt,oil|Whisk eggs, add cheese, fry until golden|1" << endl;
        file << "Fried Eggs|eggs,oil,salt|Heat oil, crack eggs, fry to preference|1" << endl;
        file << "Scrambled Eggs|eggs,oil,salt|Whisk eggs, fry while stirring constantly|1" << endl;
        file << "Egg Drop Soup|egg,water,salt|Boil water, slowly pour in whisked egg|1" << endl;
        file << "Vegetable Omelette|eggs,vegetables,oil|Fry veggies, pour eggs over them|1" << endl;
        file << "Oatmeal (Water)|oats,water,salt|Boil water, add oats, cook 5-10 mins|1" << endl;
        file << "Oatmeal (Milk)|oats,milk,sugar|Boil milk, add oats and sugar, cook until soft|1" << endl;
        file << "Rice Porridge|rice,water,milk,salt,sugar|Boil rice in water/milk mixture|1" << endl;
        file << "Buckwheat Porridge|buckwheat,water,salt|Wash buckwheat, boil in salted water (1:2 ratio)|1" << endl;
        file << "Millet Porridge|millet,water,milk,salt|Wash millet, boil until soft|1" << endl;
        file << "Rice with Milk|rice,milk,sugar|Boil rice, add hot milk and sugar|1" << endl;
        file << "Pasta with Butter|pasta,butter,salt|Boil pasta, drain, mix with butter|1" << endl;
        file << "Pasta with Cheese|pasta,cheese,salt|Boil pasta, drain, sprinkle with grated cheese|1" << endl;
        file << "Pasta with Sausage|pasta,sausage,oil|Boil pasta, fry sliced sausages, mix|1" << endl;
        file << "Spaghetti with Tomato Sauce|spaghetti,tomato paste,oil|Boil spaghetti. Fry paste with oil, mix.|1" << endl;
        file << "Pasta with Ketchup|pasta,ketchup|The classic student meal: boil pasta, add ketchup|1" << endl;
        file << "Pasta with Egg|pasta,egg,oil|Boil pasta, fry with an egg in the pan|1" << endl;
        file << "Macaroni Soup|macaroni,water,salt|Boil water, add macaroni and salt|1" << endl;
        file << "Pasta with Oil|pasta,oil|Boil pasta, toss with oil to prevent sticking|1" << endl;
        file << "Sweet Milk Soup|milk,pasta,sugar|Boil milk, add small pasta and sugar|1" << endl;
        file << "Fried Potatoes|potatoes,oil,salt|Peel, slice, and fry in oil until crispy|1" << endl;
        file << "Mashed Potatoes|potatoes,water,salt|Boil potatoes, mash with liquid|1" << endl;
        file << "Potatoes with Onions|potatoes,onion,oil|Fry potatoes together with chopped onions|1" << endl;
        file << "Baked Potatoes|potatoes,oil,salt|Cut potatoes, coat in oil/salt, bake in oven|1" << endl;
        file << "Potato Soup|potatoes,water,salt|Boil diced potatoes in salted water|1" << endl;
        file << "Potato Pancakes|potatoes,egg,flour|Grate potatoes, mix with egg/flour, fry|1" << endl;
        file << "Chicken with Potatoes|chicken,potatoes,oil|Fry or bake chicken pieces with potatoes|1" << endl;
        file << "Mushrooms with Potatoes|potatoes,mushrooms,oil|Fry potatoes, add mushrooms, cook until done|1" << endl;
        file << "Potato Stew|potatoes,water|Simmer potatoes until they fall apart|1" << endl;
        file << "Rice with Vegetables|rice,frozen vegetables,oil|Fry veggies, add boiled rice|1" << endl;
        file << "Rice with Chicken|rice,chicken,salt|Boil rice. Fry chicken. Mix.|1" << endl;
        file << "Rice with Egg|rice,egg,oil|Fry rice, crack an egg into it, stir|1" << endl;
        file << "Rice with Canned Fish|rice,canned fish|Boil rice, mix with canned fish|1" << endl;
        file << "Simple Fried Rice|rice,egg,oil|Fry yesterday's rice with egg and oil|1" << endl;
        file << "Rice with Carrots|rice,carrots,oil|Fry grated carrots, mix with rice|1" << endl;
        file << "Rice with Sausage|rice,sausage|Boil rice, add sliced fried sausage|1" << endl;
        file << "Simple Pilaf|rice,chicken,carrots,oil|Fry chicken and carrots, add rice and water, simmer|1" << endl;
        file << "Boiled Rice|rice,water|Wash rice, boil until water absorbs|1" << endl;
        file << "Rice with Butter|rice,butter|Boil rice, add a slice of butter|1" << endl;
        file << "Vegetable Rice Soup|rice,vegetables,water|Boil water, add rice and veggies|1" << endl;
        file << "Egg & Rice Bowl|rice,egg|Boil rice, top with a fried egg|1" << endl;
        file << "Chicken Soup|chicken,potatoes,carrots,water|Boil chicken, add veggies, cook until soft|1" << endl;
        file << "Noodle Soup|noodles,water,salt|Boil water, add noodles and spices|1" << endl;
        file << "Vegetable Soup|potatoes,carrots,onion,water|Chop veggies, boil in water|1" << endl;
        file << "Cheese Soup|processed cheese,potatoes,water|Boil potatoes, melt cheese in the water|1" << endl;
        file << "Instant Noodles Upgrade|instant noodles,egg|Cook noodles, add egg (poached or raw)|1" << endl;
        file << "Pancakes|flour,milk,eggs,oil|Mix batter, fry thin pancakes|1" << endl;
        file << "Crepes|flour,milk,eggs|Mix liquid batter, fry very thin|1" << endl;
        file << "Fritters|flour,kefir,egg|Mix thick batter with kefir, fry|1" << endl;
        file << "Toast with Cheese|bread,cheese|Put cheese on bread, microwave or heat|1" << endl;
        file << "Toast with Egg|bread,egg|Fry bread, top with egg|1" << endl;
        file << "Sandwich with Sausage|bread,sausage|Slice bread, add sausage|1" << endl;
        file << "Sandwich with Cheese|bread,cheese|Slice bread, add cheese|1" << endl;
        file << "Garlic Bread|bread,garlic,oil|Rub bread with garlic, fry in oil|1" << endl;
        file << "Egg Fried Bread|bread,egg,oil|Dip bread in beaten egg, fry|1" << endl;
        file << "Bread Croutons|bread,oil|Cut bread into cubes, fry until crispy|1" << endl;
        file << "Egg Sandwich|bread,egg|Boiled egg slices on bread|1" << endl;
        file << "Cheese Sandwich|bread,cheese|Just bread and cheese|1" << endl;
        file << "Hot Dog|sausage,bun|Boil sausage, put in bun|1" << endl;
        file << "Lavash with Cheese|lavash,cheese|Wrap cheese in lavash, heat up|1" << endl;
        file << "Lavash with Egg|lavash,egg|Wrap egg in lavash, fry|1" << endl;
        file << "Fried Dumplings|frozen dumplings,oil|Heat oil, fry dumplings until golden|1" << endl;
        file << "Boiled Dumplings|frozen dumplings,water|Boil water, add dumplings, cook 5-7 mins|1" << endl;
        file << "Lazy Dumplings|cottage cheese,egg,flour|Mix, roll into balls, boil|1" << endl;
        file << "Cabbage Salad|cabbage,oil,salt|Chop cabbage, squeeze with salt, add oil|1" << endl;
        file << "Tomato & Cucumber Salad|tomato,cucumber,oil|Chop veggies, mix with oil|1" << endl;
        file << "Salad with Canned Corn|corn,oil,salt|Mix corn with oil or mayo|1" << endl;
        file << "Salad with Beans|canned beans,onion|Mix beans with chopped onion|1" << endl;
        file << "Simple Salad|any vegetables,oil|Mix whatever veggies you have with oil|1" << endl;
        file << "Fried Cabbage|cabbage,oil,salt|Chop cabbage, fry in pan until soft|1" << endl;
        file << "Stewed Vegetables|mixed vegetables,oil|Simmer frozen veggie mix in pan|1" << endl;
        file << "Fried Mushrooms|mushrooms,oil|Slice mushrooms, fry until water evaporates|1" << endl;
        file << "Simple Stir Fry|vegetables,oil|High heat fry vegetables quickly|1" << endl;
        file << "Boiled Sausages|sausages,water|Boil sausages for 3-5 mins|1" << endl;
        file << "Fried Sausages|sausages,oil|Slice sausages, fry until browned|1" << endl;
        file << "Boiled Eggs|eggs,water|Boil eggs (5 mins soft, 10 mins hard)|1" << endl;
        file << "Cottage Cheese with Sugar|cottage cheese,sugar|Mix and eat|1" << endl;
        file << "Cottage Cheese with Banana|cottage cheese,banana|Slice banana into cottage cheese|1" << endl;
        file << "Simple Gravy|flour,oil,water|Fry flour, slowly add water and stir|1" << endl;
        
        file.close();
    }

public:
    Cookbook(string fileName) : dbFileName(fileName) {}

    void loadRecipes() {
        ifstream checkFile(dbFileName);
        if (!checkFile.good()) {
            cout << "[System] Database not found. Generating default recipe book..." << endl;
            generateDefaultDatabase();
        }
        checkFile.close();

        ifstream file(dbFileName);
        string line;
        while (getline(file, line)) {
            vector<string> parts = split(line, '|');
            if (parts.size() >= 4) {
                recipes.emplace_back(parts[0], split(parts[1], ','), parts[2], stoi(parts[3]));
            }
        }
        file.close();
        cout << "[System] Recipe Book Loaded. Total recipes: " << recipes.size() << endl;
    }

    void searchRecipes(const vector<string>& fridge) {
        cout << "\n--- SEARCH RESULTS ---\n";
        
        struct Result {
            const Recipe* r;
            double matchPercent;
        };
        vector<Result> results;

        for (const auto& recipe : recipes) {
            double match = recipe.calculateMatch(fridge);
            if (match > 0) { 
                results.push_back({&recipe, match});
            }
        }

        sort(results.begin(), results.end(), [](const Result& a, const Result& b) {
            return a.matchPercent > b.matchPercent;
        });

        if (results.empty()) {
            cout << "No recipes found. Go shopping!\n";
            return;
        }

        for (const auto& res : results) {
            cout << fixed << setprecision(0);
            cout << "[" << res.matchPercent << "% Match] " << res.r->getName() << endl;
            if (res.matchPercent < 100) {
                cout << "    (Missing some ingredients)\n";
            }
            cout << "    Instructions: " << res.r->getInstructions() << endl;
            cout << "------------------------\n";
        }
    }

    void showAllRecipes() {
        cout << "\n--- ALL RECIPES ---\n";
        for (const auto& r : recipes) {
            cout << "* " << r.getName() << endl;
        }
    }
};

int main() {
    cout << "====================================\n";
    cout << "             STUDENT CHEF           \n";
    cout << "====================================\n";

    Cookbook myBook("recipes_data.txt");
    myBook.loadRecipes();

    vector<string> myFridge;
    int choice;

    while (true) {
        cout << "\nMENU:\n";
        cout << "1. Show All Recipes\n";
        cout << "2. Enter My Ingredients\n";
        cout << "3. Find What To Cook\n";
        cout << "4. Exit\n";
        cout << "> ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(32767, '\n');
            continue;
        }

        if (choice == 1) {
            myBook.showAllRecipes();
        }
        else if (choice == 2) {
            myFridge.clear();
            cout << "Enter ingredients (English, lowercase, e.g., 'eggs').\n";
            cout << "Type 'done' to finish.\n";
            string item;
            while (true) {
                cout << "Add Item > ";
                cin >> item;
                if (item == "done") break;
                myFridge.push_back(item);
            }
            cout << "Fridge updated! You have " << myFridge.size() << " items.\n";
        }
        else if (choice == 3) {
            if (myFridge.empty()) {
                cout << "[!] Your fridge is empty! Use Option 2 first.\n";
            } else {
                myBook.searchRecipes(myFridge);
            }
        }
        else if (choice == 4) {
            cout << "Goodbye!\n";
            break;
        }
    }

    return 0;
}