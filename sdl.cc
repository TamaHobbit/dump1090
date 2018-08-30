#include "renderer/renderer.h"
using renderer::Renderer;

extern "C" {

	Renderer * screen;

	void initSdl(){
		static Renderer r;
		screen = &r;
		r.Initialize();
	}

	void sdlShowData(){
		screen->UpdateAndReturnWhetherToContinue();
	}

}

