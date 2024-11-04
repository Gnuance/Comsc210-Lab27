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

// function dec
int MainMenu();
bool IsValidOption(string, int, int);
bool IsAnyVillagers(map<string, tuple<int, string, string>> &);
void DisplayVillage(map<string, tuple<int, string, string>> &);
void AddVillager(map<string, tuple<int, string, string>> &);
void DeleteVillager(map<string, tuple<int, string, string>> &);
void IncreaseFriendship(map<string, tuple<int, string, string>> &);
void DecreaseFriendship(map<string, tuple<int, string, string>> &);

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
            IncreaseFrienship(village);
            break;
        case 4:
            DecreaseFrienship(village);
            break;
        case 5:
            SearchForVillager(village);
            break;
        default:
            break;
        }
    } while (userSelectedOption != 6);

    // access the map using a range-based for loop
    // cout << "Villagers and their favorite colors (range-based for loop):" << endl;
    // for (auto pair : villagerColors) {
    //     cout << pair.first << ": ";
    //     for (auto color : pair.second)
    //         cout << color << " ";
    //     cout << endl;
    // }

    // access the map using iterators
    // cout << "\nVillagers and their favorite colors (iterators):" << endl;
    // for (map<string, vector<string>>::iterator it = villagerColors.begin();
    //                                            it != villagerColors.end(); ++it) {
    //     cout << it->first << ": ";
    //     for (auto color : it->second) {
    //         cout << color << " ";
    //     }
    //     cout << endl;
    // }

    // delete an element
    villagerColors.erase("Raymond");

    // search for an element using .find() to avoid errors
    string searchKey = "Audie";
    auto it = villagerColors.find(searchKey);
    if (it != villagerColors.end())
    { // the iterator points to beyond the end of the map
      // if searchKey is not found
        cout << "\nFound " << searchKey << "'s favorite colors: ";
        for (auto color : it->second) // range loop to traverse the value/vector
            cout << color << " ";
        cout << endl;
    }
    else
        cout << endl
             << searchKey << " not found." << endl;

    // report size, clear, report size again to confirm map operations
    cout << "\nSize before clear: " << villagerColors.size() << endl;
    villagerColors.clear();
    cout << "Size after clear: " << villagerColors.size() << endl;

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

bool IsAnyVillagers(map<string, tuple<int, string, string>> &village)
{
    return village.size() > 0;
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
}

void DisplayVillage(map<string, tuple<int, string, string>> &village)
{
    if (village.size() < 1)
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

void IncreaseFriendship(map<string, tuple<int, string, string>> &)
{
}

void DecreaseFriendship(map<string, tuple<int, string, string>> &);