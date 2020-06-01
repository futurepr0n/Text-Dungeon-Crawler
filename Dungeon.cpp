#include "Dungeon.h"
#include "Player.h"
#include <iostream>

namespace std;


Dungeon::Dungeon(Player p){
    player = p;

}

void Dungeon::printActions(int numActions, string actions[]){
    cout << "Choose an action: \n";
    for (int i = 0; i < numActions; i++){
        cout << actions[i] << "\n";
    }
}

void Dungeon::handleEmptyRoom(Room *room){
    cout << "You enter the room but it is empty.\n";
    string actions[] = {"A. Move to another room"};
    while(true){
        printActions(1, actions);
        string input;
        cin >> input;
        if (input== "A" || input == "a"){
            return;
        }else{
            cout << "Incorrect choice\n";
        }
        
    }
}

void Dungeon::enterRoom(Room *room){
    if (room->enemies.size() !=0){
        //handle room with enemy
    }else if (room ->items.size()!=0){
        //handle room with chest
    } else {

    }

}

int Dungeon::runDungeon(){
    cout << "Welcome to my nifty Dungeon Game! You will find enemies and treasure.\nEnjoy your journey!\n";
    player.currentRoom = &rooms[0];
    player.previousRoom = &rooms[0];
    
    while(true){
    //enter room
    enterRoom(player.currentRoom);
    //present actions
    //take action - enter sequence
    //check if dead
    //movement options

    }


}


