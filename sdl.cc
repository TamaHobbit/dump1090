#include "renderer/renderer.h"
using renderer::Renderer;

extern "C" {

	Renderer * screen;

	bool initSdl(){
		static Renderer r;
		screen = &r;
		return r.Initialize();
	}

	bool sdlShowData(){
		return screen->UpdateAndReturnWhetherToContinue();
	}

}

