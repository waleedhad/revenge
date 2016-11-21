//
//  BBmonster.cpp
//  revenge
//
//  Created by Asim on 11/21/16.
//  Copyright © 2016 Waleed Al-Haddad. All rights reserved.
//

#include "Bmonster.hpp"

#include <iostream>


LTexture gBmonsterTexture;


Bmonster::Bmonster(int x, int y)
{
    //Initialize the offsets
    mPosX =x;
    mPosY = y;
    
    //Set collision box dimension
    mCollider.w = Bmonster_WIDTH+30;
    mCollider.h = Bmonster_HEIGHT+40;
    
    
    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
}

Bmonster::Bmonster()
{
    //Initialize the offsets
    mPosX =0;
    mPosY = 0;
    
    //Set collision box dimension
    mCollider.w = 0;
    mCollider.h = 0;
    
    
    //Initialize the velocity
    mVelX = 1;
    mVelY = 1;
}





void Bmonster::handleEvent( SDL_Event& e )
{
    //If a key was pressed
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY -= Bmonster_VEL; break;
            case SDLK_DOWN: mVelY += Bmonster_VEL; break;
            case SDLK_LEFT: mVelX -= Bmonster_VEL; break;
            case SDLK_RIGHT: mVelX += Bmonster_VEL; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY += Bmonster_VEL; break;
            case SDLK_DOWN: mVelY -= Bmonster_VEL; break;
            case SDLK_LEFT: mVelX += Bmonster_VEL; break;
            case SDLK_RIGHT: mVelX -= Bmonster_VEL; break;
        }
    }
}

void Bmonster::move( )
{
    
     

     mCollider.x = mPosX;
     
     
     //If the Bmonster collided or went too far to the left or right
    
     if( ( mPosX < 0 ) || ( mPosX + Bmonster_WIDTH > SCREEN_WIDTH ))
     {
         
     //Move back

     mVelX = - mVelX ;

     mCollider.x = mPosX;
         
     }
     
    
    
    mCollider.y = mPosY;
    
    
    //If the Bmonster collided or went too far up or down
    if( ( mPosY < 0 ) || ( mPosY + Bmonster_HEIGHT > SCREEN_HEIGHT ))
    {
        //Move back
        
        mVelY = - mVelY;
        
        mCollider.y = mPosY;
    }
}



void Bmonster::set_phase(double phase){
    
    t=phase;
}

void Bmonster::random_move( ){
    
    
    if ( t > 2*3.145){t=0;}
    t +=0.03;
    int cy=240;
    int cx=600;
    mPosX = 200*cos(t) + cx;
    mPosY = 200*sin(t) + cy;
    
    mCollider.y =  mPosY;
    mCollider.x =  mPosX;
    
}

void Bmonster::all_random_move( ){
    
    mPosY += ((rand()%10 - 5 ) * mVelY  ) ;
    mPosX += ((rand()%10 - 5 ) * mVelX  ) ;

    mCollider.y =  mPosY;
    mCollider.x =  mPosX;
    
}
void Bmonster::render()
{
    //Show the Bmonster
    gBmonsterTexture.render( mPosX, mPosY );
}


bool Bmonster::loadMedia()
{
    //Loading success flag
    bool success = true;
    
    //Load press texture
    if( !gBmonsterTexture.loadFromFile( "Megg.png" ) )
    {
        printf( "Failed to load Bmonster texture!\n" );
        success = false;
    }
    
    return success;
}




///////////////////////////////////////////////////////////


void Bmonster::close()
{
    //Free loaded images
    gBmonsterTexture.free();
    
}
