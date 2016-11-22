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


void CannonBullet::move( )
{
    //Move the EnemeyBullet left or right
    mPosX += mVelX;
    mCollider.x = mPosX;
    
    //If the EnemeyBullet collided or went too far to the left or right
    if( ( mPosX < 0 ) || ( mPosX + CannonBullet_WIDTH > SCREEN_WIDTH ) )
    {
        //Move back
        mPosX -= mVelX;
        mCollider.x = mPosX;
    }
    
    //Move the EnemeyBullet up or down
    mPosY += mVelY;
    mCollider.y = mPosY;
    
    //If the EnemeyBullet collided or went too far up or down
    if( ( mPosY < 0 ) || ( mPosY + CannonBullet_HEIGHT > SCREEN_HEIGHT ))
    {
        //Move back
        mPosY -= mVelY;
        mCollider.y = mPosY;
    }
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
