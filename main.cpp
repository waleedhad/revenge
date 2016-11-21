
//  revenge
//
//

// first try in our github

/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
 and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings


//Scene textures

#include <iostream>

#include "Yar.hpp"
#include "Egg.hpp"
#include "bullet.hpp"
#include "Energy.hpp"
#include "Energy.hpp"
#include "Monster.hpp"
#include "Cannon.hpp"
#include "EnemeyBullet.hpp"
#include "Bmonster.hpp"
#include "LTexture.hpp"

//const int MAX_BULLETS = 1;

const int MAX_Eggs = 20;

//const float shootDelayInMilliseconds = 5000;


const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );




//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;




LTexture::LTexture()
{
    //Initialize
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture()
{
    //Deallocate
    free();
}

bool LTexture::loadFromFile( std::string path )
{
    //Get rid of preexisting texture
    free();
    
    //The final texture
    SDL_Texture* newTexture = NULL;
    
    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Color key image
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
        
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
        
        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }
    
    //Return success
    mTexture = newTexture;
    return mTexture != NULL;
}

#ifdef _SDL_TTF_H
bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
    //Get rid of preexisting texture
    free();
    
    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
    if( textSurface != NULL )
    {
        //Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
        if( mTexture == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }
        
        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }
    else
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    
    
    //Return success
    return mTexture != NULL;
}
#endif

void LTexture::free()
{
    //Free texture if it exists
    if( mTexture != NULL )
    {
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
    //Modulate texture rgb
    SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
    //Set blending function
    SDL_SetTextureBlendMode( mTexture, blending );
}

void LTexture::setAlpha( Uint8 alpha )
{
    //Modulate texture alpha
    SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };
    
    //Set clip rendering dimensions
    if( clip != NULL )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    
    //Render to screen
    SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}

int LTexture::getWidth()
{
    return mWidth;
}

int LTexture::getHeight()
{
    return mHeight;
}



bool init()
{
    //Initialization flag
    bool success = true;
    
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }
        
        //Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Create vsynced renderer for window
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                
                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }
            }
        }
    }
    
    return success;
}





bool checkCollision( SDL_Rect a, SDL_Rect b )
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

