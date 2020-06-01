#include "Room.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player: public GameCharacter{
public:
    Room currentRoom;
    Room previousRoom;

    vector<Item> inventory;
    Player(string, int, int , int);
    void addItem(Item);
    void increaseStats(int,int,int);
    void lootRoom(Room *);
    void changeRooms(Room *);

};

#endif
