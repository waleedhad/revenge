
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
#include "CannonBullet.hpp"
#include "LTexture.hpp"
#include <string>


//const int MAX_BULLETS = 1;

const int MAX_Eggs = 20;

//const float shootDelayInMilliseconds = 5000;


// cannon full

const int CannonFull=5;


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

TTF_Font *gFont=NULL; //pointer to font

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


//creating text objects to be rendered by SDL True Type Font

LTexture gTextTexture;
LTexture gText_L1;
LTexture gText_L2;
LTexture gText_L3;
LTexture gText_L4;
LTexture gText_Win;


bool loadMedia_Text(){

        //Loading success flag
        bool success = true;
        
        //Open the font
        gFont = TTF_OpenFont( "font.ttf", 30 );
        if( gFont == NULL )
        {
            printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
            success = false;
        }
        else
        {
            //Render text
            SDL_Color textColor = { 0, 0, 0 };
            if( !gTextTexture.loadFromRenderedText( "GAME OVER ! ", textColor ) || !gText_L1.loadFromRenderedText(" LEVEL 1  ", textColor )
               || !gText_L2.loadFromRenderedText(" LEVEL 2  ", textColor ) || !gText_L3.loadFromRenderedText(" LEVEL 3  ", textColor )
               || !gText_L4.loadFromRenderedText(" LEVEL 4  ", textColor ) || !gText_Win.loadFromRenderedText("Congrats, you won !", textColor ) )
            {
                printf( "Failed to render text texture!\n" );
                success = false;
            }
        }
        
        return success;
    
}

#endif

///////////////////////////

// Background picture

LTexture gWaterfallTexture[16];

bool loadMedia_Waterfall()
{
    //Loading success flag
    bool success = true;
    
    //Load press texture
    for (int i=1; i<=16 ; i++){
        
        std::string file = std::to_string(i) + ".tiff";
        
        if( !gWaterfallTexture[i].loadFromFile( file.c_str() ) )
        {
            printf( "Failed to load Background texture!\n" );
            success = false;
        }
    }
 return success;
}


