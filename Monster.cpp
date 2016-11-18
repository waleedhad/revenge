//
//  Monster.cpp
//  revenge
//
//  Created by Asim on 11/17/16.
//  Copyright © 2016 Waleed Al-Haddad. All rights reserved.
//

#include "Monster.hpp"
#include <iostream>


LTexture gMonsterTexture;


Monster::Monster(int x, int y)
{
    //Initialize the offsets
    mPosX =x;
    mPosY = y;
    
    //Set collision box dimension
    mCollider.w = Monster_WIDTH+30;
    mCollider.h = Monster_HEIGHT+40;
    
    
    //Initialize the velocity
    mVelX = 0;
    mVelY = 1;
}




void Monster::handleEvent( SDL_Event& e )
{
    //If a key was pressed
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY -= Monster_VEL; break;
            case SDLK_DOWN: mVelY += Monster_VEL; break;
            case SDLK_LEFT: mVelX -= Monster_VEL; break;
            case SDLK_RIGHT: mVelX += Monster_VEL; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY += Monster_VEL; break;
            case SDLK_DOWN: mVelY -= Monster_VEL; break;
            case SDLK_LEFT: mVelX += Monster_VEL; break;
            case SDLK_RIGHT: mVelX -= Monster_VEL; break;
        }
    }
}

void Monster::move( )
{
    /*
     
     /Move the Monster left or right
    mPosX += mVelX;
    mCollider.x = mPosX;
    

     /If the Monster collided or went too far to the left or right
    if( ( mPosX < 0 ) || ( mPosX + Monster_WIDTH > SCREEN_WIDTH ))
    {
        //Move back
        mPosX -= mVelX;
        mCollider.x = mPosX;
    }
    
    
    //Move the Monster up or down
    mPosY += mVelY;
    mCollider.y = mPosY;
     
     */
    
    mCollider.y = mPosY;
    
    //std::cout<<mPosY;
    
    //If the Monster collided or went too far up or down
    if( ( mPosY < 0 ) || ( mPosY + Monster_HEIGHT > SCREEN_HEIGHT ))
    {
        //Move back
        //mPosY -= mVelY;
        
        mVelY = - mVelY;
        
        mCollider.y = mPosY;
    }
}

void Monster::random_move( ){
    
    mPosY -= ((rand()%10 - 5 ) * mVelY ) ;
    mCollider.y =  mPosY;
    
}

void Monster::render()
{
    //Show the Monster
    gMonsterTexture.render( mPosX, mPosY );
}


bool Monster::loadMedia()
{
    //Loading success flag
    bool success = true;
    
    //Load press texture
    if( !gMonsterTexture.loadFromFile( "mon.png" ) )
    {
        printf( "Failed to load Monster texture!\n" );
        success = false;
    }
    
    return success;
}




///////////////////////////////////////////////////////////


void Monster::close()
{
    //Free loaded images
    gMonsterTexture.free();
    
}
