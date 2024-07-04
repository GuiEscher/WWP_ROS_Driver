#ifndef WTL_PALETTEMANAGER_H
#define WTL_PALETTEMANAGER_H

#include "palette.h"

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace wtl {
/**
 * @brief Loads palettes provided by SDK and externally registered palettes
 */
class PaletteManager
{
	std::map<std::string, std::shared_ptr<Palette>> cache;

	PaletteManager();

  public:
	static PaletteManager& instance()
	{
		static PaletteManager instance;
		return instance;
	}

	/**
	 * @brief Save created custom palette
	 */
	void savePaletteToFile(const std::string& path,
						   const std::shared_ptr<Palette>& palette);
	/**
	 * @brief Get Palette by name
	 * @param name Name of palette
	 * @details Provided palettes: BlueRed, BWIron,  BWIron1. BWRainbow,
	 * BWRainbowHC, Gradient. Gray, Iron, Iron1, Natural, Sepia, Steps,
	 * Temperature, WBRGB, BlackRed, BWRGB, Fire, Rainbow, RainbowHC
	 * @return Pointer to a registered palette
	 */
	std::shared_ptr<Palette> getPalette(const std::string& name);

	bool registerPalette(const std::string& name,
						 std::shared_ptr<Palette>& palette);

	std::vector<std::string> getKeys() const;
};
}
#endif // WTL_THERMALFILEMANAGER_H