/////////////////////


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
    
    if( TTF_Init() < 0 )
    {
        printf( "TTF_SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    
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
    TTF_Quit();
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


    CannonBullet cannonBullet(cannon.mPosX,cannon.mPosY);
    Energy energy1;
    Energy arrEnergy[MAX_Eggs];
    
    //make all bullets false
    bullet1.isActive=false;
    enemyBullet.isActive=false;
    cannonBullet.isActive=false;
    
    //make monester status true
    monster.isActive=true;
    
    monster.mPosX= SCREEN_WIDTH-120;
    monster.mPosY= SCREEN_HEIGHT/2;
    monster.mCollider.x= monster.mPosX;
    monster.mCollider.y= monster.mPosY;


    
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
        if( !loadMedia_Waterfall() || !yar1.loadMedia() || !egg1.loadMedia() || !bullet1.loadMedia() || !energy1.loadMedia() || !cannon.loadMedia() || !monster.loadMedia() || !enemyBullet.loadMedia() || !bmonster1.loadMedia() || !cannonBullet.loadMedia() || !loadMedia_Text() )
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
            wall.x = 300;
            wall.y = 1;
            wall.w = 330;
            wall.h = SCREEN_HEIGHT-1;
            
            //Set the Egges
            
            for(int i=0; i<MAX_Eggs; i++)
           
            {
                arrEggs[i].mPosX=SCREEN_WIDTH -200;
                arrEggs[i].mPosY=40*(i);
                arrEggs[i].mCollider.x = arrEggs[i].mPosX;
                arrEggs[i].mCollider.y = arrEggs[i].mPosY;
            }
            
             //Set the Energy
            for(int i=0; i<MAX_Eggs; i++)
                
            {
                arrEnergy[i].mPosX=SCREEN_WIDTH -200 +20;
               arrEnergy[i].mPosY=40*(i);
                arrEnergy[i].mCollider.x = arrEnergy[i].mPosX;
               arrEnergy[i].mCollider.y = arrEnergy[i].mPosY;
            }
            
            //////////////////////////////////////////////////////////////////////
            //Level 1 screen
            
            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
            SDL_RenderClear( gRenderer );
            //Render current frame
            gText_L1.render( ( SCREEN_WIDTH - gTextTexture.getWidth() ) / 2, ( SCREEN_HEIGHT - gTextTexture.getHeight() ) / 2 );
            SDL_RenderPresent( gRenderer );
            SDL_Delay(2000);
            

            /////////////////////////////////////////////////////////////////////////////////////////////////////
                                                        //LEVEL 1 \\
            /////////////////////////////////////////////////////////////////////////////////////////////////////
            
           
            //moving screen counters
            int time_frame=0;
            int i=1;

            
            //While application is running
            while( !quit )
            {
                
                
                //Clear screen
               // SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
               // SDL_RenderClear( gRenderer );
                //Render water fall
                //SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
                
                time_frame+=1;

                
                if(time_frame%7 == 0 && i<=16  ) i++;
                
                printf("%d \n",time_frame);
                
                gWaterfallTexture[i].render(0,0);
                
                if(i==16)i=1;
                
                
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
                    //cannonBullet.Emove(e);
                    //bullet1.handleEvent( e );
                }
                
                //Move the objects and check collision
                yar1.move( );
                bullet1.move();
                enemyBullet.move();
                //cannonBullet.move();
                energy1.move();
                //egg1.move();
                cannon.move(yar1.mPosY);
                 cannonBullet.move();
                
                //Set the cannon
                
                

                    
                
            
                //SDL_RenderDrawRect( gRenderer, &wall );
                
                //Render objects
               
                for(int i=0; i<MAX_Eggs; i++)
                   
                {   //arrEggs[i].move();
                    arrBM[i].move();
                    arrEggs[i].random_move( 0, (SCREEN_WIDTH/2 + 500), (SCREEN_HEIGHT/2));
                    
                    //if(arrBM[i].isActive==true){arrBM[i].random_move();};
                    if(arrBM[i].isActive==true){arrBM[i].all_random_move( );};

                    if(arrEnergy[i].isActive==false){arrEnergy[i].follow_eggs(arrEggs[i].mPosX, arrEggs[i].mPosY);};
                    if(arrEnergy[i].isActive==true)arrEnergy[i].render();
                    if(arrEggs[i].isActive==false){arrEggs[i].render();};
                    if(arrBM[i].isActive==true){arrBM[i].render();};

                    
                    }
                
             
                yar1.render();
                //cannonBullet.render();
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
                    {
                        
                        //check collision with baby monster
                        if(checkCollision(arrBM[i].mCollider, bullet1.mCollider))
                        {
                            printf("baby fall");
                            arrBM[i].mPosY=SCREEN_HEIGHT+10;
                            arrBM[i].isActive=false;
                        }
                        
                        //check collision with baby monster
                        if(checkCollision(arrBM[i].mCollider, yar1.mCollider))
                        {
                            printf(" |YAR DIED | LEVEL 1");
                            yar1.mPosY=SCREEN_HEIGHT+10;
                            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                            SDL_RenderClear( gRenderer );
                            //Render current frame
                            gTextTexture.render( ( SCREEN_WIDTH - gTextTexture.getWidth() ) / 2, ( SCREEN_HEIGHT - gTextTexture.getHeight() ) / 2 );
                            SDL_RenderPresent( gRenderer );
                            SDL_Delay(2000);
                            exit(1);
                        }
                        
                        
                        
                        
                        if(arrEnergy[i].isActive==true)
                    {  arrEnergy[i].Emove();
                        
                          //check collision with waterfall
                        if(checkCollision(arrEnergy[i].mCollider, wall))
                            arrEnergy[i].mPosY=SCREEN_HEIGHT+10;
                        
                        
                        

                        
                           //check collision with yar
                        if(checkCollision(arrEnergy[i].mCollider, yar1.mCollider))
                            {
                            arrEnergy[i].mPosY=SCREEN_HEIGHT+10;
                            arrEnergy[i].GotYar=true;
                                arrEnergy[i].isActive=false;
                                count++;
                               
                                
                            }
                    
                    }
                    
                    }
                
 
                    
                    if(monster.isActive==true)


                   {
                       monster.move();
                       //monster.random_move( );
                       
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
                           //arrEnergy[LuckyEgg].isActive=true;
                            
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
                        printf(" |YAR DIED| ");
                        
                        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                        SDL_RenderClear( gRenderer );
                        //Render current frame
                        gTextTexture.render( ( SCREEN_WIDTH - gTextTexture.getWidth() ) / 2, ( SCREEN_HEIGHT - gTextTexture.getHeight() ) / 2 );
                        SDL_RenderPresent( gRenderer );
                        SDL_Delay(2000);
                        
                        exit(1);
                       
                    }


                        
                    }
                    
                    if (enemyBullet.isActive == true)
                    {
                        enemyBullet.render();
                        
                    }
                    
                
                   
                   }
                
                
                if(count>=CannonFull)
                {
                    if(checkCollision(yar1.mCollider, cannon.mCollider))
                        cannon.isActive = true;
                }
                
                if( cannon.isActive == true && currentKeyStates[ SDL_SCANCODE_S])
                //if(count>=5)
                {
                   // if(checkCollision(yar1.mCollider, cannon.mCollider) && cannonBullet.isActive==false  )
                    cannonBullet.mPosY=cannon.mPosY;
                    cannonBullet.mPosX=cannon.mPosX;
                    cannonBullet.isActive = true;
                    
                    
                }
                
                
               
                    
                if ( cannonBullet.isActive == true && cannon.isActive==true)
                    
                {
                    
                    
                    cannonBullet.mPosX += 10*cannonBullet.CannonBullet_VEL;
                    cannonBullet.mCollider.x=cannonBullet.mPosX ;
                    
                  
                    
                    
                    
                    //check collision between Yar and Enemeybullet
                    
                    
                    if(checkCollision(cannonBullet.mCollider, monster.mCollider))
                        
                    {
                        //monster.mPosY=SCREEN_HEIGHT+10;
                        monster.isActive=false;
                        cannonBullet.isActive=false;
                        printf(" | Monster DIED |  --> NEXT LEVEL 2  ");
                        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                        SDL_RenderClear( gRenderer );
                        //Render current frame
                        gText_L2.render( ( SCREEN_WIDTH - gTextTexture.getWidth() ) / 2, ( SCREEN_HEIGHT - gTextTexture.getHeight() ) / 2 );
                        SDL_RenderPresent( gRenderer );
                        SDL_Delay(2000);
                        break;
                        
                    }
                    
                    if ( cannonBullet.mPosX>SCREEN_WIDTH)
                        
                    {   printf(" %d ",count);
                        cannonBullet.isActive=false;
                        cannon.isActive=false;
                        count-=CannonFull;
                    }
                    
                    
                    
                }
                
                if (cannonBullet.isActive == true && cannon.isActive==true)
                {
                    cannonBullet.render();
                    
                }
                
                
                //Update screen
                SDL_RenderPresent( gRenderer );
            }// main game loop
            
            
           
            /////////////////////////////////////////////////////////////////////////////////////////////////////
                                                    //LEVEL 2 \\
            /////////////////////////////////////////////////////////////////////////////////////////////////////
            
            quit=false;
            
            monster.mPosX= SCREEN_WIDTH-120;
            monster.mPosY= SCREEN_HEIGHT/2;
            monster.mCollider.x= monster.mPosX;
            monster.mCollider.y= monster.mPosY;

            
            
            

            //make all bullets false
            bullet1.isActive=false;
            enemyBullet.isActive=false;
            cannonBullet.isActive=false;
            
            //make monester status true
            monster.isActive=true;
            
            
            //make all eggs false
            for (int i=0; i<MAX_Eggs; i++ ){
                arrEggs[i].isActive=false;
                arrEggs[i].set_phase(i * 2*3.14/(MAX_Eggs));
                
                arrBM[i].set_phase( arrEggs[i].t);
                
                arrBM[i].isActive=false;
            }

            
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
                    //cannonBullet.Emove(e);
                    //bullet1.handleEvent( e );
                }
                
                //Move the objects and check collision
                yar1.move( );
                bullet1.move();
                enemyBullet.move();
                //cannonBullet.move();
                energy1.move();
                //egg1.move();
                cannon.move(yar1.mPosY);
                cannonBullet.move();
                
                //Set the cannon
                
                
                
