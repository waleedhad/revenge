//
//  Yar.hpp
//  revenge
//
//  Created by Waleed Al-Haddad on 14/11/16.
//  Copyright © 2016 Waleed Al-Haddad. All rights reserved.
//

#ifndef Yar_hpp
#define Yar_hpp

#include <stdio.h>
#include "setup.h"

LTexture gEggTexture;


//The Egg that will move around on the screen
class Egg
{
public:
    //The dimensions of the Egg
    static const int Egg_WIDTH = 20;
    static const int Egg_HEIGHT = 20;
    
    //Maximum axis velocity of the Egg
    static const int Egg_VEL = 10;
    
    //Initializes the variables
    Egg(int xPos , int yPos );
    
    //Takes key presses and adjusts the Egg's velocity
    void handleEvent( SDL_Event& e );
    
    //Moves the Egg and checks collision
    void move( SDL_Rect& wall );
    
    //Shows the Egg on the screen
    void render();
    
private:
    //The X and Y offsets of the Egg
    int mPosX, mPosY;
    
    //The velocity of the Egg
    int mVelX, mVelY;
    
    //Egg's collision box
    SDL_Rect mCollider;
};

#endif /* Yar_hpp */
