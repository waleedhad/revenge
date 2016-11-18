//
//  Cannon.hpp
//  revenge
//
//  Created by Asim on 11/17/16.
//  Copyright © 2016 Waleed Al-Haddad. All rights reserved.
//

#ifndef Cannon_hpp
#define Cannon_hpp

#include <stdio.h>
#include "LTexture.hpp"

/*
 const int SCREEN_WIDTH = 640;
 const int SCREEN_HEIGHT = 480;
 */

class Cannon
{
public:
    //The dimensions of the Cannon
    static const int Cannon_WIDTH = 15;
    static const int Cannon_HEIGHT = 20;
    
    //Maximum axis velocity of the Cannon
    static const int Cannon_VEL = 0;
    
    //Initializes the variables
    Cannon(int,int);
    
    //status
    bool isActive;
    
    //Takes key presses and adjusts the Cannon's velocity
    void handleEvent( SDL_Event& e );
    
    //Moves the Cannon and checks collision
    void move(int  );
    
    //Shows the Cannon on the screen
    void render();
    
    //status
    bool loadMedia();
   
    void close();
    
    //private:
    //The X and Y offsets of the Cannon
    int mPosX, mPosY;
    
    //The velocity of the Cannon
    int mVelX, mVelY;
    
    //Cannon's collision box
    SDL_Rect mCollider;
};






#endif /* Cannon_hpp */
