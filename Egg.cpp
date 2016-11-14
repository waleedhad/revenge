//
//  Egg.cpp
//  revenge
//
//  Created by Waleed Al-Haddad on 14/11/16.
//  Copyright © 2016 Waleed Al-Haddad. All rights reserved.
//

#include "Egg.hpp"

LTexture gEggTexture;


Egg::Egg(int PosX , int PosY)
{
    //Initialize the offsets
    mPosX = PosX;
    mPosY = PosY;
    
    //Set collision box dimension
    mCollider.w = Egg_WIDTH;
    mCollider.h = Egg_HEIGHT;
    
    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
}


void Egg::handleEvent( SDL_Event& e )
{
    //If a key was pressed
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY -= Egg_VEL; break;
            case SDLK_DOWN: mVelY += Egg_VEL; break;
            case SDLK_LEFT: mVelX -= Egg_VEL; break;
            case SDLK_RIGHT: mVelX += Egg_VEL; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY += Egg_VEL; break;
            case SDLK_DOWN: mVelY -= Egg_VEL; break;
            case SDLK_LEFT: mVelX += Egg_VEL; break;
            case SDLK_RIGHT: mVelX -= Egg_VEL; break;
        }
    }
}

void Egg::move( SDL_Rect& wall )
{
    //Move the Egg left or right
    mPosX += mVelX;
    mCollider.x = mPosX;
    
    //If the Egg collided or went too far to the left or right
    if( ( mPosX < 0 ) || ( mPosX + Egg_WIDTH > SCREEN_WIDTH ) || checkCollision( mCollider, wall ) )
    {
        //Move back
        mPosX -= mVelX;
        mCollider.x = mPosX;
    }
    
    //Move the Egg up or down
    mPosY += mVelY;
    mCollider.y = mPosY;
    
    //If the Egg collided or went too far up or down
    if( ( mPosY < 0 ) || ( mPosY + Egg_HEIGHT > SCREEN_HEIGHT ) || checkCollision( mCollider, wall ) )
    {
        //Move back
        mPosY -= mVelY;
        mCollider.y = mPosY;
    }
}

void Egg::render()
{
    //Show the Egg
    gEggTexture.render( mPosX, mPosY );
}


bool Egg::loadMedia()
{
    //Loading success flag
    bool success = true;
    
    //Load press texture
    if( !gEggTexture.loadFromFile( "Egg.bmp" ) )
    {
        printf( "Failed to load Egg texture!\n" );
        success = false;
    }
    
    return success;
}

bool Egg::checkCollision( SDL_Rect a, SDL_Rect b )
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


void Egg::close()
{
    //Free loaded images
    gEggTexture.free();
    
}
