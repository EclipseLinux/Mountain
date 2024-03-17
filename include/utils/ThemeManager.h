#pragma once
#include "utils/Color.h"

namespace Mountain
{
	class ThemeManager
	{
	public:
		[[nodiscard]] static auto Primary() -> Color*
		{
			return primary;
		}

		[[nodiscard]] static auto SurfaceTint() -> Color*
		{
			return surfaceTint;
		}

		[[nodiscard]] static auto OnPrimary() -> Color*
		{
			return onPrimary;
		}

		[[nodiscard]] static auto PrimaryContainer() -> Color*
		{
			return primaryContainer;
		}

		[[nodiscard]] static auto OnPrimaryContainer() -> Color*
		{
			return onPrimaryContainer;
		}

		[[nodiscard]] static auto Secondary() -> Color*
		{
			return secondary;
		}

		[[nodiscard]] static auto OnSecondary() -> Color*
		{
			return onSecondary;
		}

		[[nodiscard]] static auto OnSecondaryContainer() -> Color*
		{
			return onSecondaryContainer;
		}

		[[nodiscard]] static auto Tertiary() -> Color*
		{
			return tertiary;
		}

		[[nodiscard]] static auto OnTertiary() -> Color*
		{
			return onTertiary;
		}

		[[nodiscard]] static auto OnTertiaryContainer() -> Color*
		{
			return onTertiaryContainer;
		}

		[[nodiscard]] static auto Error() -> Color*
		{
			return error;
		}

		[[nodiscard]] static auto ErrorContainer() -> Color*
		{
			return errorContainer;
		}

		[[nodiscard]] static auto OnErrorContainer() -> Color*
		{
			return onErrorContainer;
		}

		[[nodiscard]] static auto Background() -> Color*
		{
			return background;
		}

		[[nodiscard]] static auto OnBackground() -> Color*
		{
			return onBackground;
		}

		[[nodiscard]] static auto Surface() -> Color*
		{
			return surface;
		}

		[[nodiscard]] static auto OnSurface() -> Color*
		{
			return onSurface;
		}

		[[nodiscard]] static auto SurfaceVariant() -> Color*
		{
			return surfaceVariant;
		}

		[[nodiscard]] static auto OnSurfaceVariant() -> Color*
		{
			return onSurfaceVariant;
		}

		[[nodiscard]] static auto Outline() -> Color*
		{
			return outline;
		}

		[[nodiscard]] static auto OutlineVariant() -> Color*
		{
			return outlineVariant;
		}

		[[nodiscard]] static auto Shadow() -> Color*
		{
			return shadow;
		}

		[[nodiscard]] static auto Scrim() -> Color*
		{
			return scrim;
		}

		[[nodiscard]] static auto InverseSurface() -> Color*
		{
			return inverseSurface;
		}

		[[nodiscard]] static auto InverseOnSurface() -> Color*
		{
			return inverseOnSurface;
		}

	private:
		inline static Color* primary = new Color(0x88D1ECFF);
		inline static Color* surfaceTint = new Color(0x88D1ECFF);
		inline static Color* onPrimary = new Color(0x003544FF);
		inline static Color* primaryContainer = new Color(0x004D61FF);
		inline static Color* onPrimaryContainer = new Color(0xB7EAFFF);
		inline static Color* secondary = new Color(0xB3CAD4FF);
		inline static Color* onSecondary = new Color(0x1E333BFF);
		inline static Color* secondaryContainer = new Color(0x344A52FF);
		inline static Color* onSecondaryContainer = new Color(0xCFE6F1FF);
		inline static Color* tertiary = new Color(0xC3C3EBFF);
		inline static Color* onTertiary = new Color(0x2C2E4DFF);
		inline static Color* tertiaryContainer = new Color(0x434465FF);
		inline static Color* onTertiaryContainer = new Color(0xE1E0FF);
		inline static Color* error = new Color(0xFFB4ABFF);
		inline static Color* onError = new Color(0x690005FF);
		inline static Color* errorContainer = new Color(0x93000AFF);
		inline static Color* onErrorContainer = new Color(0xFFDAD6FF);
		inline static Color* background = new Color(0x0F1416FF);
		inline static Color* onBackground = new Color(0xDEE3E6FF);
		inline static Color* surface = new Color(0x0F1416FF);
		inline static Color* onSurface = new Color(0xDEE3E6FF);
		inline static Color* surfaceVariant = new Color(0x40484CFF);
		inline static Color* onSurfaceVariant = new Color(0xBFC8CCFF);
		inline static Color* outline = new Color(0x8A9296FF);
		inline static Color* outlineVariant = new Color(0x40484CFF);
		inline static Color* shadow = new Color(0x000000FF);
		inline static Color* scrim = new Color(0x000000FF);
		inline static Color* inverseSurface = new Color(0xDEE3E6FF);
		inline static Color* inverseOnSurface = new Color(0x2C3134FF);
		inline static Color* inversePrimary = new Color(0x08677FFF);
		inline static Color* primaryFixed = new Color(0xB7EAFFFF);
		inline static Color* onPrimaryFixed = new Color(0x001F28FF);
		inline static Color* primaryFixedDim = new Color(0x88D1ECFF);
		inline static Color* onPrimaryFixedVariant = new Color(0x004D61FF);
		inline static Color* secondaryFixed = new Color(0xCFE6F1FF);
		inline static Color* onSecondaryFixed = new Color(0x071E26FF);
		inline static Color* secondaryFixedDim = new Color(0xB3CAD4FF);
		inline static Color* onSecondaryFixedVariant = new Color(0x344A52FF);
		inline static Color* tertiaryFixed = new Color(0xE1E0FFFF);
		inline static Color* onTertiaryFixed = new Color(0x171837FF);
		inline static Color* tertiaryFixedDim = new Color(0xC3C3EBFF);
		inline static Color* onTertiaryFixedVariant = new Color(0x434465FF);
		inline static Color* surfaceDim = new Color(0x0F1416FF);
		inline static Color* surfaceBright = new Color(0x353A3CFF);
		inline static Color* surfaceContainerLowest = new Color(0x0A0F11FF);
		inline static Color* surfaceContainerLow = new Color(0x171C1FFF);
		inline static Color* surfaceContainer = new Color(0x1B2023FF);
		inline static Color* surfaceContainerHigh = new Color(0x252B2DFF);
		inline static Color* surfaceContainerHighest = new Color(0x303638FF);
	};
}