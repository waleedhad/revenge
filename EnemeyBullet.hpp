//
//  EnemeyBullet.hpp
//  revenge
//
//  Created by Asim on 11/17/16.
//  Copyright © 2016 Waleed Al-Haddad. All rights reserved.
//

#ifndef EnemeyBullet_hpp
#define EnemeyBullet_hpp

#include <stdio.h>
#include "LTexture.hpp"
#include <stdio.h>
#include <string>
#include <vector>


class EnemeyBullet
{
public:
    
    //The dimensions of the EnemeyBullet
    static const int EnemeyBullet_WIDTH = 10;
    static const int EnemeyBullet_HEIGHT = 20;
    
    //Maximum axis velocity of the EnemeyBullet
    static const int EnemeyBullet_VEL = 2;
    
    //Initializes the variables
    EnemeyBullet( int , int);
    EnemeyBullet( );
    
    
    
    //Takes key presses and adjusts the EnemeyBullet's velocity
    void handleEvent( SDL_Event& e );
    
    //Moves the EnemeyBullet and checks collision
    void move( );
    
    //Shows the EnemeyBullet on the screen
    void render();
    //load EnemeyBullet png
    bool loadMedia();
    
    
    // EnemeyBullet status
    bool isActive;
    
    void close();
    
    //private:
    
    //The X and Y offsets of the EnemeyBullet
    int mPosX, mPosY;
    
    //The velocity of the EnemeyBullet
    int mVelX, mVelY;
    
    //EnemeyBullet's collision box
    SDL_Rect mCollider;
};




#endif /* EnemeyBullet_hpp */



