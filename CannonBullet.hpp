//
//  CannonBullet.hpp
//  revenge
//
//  Created by Asim on 11/21/16.
//  Copyright © 2016 Waleed Al-Haddad. All rights reserved.
//

#ifndef CannonBullet_hpp
#define CannonBullet_hpp


#include <stdio.h>
#include "LTexture.hpp"
#include <stdio.h>
#include <string>
#include <vector>


/*
 const int SCREEN_WIDTH = 640;
 const int SCREEN_HEIGHT = 480;
 */

class CannonBullet
{
public:
    
    //The dimensions of the CannonBullet
    static const int CannonBullet_WIDTH = 10;
    static const int CannonBullet_HEIGHT = 20;
    
    //Maximum axis velocity of the CannonBullet
    static const int CannonBullet_VEL = 2;
    
    //Initializes the variables
    CannonBullet( int , int);
    CannonBullet( );
    
    
    
    //Takes key presses and adjusts the CannonBullet's velocity
    void handleEvent( SDL_Event& e );
    
    //Moves the CannonBullet and checks collision
    void move();
    
    //Shows the CannonBullet on the screen
    void render();
    //load CannonBullet png
    bool loadMedia();
    
    

    
    
    // CannonBullet status
    bool isActive;
    
    void close();
    
    
    void Emove(SDL_Event& e );
    
    //private:
    
    //The X and Y offsets of the CannonBullet
    int mPosX, mPosY;
    
    //The velocity of the CannonBullet
    int mVelX, mVelY;
    
    //CannonBullet's collision box
    SDL_Rect mCollider;
};




#endif /* CannonBullet_hpp */



