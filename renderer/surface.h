namespace renderer {
	class Surface {
	private:
		SDL_Surface * surface;

		// this class is not copyable
		Surface(const Surface&) = delete;
		Surface& operator=(const Surface&) = delete;

	public:
		Surface() : surface(nullptr) {}

		Surface(const std::string & path){
			surface = IMG_Load( path.c_str() );
			if( surface == nullptr ){
				throw exception("Unable to load file " + path + ": ", IMG_GetError());
			}
		}

		Surface(TTF_Font * font, const std::string & text, const SDL_Color & textColor){
			surface = TTF_RenderText_Solid( font, text.c_str(), textColor );
			if( surface == nullptr ){
				throw exception("Unable to render text", TTF_GetError());
			}
		}

		friend void swap(Surface& left, Surface& right){
			using std::swap;
			swap(left.surface, right.surface);
		}

		Surface(Surface&& other) : Surface() {
			swap(*this, other);
		}

		~Surface(){
			SDL_FreeSurface( surface );
		}

		SDL_Surface * Get(){
			return surface;
		}
	};
}

