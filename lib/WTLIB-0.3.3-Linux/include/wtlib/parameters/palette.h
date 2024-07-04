#ifndef WTL_PALETTE_H
#define WTL_PALETTE_H

#include "wtlib/measurement/colortypes.h"

#include <memory>
#include <string>

namespace wtl {
/**
 * @brief Color %Palette used to visualize and colorize temperature data
 */
class Palette
{
	friend class PaletteManager;

	paletteRGB256 m_Colors;
	std::string m_Name;

  public:
	/**
	 * @brief Set RGB colors to %Palette.
	 * @param[in] colors array of 256 3-channel colors.
	 */
	static std::shared_ptr<Palette> fromRGB(const paletteRGB256& colors,
											const std::string& name);

	/**
	 * @brief Set YCbCr colors to %Palette.
	 * @param colors array of 256 3-channel colors.
	 */
	static std::shared_ptr<Palette> fromYCbCr(const paletteYcBCr256& colors,
											  const std::string& name);

	/**
	 * @brief Assignment operator.
	 * @param x Source palette instance.
	 */
	Palette& operator=(const Palette& x) = default;

	/**
	 * @brief Comparison operator.
	 * @param x Compared instance.
	 * @return True if two compared instances have equal name and colors.
	 */
	bool operator==(const Palette& other);

	/**
	 * @brief Palette Name Getter.
	 * @return Palette name string.
	 */
	const std::string& getName() const;

	/**
	 * @brief Get palette colors in RGB colorspace.
	 * @param colors 2d array of 256 3-channel colors used as output.
	 */
	const paletteRGB256& getPaletteRGBColors() const;

	/**
	 * @brief Get palette colors in YCbCr colorspace.
	 * @param colors 2d array of 256 3-channel colors used as output.
	 */
	paletteYcBCr256 getPaletteYCrCbColors() const;

	/**
	 * @brief Get one rgb color from palette by index.
	 * @param row to table of palette colors, 0-255.
	 * @return Pointer to array of three 1 byte numbers, represents onr RGB
	 * color.
	 */
	const RGB& getRGBColorByRow(unsigned char row) const;

	/**
	 * @brief Get one ycbcr color from palette by index.
	 * @param row to table of palette colors, 0-255.
	 * @return Pointer to array of three 1 byte numbers, represents onr RGB
	 * color.
	 */
	YCbCr getYCbCrColorByRow(unsigned char row) const;
};
}
#endif // WTL_PALETTES_H
