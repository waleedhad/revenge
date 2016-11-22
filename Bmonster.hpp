//
//  Bmonster.hpp
//  revenge
//
//  Created by Asim on 11/21/16.
//  Copyright © 2016 Waleed Al-Haddad. All rights reserved.
//

//

#ifndef Bmonster_hpp
#define Bmonster_hpp

#include <stdio.h>
#include "LTexture.hpp"

/*
 const int SCREEN_WIDTH = 640;
 const int SCREEN_HEIGHT = 480;
 */

class Bmonster
{
public:
    //The dimensions of the Bmonster
    static const int Bmonster_WIDTH = 20;
    static const int Bmonster_HEIGHT = 20;
    
    //Maximum axis velocity of the Bmonster
    static const int Bmonster_VEL = 1;
    
    //Initializes the variables
    Bmonster(int,int);
    //Initializes the variables
    
    Bmonster();
    
    double t=0;
    
    
    void set_phase(double phase);
    
    void all_random_move( );
    
    //status
    bool isActive;
    
    //Takes key presses and adjusts the Bmonster's velocity
    void handleEvent( SDL_Event& e );
    
    //Moves the Bmonster and checks collision
    void move( );
    
    //Shows the Bmonster on the screen
    void render();
    
    //load pic
    bool loadMedia();
    
    void close();
    
    void random_move( );
    
    //The X and Y offsets of the Bmonster
    int mPosX, mPosY;
    
    //The velocity of the Bmonster
    int mVelX, mVelY;
    
    //Bmonster's collision box
    SDL_Rect mCollider;
};




#endif /* Bmonster_hpp */



