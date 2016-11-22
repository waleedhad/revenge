//
//  EnemeyEnemeyBullet.cpp
//  revenge
//
//  Created by Asim on 11/17/16.
//  Copyright © 2016 Waleed Al-Haddad. All rights reserved.
//

#include "EnemeyBullet.hpp"




LTexture gEnemeyBulletTexture;

EnemeyBullet::EnemeyBullet(int x,int y)
{
    //Initialize the offsets
    mPosX = x;
    mPosY = y;
    
    //Set collision box dimension
    mCollider.w = EnemeyBullet_WIDTH;
    mCollider.h = EnemeyBullet_HEIGHT;
    
    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
    
    isActive=false;
    
    
    
}


void EnemeyBullet::move( )
{
    //Move the EnemeyBullet left or right
    mPosX += mVelX;
    mCollider.x = mPosX;
    
    //If the EnemeyBullet collided or went too far to the left or right
    if( ( mPosX < 0 ) || ( mPosX + EnemeyBullet_WIDTH > SCREEN_WIDTH ) )
    {
        //Move back
        mPosX -= mVelX;
        mCollider.x = mPosX;
    }
    
    //Move the EnemeyBullet up or down
    mPosY += mVelY;
    mCollider.y = mPosY;
    
    //If the EnemeyBullet collided or went too far up or down
    if( ( mPosY < 0 ) || ( mPosY + EnemeyBullet_HEIGHT > SCREEN_HEIGHT ))
    {
        //Move back
        mPosY -= mVelY;
        mCollider.y = mPosY;
    }
}



void EnemeyBullet::render()
{
    //Show the EnemeyBullet
    gEnemeyBulletTexture.render( mPosX, mPosY );
}


bool EnemeyBullet::loadMedia()
{
    //Loading success flag
    bool success = true;
    
    //Load press texture
    if( !gEnemeyBulletTexture.loadFromFile( "Bulletm.png" ) )
    {
        printf( "Failed to load EnemeyBullet texture!\n" );
        success = false;
    }
    
    return success;
}

void EnemeyBullet::handleEvent( SDL_Event& e )
{
    //If a key was pressed
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY -= EnemeyBullet_VEL; break;
            case SDLK_DOWN: mVelY += EnemeyBullet_VEL; break;
            case SDLK_LEFT: mVelX -= EnemeyBullet_VEL; break;
            case SDLK_RIGHT: mVelX += EnemeyBullet_VEL; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY += EnemeyBullet_VEL; break;
            case SDLK_DOWN: mVelY -= EnemeyBullet_VEL; break;
            case SDLK_LEFT: mVelX += EnemeyBullet_VEL; break;
            case SDLK_RIGHT: mVelX -= EnemeyBullet_VEL; break;
        }
    }
}



void EnemeyBullet::close()
{
    //Free loaded images
    gEnemeyBulletTexture.free();
    
}
