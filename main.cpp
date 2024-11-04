/*
    Lab 27: Villager Map (Update from template code)
        1. Change the data we're storing to friendship level (0-10), the villager's species (string), and the villager's catchphrase (string).
        2. Change the data structure held in the std::map's value from a vector to a std::tuple.
        3. Convert the rest of the code to support the new std::tuple.
        4. Make the program menu-driven that will support the given menu.
            1. Add Villager
            2. Delete Villager
            3. Increase Friendship
            4. Decrease Friendship
            5. Search for Villager
            6. Exit
        5. The increase/decrease friendship can just add a point each time, making sure that the level is never negative.
        6. After each operation is complete, output the std::map's contents of villager data in this format (you can improve on the format if you wish):
            Villager details:
            Drago [5, Alligator, Snap to It!]
            Kyle [10, Wolf, Hubba hubba!]
            Raymond [8, Cat, Nice fit]
        7. When the villager chooses to add a villager, present a submenu for data entry:
            Enter choice: 1
            Villager name: Del
            Friendship level: 8
            Species: Alligator
            Catchphrase: Got a snack?
            Del added.
*/

#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;

// variable dec
const int FRIENDSHIP_MAX_VALUE = 10;
const int FRIENDSHIP_MIN_VALUE = 0;

// function dec
int MainMenu();
bool IsValidOption(string, int, int);
bool IsAnyVillagers(const map<string, tuple<int, string, string>> &);
void DisplayVillage(const map<string, tuple<int, string, string>> &);
void AddVillager(map<string, tuple<int, string, string>> &);
void DeleteVillager(map<string, tuple<int, string, string>> &);
void IncreaseFriendship(map<string, tuple<int, string, string>> &);
void DecreaseFriendship(map<string, tuple<int, string, string>> &);
void SearchForVillager(const map<string, tuple<int, string, string>> &);

int main()
{
    // declarations
    int userSelectedOption = 0;                      // represents user option chosen from menu
    map<string, tuple<int, string, string>> village; // map representing a group of villagers (village)

    // prompt user for selection and input
    // user selection 4 is the program exit code
    do
    {
        userSelectedOption = MainMenu();
        switch (userSelectedOption)
        {
        case 1:
            AddVillager(village);
            break;
        case 2:
            DeleteVillager(village);
            break;
        case 3:
            IncreaseFriendship(village);
            break;
        case 4:
            DecreaseFriendship(village);
            break;
        case 5:
            SearchForVillager(village);
            break;
        default:
            break;
        }
    } while (userSelectedOption != 6);

    return 0;
}

// main menu fuction for user selection
int MainMenu()
{
    string userInput = "";

    do
    {
        // output prompt
        cout << "*** VILLAGE MANAGER 3001 ***" << "\n"
             << "[1] Add a villager" << "\n"
             << "[2] Delete a villager" << "\n"
             << "[3] Increase friendship" << "\n"
             << "[4] Decrease friendship" << "\n"
             << "[5] Search for villager" << "\n"
             << "[6] Exit" << "\n"
             << "Choice --> ";
        getline(cin, userInput); // get user input as string and test
        cout << "\n";
    } while (!IsValidOption(userInput, 1, 6));

    // if isValidOption passed, stoi(userInput) has already been tested and is safe
    return stoi(userInput);
}

// return t/f if userInput is a valid int between min and max
// helper function for main_menu and deleteVillager
// WARNING: stoi() will convert a double to an int or any string following an int.
// Ex: stoi("2.9") will return 2 and so will stoi("2tGznso"), etc.
bool IsValidOption(string userInput, int minOption, int maxOption)
{
    int selectedOption = 0;
    try
    {
        selectedOption = stoi(userInput);
    }
    catch (const std::exception &e)
    {
        cout << "Invalid input: Please enter a valid integer." << "\n\n";
        return false;
    }

    // if userInput is an int but outside expected range
    if (selectedOption < minOption || selectedOption > maxOption)
    {
        cout << "Invalid input: Please enter an integer between " << minOption << " and " << maxOption << "." << "\n\n";
        return false;
    }

    return true;
}

// tests if village has any villagers
bool IsAnyVillagers(const map<string, tuple<int, string, string>> &village)
{
    return village.size() > 0;
}

