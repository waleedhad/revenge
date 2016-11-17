//
//  bullet.cpp
//  revenge
//
//  Created by Asim on 11/14/16.
//  Copyright © 2016 Waleed Al-Haddad. All rights reserved.
//

#include "bullet.hpp"




LTexture gBulletTexture;

Bullet::Bullet()
{
    //Initialize the offsets
    mPosX = 0;
    mPosY = 0;
    
    //Set collision box dimension
    mCollider.w = Bullet_WIDTH;
    mCollider.h = Bullet_HEIGHT;
    
    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
    
    isActive=false;
    
    
    
}


void Bullet::move( )
{
    //Move the Bullet left or right
    mPosX += mVelX;
    mCollider.x = mPosX;
    
    //If the Bullet collided or went too far to the left or right
    if( ( mPosX < 0 ) || ( mPosX + Bullet_WIDTH > SCREEN_WIDTH ) )
    {
        //Move back
        mPosX -= mVelX;
        mCollider.x = mPosX;
    }
    
    //Move the Bullet up or down
    mPosY += mVelY;
    mCollider.y = mPosY;
    
    //If the Bullet collided or went too far up or down
    if( ( mPosY < 0 ) || ( mPosY + Bullet_HEIGHT > SCREEN_HEIGHT ))
    {
        //Move back
        mPosY -= mVelY;
        mCollider.y = mPosY;
    }
}



void Bullet::render()
{
    //Show the Bullet
    gBulletTexture.render( mPosX, mPosY );
}


bool Bullet::loadMedia()
{
    //Loading success flag
    bool success = true;
    
    //Load press texture
    if( !gBulletTexture.loadFromFile( "Bullet.png" ) )
    {
        printf( "Failed to load Bullet texture!\n" );
        success = false;
    }
    
    return success;
}

void Bullet::handleEvent( SDL_Event& e )
{
    //If a key was pressed
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY -= Bullet_VEL; break;
            case SDLK_DOWN: mVelY += Bullet_VEL; break;
            case SDLK_LEFT: mVelX -= Bullet_VEL; break;
            case SDLK_RIGHT: mVelX += Bullet_VEL; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY += Bullet_VEL; break;
            case SDLK_DOWN: mVelY -= Bullet_VEL; break;
            case SDLK_LEFT: mVelX += Bullet_VEL; break;
            case SDLK_RIGHT: mVelX -= Bullet_VEL; break;
        }
    }
}



void Bullet::close()
{
    //Free loaded images
    gBulletTexture.free();
    
}
