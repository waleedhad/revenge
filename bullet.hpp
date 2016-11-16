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
#include "setup.h"
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
    void move( SDL_Rect& wall );
    
    //Shows the Bullet on the screen
    void render();
    
    bool loadMedia();
    bool checkCollision( SDL_Rect a, SDL_Rect b );
    //The X and Y offsets of the Bullet
    int mPosX, mPosY;
    
    bool isActive;
    void add_new_bullet();
    //Dot's collision boxes
    std::vector<SDL_Rect> mColliders;
    
    //Moves the collision boxes relative to the dot's offset
    void shiftColliders();
    
    //Moves the dot and checks collision
    void move( std::vector<SDL_Rect>& otherColliders );
    
    //Gets the collision boxes
    std::vector<SDL_Rect>& getColliders();
    
    bool checkCollision( std::vector<SDL_Rect>& a, std::vector<SDL_Rect>& b );


    
    void close();
    
private:
    
    //The velocity of the Bullet
    int mVelX, mVelY;
    
    //Bullet's collision box
    SDL_Rect mCollider;
};




#endif /* bullet_hpp */
