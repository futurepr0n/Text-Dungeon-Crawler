#include "Dungeon.h"
#include "Player.h"
#include <iostream>

using namespace std;

Dungeon::Dungeon(Player p)
{
    player = p;
}// check

void Dungeon::printActions(int numActions, string actions[]){
    cout << "Choose an action: \n";
    for (int i = 0; i < numActions; i++){
        cout << actions[i] << "\n";
    }
} //check

void Dungeon::handleFightActions(GameCharacter *enemy){
    string actions[] = {
        "A. Attack",
        "B. Retreat"
    };
    while(true){
        printActions(2, actions);
        string input;
        cin >> input;
        //handle the player actions
        if (input == "A" || input == "a"){
            int damage = enemy->takeDamage(player.attack);
            cout << "You have struck the enemy, and it has done " << damage << " of damage!\n";            
            return;
        }else if(input == "B" || input == "b"){
            player.changeRooms(player.previousRoom);
            enterRoom(player.currentRoom);
            return;
        }else {
            cout << "Incorrect choice\n";
        }
        //check enemy is dead
        if (enemy->checkIsDead()){
            cout << "Congradulations! You killed the "<< enemy->name <<" enemy!\n";
            player.increaseStats(10,5,5);
            player.currentRoom->clearEnemies();
            return;            
        }
        //handle enemy actions
        int damage = player.takeDamage(enemy->attack);
        cout<< enemy->name << "'s attack does " << damage << " Damage! \n";
        cout<< "You now have " << player.currentHealth<<" Health left. \n";
        if(player.checkIsDead()){
            return;
        }
    }
} // check

void Dungeon::handleRoomWithEnemy(Room *room){
    GameCharacter enemy = room->enemies.front();
    cout << "You enter the room and see a "<< enemy.name << "\n";
    string actions[] = {
        "A. Fight this mofo!" + enemy.name, 
        "B. Go back to previous room"
    };
    while(true){
        printActions(2, actions);
        string input;
        cin >> input;
        if (input == "A" || input == "a"){
            handleFightActions(&enemy);
            return;
        }else if(input == "B" || input == "b"){
            player.changeRooms(player.previousRoom);
            enterRoom(player.currentRoom);
            return;
        }else {
            cout << "Incorrect choice\n";
        }
    }
}//check

void Dungeon::handleLootActions(Room *room){
    Item item = room->items.front();
    int size = room->items.size();
    player.lootRoom(room);
    room->clearLoot();
    for (int i = 0; i < size; i++){
        cout << "You broke into the treasure and looks like you found " << item.name << ".\n";
        cout << "Your health is now " << player.currentHealth << ", your attack is now " << player.attack <<", and your defence is now " << player.defence << ".\n";
    }
} //check

void Dungeon::handleRoomWithChest(Room *room){
    cout << "You enter the room and see a large treasure chest.\n";
    string actions[] = {
        "A. Loot loot, woot woot", 
        "B. Move to another room"
    };
    while(true){
        printActions(2, actions);
        string input;
        cin >> input;
        if (input == "A" || input == "a"){
            handleLootActions(room);
            return;
        }else if(input == "B" || input == "b"){
            return;
        }else {
            cout << "Incorrect choice\n";
        }
    }
} //check

void Dungeon::handleEmptyRoom(Room *room){
    cout << "You enter the room but it is empty.\n";
    string actions[] = {"A. Move to another room"};
    while(true){
        printActions(1, actions);
        string input;
        cin >> input;
        if (input == "A" || input == "a"){
            return;
        }else{
            cout << "Incorrect choice\n";
        }
    }
} // check

void Dungeon::enterRoom(Room *room){
    if (room->enemies.size() !=0){
        handleRoomWithEnemy(room);
    }else if (room ->items.size()!=0){
        handleRoomWithChest(room);
    } else {
        handleEmptyRoom(room);
    }
} //check

void Dungeon::handleMovementActions(Room *room){
    while(true){
        if (room->pos == 0) {
            string actions[] = {"A. Move Right", "B. Move Down"};
            printActions(2, actions);
            string input;
            cin >> input;
            if (input == "A"||input == "a"){
                player.changeRooms(&rooms[1]);
                return;
            }else if (input == "B" || input == "b"){
                player.changeRooms(&rooms[2]);
                return;
            }else{
                cout<<"Incorrect choice\n";
            }
        } else if (room->pos == 1) {
            string actions[] = {"A. Move Left"};
            printActions(1, actions);
            string input;
            cin >> input;
            if (input == "A"|| input == "a"){
                player.changeRooms(&rooms[0]);
                return;
            }else{
                cout<<"Incorrect choice\n";
            }
        }else if (room->pos == 2) {
            string actions[] = {"A. Move Up", "B. Move Right"};
            printActions(2, actions);
            string input;
            cin >> input;
            if (input == "A"||input == "a"){
                player.changeRooms(&rooms[0]);
                return;
            }else if (input == "B" || input == "b"){
                player.changeRooms(&rooms[3]);
                return;
            }else{
                cout<<"Incorrect choice\n";
            }
        }else {
            string actions[] = {"A. Move Left"};
            printActions(1, actions);
            string input;
            cin >> input;
            if (input == "A"||input == "a"){
                player.changeRooms(&rooms[2]);
                return;
            }else{
                cout<<"Incorrect choice\n";
            }
        }
    }

}//check

int Dungeon::performEndGameLogic(){
    string actions[] = {"A. Yes", "B. No"};
    while(true){
        printActions(2,actions);
        string input;
        cin >> input;
        if(input == "A" || input == "a"){
            return 1;
        }else if(input == "B" || input == "b"){
            return 0;
        }else{
            cout << "Incorrect choice.\n";
        }
    }

} // check

int Dungeon::runDungeon(){
    cout << "Welcome to my nifty Dungeon Game! You will find enemies and treasure.\nEnjoy your journey!\n";
    player.currentRoom = &rooms[0];
    player.previousRoom = &rooms[0];
    while(true){
        enterRoom(player.currentRoom);        
        if(player.checkIsDead()){
            cout << "I'm Sorry!\nYou have lost the Game :(\nTry again?\n";
            return performEndGameLogic();
        }else{
            if (player.currentRoom->isExit){
                if (player.currentRoom->enemies.size()==0){
                    cout << "You win! Play again?\n";
                    return performEndGameLogic();
                }
            }
        }
        handleMovementActions(player.currentRoom);
    }
}//check