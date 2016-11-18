//
//  Cannon.cpp
//  revenge
//
//  Created by Asim on 11/17/16.
//  Copyright © 2016 Waleed Al-Haddad. All rights reserved.
//

#include "Cannon.hpp"

LTexture gCannonTexture;


Cannon::Cannon(int x, int y)
{
    //Initialize the offsets
    mPosX =x;
    mPosY = y;
    
    //Set collision box dimension
    mCollider.w = Cannon_WIDTH+30;
    mCollider.h = Cannon_HEIGHT+40;
    
    
    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
}




void Cannon::handleEvent( SDL_Event& e )
{
    //If a key was pressed
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY -= Cannon_VEL; break;
            case SDLK_DOWN: mVelY += Cannon_VEL; break;
            case SDLK_LEFT: mVelX -= Cannon_VEL; break;
            case SDLK_RIGHT: mVelX += Cannon_VEL; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY += Cannon_VEL; break;
            case SDLK_DOWN: mVelY -= Cannon_VEL; break;
            case SDLK_LEFT: mVelX += Cannon_VEL; break;
            case SDLK_RIGHT: mVelX -= Cannon_VEL; break;
        }
    }
}

void Cannon::move( int YarYpos )
{
     //Move the Cannon up or down
    mPosY=YarYpos+10;
    mCollider.y = mPosY;
    
    //If the Cannon collided or went too far up or down
    if( ( mPosY < 0 ) || ( mPosY + Cannon_HEIGHT > SCREEN_HEIGHT ))
    {
        //Move back
        mPosY = YarYpos-10;
        mCollider.y = mPosY;
    }
}

void Cannon::render()
{
    //Show the Cannon
    gCannonTexture.render( mPosX, mPosY );
}


bool Cannon::loadMedia()
{
    //Loading success flag
    bool success = true;
    
    //Load press texture
    if( !gCannonTexture.loadFromFile( "cannon.png" ) )
    {
        printf( "Failed to load Cannon texture!\n" );
        success = false;
    }
    
    return success;
}


///////////////////////////////////////////////////////////


void Cannon::close()
{
    //Free loaded images
    gCannonTexture.free();
    
}