//                //Clear screen
//                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
//                SDL_RenderClear( gRenderer );
//                
//                //Render water fall
//                SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
//                SDL_RenderDrawRect( gRenderer, &wall );
                
                time_frame+=1;
                
                
                if(time_frame%7 == 0 && i<=16  ) i++;
                
                printf("%d \n",time_frame);
                
                gWaterfallTexture[i].render(0,0);
                
                if(i==16)i=1;

                
                //Render objects
                
                for(int i=0; i<MAX_Eggs; i++)
                    
                {   arrEggs[i].move();
                    arrBM[i].move();
                    arrEggs[i].random_move( 0.02, (SCREEN_WIDTH/2 + 500), (SCREEN_HEIGHT/2) );
                    
                    //if(arrBM[i].isActive==true){arrBM[i].random_move();};
                    if(arrBM[i].isActive==true){arrBM[i].all_random_move( );};
                    
                    if(arrEnergy[i].isActive==false){arrEnergy[i].follow_eggs(arrEggs[i].mPosX, arrEggs[i].mPosY);};
                    if(arrEnergy[i].isActive==true)arrEnergy[i].render();
                    if(arrEggs[i].isActive==false){arrEggs[i].render();};
                    if(arrBM[i].isActive==true){arrBM[i].render();};
                    
                    
                }
                
                
                yar1.render();
                //cannonBullet.render();
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
                {
                    
                    //check collision with baby monster
                    if(checkCollision(arrBM[i].mCollider, bullet1.mCollider))
                    {
                        printf(" | BABY MONSTER DIED | Level 2 ");
                        arrBM[i].mPosY=SCREEN_HEIGHT+10;
                        arrBM[i].isActive=false;
                    }
                    
                    //check collision with baby monster
                    if(checkCollision(arrBM[i].mCollider, yar1.mCollider))
                    {
                        printf(" | YAR DIED   | LEVEL 2 ");
                        yar1.mPosY=SCREEN_HEIGHT+10;
                        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                        SDL_RenderClear( gRenderer );
                        //Render current frame
                        gTextTexture.render( ( SCREEN_WIDTH - gTextTexture.getWidth() ) / 2, ( SCREEN_HEIGHT - gTextTexture.getHeight() ) / 2 );
                        SDL_RenderPresent( gRenderer );
                        SDL_Delay(2000);
                        exit(2);
                    }
                    
                    
                    
                    
                    if(arrEnergy[i].isActive==true)
                    {  arrEnergy[i].Emove();
                        
                        //check collision with waterfall
                        if(checkCollision(arrEnergy[i].mCollider, wall))
                            arrEnergy[i].mPosY=SCREEN_HEIGHT+10;
                        
                        
                        
                        
                        
                        //check collision with yar
                        if(checkCollision(arrEnergy[i].mCollider, yar1.mCollider))
                        {
                            arrEnergy[i].mPosY=SCREEN_HEIGHT+10;
                            arrEnergy[i].GotYar=true;
                            arrEnergy[i].isActive=false;
                            count++;
                            
                            
                        }
                        
                    }
                    
                }
                
                
                
                if(monster.isActive==true)
                    
                    
                {
                    monster.move();
                    //monster.random_move( );
                    
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
                            //arrEnergy[LuckyEgg].isActive=true;
                            
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
                            printf(" | YAR DIED | LEVEL 2 ");
                            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                            SDL_RenderClear( gRenderer );
                            //Render current frame
                            gTextTexture.render( ( SCREEN_WIDTH - gTextTexture.getWidth() ) / 2, ( SCREEN_HEIGHT - gTextTexture.getHeight() ) / 2 );
                            SDL_RenderPresent( gRenderer );
                            SDL_Delay(2000);
                            exit(2);
                            
                        }
                        
                        
                        
                    }
                    
                    if (enemyBullet.isActive == true)
                    {
                        enemyBullet.render();
                        
                    }
                    
                    
                    
                }
                
                
                if(count>=CannonFull)
                {
                    if(checkCollision(yar1.mCollider, cannon.mCollider))
                        cannon.isActive = true;
                }
                
                if( cannon.isActive == true && currentKeyStates[ SDL_SCANCODE_S])
                    //if(count>=5)
                {
                    // if(checkCollision(yar1.mCollider, cannon.mCollider) && cannonBullet.isActive==false  )
                    cannonBullet.mPosY=cannon.mPosY;
                    cannonBullet.mPosX=cannon.mPosX;
                    cannonBullet.isActive = true;
                    
                    
                }
                
                
                
                
                if ( cannonBullet.isActive == true && cannon.isActive==true)
                    
                {
                    
                    
                    cannonBullet.mPosX += 10*cannonBullet.CannonBullet_VEL;
                    cannonBullet.mCollider.x=cannonBullet.mPosX;
                    
                    
                    
                    
                    
                    //check collision between Yar and Enemeybullet
                    
                    
                    if(checkCollision(cannonBullet.mCollider, monster.mCollider))
                        
                    {
                        monster.mPosY=SCREEN_HEIGHT+10;
                        monster.isActive=false;
                        cannonBullet.isActive=false;
                        printf(" | MONSTER DIED | --> LEVEL 3 ");
                        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                        SDL_RenderClear( gRenderer );
                        //Render current frame
                        gText_L3.render( ( SCREEN_WIDTH - gTextTexture.getWidth() ) / 2, ( SCREEN_HEIGHT - gTextTexture.getHeight() ) / 2 );
                        SDL_RenderPresent( gRenderer );
                        SDL_Delay(2000);
                        break;
                        
                    }
                    
                    if ( cannonBullet.mPosX>SCREEN_WIDTH)
                        
                    {   printf(" %d ",count);
                        cannonBullet.isActive=false;
                        cannon.isActive=false;
                        count-=CannonFull;
                        
                    }
                    
                    
                    
                }
                
                if (cannonBullet.isActive == true && cannon.isActive==true)
                {
                    cannonBullet.render();
                    
                }
                
                
                //Update screen
                SDL_RenderPresent( gRenderer );
            }// main game loop
    
    
            /////////////////////////////////////////////////////////////////////////////////////////////////////
                                                        //LEVEL 3 \\
            /////////////////////////////////////////////////////////////////////////////////////////////////////
            quit=false;
            
            
            
            monster.mPosX= SCREEN_WIDTH-120;
            monster.mPosY= SCREEN_HEIGHT/2;
            monster.mCollider.x= monster.mPosX;
            monster.mCollider.y= monster.mPosY;

            
            //make all bullets false
            bullet1.isActive=false;
            enemyBullet.isActive=false;
            cannonBullet.isActive=false;
            
            //make monester status true
            monster.isActive=true;
            
            
            //make all eggs false
            for (int i=0; i<MAX_Eggs; i++ ){
                arrEggs[i].isActive=false;
                arrEggs[i].set_phase(i * 2*3.14/(MAX_Eggs));
                
                arrBM[i].set_phase( arrEggs[i].t);
                
                arrBM[i].isActive=false;
            }

            
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
                    //cannonBullet.Emove(e);
                    //bullet1.handleEvent( e );
                }
                
                //Move the objects and check collision
                yar1.move( );
                bullet1.move();
                enemyBullet.move();
                //cannonBullet.move();
                energy1.move();
                //egg1.move();
                cannon.move(yar1.mPosY);
                cannonBullet.move();
                
                //Set the cannon
                
                
                
                /*/Clear screen
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );
                
                //Render water fall
                SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
                //SDL_RenderDrawRect( gRenderer, &wall );
                 */
                
                time_frame+=1;
                
                
                if(time_frame%7 == 0 && i<=16  ) i++;
                
                printf("%d \n",time_frame);
                
                gWaterfallTexture[i].render(0,0);
                
                if(i==16)i=1;
                
                //Render objects
                
                for(int i=0; i<MAX_Eggs; i++)
                    
                {   arrEggs[i].move();
                    arrBM[i].move();
                    arrEggs[i].random_move( 0, (SCREEN_WIDTH/2+500), monster.mPosY );
                    
                    //if(arrBM[i].isActive==true){arrBM[i].random_move();};
                    if(arrBM[i].isActive==true){arrBM[i].all_random_move( );};
                    
                    if(arrEnergy[i].isActive==false){arrEnergy[i].follow_eggs(arrEggs[i].mPosX, arrEggs[i].mPosY);};
                    if(arrEnergy[i].isActive==true)arrEnergy[i].render();
                    if(arrEggs[i].isActive==false){arrEggs[i].render();};
                    if(arrBM[i].isActive==true){arrBM[i].render();};
                    
                }
                
                
                yar1.render();
                //cannonBullet.render();
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
                {
                    
                    //check collision with baby monster
                    if(checkCollision(arrBM[i].mCollider, bullet1.mCollider))
                    {
                        arrBM[i].mPosY=SCREEN_HEIGHT+10;
                        arrBM[i].isActive=false;
                    }
                    
                    //check collision with baby monster
                    if(checkCollision(arrBM[i].mCollider, yar1.mCollider))
                    {
                        printf(" |YAR DIED |");
                        yar1.mPosY=SCREEN_HEIGHT+10;
                        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                        SDL_RenderClear( gRenderer );
                        //Render current frame
                        gTextTexture.render( ( SCREEN_WIDTH - gTextTexture.getWidth() ) / 2, ( SCREEN_HEIGHT - gTextTexture.getHeight() ) / 2 );
                        SDL_RenderPresent( gRenderer );
                        SDL_Delay(2000);
                        exit(3);
                    }
                    
                    
                    
                    
                    if(arrEnergy[i].isActive==true)
                    {  arrEnergy[i].Emove();
                        
                        //check collision with waterfall
                        if(checkCollision(arrEnergy[i].mCollider, wall))
                            arrEnergy[i].mPosY=SCREEN_HEIGHT+10;
                        
                        
                        
                        
                        
                        //check collision with yar
                        if(checkCollision(arrEnergy[i].mCollider, yar1.mCollider))
                        {
                            arrEnergy[i].mPosY=SCREEN_HEIGHT+10;
                            arrEnergy[i].GotYar=true;
                            arrEnergy[i].isActive=false;
                            count++;
                            
                            
                        }
                        
                    }
                    
                }
                
                
                
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
                            //arrEnergy[LuckyEgg].isActive=true;
                            
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
                            printf(" | YAR DIED  | LEVEL 3 ");
                            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                            SDL_RenderClear( gRenderer );
                            //Render current frame
                            gTextTexture.render( ( SCREEN_WIDTH - gTextTexture.getWidth() ) / 2, ( SCREEN_HEIGHT - gTextTexture.getHeight() ) / 2 );
                            SDL_RenderPresent( gRenderer );
                            SDL_Delay(2000);
                            exit(3);
                            
                        }
                        
                        
                        
                    }
                    
                    if (enemyBullet.isActive == true)
                    {
                        enemyBullet.render();
                        
                    }
                    
                    
                    
                }
                
                
                if(count>=CannonFull)
                {
                    if(checkCollision(yar1.mCollider, cannon.mCollider))
                        cannon.isActive = true;
                }
                
                if( cannon.isActive == true && currentKeyStates[ SDL_SCANCODE_S])
                    //if(count>=5)
                {
                    // if(checkCollision(yar1.mCollider, cannon.mCollider) && cannonBullet.isActive==false  )
                    cannonBullet.mPosY=cannon.mPosY;
                    cannonBullet.mPosX=cannon.mPosX;
                    cannonBullet.isActive = true;
                    
                    
                }
                
                
                
                
                if ( cannonBullet.isActive == true && cannon.isActive==true)
                    
                {
                    
                    
                    cannonBullet.mPosX += 10*cannonBullet.CannonBullet_VEL;
                    cannonBullet.mCollider.x=cannonBullet.mPosX ;
                    
                    
                    
                    
                    
                    //check collision between Yar and Enemeybullet
                    
                    
                    if(checkCollision(cannonBullet.mCollider, monster.mCollider))
                        
                    {
                        monster.mPosY=SCREEN_HEIGHT+10;
                        monster.isActive=false;
                        printf(" |MONSTER DIED | --> LEVEL 4 ");
                        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                        SDL_RenderClear( gRenderer );
                        //Render current frame
                        gText_L4.render( ( SCREEN_WIDTH - gTextTexture.getWidth() ) / 2, ( SCREEN_HEIGHT - gTextTexture.getHeight() ) / 2 );
                        SDL_RenderPresent( gRenderer );
                        SDL_Delay(2000);
                        break;
                        
                    }
                    
                    if ( cannonBullet.mPosX>SCREEN_WIDTH)
                        
                    {   printf(" %d ",count);
                        cannonBullet.isActive=false;
                        cannon.isActive=false;
                        count-=CannonFull;
                        
                    }
                    
                    
                    
                }
                
                if (cannonBullet.isActive == true && cannon.isActive==true)
                {
                    cannonBullet.render();
                    
                }
                
                
                //Update screen
                SDL_RenderPresent( gRenderer );
            }// main game loop
    
    
    
            /////////////////////////////////////////////////////////////////////////////////////////////////////
                                                    //LEVEL 4 \\
            /////////////////////////////////////////////////////////////////////////////////////////////////////
            quit=false;
            
            
            monster.mPosX= SCREEN_WIDTH-120;
            monster.mPosY= SCREEN_HEIGHT/2;
            monster.mCollider.x= monster.mPosX;
            monster.mCollider.y= monster.mPosY;

            
            //make all bullets false
            bullet1.isActive=false;
            enemyBullet.isActive=false;
            cannonBullet.isActive=false;
            
            //make monester status true
            monster.isActive=true;
            
            
            //make all eggs false
            for (int i=0; i<MAX_Eggs; i++ ){
                arrEggs[i].isActive=false;
                arrEggs[i].set_phase(i * 2*3.14/(MAX_Eggs));
                
                arrBM[i].set_phase( arrEggs[i].t);
                
                arrBM[i].isActive=false;
            }

            
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
                    //cannonBullet.Emove(e);
                    //bullet1.handleEvent( e );
                }
                
                //Move the objects and check collision
                yar1.move( );
                bullet1.move();
                enemyBullet.move();
                //cannonBullet.move();
                energy1.move();
                //egg1.move();
                cannon.move(yar1.mPosY);
                cannonBullet.move();
                
                //Set the cannon
                
                
                
                /*
                 /Clear screen
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );
                
                //Render water fall
                SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
                //SDL_RenderDrawRect( gRenderer, &wall );
                 */
                
                time_frame+=1;
                
                
                if(time_frame%7 == 0 && i<=16  ) i++;
                
                printf("%d \n",time_frame);
                
                gWaterfallTexture[i].render(0,0);
                
                if(i==16)i=1;
                
                //Render objects
                
                for(int i=0; i<MAX_Eggs; i++)
                    
                {   arrEggs[i].move();
                    arrBM[i].move();
                    arrEggs[i].random_move( 0.03, (SCREEN_WIDTH/2+500), monster.mPosY );
                    
                    //if(arrBM[i].isActive==true){arrBM[i].random_move();};
                    if(arrBM[i].isActive==true){arrBM[i].all_random_move( );};
                    
                    if(arrEnergy[i].isActive==false){arrEnergy[i].follow_eggs(arrEggs[i].mPosX, arrEggs[i].mPosY);};
                    if(arrEnergy[i].isActive==true)arrEnergy[i].render();
                    if(arrEggs[i].isActive==false){arrEggs[i].render();};
                    if(arrBM[i].isActive==true){arrBM[i].render();};
                    
                    
                }
                
                
                yar1.render();
                //cannonBullet.render();
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
                {
                    
                    //check collision with baby monster
                    if(checkCollision(arrBM[i].mCollider, bullet1.mCollider))
                    {
                        printf("baby fall");
                        arrBM[i].mPosY=SCREEN_HEIGHT+10;
                        arrBM[i].isActive=false;
                    }
                    
                    //check collision with baby monster
                    if(checkCollision(arrBM[i].mCollider, yar1.mCollider))
                    {
                        printf(" |YAR DIED | LEVEL 4 ");
                        yar1.mPosY=SCREEN_HEIGHT+10;
                        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                        SDL_RenderClear( gRenderer );
                        //Render current frame
                        gTextTexture.render( ( SCREEN_WIDTH - gTextTexture.getWidth() ) / 2, ( SCREEN_HEIGHT - gTextTexture.getHeight() ) / 2 );
                        SDL_RenderPresent( gRenderer );
                        SDL_Delay(2000);
                        exit(4);
                    }
                    
                    
                    
                    
                    if(arrEnergy[i].isActive==true)
                    {  arrEnergy[i].Emove();
                        
                        //check collision with waterfall
                        if(checkCollision(arrEnergy[i].mCollider, wall))
                            arrEnergy[i].mPosY=SCREEN_HEIGHT+10;
                        
                        
                        
                        
                        
                        //check collision with yar
                        if(checkCollision(arrEnergy[i].mCollider, yar1.mCollider))
                        {
                            arrEnergy[i].mPosY=SCREEN_HEIGHT+10;
                            arrEnergy[i].GotYar=true;
                            arrEnergy[i].isActive=false;
                            count++;
                            
                            
                        }
                        
                    }
                    
                }
                
                
                
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
                            //arrEnergy[LuckyEgg].isActive=true;
                            
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
                            printf(" |YAR DIED | LEVEL 4 ");
                            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                            SDL_RenderClear( gRenderer );
                            //Render current frame
                            gTextTexture.render( ( SCREEN_WIDTH - gTextTexture.getWidth() ) / 2, ( SCREEN_HEIGHT - gTextTexture.getHeight() ) / 2 );
                            SDL_RenderPresent( gRenderer );
                            SDL_Delay(2000);
                            exit(4);
                            
                        }
                        
                        
                        
                    }
                    
                    if (enemyBullet.isActive == true)
                    {
                        enemyBullet.render();
                        
                    }
                    
                    
                    
                }
                
                
                if(count>=CannonFull)
                {
                    if(checkCollision(yar1.mCollider, cannon.mCollider))
                        cannon.isActive = true;
                }
                
                if( cannon.isActive == true && currentKeyStates[ SDL_SCANCODE_S])
                    //if(count>=5)
                {
                    // if(checkCollision(yar1.mCollider, cannon.mCollider) && cannonBullet.isActive==false  )
                    cannonBullet.mPosY=cannon.mPosY;
                    cannonBullet.mPosX=cannon.mPosX;
                    cannonBullet.isActive = true;
                    
                    
                }
                
                
                
                
                if ( cannonBullet.isActive == true && cannon.isActive==true)
                    
                {
                    
                    
                    cannonBullet.mPosX += 10*cannonBullet.CannonBullet_VEL;
                    cannonBullet.mCollider.x=cannonBullet.mPosX ;
                    
                    
                    
                    
                    
                    //check collision between Yar and Enemeybullet
                    
                    
                    if(checkCollision(cannonBullet.mCollider, monster.mCollider))
                        
                    {
                        monster.mPosY=SCREEN_HEIGHT+10;
                        monster.isActive=false;
                        printf(" | MONSTER DIED | ---> YOU WON ! ");
                        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                        SDL_RenderClear( gRenderer );
                        //Render current frame
                        gText_Win.render( ( SCREEN_WIDTH - gTextTexture.getWidth() ) / 2, ( SCREEN_HEIGHT - gTextTexture.getHeight() ) / 2 );
                        SDL_RenderPresent( gRenderer );
                        SDL_Delay(2000);
                        break;
                        
                    }
                    
                    if ( cannonBullet.mPosX>SCREEN_WIDTH)
                        
                    {   printf(" %d ",count);
                        cannonBullet.isActive=false;
                        cannon.isActive=false;
                        count-=CannonFull;
                        
                    }
                    
                    
                    
                }
                
                if (cannonBullet.isActive == true && cannon.isActive==true)
                {
                    cannonBullet.render();
                    
                }
                
                
                //Update screen
                SDL_RenderPresent( gRenderer );
            }// main game loop
            
    
    //////////////////////////////////////////////////////
    //Free resources and close SDL
    //////////////////////////////////////////////////////
            
    yar1.close();
    bullet1.close();
    cannon.close();
    monster.close();
    egg1.close();

    close();
    
    return 0;
        }}}

////////////////////////////////////////////////////////////
