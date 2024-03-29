#include <iostream>
#include<stdio.h>
#include <SDL2/SDL.h>
#include <time.h>
#include <SDL2/SDL_image.h>
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

int w,j,q;

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

SDL_Window *main_window = NULL;
SDL_Renderer *main_renderer = NULL;
class Ltexture
{
public:
    Ltexture();
    ~Ltexture();
    bool loadFromFile(string path);
    void free();
    void setColor(Uint8 red,Uint8 green,Uint8 blue);
    void setBlendMode(SDL_BlendMode blending);
    void setAlpha(Uint8 alpha);
    void render(int x,int y, SDL_Rect *clip = NULL);
    int getw();
    int getH();
private:
    SDL_Texture *mTexture;
    int mwidth,mHeight;
};
Ltexture algo_vis_button,quit_button,play_button,merge_button,bubble_button,insertion_button;
Ltexture bubble_ascending_button,bubble_descending_button,insertion_ascending_button,insertion_descending_button;
bool init();
bool loadMedia();
void close();

Ltexture::Ltexture()
{
    mTexture = NULL;
    mwidth = 0,mHeight = 0;
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
    mwidth = loadedSurface->w;
    mHeight = loadedSurface->h;
    SDL_FreeSurface(loadedSurface);
    mTexture = newTexture;
    return newTexture!=NULL;
}
void Ltexture::free()
{
    SDL_DestroyTexture(mTexture);
    mTexture = NULL;
    mwidth=0;
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
    SDL_Rect renderQuad = {x,y,mwidth,mHeight};
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
    return mwidth;
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
                }
            }
        }
    }

    return s;
}
bool loadMedia()
{

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
    //bool main_menu_te_jabo = true;
    int mx,my;
    SDL_Event e;
    SDL_Event s;
    int arad[25];

    int araa[25];

    SDL_Rect aras[25];

    int ialc = 0,idlc = 0;
    const Uint8* state = SDL_GetKeyboardState(NULL);
    bool paused = false;

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
                }
                else if(hover(insertion_button_x,insertion_button_y,insertion_button_width,insertion_button_height,mx,my)&&!list_menu && menu)
                {
                    list_menu = true;
                    insertion_menu = false;
                    //cout << insertion_menu<< '\n';
                }
                else if(hover(insertion_descending_button_x,insertion_descending_button_y,insertion_descending_button_width,insertion_descending_button_height,mx,my) && !insertion_menu && menu)
                {
                //  insertion_menu = true;
                    insertion_descending_menu = false;
                    for(w=0;w<25;w++)
                    {
                        arad[w] = 25 - w;
                    }
                    for(w=0;w<25;w++)
                    {
                        araa[w]= w;
                    }

                }
                else if(hover(insertion_ascending_button_x,insertion_ascending_button_y,insertion_ascending_button_width,insertion_ascending_button_height,mx,my)&& !insertion_menu && menu)
                {
                    //insertion_menu = true;
                    insertion_ascending_menu = false;
                    for(w=0;w<25;w++)
                    {
                        arad[w] = 25 - w;
                    }
                    for(w=0;w<25;w++)
                    {
                        araa[w]= w;
                    }

                }
                else if(hover(bubble_ascending_button_x,bubble_ascending_button_y,bubble_ascending_button_width,bubble_ascending_button_height,mx,my)&& list_menu && menu)
                {
                    //bubble_menu = true;
                    bubble_ascending_menu = false;
                    ialc = 0;
                    for(w=0;w<25;w++)
                    {
                        arad[w] = 25 - w;
                    }
                    for(w=0;w<25;w++)
                    {
                        araa[w]= w;
                    }

                }
                else if(hover(bubble_descending_button_x,bubble_descending_button_y,bubble_descending_button_width,bubble_descending_button_height,mx,my)&& list_menu && menu)
                {
                    //bubble_menu = true;
                    bubble_descending_menu = false;
                    idlc = 0;
                    for(w=0;w<25;w++)
                    {
                        arad[w] = 25 - w;
                    }
                    for(w=0;w<25;w++)
                    {
                        araa[w]= w;
                    }

                }
            }
        }
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

                    SDL_SetRenderDrawColor( main_renderer, 0x92, 0x2A, 0x31, 0xFF );
                    SDL_RenderClear( main_renderer );
                    bubble_ascending_button.render(bubble_ascending_button_x,bubble_ascending_button_y,&bubble_ascending_button_rect);
                    bubble_descending_button.render(bubble_descending_button_x,bubble_descending_button_y,&bubble_descending_button_rect);
                    SDL_RenderPresent(main_renderer);
                    if(!bubble_ascending_menu)
                    {


                        SDL_RenderPresent(main_renderer);
                        SDL_SetRenderDrawColor( main_renderer,0xDD, 0xAD,  0x02 , 0xFF );
                        SDL_RenderClear(main_renderer);
                        for(w=0;w<24;)
                        {
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
                                    reset(&insertion_ascending_menu);
                                    reset(&insertion_menu);

                                }
                                SDL_SetRenderDrawColor( main_renderer,0xDD, 0xAD,  0x02 , 0xFF );
                                SDL_RenderClear(main_renderer);
                                if(!paused)w++;

                            }
                        }

                        else if(!bubble_descending_menu)
                        {

                            SDL_RenderPresent(main_renderer);
                            SDL_SetRenderDrawColor( main_renderer,0xDD, 0xAD,  0x02 , 0xFF );
                            SDL_RenderClear(main_renderer);

                            for(w=0;w<24;)
                            {

                                while(SDL_PollEvent(&s))
                                {
                                    if(s.type == SDL_QUIT){
                                        quit = true;
                                        break;
                                    }
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
                                                    ialc++;

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
                                }
                                if(!paused){
                                    if(araa[w]<araa[w+1])
                                    {
                                        swap(araa[w],araa[w+1]);
                                    }
                                    for(j = w;j<w+1;j++)
                                    {
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
                                        SDL_RenderClear(main_renderer);
                                    }
                                }

                                if(quit)
                                {
                                    break;
                                }
                                if(idlc==25*25*25)
                                {
                                    reset(&list_menu);
                                    reset(&insertion_ascending_menu);
                                    reset(&insertion_menu);
                                }
                                if(!paused) w++;
                                SDL_SetRenderDrawColor( main_renderer,0xDD, 0xAD,  0x02 , 0xFF );
                                SDL_RenderClear(main_renderer);
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
                            for(w=0;w<25;w++)
                            {
                                arad[w] = 25 -w;
                            }
                            for(w=0;w<25;w++)
                            {
                                araa[w]=w;
                            }

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
                            for(w=0;w<25;w++)
                            {
                                arad[w] = 25 -w;
                            }
                            for(w=0;w<25;w++)
                            {
                                araa[w]=w;
                            }
                            
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
