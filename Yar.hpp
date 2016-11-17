//
//  Yar.hpp
//  revenge
//
//  Created by Waleed Al-Haddad on 14/11/16.
//  Copyright © 2016 Waleed Al-Haddad. All rights reserved.
//

#ifndef Yar_hpp
#define Yar_hpp

#include <stdio.h>
#include "LTexture.hpp"



class Yar
{
public:
    //The dimensions of the Yar
    static const int Yar_WIDTH = 20;
    static const int Yar_HEIGHT = 20;
    
    //Maximum axis velocity of the Yar
    static const int Yar_VEL = 10;
    
    //Initializes the variables
    Yar();
    Yar(int x, int y);
    
    //statuse
    bool isActive;
    //Takes key presses and adjusts the Yar's velocity
    void handleEvent( SDL_Event& e );
    
    //Moves the Yar and checks collision
    void move();
    
    //Shows the Yar on the screen
    void render();
    //load pic
    bool loadMedia();
    
    bool checkCollision( SDL_Rect a, SDL_Rect b );
    //The X and Y offsets of the Yar
    int mPosX, mPosY;

    void close();
    
//private:
    
    //The velocity of the Yar
    int mVelX, mVelY;
    
    //Yar's collision box
    SDL_Rect mCollider;
};

#endif /* Yar_hpp */
