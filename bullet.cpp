//
//  bullet.cpp
//  revenge
//
//  Created by Asim on 11/14/16.
//  Copyright © 2016 Waleed Al-Haddad. All rights reserved.
//

#include "bullet.hpp"
#include<iostream>
#include "setup.h"



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
    
    
    
}

Bullet::Bullet( int x, int y )
{
    //Initialize the offsets
    mPosX = x;
    mPosY = y;
    
    //Create the necessary SDL_Rects
    mColliders.resize( 11 );
    
    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
    
    //Initialize the collision boxes' width and height
    mColliders[ 0 ].w = 6;
    mColliders[ 0 ].h = 1;
    
    mColliders[ 1 ].w = 10;
    mColliders[ 1 ].h = 1;
    
    mColliders[ 2 ].w = 14;
    mColliders[ 2 ].h = 1;
    
    mColliders[ 3 ].w = 16;
    mColliders[ 3 ].h = 2;
    
    mColliders[ 4 ].w = 18;
    mColliders[ 4 ].h = 2;
    
    mColliders[ 5 ].w = 20;
    mColliders[ 5 ].h = 6;
    
    mColliders[ 6 ].w = 18;
    mColliders[ 6 ].h = 2;
    
    mColliders[ 7 ].w = 16;
    mColliders[ 7 ].h = 2;
    
    mColliders[ 8 ].w = 14;
    mColliders[ 8 ].h = 1;
    
    mColliders[ 9 ].w = 10;
    mColliders[ 9 ].h = 1;
    
    mColliders[ 10 ].w = 6;
    mColliders[ 10 ].h = 1;
    
    //Initialize colliders relative to position
    shiftColliders();
}

void Bullet::shiftColliders()
{
    //The row offset
    int r = 0;
    
    //Go through the dot's collision boxes
    for( int set = 0; set < mColliders.size(); ++set )
    {
        //Center the collision box
        mColliders[ set ].x = mPosX + ( Bullet_WIDTH - mColliders[ set ].w ) / 2;
        
        //Set the collision box at its row offset
        mColliders[ set ].y = mPosY + r;
        
        //Move the row offset down the height of the collision box
        r += mColliders[ set ].h;
    }
}

std::vector<SDL_Rect>& Bullet::getColliders()
{
    return mColliders;
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






void Bullet::move( SDL_Rect& wall )
{
    //Move the Bullet left or right
    mPosX += mVelX;
    mCollider.x = mPosX;
    
    //If the Bullet collided or went too far to the left or right
    if( ( mPosX < 0 ) || ( mPosX + Bullet_WIDTH > SCREEN_WIDTH ) || checkCollision( mCollider, wall ) )
    {
        //Move back
        mPosX -= mVelX;
        mCollider.x = mPosX;
    }
    
    //Move the Bullet up or down
    mPosY += mVelY;
    mCollider.y = mPosY;
    
    //If the Bullet collided or went too far up or down
    if( ( mPosY < 0 ) || ( mPosY + Bullet_HEIGHT > SCREEN_HEIGHT ) || checkCollision( mCollider, wall ) )
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
    if( !gBulletTexture.loadFromFile( "Bullet.bmp" ) )
    {
        printf( "Failed to load Bullet texture!\n" );
        success = false;
    }
    
    return success;
}


void Bullet::move( std::vector<SDL_Rect>& otherColliders )
{
    //Move the Bullet left or right
    mPosX += mVelX;
    shiftColliders();
    
    //If the Bullet collided or went too far to the left or right
    if( ( mPosX < 0 ) || ( mPosX + Bullet_WIDTH > SCREEN_WIDTH ) || checkCollision( mColliders, otherColliders ) )
    {
        //Move back
        mPosX -= mVelX;
        shiftColliders();
    }
    
    //Move the Bullet up or down
    mPosY += mVelY;
    shiftColliders();
    
    //If the Bullet collided or went too far up or down
    if( ( mPosY < 0 ) || ( mPosY + Bullet_HEIGHT > SCREEN_HEIGHT ) || checkCollision( mColliders, otherColliders ) )
    {
        //Move back
        mPosY -= mVelY;
        shiftColliders();
    }
}


bool Bullet::checkCollision( std::vector<SDL_Rect>& a, std::vector<SDL_Rect>& b )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
    
    //Go through the A boxes
    for( int Abox = 0; Abox < a.size(); Abox++ )
    {
        //Calculate the sides of rect A
        leftA = a[ Abox ].x;
        rightA = a[ Abox ].x + a[ Abox ].w;
        topA = a[ Abox ].y;
        bottomA = a[ Abox ].y + a[ Abox ].h;
        
        //Go through the B boxes
        for( int Bbox = 0; Bbox < b.size(); Bbox++ )
        {
            //Calculate the sides of rect B
            leftB = b[ Bbox ].x;
            rightB = b[ Bbox ].x + b[ Bbox ].w;
            topB = b[ Bbox ].y;
            bottomB = b[ Bbox ].y + b[ Bbox ].h;
            
            //If no sides from A are outside of B
            if( ( ( bottomA <= topB ) || ( topA >= bottomB ) || ( rightA <= leftB ) || ( leftA >= rightB ) ) == false )
            {
                //A collision is detected
                return true;
            }
        }
    }
    
    //If neither set of collision boxes touched
    return false;
}
bool Bullet::checkCollision( SDL_Rect a, SDL_Rect b )
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


void Bullet::close()
{
    //Free loaded images
    gBulletTexture.free();
    
}
