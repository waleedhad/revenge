//
//  Energy.cpp
//  revenge
//
//  Created by Asim on 11/14/16.
//  Copyright © 2016 Waleed Al-Haddad. All rights reserved.
//

#include "Energy.hpp"
#include<iostream>
#include "setup.h"



LTexture gEnergyTexture;

Energy::Energy()
{
    //Initialize the offsets
    mPosX = 0;
    mPosY = 0;
    
    //Set collision box dimension
    mCollider.w = Energy_WIDTH;
    mCollider.h = Energy_HEIGHT;
    
    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
    
   // isActive;
    
    
    
    
}


void Energy::move( )
{
    //Move the Energy left or right
    mPosX += mVelX;
    mCollider.x = mPosX;
    
    //If the Energy collided or went too far to the left or right
    if( ( mPosX < 0 ) || ( mPosX + Energy_WIDTH > SCREEN_WIDTH ) )
    {
        //Move back
        mPosX -= mVelX;
        mCollider.x = mPosX;
    }
    
    //Move the Energy up or down
    mPosY += mVelY;
    mCollider.y = mPosY;
    
    //If the Energy collided or went too far up or down
    if( ( mPosY < 0 ) || ( mPosY + Energy_HEIGHT > SCREEN_HEIGHT ))
    {
        //Move back
        mPosY -= mVelY;
        mCollider.y = mPosY;
    }
}

void Energy::Emove( )
{
mPosX -= (rand() %10)/5;
mCollider.x =  mPosX;
}


void Energy::render()
{
    //Show the Energy
    gEnergyTexture.render( mPosX, mPosY );
}


bool Energy::loadMedia()
{
    //Loading success flag
    bool success = true;
    
    //Load press texture
    if( !gEnergyTexture.loadFromFile( "Energy.png" ) )
    {
        printf( "Failed to load Energy texture!\n" );
        success = false;
    }
    
    return success;
}

void Energy::handleEvent( SDL_Event& e )
{
    //If a key was pressed
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY -= Energy_VEL; break;
            case SDLK_DOWN: mVelY += Energy_VEL; break;
            case SDLK_LEFT: mVelX -= Energy_VEL; break;
            case SDLK_RIGHT: mVelX += Energy_VEL; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY += Energy_VEL; break;
            case SDLK_DOWN: mVelY -= Energy_VEL; break;
            case SDLK_LEFT: mVelX += Energy_VEL; break;
            case SDLK_RIGHT: mVelX -= Energy_VEL; break;
        }
    }
}




bool Energy::checkCollision( SDL_Rect a, SDL_Rect b )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
    
    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;
    
    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;
    
    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }
    
    if( topA >= bottomB )
    {
        return false;
    }
    
    if( rightA <= leftB )
    {
        return false;
    }
    
    if( leftA >= rightB )
    {
        return false;
    }
    
    //If none of the sides from A are outside B
    return true;
}

///////////////////////////////////////////////////////////


void Energy::close()
{
    //Free loaded images
    gEnergyTexture.free();
    
}
