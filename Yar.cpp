//
//  Yar.cpp
//  revenge
//
//  Created by Waleed Al-Haddad on 14/11/16.
//  Copyright © 2016 Waleed Al-Haddad. All rights reserved.
//

#include "Yar.hpp"


LTexture gYarTexture;


Yar::Yar()
{
    //Initialize the offsets
    mPosX = 0;
    mPosY = 0;
    
    //Set collision box dimension
    mCollider.w = Yar_WIDTH;
    mCollider.h = Yar_HEIGHT;
    
    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
}


Yar::Yar(int x, int y)
{
    //Initialize the offsets
    mPosX = x;
    mPosY = y;
    
    //Set collision box dimension
    mCollider.w = Yar_WIDTH;
    mCollider.h = Yar_HEIGHT;
    
    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
}


void Yar::handleEvent( SDL_Event& e )
{
    //If a key was pressed
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY -= Yar_VEL; break;
            case SDLK_DOWN: mVelY += Yar_VEL; break;
            case SDLK_LEFT: mVelX -= Yar_VEL; break;
            case SDLK_RIGHT: mVelX += Yar_VEL; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY += Yar_VEL; break;
            case SDLK_DOWN: mVelY -= Yar_VEL; break;
            case SDLK_LEFT: mVelX += Yar_VEL; break;
            case SDLK_RIGHT: mVelX -= Yar_VEL; break;
        }
    }
}

void Yar::move( )
{
    //Move the Yar left or right
    mPosX += mVelX;
    mCollider.x = mPosX;
    
    //If the Yar collided or went too far to the left or right
    if( ( mPosX < 0 ) || ( mPosX + Yar_WIDTH > SCREEN_WIDTH ) )
    {
        //Move back
        mPosX -= mVelX;
        mCollider.x = mPosX;
    }
    
    //Move the Yar up or down
    mPosY += mVelY;
    mCollider.y = mPosY;
    
    //If the Yar collided or went too far up or down
    if( ( mPosY < 0 ) || ( mPosY + Yar_HEIGHT > SCREEN_HEIGHT ) )
    {
        //Move back
        mPosY -= mVelY;
        mCollider.y = mPosY;
    }
}

void Yar::render()
{
    //Show the Yar
    gYarTexture.render( mPosX, mPosY );
}


bool Yar::loadMedia()
{
    //Loading success flag
    bool success = true;
    
    //Load press texture
    if( !gYarTexture.loadFromFile( "Yar.png" ) )
    {
        printf( "Failed to load Yar texture!\n" );
        success = false;
    }
    
    return success;
}

///////////////////////////////////////////////////////////


void Yar::close()
{
    //Free loaded images
    gYarTexture.free();

}