void close()
{
    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;
    
    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

///////////////////////////////////////////////////////////////////////////////////////////////////

int main( int argc, char* args[] )
{
   
    
    
    // count no of collected energy;
    int count=0;
    
    //time to randomlly move
   srand( static_cast<unsigned int>(time(NULL)));
    
    
    // iinstantiateobjects for the game
    Yar yar1;
    Egg egg1;
    Cannon cannon(-20,SCREEN_HEIGHT/2);
    Monster monster(SCREEN_WIDTH-120,SCREEN_HEIGHT/2);
    Egg arrEggs[MAX_Eggs];
    Bmonster arrBM[MAX_Eggs];
    Bullet bullet1;
    EnemeyBullet enemyBullet( monster.mPosX , monster.mPosY);
    Bmonster bmonster1(egg1.mPosX , egg1.mPosY);


    
    Energy energy1;
    Energy arrEnergy[MAX_Eggs];
    
    //make all bullets false
    bullet1.isActive=false;
    enemyBullet.isActive=false;
    
    //make monester status true
    monster.isActive=true;

    
    //make all eggs false
    for (int i=0; i<MAX_Eggs; i++ ){
    arrEggs[i].isActive=false;
    arrEggs[i].set_phase(i * 2*3.14/(MAX_Eggs));
        
    arrBM[i].set_phase( arrEggs[i].t);

    arrBM[i].isActive=false;
    }
    
    
    
    //Start up SDL and create window
    if( !init() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        //Load media
        if( !yar1.loadMedia() || !egg1.loadMedia() || !bullet1.loadMedia() || !energy1.loadMedia() || !cannon.loadMedia() || !monster.loadMedia() || !enemyBullet.loadMedia() || !bmonster1.loadMedia())
        {
            printf( "Failed to load media!\n" );
        }
        else
        {
            //Main loop flag
            bool quit = false;
            
            
            //Current time start time
            //unsigned int lastTime = 315, currentTime=100;
            
            
            //Event handler
            SDL_Event e;
            
            //Set the water fall
            SDL_Rect wall;
            wall.x = 200;
            wall.y = 1;
            wall.w = 100;
            wall.h = SCREEN_HEIGHT-1;
            
            //Set the Egges
            
            for(int i=0; i<MAX_Eggs; i++)
           
            {
                arrEggs[i].mPosX=500;
                arrEggs[i].mPosY=40*(i+1);
                arrEggs[i].mCollider.x = arrEggs[i].mPosX;
                arrEggs[i].mCollider.y = arrEggs[i].mPosY;
            }
            
             //Set the Energy
            for(int i=0; i<MAX_Eggs; i++)
                
            {
                arrEnergy[i].mPosX=500+20;
               arrEnergy[i].mPosY=40*(i+1);
                arrEnergy[i].mCollider.x = arrEnergy[i].mPosX;
               arrEnergy[i].mCollider.y = arrEnergy[i].mPosY;
            }
            

            
            //While application is running
            while( !quit )
            {
                
                // get start time
                
                //currentTime = SDL_GetTicks();
    
                
                //Handle events on queue
                while( SDL_PollEvent( &e ) != 0 )
                {
                    //User requests quit
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                    
                    //Handle input for the objects
                    yar1.handleEvent( e );
                    //bullet1.handleEvent( e );
                }
                
                //Move the objects and check collision
                yar1.move( );
                bullet1.move();
                enemyBullet.move();
                energy1.move();
                //egg1.move();
                cannon.move(yar1.mPosY);
                
                //Set the cannon
                

                
                //Clear screen
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );
                
                //Render water fall
                SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
                SDL_RenderDrawRect( gRenderer, &wall );
                
                //Render objects
               
                for(int i=0; i<MAX_Eggs; i++)
                   
                {   arrEggs[i].move();
                    arrBM[i].move();
                    arrEggs[i].random_move( );
                    
                    //if(arrBM[i].isActive==true){arrBM[i].random_move();};
                    if(arrBM[i].isActive==true){arrBM[i].all_random_move( );};

                    if(arrEnergy[i].isActive==false){arrEnergy[i].follow_eggs(arrEggs[i].mPosX, arrEggs[i].mPosY);};
                    arrEnergy[i].render();
                    if(arrEggs[i].isActive==false){arrEggs[i].render();};
                    if(arrBM[i].isActive==true){arrBM[i].render();};

                    
                    }
                
             
                yar1.render();
                cannon.render();
                monster.render();
                //bmonster1.render();
                //egg1.render();
               
               
            ////Handle input for bullets
                
                if(currentKeyStates[ SDL_SCANCODE_SPACE ]  )
                {
                        if (bullet1.isActive == false)
                        {
                            bullet1.mPosX = yar1.mPosX + 25;
                            bullet1.mPosY= yar1.mPosY ;
                            bullet1.isActive = true;
                            //break;
                        }
                    
                    //update game objects
                
                        if (bullet1.isActive == true)
                        {
                            bullet1.mPosX += 10*bullet1.Bullet_VEL;
                            
                            //check collision between eggs and bullet
                            
                            for(int i=0; i<MAX_Eggs; i++)
                            {
                             
                            if(checkCollision(bullet1.mCollider,arrEggs[i].mCollider))
                                
                              {
                            
                                arrEggs[i].mPosX += SCREEN_WIDTH+10;
                                
                                arrEnergy[i].isActive=true;
                                arrEggs[i].isActive=true;
                                 
                                
                              }
                                
                              }
                            
                            
                            if (bullet1.mPosX > SCREEN_WIDTH)
                            {
                                bullet1.isActive = false;
                            }
                        
                          }
                    
                    
                    
                if (bullet1.isActive == true)
                {
                    bullet1.render();
                    
                }
                
                    
                }// if [space]
                
                // Update energy object
                
                    for(int i=0; i<MAX_Eggs; i++)
                    {   if(arrEnergy[i].isActive==true)
                            arrEnergy[i].Emove();
                        
                          //check collision with waterfall
                        if(checkCollision(arrEnergy[i].mCollider, wall))
                            arrEnergy[i].mPosY=SCREEN_HEIGHT+10;
                        
                           //check collision with yar
                        if(checkCollision(arrEnergy[i].mCollider, yar1.mCollider))
                            {
                            arrEnergy[i].mPosY=SCREEN_HEIGHT+10;
                            arrEnergy[i].GotYar=true;
                                
                            }
                    
                    }
                
                
                
                    
                    //printf(" %d  hello", rand()%10);
                    //lastTime = SDL_GetTicks();
                    //printf("%u,      %u \n",SDL_GetTicks() ,lastTime);
                  
                    
                    if(monster.isActive==true)


                   {
                       monster.move();
                       monster.random_move( );
                       
                       /*
                       enemyBullet.mPosX = monster.mPosX + 25;
                       enemyBullet.mPosY= monster.mPosY ;
                        */
                       
                    enemyBullet.isActive = true;

                       /*
                       if ( rand()%10 < 1){
                           enemyBullet.isActive = true;
                       };

                       */
                       
                    //update game objects
                       
                   srand( static_cast<unsigned int>(time(NULL)));
                       
                   if ( enemyBullet.mPosX < 0 && rand()%10< 1 )
                   {
                       enemyBullet.mPosY=monster.mPosY;
                       enemyBullet.mPosX=monster.mPosX;
                   }
                    
                       if (rand()%10< 1 ){
                           
                           int LuckyEgg=rand()%MAX_Eggs;

                           if(arrEggs[LuckyEgg].mPosX<SCREEN_WIDTH-20){
                           arrBM[LuckyEgg].isActive=true;
                           arrBM[LuckyEgg].mPosX=arrEggs[LuckyEgg].mPosX;
                           arrBM[LuckyEgg].mPosY=arrEggs[LuckyEgg].mPosY;
                           
                           arrEggs[LuckyEgg].isActive=true;
                           arrEnergy[LuckyEgg].isActive=true;
                            
                           }
                       }

                       
                    
                    if ( enemyBullet.isActive == true)
                        
                    {
                        
                        
                        enemyBullet.mPosX -= enemyBullet.EnemeyBullet_VEL;
                        
                        
                        
                        //check collision between Yar and Enemeybullet
                        
                       
                    if(checkCollision(yar1.mCollider, enemyBullet.mCollider))
                        
                    {
                        
                        yar1.mPosX-= SCREEN_HEIGHT+10;
                        yar1.isActive=false;
                         printf("hhhhhhh");
                        break;
                       
                    }


                        
                    }
                    
                    if (enemyBullet.isActive == true)
                    {
                        enemyBullet.render();
                        
                    }
                    
                
                   
                }
                
                
                //Update screen
                SDL_RenderPresent( gRenderer );
            }// main game loop
            
            //count no of collected energy;
            for(int i=0; i<MAX_Eggs; i++)
            {   if(arrEnergy[i].GotYar==true)
                count++;
            } printf("here %d",count);
            
            
 ////////////////////////////////////////////////////////////////level2
            
            
            
            //While application is running
            while( !quit )
            {
                yar1.mPosX= SCREEN_HEIGHT/2;
                yar1.isActive=true;
                // get start time
                
                //currentTime = SDL_GetTicks();
                
                
                //Handle events on queue
                while( SDL_PollEvent( &e ) != 0 )
                {
                    //User requests quit
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                    
                    //Handle input for the objects
                    yar1.handleEvent( e );
                    bullet1.handleEvent( e );
                }
                
                //Move the objects and check collision
                yar1.move( );
                bullet1.move();
                enemyBullet.move();
                energy1.move();
                //egg1.move();
                cannon.move(yar1.mPosY);
                
                //Set the cannon
                
                
                
                //Clear screen
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );
                
                //Render water fall
                SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
                SDL_RenderDrawRect( gRenderer, &wall );
                
                //Render objects
                
                for(int i=0; i<MAX_Eggs; i++)
                    
                {   arrEggs[i].move();
                    arrEggs[i].random_move( );
                    if(arrEnergy[i].isActive==false){arrEnergy[i].follow_eggs(arrEggs[i].mPosX, arrEggs[i].mPosY);};
                    arrEnergy[i].render();
                    if(arrEggs[i].isActive==false){arrEggs[i].render();};
                    
                }
                
                
                yar1.render();
                cannon.render();
                monster.render();
                
                
                ////Handle input for bullets
                
                if(currentKeyStates[ SDL_SCANCODE_SPACE ]  )
                {
                    if (bullet1.isActive == false)
                    {
                        bullet1.mPosX = yar1.mPosX + 25;
                        bullet1.mPosY= yar1.mPosY ;
                        bullet1.isActive = true;
                        //break;
                    }
                    
                    //update game objects
                    
                    if (bullet1.isActive == true)
                    {
                        bullet1.mPosX += 10*bullet1.Bullet_VEL;
                        
                        //check collision between eggs and bullet
                        
                        for(int i=0; i<MAX_Eggs; i++)
                        {
                            
                            if(checkCollision(bullet1.mCollider,arrEggs[i].mCollider))
                                
                            {
                                
                                arrEggs[i].mPosX += SCREEN_WIDTH+10;
                                
                                arrEnergy[i].isActive=true;
                                arrEggs[i].isActive=true;
                                
                            }
                            
                        }
                        
                        
                        if (bullet1.mPosX > SCREEN_WIDTH)
                        {
                            bullet1.isActive = false;
                        }
                        
                    }
                    
                    
                    
                    if (bullet1.isActive == true)
                    {
                        bullet1.render();
                        
                    }
                    
                    
                }// if [space]
                
                // Update energy object
                
                for(int i=0; i<MAX_Eggs; i++)
                {   if(arrEnergy[i].isActive==true)
                    arrEnergy[i].Emove();
                    
                    //check collision with waterfall
                    if(checkCollision(arrEnergy[i].mCollider, wall))
                        arrEnergy[i].mPosY=SCREEN_HEIGHT+10;
                    
                    //check collision with yar
                    if(checkCollision(arrEnergy[i].mCollider, yar1.mCollider))
                    {
                        arrEnergy[i].mPosY=SCREEN_HEIGHT+10;
                        arrEnergy[i].GotYar=true;
                    }
                    
                }
                
                
                
                
                //printf(" %d  hello", rand()%10);
                //lastTime = SDL_GetTicks();
                //printf("%u,      %u \n",SDL_GetTicks() ,lastTime);
                
                
                if(monster.isActive==true)
                    
                    
                {
                    monster.move();
                    monster.random_move( );
                    
                    /*
                     enemyBullet.mPosX = monster.mPosX + 25;
                     enemyBullet.mPosY= monster.mPosY ;
                     */
                    
                    enemyBullet.isActive = true;
                    
                    /*
                     if ( rand()%10 < 1){
                     enemyBullet.isActive = true;
                     };
                     
                     */
                    
                    //update game objects
                    
                    srand( static_cast<unsigned int>(time(NULL)));
                    
                    if ( enemyBullet.mPosX < 0 && rand()%10< 1 )
                    {
                        enemyBullet.mPosY=monster.mPosY;
                        enemyBullet.mPosX=monster.mPosX;
                    }
                    
                    
                    if ( enemyBullet.isActive == true)
                        
                    {
                        
                        
                        enemyBullet.mPosX -= enemyBullet.EnemeyBullet_VEL;
                        
                        
                        
                        //check collision between Yar and Enemeybullet
                        
                        
                        if(checkCollision(yar1.mCollider, enemyBullet.mCollider))
                            
                        {
                            
                            yar1.mPosX-= SCREEN_HEIGHT+10;
                            yar1.isActive=false;
                            
                            
                        }
                        
                        
                        
                    }
                    
                    if (enemyBullet.isActive == true)
                    {
                        enemyBullet.render();
                        
                    }
                    
                    
                    
                }
                
                
                //Update screen
                SDL_RenderPresent( gRenderer );
            }// main game loop
        
        
        }// else end
        
   }//main end
    
    
    
    
    /////////////////////////////////////////////////////
    
    
    
    
    
    
    
    //Free resources and close SDL
    
    yar1.close();
    bullet1.close();
    cannon.close();
    monster.close();
    egg1.close();

    close();
    
    return 0;
}
