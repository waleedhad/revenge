//
//  CannonBullet.cpp
//  revenge
//
//  Created by Asim on 11/21/16.
//  Copyright © 2016 Waleed Al-Haddad. All rights reserved.
//

#include "CannonBullet.hpp"



LTexture gCannonBulletTexture;

CannonBullet::CannonBullet(int x, int y)
{
    //Initialize the offsets
    mPosX = x;
    mPosY = y;
    
    //Set collision box dimension
    mCollider.w = CannonBullet_WIDTH;
    mCollider.h = CannonBullet_HEIGHT;
    
    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
    
    
    
}

CannonBullet::CannonBullet()
{
    //Initialize the offsets
    mPosX = 0;
    mPosY = 0;
    
    //Set collision box dimension
    mCollider.w = CannonBullet_WIDTH;
    mCollider.h = CannonBullet_HEIGHT;
    
    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
    
    
    
}


void CannonBullet::move( int YarYpos )
{
    //Move the Cannon up or down
    mPosY=YarYpos+10;
    mCollider.y = mPosY;
    
    mPosX += mVelX;
    mCollider.x = mPosX;

    
}

void CannonBullet::render()
{
    //Show the CannonBullet
    gCannonBulletTexture.render( mPosX, mPosY );
}


bool CannonBullet::loadMedia()
{
    //Loading success flag
    bool success = true;
    
    //Load press texture
    if( !gCannonBulletTexture.loadFromFile( "Bullet.png" ) )
    {
        printf( "Failed to load CannonBullet texture!\n" );
        success = false;
    }
    
    return success;
}




void CannonBullet::Emove(SDL_Event& e )
{
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        if( e.key.keysym.sym==SDLK_s )
        mVelX += CannonBullet_VEL;
            
                
            
    }
    
}



void CannonBullet::close()
{
    //Free loaded images
    gCannonBulletTexture.free();
    
}
