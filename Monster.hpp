//
//  Monster.hpp
//  revenge
//
//  Created by Asim on 11/17/16.
//  Copyright © 2016 Waleed Al-Haddad. All rights reserved.
//

#ifndef Monster_hpp
#define Monster_hpp

#include <stdio.h>
#include "LTexture.hpp"

/*
 const int SCREEN_WIDTH = 640;
 const int SCREEN_HEIGHT = 480;
 */

class Monster
{
public:
    //The dimensions of the Monster
    static const int Monster_WIDTH = 15;
    static const int Monster_HEIGHT = 20;
    
    //Maximum axis velocity of the Monster
    static const int Monster_VEL = 5;
    
    //Initializes the variables
    Monster(int,int);
    
    //status
    bool isActive;
    
    //Takes key presses and adjusts the Monster's velocity
    void handleEvent( SDL_Event& e );
    
    //Moves the Monster and checks collision
    void move( );
    
    //Shows the Monster on the screen
    void render();
    
    //load pic
    bool loadMedia();
    
    void close();
    
    void random_move( );
    
    //The X and Y offsets of the Monster
    int mPosX, mPosY;
    
    //The velocity of the Monster
    int mVelX, mVelY;
    
    //Monster's collision box
    SDL_Rect mCollider;
};




#endif /* Monster_hpp */
