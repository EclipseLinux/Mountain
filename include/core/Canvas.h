#pragma once
#include "SDL_video.h"
#include "core/Element.h"
#include "gpu/GrDirectContext.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkPaint.h"
#include "include/core/SkPath.h"
#include "include/core/SkRefCnt.h"

namespace Mountain::Internals
{
	inline SkCanvas* currentCanvas;
	inline SkPaint currentPaint;
	inline SkPath currentClip;
	inline sk_sp<GrDirectContext> currentContext;

	void createCanvas(SDL_Window* window, Element* element, SDL_GLContext& context,
					  sk_sp<SkSurface>& surface, sk_sp<GrDirectContext>& skiaCtx);
}

#define mn_canvas Mountain::Internals::currentCanvas
#define mn_paint Mountain::Internals::currentPaint
#define mn_path Mountain::Internals::currentClip
#define mn_iGrContext Mountain::Internals::currentContext