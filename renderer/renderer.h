#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <vector>
#include <memory>

#include "exception.h"
#include "texture.h"
#include "../SDL_FontCache/SDL_FontCache.h"

namespace renderer {

	const size_t SCREEN_WIDTH = 640;
	const size_t SCREEN_HEIGHT = 480;

	class Renderer {
	private:
		SDL_Window * window;
		SDL_Renderer * renderer;
    bool sdl_img_initialized = false;

		FC_Font * font;
		std::vector<Texture> textures;
		Texture * selfTexture = nullptr;
		Texture * planeTexture = nullptr;

		// this class is not copyable
		Renderer(const Renderer&) = delete;
		Renderer& operator=(const Renderer&) = delete;

	public:
		Renderer(){
  		SDL_Init(SDL_INIT_VIDEO);
  	}

  	~Renderer(){
  		textures.clear(); // I want to destroy the textures before quitting the SDL subsystem
  		if(renderer != nullptr){
  			SDL_DestroyRenderer(renderer);
  		}
  		if(window != nullptr){
  			SDL_DestroyWindow(window);
  		}
  		if(sdl_img_initialized){
  			IMG_Quit();
  		}
  		if( font != nullptr ){
				FC_FreeFont(font);
  		}
  		SDL_Quit();
  	}

	private:
  	void LoadTextures(){
  		textures.reserve(2);
  		textures.emplace_back(window, renderer, "gfx/green-circle.png");
  		textures.emplace_back(window, renderer, "gfx/open-circle.png");
  		selfTexture = &textures[0];
			planeTexture = &textures[1];
		}

		bool GetEvents(){
  			SDL_Event e;
      	while( SDL_PollEvent( &e ) != 0 ) {
          	if( e.type == SDL_QUIT ) {
              	return false;
          	}
      	}
      	return true;
    }

		void Draw(){
      SDL_RenderClear( renderer );

      // for each plane: {
				//mpq_class normalisedLatitude = latDistance / latitudeMaxDiff;
				//double xPos = normalisedLatitude.get_d() * SCREEN_WIDTH / 2.0 - 16.0;
				//mpq_class normalisedLongitude = lonDistance / longitudeMaxDiff;
				//double yPos = normalisedLongitude.get_d() * SCREEN_HEIGHT / 2.0 - 16.0;
				//planeTexture->render( renderer, xPos, yPos );
			//}

			//std::string longitude = std::to_string(airplanes.size());
      //FC_Draw(font, renderer, 50, 50, "%s", longitude.c_str());

      SDL_RenderPresent( renderer );
		}

	public:
  	bool Initialize(){
  		try {
  			window = SDL_CreateWindow("ADSB viewer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  			if (window == nullptr){
    			throw exception("Window init error", SDL_GetError());
  			}
  			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  			if (renderer == nullptr){
    			throw exception("Renderer init error", SDL_GetError());
  			}
				SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0xFF );
    		int imgFlags = IMG_INIT_PNG;
    		if( !( IMG_Init( imgFlags ) & imgFlags ) ){
    			throw exception("SDL_image init error", SDL_GetError());
    		}
    		sdl_img_initialized = true;
    		font = FC_CreateFont();
    		FC_LoadFont(font, renderer, "gfx/fonts/FreeSans.ttf", 20, FC_MakeColor(128,80,255,255), TTF_STYLE_NORMAL);
  			LoadTextures();
  			return true;
  		} catch( exception e ){
				auto title = e.GetTitle();
				auto message = e.GetMessage();
    		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title.c_str(), message.c_str(), window);
    		return false;
    	}
  	}

		bool UpdateAndReturnWhetherToContinue(){
			if( GetEvents() ){
				Draw();
				return true;
			}
			return false;
  	}
	};
}

