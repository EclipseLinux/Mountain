#pragma once
#include "SDL_video.h"
#include "core/Element.h"
#include "core/SkTypeface.h"
#include "gpu/GrDirectContext.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkPaint.h"
#include "include/core/SkPath.h"
#include "include/core/SkRefCnt.h"

#ifdef __WIN32__
#	include "ports/SkTypeface_win.h"
#else
#	include "ports/SkFontMgr_fontconfig.h"
#endif

namespace Mountain::Internals
{
	inline SkCanvas* currentCanvas;
	inline SkPaint currentPaint;
	inline SkPath currentClip;
	inline sk_sp<GrDirectContext> currentContext;
	inline sk_sp<SkFontMgr> fontManager;

	inline void createFontMgr()
	{
#ifdef __WIN32__
		fontManager = SkFontMgr_New_GDI();
#else
		fontManager = SkFontMgr_New_FontConfig(nullptr);
#endif
	}

	void createCanvas(SDL_Window* window, Element* element, SDL_GLContext& context,
					  sk_sp<SkSurface>& surface, sk_sp<GrDirectContext>& skiaCtx);
}

#define mn_canvas Mountain::Internals::currentCanvas
#define mn_paint Mountain::Internals::currentPaint
#define mn_path Mountain::Internals::currentClip
#define mn_iGrContext Mountain::Internals::currentContext
#define mn_fontMgr Mountain::Internals::fontManager