//
//  Energy.hpp
//  revenge
//
//  Created by Asim on 11/14/16.
//  Copyright © 2016 Waleed Al-Haddad. All rights reserved.
//

#ifndef Energy_hpp
#define Energy_hpp


#include <stdio.h>
#include "LTexture.hpp"
#include <stdio.h>
#include <string>
#include <vector>


/*
 const int SCREEN_WIDTH = 640;
 const int SCREEN_HEIGHT = 480;
 */

class Energy
{
public:
    //The dimensions of the Energy
    static const int Energy_WIDTH = 15;
    static const int Energy_HEIGHT = 20;
    
    //Maximum axis velocity of the Energy
    static const int Energy_VEL = 10;
    
    //Initializes the variables
    Energy( int , int);
    Energy( );
    
    
    
    //Takes key presses and adjusts the Energy's velocity
    void handleEvent( SDL_Event& e );
    
    //Moves the Energy and checks collision
    void move( );
    void Emove( );
    
    //Shows the Energy on the screen
    void render();
    
    bool loadMedia();
    bool checkCollision( SDL_Rect a, SDL_Rect b );
    //The X and Y offsets of the Energy
    int mPosX, mPosY;
    
    //status
    bool isActive;
    bool GotYar;
       
    
    
    void close();
    
    //private:
    
    //The velocity of the Energy
    int mVelX, mVelY;
    
    //Energy's collision box
    SDL_Rect mCollider;
};




#endif /* Energy_hpp */
