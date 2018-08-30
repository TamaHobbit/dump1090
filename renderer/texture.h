#include "surface.h"

namespace renderer {
	class Texture {
	private:
		SDL_Texture * texture;
		int width;
		int height;

		// this class is not copyable
		Texture(const Texture&) = delete;
		Texture& operator=(const Texture&) = delete;

	public:
		Texture(SDL_Window * window, SDL_Renderer * renderer, const std::string & path){
			Surface surface(path);
    	auto surf = surface.Get();
    	texture = SDL_CreateTextureFromSurface( renderer, surf );
    	if( texture == nullptr ){
    		throw exception("Unable to create texture", SDL_GetError());
    	}
    	width = surf->w;
    	height = surf->h;
		}

		int getWidth(){
			return width;
		}

		int getHeight(){
			return height;
		}

		friend void swap(Texture& left, Texture& right){
			using std::swap;
			swap(left.texture, right.texture);
			swap(left.width, right.width);
			swap(left.height, right.height);
		}

		Texture(Texture&& other) {
			texture = nullptr;
			swap(*this, other);
		}

		~Texture(){
			SDL_DestroyTexture(texture);
		}

		void render(SDL_Renderer * renderer, int x, int y, const SDL_Rect* clip = nullptr, const double angle = 0.0,
								SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE){
			SDL_Rect renderQuad = { x, y, width, height };
			if( clip != nullptr ){
				renderQuad.w = clip->w;
				renderQuad.h = clip->h;
			}
			SDL_RenderCopyEx( renderer, texture, clip, &renderQuad, angle, center, flip );
		}
	};
}

