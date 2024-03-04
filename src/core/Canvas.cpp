#include "core/Canvas.h"
#include "core/SkCanvas.h"
#include "core/SkColorSpace.h"
#include "gpu/ganesh/SkSurfaceGanesh.h"
#include "include/gpu/GrBackendSurface.h"
#include "include/gpu/GrDirectContext.h"
#include "include/gpu/ganesh/gl/GrGLBackendSurface.h"
#include "include/gpu/ganesh/gl/GrGLDirectContext.h"
#include "include/gpu/gl/GrGLInterface.h"

#include "src/gpu/ganesh/gl/GrGLDefines.h"
#include "src/gpu/ganesh/gl/GrGLUtil.h"

namespace Mountain::Internals
{
	void createCanvas(SDL_Window* window, Element* element, SDL_GLContext& context,
					  sk_sp<SkSurface>& surface, sk_sp<GrDirectContext>& skiaCtx)
	{
		int drawWidth;
		int drawHeight;
		SDL_GL_GetDrawableSize(window, &drawWidth, &drawHeight);

		auto interface = GrGLMakeNativeInterface();

		// setup contexts
		skiaCtx = GrDirectContexts::MakeGL(interface);

		GrGLint buffer;
		GR_GL_GetIntegerv(interface.get(), GR_GL_FRAMEBUFFER_BINDING, &buffer);
		GrGLFramebufferInfo info;
		info.fFBOID = (GrGLuint)buffer;
		SkColorType colorType;

		uint32_t windowFormat = SDL_GetWindowPixelFormat(window);
		int contextType;
		SDL_GL_GetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, &contextType);

		if (SDL_PIXELFORMAT_RGBA8888 == windowFormat)
		{
			info.fFormat = GR_GL_RGBA8;
			colorType = kRGBA_8888_SkColorType;
		}
		else
		{
			colorType = kBGRA_8888_SkColorType;
			if (SDL_GL_CONTEXT_PROFILE_ES == contextType)
			{
				info.fFormat = GR_GL_BGRA8;
			}
			else
			{
				// We assume the internal format is RGBA8 on desktop GL
				info.fFormat = GR_GL_RGBA8;
			}
		}

		auto target = GrBackendRenderTargets::MakeGL(drawWidth, drawHeight, 1, 8, info);

		SkSurfaceProps props;

		surface = sk_sp<SkSurface>(SkSurfaces::WrapBackendRenderTarget(
			skiaCtx.get(), target, kBottomLeft_GrSurfaceOrigin, colorType, nullptr,
			&props));

		auto* canvas = surface->getCanvas();
		canvas->scale((float)drawWidth / element->Width(),
					  (float)drawHeight / element->Height());
	}
}