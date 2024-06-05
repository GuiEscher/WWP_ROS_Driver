#ifndef PALETTEMANAGER_H
#define PALETTEMANAGER_H

#include <memory>
#include </home/guilherme/wwpcamera/src/wwpcamera/src/lib/wwp-data-sdk-0.3.0-linux/wwp-data-sdk/headers/sourceparameters/palette.h>
#include <fstream>
#include <sstream>
#include <iostream>

namespace wtl
{
    /**
     * @brief Loads palettes provided by SDK
     */
    class PaletteManager
    {

    public:
        /**
         * @brief Save created custom palette
         */
        static void savePaletteToFile(const std::string &path, std::shared_ptr<Palette> palette);
        /**
         * @brief Get Palette by name
         * @param name One of palettes provided by SDK.
         * @details Provided palettes: BlueRed, BWIron,  BWIron1. BWRainbow, BWRainbowHC, Gradient.
         * Gray, Iron, Iron1, Natural, Sepia, Steps, Temperature, WBRGB, BlackRed, BWRGB, Fire, Rainbow, RainbowHC
         */
        static std::shared_ptr<Palette> getPalette(const std::string name);
    private:
        static const uint8_t blackRedPlt [256][3];
        static const uint8_t blueRedPlt [256][3];
        static const uint8_t BWIronPlt [256][3];
        static const uint8_t BWIron1Plt [256][3];
        static const uint8_t BWRainbowPlt [256][3];
        static const uint8_t BWRainbowHCPlt [256][3];
        static const uint8_t BWRGBPlt [256][3];
        static const uint8_t firePlt [256][3];
        static const uint8_t gradientPlt [256][3];
        static const uint8_t grayPlt [256][3];
        static const uint8_t ironPlt [256][3];
        static const uint8_t iron1Plt [256][3];
        static const uint8_t naturalPlt [256][3];
        static const uint8_t rainbowPlt [256][3];
        static const uint8_t rainbowHCPlt [256][3];
        static const uint8_t sepiaPlt [256][3];
        static const uint8_t stepsPlt [256][3];
        static const uint8_t temperaturePlt [256][3];
        static const uint8_t WBRGBPlt [256][3];
    };
}
#endif // THERMALFILEMANAGER_H
