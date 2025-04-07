#include <iostream>
#include <limits>
#include <vector>
#include <string>

using namespace std;

int health = 100; // Health points of the player
vector<string> inventory; // Inventory to hold items

void intro();
int getValidatedInput(int min, int max);
void firstDecision();
void encounterScenario();
void endGame(string result);
void addItem(string item);
void showInventory();
void takeDamage(int damage);

int main() {
    intro();
    firstDecision();
    return 0;
}

void intro() {
    cout << "====================================\n";
    cout << "      Escape the Dungeon\n";
    cout << "====================================\n";
    cout << "You find yourself trapped in a dark, damp dungeon.\n";
    cout << "Your mission is to find a way out.\n";
    cout << "Good luck, adventurer!\n\n";
}

int getValidatedInput(int min, int max) {
    int choice;
    while (true) {
        cout << "Enter your choice (" << min << "-" << max << "): ";
        cin >> choice;

        if (cin.fail() || choice < min || choice > max) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please try again.\n";
        } else {
            break;
        }
    }
    return choice;
}

void firstDecision() {
    cout << "\nYou see three paths:\n";
    cout << "1. Left tunnel (dimly lit, smells of sulfur)\n";
    cout << "2. Right passage (cold breeze, eerie silence)\n";
    cout << "3. Forward into the darkness\n";

    int path = getValidatedInput(1, 3);

    if (path == 1) {
        cout << "\nYou carefully step into the left tunnel...\n";
        cout << "A growl echoes — something is waiting ahead.\n";
        encounterScenario();
    }
    else if (path == 2) {
        cout << "\nYou walk down the right passage...\n";
        cout << "The floor collapses beneath you! You fall into a pit.\n";
        endGame("lose");
    }
    else {
        cout << "\nYou push forward, feeling your way in the darkness...\n";
        cout << "You trip over something... it's a lever.\n";
        encounterScenario();
    }
}

void encounterScenario() {
    cout << "\nYou encounter a giant rat blocking your way!\n";
    cout << "What will you do?\n";
    cout << "1. Fight it\n";
    cout << "2. Run away\n";
    cout << "3. Try to trick it\n";
    cout << "4. Use an item\n";

    int choice = getValidatedInput(1, 4);
    int nextChoice = 0; // Declare nextChoice outside the switch

    switch (choice) {
        case 1:
            cout << "\nYou draw your weapon and fight! It's a tough battle...\n";
            takeDamage(30);
            if (health <= 0) {
                endGame("lose");
            }
            cout << "But you defeat the beast and move forward!\n";
            cout << "You find a ladder leading to the surface. You escape!\n";
            endGame("win");
            break;
        case 2:
            cout << "\nYou turn to run — but the rat is faster.\n";
            takeDamage(50);
            if (health <= 0) {
                endGame("lose");
            }
            cout << "You’ve been caught. Game Over.\n";
            endGame("lose");
            break;
        case 3:
            cout << "\nYou distract the rat with noise and sneak past.\n";
            addItem("Hidden Key");
            cout << "The rat is confused and scurries away.\n";
            cout << "You find a hidden key on the floor and pick it up.\n";
            cout << "The key seems to unlock something... perhaps a door up ahead.\n";
            cout << "Do you want to continue exploring?\n";
            cout << "1. Yes\n";
            cout << "2. No, I want to return to the previous path\n";
            nextChoice = getValidatedInput(1, 2); // Get the next choice here
            if (nextChoice == 1) {
                cout << "\nYou continue your journey...\n";
                firstDecision();
            } else {
                cout << "\nYou turn around and retrace your steps...\n";
                firstDecision();
            }
            break;
        case 4:
            showInventory();
            cout << "You use the torch in your bag. The rat is scared of fire!\n";
            cout << "It runs off and you escape. YOU WIN!\n";
            endGame("win");
            break;
    }
}

void endGame(string result) {
    if (result == "win") {
        cout << "Congratulations! You've escaped the dungeon!\n";
    } else if (result == "lose") {
        cout << "You were trapped forever... Better luck next time.\n";
    }
    cout << "====================================\n";
    cout << "Game Over\n";
    cout << "====================================\n";
    exit(0);
}

void addItem(string item) {
    inventory.push_back(item);
    cout << item << " has been added to your inventory.\n";
}

void showInventory() {
    cout << "\nYour inventory contains:\n";
    if (inventory.empty()) {
        cout << "Nothing...\n";
    } else {
        for (const string& item : inventory) {
            cout << "- " << item << endl;
        }
    }
}

void takeDamage(int damage) {
    health -= damage;
    cout << "You have taken " << damage << " damage. Health remaining: " << health << endl;
    if (health <= 0) {
        endGame("lose");
    }
}
