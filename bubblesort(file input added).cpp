#include <iostream>
#include<stdio.h>
#include <SDL2/SDL.h>
#include <time.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
const int sw = 1080;
const int sh = 800;
const int algo_vis_button_x=375,algo_vis_button_y=50,algo_vis_button_width = 300,algo_vis_button_height = 200;
const int play_button_x=400,play_button_y=300,play_button_width = 256,play_button_height=128;
const int quit_button_x = 400,quit_button_y=500,quit_button_width = 256,quit_button_height=128;
const int merge_button_x=375,merge_button_y=150,merge_button_width = 300,merge_button_height=100;
const int bubble_button_x=375,bubble_button_y=300,bubble_button_width = 300,bubble_button_height=100;
const int insertion_button_x=375,insertion_button_y=450,insertion_button_width = 300,insertion_button_height=100;
const int bubble_ascending_button_x=400,bubble_ascending_button_y=150,bubble_ascending_button_width = 300,bubble_ascending_button_height=200;
const int bubble_descending_button_x=400,bubble_descending_button_y=400,bubble_descending_button_width = 300,bubble_descending_button_height=200;
const int insertion_ascending_button_x=400,insertion_ascending_button_y=150,insertion_ascending_button_width = 300,insertion_ascending_button_height=200;
const int insertion_descending_button_x=400,insertion_descending_button_y=400,insertion_descending_button_width = 300,insertion_descending_button_height=200;
const int bubble_ascending_load_x=50,bubble_ascending_load_y=50,bubble_ascending_load_width = 150,bubble_ascending_load_height = 80;
const int bubble_descending_load_x=50,bubble_descending_load_y=50,bubble_descending_load_width = 150,bubble_descending_load_height = 80;
const int insertion_ascending_load_x=50,insertion_ascending_load_y=50,insertion_ascending_load_width = 150,insertion_ascending_load_height = 80;
const int insertion_descending_load_x=50,insertion_descending_load_y=50,insertion_descending_load_width = 150,insertion_descending_load_height = 80;
const int user_input_button_x=400,user_input_button_y=100,user_input_button_width = 300,user_input_button_height=200;
const int file_input_button_x=400,file_input_button_y=350,file_input_button_width = 300,file_input_button_height=200;
int w,j,q;

std::string numbers;
SDL_Texture* numberInputTexture = NULL;

bool user_input1 = true;

bool hover(int x1,int y1,int h,int w,int mx,int my)
{
    if(mx >= x1 && mx <= x1+h && my >= y1  && my<=y1+w)return 1;
    return 0;
}
using namespace std;
void reset(bool *b)
{
    if(*b) *b = false;
    else *b = true;
}
SDL_Rect algo_vis_rect,quit_rect,play_rect,merge_button_rect,bubble_button_rect,insertion_button_rect;
SDL_Rect bubble_ascending_button_rect,bubble_descending_button_rect,insertion_ascending_button_rect,insertion_descending_button_rect;
SDL_Rect bubble_ascending_load_button_rect,bubble_descending_load_button_rect,insertion_ascending_load_button_rect,insertion_descending_load_button_rect;
SDL_Rect file_input_rect, user_input_rect;

SDL_Window *main_window = NULL;
SDL_Renderer *main_renderer = NULL;

SDL_Color textColor = {0, 0, 0, 0xFF};

