//Credit to Bill Booth.

#ifndef _SCREEN
#define _SCREEN


const int ROW   = 480;
const int COL   = 640;
const int DELAY = 10;
SDL_Event event;

class graphic{
     private:
    	 SDL_Surface *screen;
    	 
     public:
    	 graphic();
    	 void update();
    	 void clear();
    	 void plotPixel(int x, int y, int color);
    	 void display(int data[], int s);
};


graphic::graphic(){
	// Initialize SDL's subsystems - in this case, only video.
	if ( SDL_Init(SDL_INIT_VIDEO) < 0 ){
	  fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
	  exit(1);
	}	
	
	// Attempt to create a 640x480 window with 32bit pixels.
	screen = SDL_SetVideoMode(COL, ROW, 32, SDL_SWSURFACE);
	
	// If we fail, return error.
	if ( screen == NULL ){
	  fprintf(stderr, "Unable to set 640x480 video: %s\n", SDL_GetError());
	  exit(1);
	}
	// Register SDL_Quit to be called at exit; makes sure things are
	// cleaned up when we quit.
	atexit(SDL_Quit);
	
}

void graphic::update(){
	// Tell SDL to update the whole screen
	SDL_UpdateRect(screen, 0, 0, COL, ROW);    
}

void graphic::clear(){
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
}


void graphic::plotPixel(int x, int y, int color)
{
  unsigned int *ptr = (unsigned int*)screen->pixels;
  int lineoffset = y * (screen->pitch / 4);
  ptr[lineoffset + x] = color;
}

void graphic::display(int data[], int s){
	  clear();
	  for(int i = 0; i < s; i++)
		  plotPixel(i,data[i],0xffffff);
	  update();				 	
}

#endif