// output village to screen
void DisplayVillage(const map<string, tuple<int, string, string>> &village)
{
    if (!IsAnyVillagers(village))
    {
        cout << "No villagers in this village." << "\n\n";
        return;
    }

    int count = 0;
    cout << "Village:" << "\n";
    for (auto it = village.begin(); it != village.end(); it++)
    {
        auto [friendshipLevel, species, catchPhrase] = it->second;
        cout << "\t[" << ++count << "] " << it->first << " [" << friendshipLevel << ", " << species << ", " << catchPhrase << ")" << "\n";
    }
    cout << "\n";
}

// adds random villager to trip
void AddVillager(map<string, tuple<int, string, string>> &village)
{
    string name = "";
    int friendshipLevel = -1;
    string species = "";
    string catchPhrase = "";
    string userInput = ""; // temp string to capture user input before assigning value

    // get user input for villager info
    cout << "Villager name: ";
    getline(cin, name);
    // test to make sure user input for friendship level is valid int 0 to 10
    do
    {
        // output prompt
        cout << "Friendship level: ";
        getline(cin, userInput); // get user input as string and test
        cout << "\n";
    } while (!IsValidOption(userInput, 0, 10));
    // if isValidOption passed, stoi(userInput) has already been tested and is safe
    friendshipLevel = stoi(userInput);
    cout << "Species: ";
    getline(cin, species);
    cout << "Catchphrase: ";
    getline(cin, catchPhrase);

    // user input collected, add villager to village
    village.insert({name, make_tuple(friendshipLevel, species, catchPhrase)});

    cout << "Added to village: " << name << " [" << friendshipLevel << ", " << species << ", " << catchPhrase << "]" << "\n\n";

    DisplayVillage(village); // output village after completion
}

void DeleteVillager(map<string, tuple<int, string, string>> &village)
{
    // guard statement in case of empty list
    if (!IsAnyVillagers(village))
    {
        cout << "No villagers in this village to delete." << "\n\n";
        return;
    }

    string userInput = "";
    auto it = village.begin(); // iterator to first element

    // display Goats in current trip available for selection
    // prompt user for index to delete
    // WARNING: index DISPLAYED TO USER begins at 1
    do
    {
        DisplayVillage(village);
        cout << "Please enter index to delete --> ";
        getline(cin, userInput); // get user input as string
        // make sure user value is valid and delete
        if (IsValidOption(userInput, 1, village.size()))
        {
            advance(it, stoi(userInput) - 1); // -1 because index displayed to users starts at 1
            cout << "\n"
                 << "Updated Village After Removing: " << it->first << "\n";
            village.erase(it);
            DisplayVillage(village);
            break;
        }
    } while (true);
}

// increases friendship of all villagers by 1
void IncreaseFriendship(map<string, tuple<int, string, string>> &village)
{
    if (!IsAnyVillagers(village))
    {
        cout << "No villagers in this village to increase friendship." << "\n\n";
        return;
    }

    // loop through village increasing friendship by 1 if not == to max value
    for (auto it = village.begin(); it != village.end(); it++)
    {
        auto [friendshipLevel, species, catchPhrase] = it->second;
        if (friendshipLevel < FRIENDSHIP_MAX_VALUE)
        {
            village[it->first] = make_tuple(friendshipLevel + 1, species, catchPhrase);
        }
    }
    DisplayVillage(village); // output village after completion
}

// decreases friendship of all villagers by 1
void DecreaseFriendship(map<string, tuple<int, string, string>> &village)
{
    if (!IsAnyVillagers(village))
    {
        cout << "No villagers in this village to decrease friendship." << "\n\n";
        return;
    }

    // loop through village increasing friendship by 1 if not == to max value
    for (auto it = village.begin(); it != village.end(); it++)
    {
        auto [friendshipLevel, species, catchPhrase] = it->second;
        if (friendshipLevel > FRIENDSHIP_MIN_VALUE)
        {
            village[it->first] = make_tuple(friendshipLevel - 1, species, catchPhrase);
        }
    }
    DisplayVillage(village); // output village after completion
}

// searches for villager by name
void SearchForVillager(const map<string, tuple<int, string, string>> &village){
if (!IsAnyVillagers(village))
    {
        cout << "No villagers in this village." << "\n\n";
        return;
    }

    string name = "";

    cout << "Please enter villager name: ";
    getline(cin, name);

    auto it = village.find(name); // find villager by name

    // output results
    if (it != village.end())
    {
        cout << "Villager: " << name << " found in village!";
    } else {
        cout << "Villager: " << name << " NOT found in village!";
    }
    cout << endl;
}