TTF_Font* textfont = NULL;
class Ltexture
{
public:
    Ltexture();
    ~Ltexture();
    bool loadFromFile(string path);
    #if defined(_SDL_TTF_H) || defined(SDL_TTF_H)
    bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
    #endif
    void free();
    void setColor(Uint8 red,Uint8 green,Uint8 blue);
    void setBlendMode(SDL_BlendMode blending);
    void setAlpha(Uint8 alpha);
    void render(int x,int y, SDL_Rect *clip = NULL);
    void renderText(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
    int getw();
    int getH();
private:
    SDL_Texture *mTexture;
    int mWidth,mHeight;
};
Ltexture algo_vis_button,quit_button,play_button,merge_button,bubble_button,insertion_button;
Ltexture bubble_ascending_button,bubble_descending_button,insertion_ascending_button,insertion_descending_button;
Ltexture bubble_ascending_load_button, bubble_descending_load_button, insertion_ascending_load_button, insertion_descending_load_button;
Ltexture user_input_button,file_input_button;
bool init();
bool loadMedia();
void close();

SDL_Texture* loadTextTexture(string textureText,SDL_Color textColor)
{
    SDL_Texture* textTextureTemp = NULL;
    SDL_Surface* textSurface = TTF_RenderText_Blended(textfont, textureText.c_str(), textColor);
    if( textSurface == NULL ) printf( "Unable to render text texture for menu! SDL_ttf Error: %s\n", TTF_GetError() );
    else
    {
        textTextureTemp = SDL_CreateTextureFromSurface(main_renderer, textSurface);
        if(textTextureTemp == NULL)   printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        SDL_FreeSurface(textSurface);
    }
    return textTextureTemp;
}


Ltexture::Ltexture()
{
    mTexture = NULL;
    mWidth = 0,mHeight = 0;
}
Ltexture::~Ltexture()
{
    free();
}
bool Ltexture::loadFromFile(string path)
{
    free();
    SDL_Texture *newTexture = NULL;
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    SDL_SetColorKey(loadedSurface,SDL_TRUE,SDL_MapRGB(loadedSurface->format,0,0xFF,0xFF));
    newTexture = SDL_CreateTextureFromSurface(main_renderer,loadedSurface);
    mWidth = loadedSurface->w;
    mHeight = loadedSurface->h;
    SDL_FreeSurface(loadedSurface);
    mTexture = newTexture;
    return newTexture!=NULL;
}
void Ltexture::free()
{
    SDL_DestroyTexture(mTexture);
    mTexture = NULL;
    mWidth=0;
    mHeight=0;
}
void Ltexture::setColor(Uint8 red,Uint8 blue, Uint8 green)
{
    SDL_SetTextureColorMod(mTexture,red,green,blue);
}
void Ltexture::setBlendMode(SDL_BlendMode blending)
{
    SDL_SetTextureBlendMode(mTexture,blending);
}
void Ltexture::setAlpha(Uint8 alpha)
{
    SDL_SetTextureAlphaMod(mTexture,alpha);
}
void Ltexture::render(int x,int y,SDL_Rect* clip)
{
    SDL_Rect renderQuad = {x,y,mWidth,mHeight};
    renderQuad.w = clip->w;
    renderQuad.h = clip->h;
    SDL_RenderCopy(main_renderer,mTexture,clip,&renderQuad);
}
int Ltexture::getH()
{
    return mHeight;
}
int Ltexture::getw()
{
    return mWidth;
}

void Ltexture::renderText(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    SDL_Rect renderQuad = {x,y,mWidth,mHeight};
    if(clip!=NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopyEx(main_renderer, mTexture, clip, &renderQuad, angle, center, flip);
}

#if defined(_SDL_TTF_H) || defined(SDL_TTF_H)
bool Ltexture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( textfont, textureText.c_str(), textColor );
	if( textSurface != NULL )
	{
		//Create texture from surface pixels
    mTexture = SDL_CreateTextureFromSurface( main_renderer, textSurface );
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

	return mTexture != NULL;
}
#endif


SDL_Texture* loadTexture(std::string path)
{
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL)   printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    else
    {
        newTexture = SDL_CreateTextureFromSurface(main_renderer, loadedSurface);
        if(newTexture==NULL)  printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}



Ltexture  header_text_input_texture;
void HeaderInputFromUser(){

  SDL_Rect  headerRect = {0, 0, sw, sh};
  bool quit_this = false;
  SDL_Event e1;
  SDL_Color textColor ={0xFF,0xFF,0xFF};


  std::string inputText = " ";

  SDL_StartTextInput();

  while( !quit_this )
  {

    bool renderText = false;


    while( SDL_PollEvent( &e1 ) != 0 )
    {
      if(e1.type == SDL_QUIT)
      {
        quit_this = true;

      }

       if( e1.type == SDL_KEYDOWN )
      {
        if( e1.key.keysym.sym == SDLK_RETURN )
        {
          quit_this = true;
        }

        if( e1.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0 )
        {
          inputText.pop_back();
          renderText = true;
        }


      }
      else if( e1.type == SDL_TEXTINPUT )
      {
        if( !( SDL_GetModState() & KMOD_CTRL && ( e1.text.text[ 0 ] == 'c' || e1.text.text[ 0 ] == 'C' || e1.text.text[ 0 ] == 'v' || e1.text.text[ 0 ] == 'V' ) ) )
        {
          inputText += e1.text.text;
          renderText = true;
        }
      }
    }


    if( renderText )
    {

      if( inputText != " " )
      {

        header_text_input_texture.loadFromRenderedText( inputText.c_str(), textColor );
      }

      else
      {


        header_text_input_texture.loadFromRenderedText( " ", textColor );
      }
    }




    SDL_SetRenderDrawColor( main_renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear( main_renderer );

    SDL_RenderSetViewport(main_renderer, &headerRect);


    SDL_RenderCopy(main_renderer, numberInputTexture,  NULL, NULL);

    header_text_input_texture.renderText(100,100 );


    SDL_RenderPresent( main_renderer);
  }


  SDL_StopTextInput();
  SDL_RenderClear( main_renderer );
  numbers += inputText;
  printf("%s\n", numbers.c_str());

}


bool init()
{
    bool s = true;
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        s = false;
    }
    else
    {
        if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1"))
        {
            s = false;
        }
        else
        {
            main_window = SDL_CreateWindow("SDL_Project",0,0,sw,sh,SDL_WINDOW_SHOWN);
            if(main_window==NULL)
            {
                s= false;
            }
            else
            {
                main_renderer = SDL_CreateRenderer(main_window,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
                if(main_renderer == NULL)
                {
                    s = false;
                }
                else
                {
                    SDL_SetRenderDrawColor(main_renderer,0xFF,0xFF,0xFF,0xFF);
                    int imgFlags = IMG_INIT_PNG;
                    if(!(IMG_Init(imgFlags) && imgFlags))
                    {
                        s = false;
                    }
                    if( TTF_Init() == -1 )
                    {
                      printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                      s = false;
                    }
                }
            }
        }
    }

    return s;
}
bool loadMedia()
{
    numberInputTexture = loadTexture("Merge Sort.png");
    bool s = true;

    s = s & algo_vis_button.loadFromFile("rsz_algo_vis.png");
    algo_vis_rect.x = 0;
    algo_vis_rect.y = 0;
    algo_vis_rect.w = 300;
    algo_vis_rect.h = 200;

    s = s & play_button.loadFromFile("Play.png");
    play_rect.x = 0;
    play_rect.y = 0;
    play_rect.w = 256;
    play_rect.h = 128;

    s = s & quit_button.loadFromFile("Quit.png");
    quit_rect.x = 0;
    quit_rect.y = 0;
    quit_rect.w = 256;
    quit_rect.h = 128;

    s = s & merge_button.loadFromFile("Merge Sort.png");
    merge_button_rect.x = 0;
    merge_button_rect.y = 0;
    merge_button_rect.w = merge_button_width;
    merge_button_rect.h = merge_button_height;

    s = s & bubble_button.loadFromFile("Bubble Sort.png");
    bubble_button_rect.x = 0;
    bubble_button_rect.y = 0;
    bubble_button_rect.w = bubble_button_width;
    bubble_button_rect.h = bubble_button_height;

    s = s & insertion_button.loadFromFile("Insertion sort.png");
    insertion_button_rect.x = 0;
    insertion_button_rect.y = 0;
    insertion_button_rect.w = insertion_button_width;
    insertion_button_rect.h = insertion_button_height;

    s = s & insertion_ascending_button.loadFromFile("Ascending.png");
    insertion_ascending_button_rect.x = 0;
    insertion_ascending_button_rect.y = 0;
    insertion_ascending_button_rect.w = insertion_ascending_button_width;
    insertion_ascending_button_rect.h = insertion_ascending_button_height;

    s = s & insertion_descending_button.loadFromFile("Descending.png");
    insertion_descending_button_rect.x = 0;
    insertion_descending_button_rect.y = 0;
    insertion_descending_button_rect.w = insertion_descending_button_width;
    insertion_descending_button_rect.h = insertion_descending_button_height;

    s = s & bubble_ascending_button.loadFromFile("Ascending.png");
    bubble_ascending_button_rect.x = 0;
    bubble_ascending_button_rect.y = 0;
    bubble_ascending_button_rect.w = bubble_ascending_button_width;
    bubble_ascending_button_rect.h = bubble_ascending_button_height;

    s = s & bubble_descending_button.loadFromFile("Descending.png");
    bubble_descending_button_rect.x = 0;
    bubble_descending_button_rect.y = 0;
    bubble_descending_button_rect.w = bubble_descending_button_width;
    bubble_descending_button_rect.h = bubble_descending_button_height;

    s = s & bubble_ascending_load_button.loadFromFile("Bubble_Ascending_Load.png");
    bubble_ascending_load_button_rect.x = 0;
    bubble_ascending_load_button_rect.y = 0;
    bubble_ascending_load_button_rect.w = bubble_ascending_load_width;
    bubble_ascending_load_button_rect.h = bubble_ascending_load_height;

    s = s & bubble_descending_load_button.loadFromFile("Bubble_Descending_Load.png");
    bubble_descending_load_button_rect.x = 0;
    bubble_descending_load_button_rect.y = 0;
    bubble_descending_load_button_rect.w = bubble_descending_load_width;
    bubble_descending_load_button_rect.h = bubble_descending_load_height;

    s = s & insertion_ascending_load_button.loadFromFile("Insertion_Ascending_Load.png");
    insertion_ascending_load_button_rect.x = 0;
    insertion_ascending_load_button_rect.y = 0;
    insertion_ascending_load_button_rect.w = insertion_ascending_load_width;
    insertion_ascending_load_button_rect.h = insertion_ascending_load_height;

    s = s & insertion_descending_load_button.loadFromFile("Insertion_Descending_Load.png");
    insertion_descending_load_button_rect.x = 0;
    insertion_descending_load_button_rect.y = 0;
    insertion_descending_load_button_rect.w = insertion_descending_load_width;
    insertion_descending_load_button_rect.h = insertion_descending_load_height;

    s = s & file_input_button.loadFromFile("File Input.png");
    file_input_rect.x = 0;
    file_input_rect.y = 0;
    file_input_rect.w = file_input_button_width;
    file_input_rect.h = file_input_button_height;

    s = s & user_input_button.loadFromFile("User Input.png");
    user_input_rect.x = 0;
    user_input_rect.y = 0;
    user_input_rect.w = file_input_button_width;
    user_input_rect.h = file_input_button_height;

    textfont = TTF_OpenFont("Fonts/Raleway-Light.ttf",20);
    return s;

}
int main()
{

    init();
    loadMedia();

    bool quit = false;
    bool menu = false;
    bool list_menu = false;
    bool insertion_menu = true;
    bool merge_menu = true;
    bool bubble_menu = true;
    bool bubble_ascending_menu = true;
    bool bubble_descending_menu = true;
    bool insertion_ascending_menu = true;
    bool insertion_descending_menu = true;
    bool quit_hobe = false;
    bool bascanned = false;
    bool bdscanned = false;
    bool iascanned = false;
    bool idscanned = false;
    bool file_input_ia = false;
    bool file_input_id = false;
    bool file_input_ba = false;
    bool file_input_bd = false;
    bool user_input_ia = false;
    bool user_input_id = false;
    bool user_input_ba = false;
    bool user_input_bd = false;
    bool file_input_taken_ba = false;
    bool file_input_taken_bd = false;
    bool file_input_taken_ia = false;
    bool file_input_taken_id = false;
      //bool main_menu_te_jabo = true;
    int mx,my;
    SDL_Event e;
    SDL_Event s;
    int arad[25];

    int araa[25];
    srand(time(NULL));
    SDL_Rect aras[25];
    int x;
    FILE *fp1 = NULL, *fp2 = NULL;
    int ialc = 0,idlc = 0;
    const Uint8* state = SDL_GetKeyboardState(NULL);
    bool paused = false;

    int arr[3]= {1,2,35};
    char temp[100];
    sprintf(temp, "%d %d %d", arr[0], arr[1], arr[2]);

    // SDL_Color putkii = {0xFF, 0xFF, 0xFF};
    // SDL_Texture* Test = loadTextTexture(temp, putkii);
    // SDL_Rect bal = {0,0,400, 80};
    // SDL_RenderSetViewport(main_renderer, &bal);
    // SDL_RenderCopy(main_renderer, Test, NULL, NULL);
    // SDL_RenderPresent(main_renderer);
    // SDL_Delay(2000);
    // SDL_RenderClear(main_renderer);

    while(!quit)
    {
        while(SDL_PollEvent(&e))
        {
            SDL_GetMouseState(&mx,&my);
            if(e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if(e.type == SDL_MOUSEBUTTONDOWN)
            {
                if(hover(play_button_x,play_button_y,play_button_width,play_button_height,mx,my)&&!menu)
                {
                    menu = true;
                }
                else if(hover(quit_button_x,quit_button_y,quit_button_width,quit_button_height,mx,my)&& !menu)
                {
                    quit = true;
                }
                else if(hover(merge_button_x,merge_button_y,merge_button_width,merge_button_height,mx,my)&& !list_menu && menu)
                {
                    list_menu = true;
                    merge_menu = false;
                }
                else if(hover(bubble_button_x,bubble_button_y,bubble_button_width,bubble_button_height,mx,my)&& !list_menu && menu)
                {
                    list_menu = true;
                    bubble_menu = false;
                    bubble_ascending_menu = true;
                    bubble_descending_menu = true;
                    user_input_ba = false;
                    user_input_bd = false;
                    file_input_ba = false;
                    file_input_bd = false;

                }
                else if(hover(insertion_button_x,insertion_button_y,insertion_button_width,insertion_button_height,mx,my)&&!list_menu && menu)
                {
                    list_menu = true;
                    insertion_menu = false;
                    insertion_ascending_menu = true;
                    insertion_descending_menu = true;
                    user_input_ia = false;
                    user_input_id = false;
                    file_input_ia = false;
                    file_input_id = false;
                    //cout << insertion_menu<< '\n';
                }
                else if(hover(insertion_descending_button_x,insertion_descending_button_y,insertion_descending_button_width,insertion_descending_button_height,mx,my) && list_menu && menu && insertion_ascending_menu &&insertion_descending_menu)
                {
                //  insertion_menu = true;
                    insertion_descending_menu = false;
                    insertion_ascending_menu = true;
                }
                else if(hover(insertion_ascending_button_x,insertion_ascending_button_y,insertion_ascending_button_width,insertion_ascending_button_height,mx,my)&& list_menu && menu &&insertion_ascending_menu && insertion_descending_menu)
                {
                    //insertion_menu = true;
                    insertion_ascending_menu = false;
                    insertion_descending_menu = true;
                }
                else if(hover(bubble_ascending_button_x,bubble_ascending_button_y,bubble_ascending_button_width,bubble_ascending_button_height,mx,my)&& list_menu && menu && bubble_ascending_menu && bubble_descending_menu)
                {

                    //bubble_menu = true;
                    bubble_ascending_menu = false;
                    bubble_descending_menu = true;
                    //printf("%d\n",bubble_ascending_menu);
                    ialc = 0;
                    user_input_ba = false;
                }
                else if(hover(bubble_descending_button_x,bubble_descending_button_y,bubble_descending_button_width,bubble_descending_button_height,mx,my)&& list_menu && menu && bubble_descending_menu && bubble_ascending_menu)
                {

                    bubble_descending_menu = false;
                    bubble_ascending_menu = true;

                    idlc = 0;
                    user_input_bd = false;

                }
                else if(hover(file_input_button_x,file_input_button_y,file_input_button_width,file_input_button_height,mx,my) && !insertion_ascending_menu)
                {
                  file_input_ia = true;
                }
                else if(hover(file_input_button_x,file_input_button_y,file_input_button_width,file_input_button_height,mx,my) && !insertion_descending_menu)
                {
                  file_input_id = true;
                }
              else if(hover(file_input_button_x,file_input_button_y,file_input_button_width,file_input_button_height,mx,my) && !bubble_ascending_menu)
                {
                  file_input_ba = true;

                }
                else if(hover(file_input_button_x,file_input_button_y,file_input_button_width,file_input_button_height,mx,my) && !bubble_descending_menu)
                {
                  file_input_bd = true;

                }
                else if(hover(user_input_button_x,user_input_button_y,user_input_button_width,user_input_button_height,mx,my) && !insertion_ascending_menu)
                {
                  user_input_ia = true;
                }
                else if(hover(user_input_button_x,user_input_button_y,user_input_button_width,user_input_button_height,mx,my) && !insertion_descending_menu)
                {
                  user_input_id = true;
                }
                else if(hover(user_input_button_x,user_input_button_y,user_input_button_width,user_input_button_height,mx,my) && !bubble_ascending_menu)
                {
                  user_input_ba = true;

                }
                else if(hover(user_input_button_x,user_input_button_y,user_input_button_width,user_input_button_height,mx,my) && !bubble_descending_menu)
                {
                  user_input_bd = true;

                }
            }
        }
        if(state[SDL_SCANCODE_K]) HeaderInputFromUser();
        if(!menu)
        {
            SDL_SetRenderDrawColor( main_renderer, 0xFF, 0xFF, 0xFF, 0xFF );
            SDL_RenderClear( main_renderer );
            algo_vis_button.render(algo_vis_button_x,algo_vis_button_y,&algo_vis_rect);
            play_button.render(play_button_x,play_button_y,&play_rect);
            quit_button.render(quit_button_x,quit_button_y,&quit_rect);
            SDL_RenderPresent(main_renderer);
        }
        else if(menu)
        {
            if(!list_menu)
            {
                SDL_SetRenderDrawColor( main_renderer, 0x00, 0x00, 0x00, 0xFF );
                SDL_RenderClear( main_renderer );
                merge_button.render(merge_button_x,merge_button_y,&merge_button_rect);
                bubble_button.render(bubble_button_x,bubble_button_y,&bubble_button_rect);
                insertion_button.render(insertion_button_x,insertion_button_y,&insertion_button_rect);
                SDL_RenderPresent(main_renderer);
            }
            else
            {
                if(!merge_menu)
                {

                }
                else if(!bubble_menu)
                {
                  if(bubble_ascending_menu && bubble_descending_menu){
                  SDL_SetRenderDrawColor( main_renderer, 0x92, 0x2A, 0x31, 0xFF );
                  SDL_RenderClear( main_renderer );
                  bubble_ascending_button.render(bubble_ascending_button_x,bubble_ascending_button_y,&bubble_ascending_button_rect);
                  bubble_descending_button.render(bubble_descending_button_x,bubble_descending_button_y,&bubble_descending_button_rect);
                  SDL_RenderPresent(main_renderer);}
                  if(!bubble_ascending_menu)
                  {


                      //SDL_RenderPresent(main_renderer);
                      SDL_SetRenderDrawColor( main_renderer,0xDD, 0xAD,  0x02 , 0xFF );
                      SDL_RenderClear(main_renderer);
                      if(!user_input_ba){

                      user_input_button.render(user_input_button_x,user_input_button_y,&user_input_rect);
                      file_input_button.render(file_input_button_x,file_input_button_y,&file_input_rect);
                  }//  SDL_RenderPresent(main_renderer);

                      SDL_RenderPresent(main_renderer);


                    if(file_input_ba){

                      for(w=0;w<24;)
                      {
                        bubble_ascending_load_button.render(bubble_ascending_load_x,bubble_ascending_load_y,&bubble_ascending_load_button_rect);
                          while(SDL_PollEvent(&s))
                          {
                              if(s.type==SDL_KEYDOWN)
                              {
                                  if(s.key.keysym.sym==SDLK_SPACE)
                                  {
                                      reset(&paused);
                                  }

                                  else if(paused && s.key.keysym.sym == SDLK_RIGHT)
                                  {
                                      if(arad[w]>arad[w+1])
                                      {
                                          swap(arad[w],arad[w+1]);
                                          //printf("%d %d\n",w,w+1);
                                      }
                                      // printf("Okay\n");
                                      for(j = w;j<w+1;j++)
                                      {
                                          // printf("Okay2\n");
                                          for(q=0;q<25;q++)
                                          {
                                              // printf("Okay3\n");
                                              if(s.type == SDL_QUIT)
                                              {
                                                  quit = true;
                                                  break;
                                              }
                                              ialc++;

                                              aras[q] ={250 + q*20,450-arad[q]*15,15,arad[q]*15};
                                              SDL_SetRenderDrawColor( main_renderer,0xDD, 0xDD,  0xDD , 0xFF );
                                              SDL_RenderFillRect( main_renderer, &aras[q] );

                                          }
                                          SDL_RenderPresent(main_renderer);
                                          SDL_Delay(100);

                                          SDL_SetRenderDrawColor( main_renderer,0xDD, 0xAD,  0x02 , 0xFF );
                                          SDL_RenderClear(main_renderer);
                                      }
                                      w++;
                                  }


                              }
                              if(s.type == SDL_QUIT)
                              {
                                  quit = true;
                                  break;
                              }

                          }
                          if(!paused){
                              if(arad[w]>arad[w+1])
                              {
                                  swap(arad[w],arad[w+1]);
                                  //printf("%d %d\n",w,w+1);
                              }
                              for(j = w;j<w+1;j++){

                                  for(q=0;q<25;q++)
                                  {
                                      if(s.type == SDL_QUIT)
                                      {
                                          quit = true;
                                          break;
                                      }
                                      ialc++;

                                      aras[q] ={250 + q*20,450-arad[q]*15,15,arad[q]*15};
                                      SDL_SetRenderDrawColor( main_renderer,0xDD, 0xDD,  0xDD , 0xFF );
                                      SDL_RenderFillRect( main_renderer, &aras[q] );

                                  }
                                  if(quit)
                                  {
                                      break;
                                  }
                                  SDL_RenderPresent(main_renderer);
                                  SDL_Delay(100);

                                  SDL_SetRenderDrawColor( main_renderer,0xDD, 0xAD,  0x02 , 0xFF );
                                  SDL_RenderClear(main_renderer);}
                              }
                              if(quit){
                                  break;
                              }
                              if(ialc==25*25*25)
                              {

                                  reset(&list_menu);
                                  reset(&bubble_ascending_menu);
                                  reset(&bubble_menu);
                                  reset(&file_input_ba);
                              }
                              SDL_SetRenderDrawColor( main_renderer,0xDD, 0xAD,  0x02 , 0xFF );
                              SDL_RenderClear(main_renderer);
                              if(!paused)w++;

                          }
                      }
                      else if(user_input_ba){

                        if(!file_input_taken_ba)
                        {
                          fp1 = fopen("in.txt","r");
                          for(x = 0;x<25;x++)
                          {
                            fscanf(fp1, "%d", &arad[x]);
                          }
                          if(x==25)
                          {
                            fclose(fp1);
                            reset(&file_input_taken_ba);
                          }
                        }
                        for(w=0;w<24;)
                        {
                          bubble_ascending_load_button.render(bubble_ascending_load_x,bubble_ascending_load_y,&bubble_ascending_load_button_rect);
                            while(SDL_PollEvent(&s))
                            {
                                if(s.type==SDL_KEYDOWN)
                                {
                                    if(s.key.keysym.sym==SDLK_SPACE)
                                    {
                                        reset(&paused);
                                    }

                                    else if(paused && s.key.keysym.sym == SDLK_RIGHT)
                                    {
                                        if(arad[w]>arad[w+1])
                                        {
                                            swap(arad[w],arad[w+1]);
                                            //printf("%d %d\n",w,w+1);
                                        }
                                        // printf("Okay\n");
                                        for(j = w;j<w+1;j++)
                                        {
                                            // printf("Okay2\n");
                                            for(q=0;q<25;q++)
                                            {
                                                // printf("Okay3\n");
                                                if(s.type == SDL_QUIT)
                                                {
                                                    quit = true;
                                                    break;
                                                }
                                                ialc++;

                                                aras[q] ={250 + q*20,450-arad[q]*15,15,arad[q]*15};
                                                SDL_SetRenderDrawColor( main_renderer,0xDD, 0xDD,  0xDD , 0xFF );
                                                SDL_RenderFillRect( main_renderer, &aras[q] );

                                            }
                                            SDL_RenderPresent(main_renderer);
                                            SDL_Delay(100);

                                            SDL_SetRenderDrawColor( main_renderer,0xDD, 0xAD,  0x02 , 0xFF );
                                            SDL_RenderClear(main_renderer);
                                        }
                                        w++;
                                    }


                                }
                                if(s.type == SDL_QUIT)
                                {
                                    quit = true;
                                    break;
                                }

                            }
                            if(!paused){
                                if(arad[w]>arad[w+1])
                                {
                                    swap(arad[w],arad[w+1]);
                                    //printf("%d %d\n",w,w+1);
                                }
                                for(j = w;j<w+1;j++){

                                    for(q=0;q<25;q++)
                                    {
                                        if(s.type == SDL_QUIT)
                                        {
                                            quit = true;
                                            break;
                                        }
                                        ialc++;

                                        aras[q] ={250 + q*20,450-arad[q]*15,15,arad[q]*15};
                                        SDL_SetRenderDrawColor( main_renderer,0xDD, 0xDD,  0xDD , 0xFF );
                                        SDL_RenderFillRect( main_renderer, &aras[q] );

                                    }
                                    if(quit)
                                    {
                                        break;
                                    }
                                    SDL_RenderPresent(main_renderer);
                                    SDL_Delay(100);

                                    SDL_SetRenderDrawColor( main_renderer,0xDD, 0xAD,  0x02 , 0xFF );
                                    SDL_RenderClear(main_renderer);}
                                }
                                if(quit){
                                    break;
                                }
                                if(ialc==25*25*25)
                                {
                                  fp2 = fopen("out.txt","w");
                                  for(x=0;x<25;x++)
                                  {
                                    fprintf(fp2, "%d ", arad[x]);
                                  }
                                  if(x==25)
                                  {
                                    fclose(fp2);
                                  }
                                    reset(&list_menu);
                                    reset(&bubble_ascending_menu);
                                    reset(&bubble_menu);
                                    reset(&user_input_ba);

                                }
                                SDL_SetRenderDrawColor( main_renderer,0xDD, 0xAD,  0x02 , 0xFF );
                                SDL_RenderClear(main_renderer);
                                if(!paused)w++;

                            }
                        }
                      }
                      else  if(!bubble_descending_menu)
                        {


                            //SDL_RenderPresent(main_renderer);
                            SDL_SetRenderDrawColor( main_renderer,0xDD, 0xAD,  0x02 , 0xFF );
                            SDL_RenderClear(main_renderer);
                            if(!user_input_bd){

                            user_input_button.render(user_input_button_x,user_input_button_y,&user_input_rect);
                            file_input_button.render(file_input_button_x,file_input_button_y,&file_input_rect);
                          //  SDL_RenderPresent(main_renderer);
                          //printf("bubble descending menu = %d\nfile input bd = %d\nuser input bd = %d\n",bubble_descending_menu,file_input_bd,user_input_bd);
                            SDL_RenderPresent(main_renderer);}


                          if(file_input_bd){

                            for(w=0;w<24;)
                            {
                              bubble_descending_load_button.render(bubble_descending_load_x,bubble_descending_load_y,&bubble_descending_load_button_rect);
                                while(SDL_PollEvent(&s))
                                {
                                    if(s.type==SDL_KEYDOWN)
                                    {
                                        if(s.key.keysym.sym==SDLK_SPACE)
                                        {
                                            reset(&paused);
                                        }

                                        else if(paused && s.key.keysym.sym == SDLK_RIGHT)
                                        {
                                            if(araa[w]<araa[w+1])
                                            {
                                                swap(araa[w],araa[w+1]);
                                                //printf("%d %d\n",w,w+1);
                                            }
                                            // printf("Okay\n");
                                            for(j = w;j<w+1;j++)
                                            {
                                                // printf("Okay2\n");
                                                for(q=0;q<25;q++)
                                                {
                                                    // printf("Okay3\n");
                                                    if(s.type == SDL_QUIT)
                                                    {
                                                        quit = true;
                                                        break;
                                                    }
                                                    idlc++;

                                                    aras[q] ={250 + q*20,450-araa[q]*15,15,araa[q]*15};
                                                    SDL_SetRenderDrawColor( main_renderer,0xDD, 0xDD,  0xDD , 0xFF );
                                                    SDL_RenderFillRect( main_renderer, &aras[q] );

                                                }
                                                SDL_RenderPresent(main_renderer);
                                                SDL_Delay(100);

                                                SDL_SetRenderDrawColor( main_renderer,0xDD, 0xAD,  0x02 , 0xFF );
                                                SDL_RenderClear(main_renderer);
                                            }
                                            w++;
                                        }


                                    }
                                    if(s.type == SDL_QUIT)
                                    {
                                        quit = true;
                                        break;
                                    }

                                }
                                if(!paused){
                                    if(araa[w]<araa[w+1])
                                    {
                                        swap(araa[w],araa[w+1]);
                                        //printf("%d %d\n",w,w+1);
                                    }
                                    for(j = w;j<w+1;j++){

                                        for(q=0;q<25;q++)
                                        {
                                            if(s.type == SDL_QUIT)
                                            {
                                                quit = true;
                                                break;
                                            }
                                            idlc++;

                                            aras[q] ={250 + q*20,450-araa[q]*15,15,araa[q]*15};
                                            SDL_SetRenderDrawColor( main_renderer,0xDD, 0xDD,  0xDD , 0xFF );
                                            SDL_RenderFillRect( main_renderer, &aras[q] );

                                        }
                                        if(quit)
                                        {
                                            break;
                                        }
                                        SDL_RenderPresent(main_renderer);
                                        SDL_Delay(100);

                                        SDL_SetRenderDrawColor( main_renderer,0xDD, 0xAD,  0x02 , 0xFF );
                                        SDL_RenderClear(main_renderer);}
                                    }
                                    if(quit){
                                        break;
                                    }
                                    if(idlc==25*25*25)
                                    {

                                        reset(&list_menu);
                                        reset(&bubble_descending_menu);
                                        reset(&bubble_menu);
                                        reset(&file_input_bd);
                                    }
                                    SDL_SetRenderDrawColor( main_renderer,0xDD, 0xAD,  0x02 , 0xFF );
                                    SDL_RenderClear(main_renderer);
                                    if(!paused)w++;

                                }
                            }
                            else if(user_input_bd){

                              if(!file_input_taken_bd)
                              {
                                fp1 = fopen("in.txt","r");
                                for(x = 0;x<25;x++)
                                {
                                  fscanf(fp1, "%d", &araa[x]);
                                }
                                if(x==25)
                                {
                                  fclose(fp1);
                                  reset(&file_input_taken_bd);
                                }
                              }
                              for(w=0;w<24;)
                              {
                                bubble_descending_load_button.render(bubble_descending_load_x,bubble_descending_load_y,&bubble_descending_load_button_rect);
                                  while(SDL_PollEvent(&s))
                                  {
                                      if(s.type==SDL_KEYDOWN)
                                      {
                                          if(s.key.keysym.sym==SDLK_SPACE)
                                          {
                                              reset(&paused);
                                          }

                                          else if(paused && s.key.keysym.sym == SDLK_RIGHT)
                                          {
                                              if(araa[w]<araa[w+1])
                                              {
                                                  swap(araa[w],araa[w+1]);
                                                  //printf("%d %d\n",w,w+1);
                                              }
                                              // printf("Okay\n");
                                              for(j = w;j<w+1;j++)
                                              {
                                                  // printf("Okay2\n");
                                                  for(q=0;q<25;q++)
                                                  {
                                                      // printf("Okay3\n");
                                                      if(s.type == SDL_QUIT)
                                                      {
                                                          quit = true;
                                                          break;
                                                      }
                                                      idlc++;

                                                      aras[q] ={250 + q*20,450-araa[q]*15,15,araa[q]*15};
                                                      SDL_SetRenderDrawColor( main_renderer,0xDD, 0xDD,  0xDD , 0xFF );
                                                      SDL_RenderFillRect( main_renderer, &aras[q] );

                                                  }
                                                  SDL_RenderPresent(main_renderer);
                                                  SDL_Delay(100);

                                                  SDL_SetRenderDrawColor( main_renderer,0xDD, 0xAD,  0x02 , 0xFF );
                                                  SDL_RenderClear(main_renderer);
                                              }
                                              w++;
                                          }


                                      }
                                      if(s.type == SDL_QUIT)
                                      {
                                          quit = true;
                                          break;
                                      }

                                  }
                                  if(!paused){
                                      if(araa[w]<araa[w+1])
                                      {
                                          swap(araa[w],araa[w+1]);
                                          //printf("%d %d\n",w,w+1);
                                      }
                                      for(j = w;j<w+1;j++){

                                          for(q=0;q<25;q++)
                                          {
                                              if(s.type == SDL_QUIT)
                                              {
                                                  quit = true;
                                                  break;
                                              }
                                              ialc++;

                                              aras[q] ={250 + q*20,450-araa[q]*15,15,araa[q]*15};
                                              SDL_SetRenderDrawColor( main_renderer,0xDD, 0xDD,  0xDD , 0xFF );
                                              SDL_RenderFillRect( main_renderer, &aras[q] );

                                          }
                                          if(quit)
                                          {
                                              break;
                                          }
                                          SDL_RenderPresent(main_renderer);
                                          SDL_Delay(100);

                                          SDL_SetRenderDrawColor( main_renderer,0xDD, 0xAD,  0x02 , 0xFF );
                                          SDL_RenderClear(main_renderer);}
                                      }
                                      if(quit){
                                          break;
                                      }
                                      if(idlc==25*25*25)
                                      {
                                        fp2 = fopen("out.txt","w");
                                        for(x=0;x<25;x++)
                                        {
                                          fprintf(fp2, "%d ", araa[x]);
                                        }
                                        if(x==25)
                                        {
                                          fclose(fp2);
                                        }
                                          reset(&list_menu);
                                          reset(&bubble_descending_menu);
                                          reset(&bubble_menu);
                                          reset(&user_input_bd);

                                      }
                                      SDL_SetRenderDrawColor( main_renderer,0xDD, 0xAD,  0x02 , 0xFF );
                                      SDL_RenderClear(main_renderer);
                                      if(!paused)w++;

                                  }
                              }
                            }
                    }
                    else if(!insertion_menu)
                    {
                        SDL_SetRenderDrawColor( main_renderer,0xDD, 0xAD,  0x02 , 0xFF );
                        SDL_RenderClear(main_renderer);
                        insertion_ascending_button.render(insertion_ascending_button_x,insertion_ascending_button_y,&insertion_ascending_button_rect);
                        insertion_descending_button.render(insertion_descending_button_x,insertion_descending_button_y,&insertion_descending_button_rect);
                        SDL_RenderPresent(main_renderer);
                        if(!insertion_ascending_menu)
                        {
                          if(!iascanned)
                          {

                            for(int v=0;v<25;v++)
                            {
                              scanf("%d",&arad[v]);
                            }
                            iascanned = true;
                          }

                            SDL_RenderPresent(main_renderer);
                            SDL_SetRenderDrawColor( main_renderer,0xDD, 0xAD,  0x02 , 0xFF );
                            SDL_RenderClear(main_renderer);
                            for(w=0;w<25;)
                            {
                              //insertion_ascending_load_button.render(insertion_ascending_load_x,insertion_ascending_load_y,&insertion_ascending_load_button_rect);
                                //if(paused) continue;
                                while(SDL_PollEvent(&s))
                                {
                                    if(s.type==SDL_KEYDOWN)
                                    {
                                        if(s.key.keysym.sym==SDLK_SPACE)
                                        {
                                            reset(&paused);
                                        }

                                        else if(paused && s.key.keysym.sym == SDLK_RIGHT)
                                        {
                                            int j = w;
                                            while(j >= 1 && arad[j] <= arad[j-1])
                                            {
                                                swap(arad[j],arad[j-1]);
                                                if(s.type==SDL_KEYDOWN)
                                                {
                                                    if(s.key.keysym.sym==SDLK_SPACE) reset(&paused);

                                                }
                                                if(s.type == SDL_QUIT){
                                                    quit = true;
                                                    break;
                                                }
                                                for(q=0;q<25;q++)
                                                {
                                                    insertion_ascending_load_button.render(insertion_ascending_load_x,insertion_ascending_load_y,&insertion_ascending_load_button_rect);
                                                    aras[q] ={250 + q*20,450-arad[q]*15,15,arad[q]*15};
                                                    SDL_SetRenderDrawColor( main_renderer,0xDD, 0xDD,  0xDD , 0xFF );
                                                    SDL_RenderFillRect( main_renderer, &aras[q] );
                                                }
                                                SDL_RenderPresent(main_renderer);
                                                SDL_Delay(100);

                                                SDL_SetRenderDrawColor( main_renderer,0xDD, 0xAD,  0x02 , 0xFF );
                                                SDL_RenderClear(main_renderer);
                                                j--;
                                            }
                                            w++;
                                            if(quit)
                                            {
                                                break;
                                            }
                                        }

                                    }
                                    if(s.type == SDL_QUIT){
                                        quit = true;
                                        break;
                                    }

                                }
                                int j;
                                j = w;
                                if(!paused){

                                    while(j >= 1 && arad[j] <= arad[j-1])
                                    {
                                        swap(arad[j],arad[j-1]);
                                        if(s.type==SDL_KEYDOWN)
                                        {
                                            if(s.key.keysym.sym==SDLK_SPACE) reset(&paused);

                                        }
                                        if(s.type == SDL_QUIT){
                                            quit = true;
                                            break;
                                        }
                                        for(q=0;q<25;q++)
                                        {
                                            insertion_ascending_load_button.render(insertion_ascending_load_x,insertion_ascending_load_y,&insertion_ascending_load_button_rect);
                                            aras[q] ={250 + q*20,450-arad[q]*15,15,arad[q]*15};
                                            SDL_SetRenderDrawColor( main_renderer,0xDD, 0xDD,  0xDD , 0xFF );
                                            SDL_RenderFillRect( main_renderer, &aras[q] );
                                        }
                                        SDL_RenderPresent(main_renderer);
                                        SDL_Delay(100);

                                        SDL_SetRenderDrawColor( main_renderer,0xDD, 0xAD,  0x02 , 0xFF );
                                        SDL_RenderClear(main_renderer);
                                        j--;
                                    }
                                    if(w==24 && j==0)
                                    {
                                        reset(&list_menu);
                                        reset(&insertion_ascending_menu);
                                        reset(&insertion_menu);
                                        reset(&iascanned);
                                    }
                                }
                                if(quit)
                                {
                                    break;
                                }

                                SDL_SetRenderDrawColor( main_renderer,0xDD, 0xAD,  0x02 , 0xFF );
                                SDL_RenderClear(main_renderer);
                                if(!paused) w++;
                            }
                        }


                        else if(!insertion_descending_menu)
                        {
                          // if(!idscanned)
                          // {
                          //   printf("Enter 25 numbers(ranging from 1 to 25):\n");
                          //   for(int v=0;v<25;v++)
                          //   {
                          //     scanf("%d",&araa[v]);
                          //   }
                          //   idscanned = true;
                          // }
                            SDL_RenderPresent(main_renderer);
                            SDL_SetRenderDrawColor( main_renderer,0xDD, 0xAD,  0x02 , 0xFF );
                            SDL_RenderClear(main_renderer);
                            for(w=0;w<25;)
                            {

                                    //if(paused) continue;
                                while(SDL_PollEvent(&s))
                                {
                                    if(s.type==SDL_KEYDOWN)
                                    {
                                        if(s.key.keysym.sym==SDLK_SPACE)
                                        {
                                            reset(&paused);
                                        }
                                        else if(paused && s.key.keysym.sym == SDLK_RIGHT)
                                        {
                                            int j = w;
                                            while(j >= 1 && araa[j] >= araa[j-1])
                                            {
                                                swap(araa[j],araa[j-1]);
                                                if(s.type==SDL_KEYDOWN)
                                                {
                                                    if(s.key.keysym.sym==SDLK_SPACE) reset(&paused);

                                                }
                                                if(s.type == SDL_QUIT){
                                                    quit = true;
                                                    break;
                                                }
                                                for(q=0;q<25;q++)
                                                {
                                                    insertion_descending_load_button.render(insertion_descending_load_x,insertion_descending_load_y,&insertion_descending_load_button_rect);
                                                    aras[q] ={250 + q*20,450-araa[q]*15,15,araa[q]*15};
                                                    SDL_SetRenderDrawColor( main_renderer,0xDD, 0xDD,  0xDD , 0xFF );
                                                    SDL_RenderFillRect( main_renderer, &aras[q] );
                                                }
                                                SDL_RenderPresent(main_renderer);
                                                SDL_Delay(100);

                                                SDL_SetRenderDrawColor( main_renderer,0xDD, 0xAD,  0x02 , 0xFF );
                                                SDL_RenderClear(main_renderer);
                                                j--;
                                            }
                                            w++;
                                            if(quit)
                                            {
                                                break;
                                            }
                                        }


                                    }
                                    if(s.type == SDL_QUIT)
                                    {
                                        quit = true;
                                        break;
                                    }
                                }
                                int j;
                                j = w;
                                if(!paused){
                                    while(j >= 1 && araa[j] >= araa[j-1])
                                    {
                                        swap(araa[j],araa[j-1]);
                                        while(SDL_PollEvent(&s))
                                        {
                                            if(s.type==SDL_KEYDOWN)
                                            {
                                                if(s.key.keysym.sym==SDLK_SPACE) reset(&paused);

                                            }
                                        }
                                        for(q=0;q<25;q++)
                                        {
                                            insertion_descending_load_button.render(insertion_descending_load_x,insertion_descending_load_y,&insertion_descending_load_button_rect);
                                            aras[q] ={250 + q*20,450-araa[q]*15,15,araa[q]*15};
                                            SDL_SetRenderDrawColor( main_renderer,0xDD, 0xDD,  0xDD , 0xFF );
                                            SDL_RenderFillRect( main_renderer, &aras[q] );
                                        }

                                        if(s.type == SDL_QUIT)
                                        {
                                            quit = true;
                                            break;
                                        }

                                        SDL_RenderPresent(main_renderer);
                                        SDL_Delay(100);

                                        SDL_SetRenderDrawColor( main_renderer,0xDD, 0xAD,  0x02 , 0xFF );
                                        SDL_RenderClear(main_renderer);
                                        j--;
                                    }
                                    if(w==24 && j==0)
                                    {
                                        reset(&list_menu);
                                        reset(&insertion_descending_menu);
                                        reset(&insertion_menu);
                                        reset(&idscanned);
                                    }
                                    if(!paused) w++;
                                }
                                if(quit)
                                {
                                    break;
                                }
                                SDL_SetRenderDrawColor( main_renderer,0xDD, 0xAD,  0x02 , 0xFF );
                                SDL_RenderClear(main_renderer);
                            }
                        }
                    }

                }
            }
        }
        return 0;
    }
 
