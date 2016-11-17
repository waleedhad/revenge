//
//  bullet.hpp
//  revenge
//
//  Created by Asim on 11/14/16.
//  Copyright © 2016 Waleed Al-Haddad. All rights reserved.
//

#ifndef bullet_hpp
#define bullet_hpp


#include <stdio.h>
#include "LTexture.hpp"
#include <stdio.h>
#include <string>
#include <vector>


/*
 const int SCREEN_WIDTH = 640;
 const int SCREEN_HEIGHT = 480;
 */

class Bullet
{
public:
    
    //The dimensions of the Bullet
    static const int Bullet_WIDTH = 10;
    static const int Bullet_HEIGHT = 20;
    
    //Maximum axis velocity of the Bullet
    static const int Bullet_VEL = 10;
    
    //Initializes the variables
     Bullet( int , int);
     Bullet( );
  
    
    
    //Takes key presses and adjusts the Bullet's velocity
    void handleEvent( SDL_Event& e );
    
    //Moves the Bullet and checks collision
    void move( );
    
    //Shows the Bullet on the screen
    void render();
    //load bullet png
    bool loadMedia();
   
    
    // bullet status
    bool isActive;
    
    void close();
    
//private:
    
    //The X and Y offsets of the Bullet
    int mPosX, mPosY;
    
    //The velocity of the Bullet
    int mVelX, mVelY;
    
    //Bullet's collision box
    SDL_Rect mCollider;
};




#endif /* bullet_hpp */
