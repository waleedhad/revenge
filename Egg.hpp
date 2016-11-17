//
//  Egg.hpp
//  revenge
//
//  Created by Waleed Al-Haddad on 14/11/16.
//  Copyright © 2016 Waleed Al-Haddad. All rights reserved.
//

#ifndef Egg_hpp
#define Egg_hpp

#include <stdio.h>
#include "setup.h"

/*
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
 */

class Egg
{
public:
    //The dimensions of the Egg
    static const int Egg_WIDTH = 15;
    static const int Egg_HEIGHT = 20;
    
    //Maximum axis velocity of the Egg
    static const int Egg_VEL = 0;
    
    //Initializes the variables
    Egg();
  
    //status
    bool isActive;
    
    //Takes key presses and adjusts the Egg's velocity
    void handleEvent( SDL_Event& e );
    
    //Moves the Egg and checks collision
    void move( );
    
    //Shows the Egg on the screen
    void render();
    // load egg pic
    bool loadMedia();
 
    void close();
    
//private:
    //The X and Y offsets of the Egg
    int mPosX, mPosY;
    
    //The velocity of the Egg
    int mVelX, mVelY;
    
    //Egg's collision box
    SDL_Rect mCollider;
};

#endif /* Egg_hpp */
