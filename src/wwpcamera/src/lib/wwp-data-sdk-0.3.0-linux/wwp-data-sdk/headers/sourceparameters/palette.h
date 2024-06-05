#ifndef PALETTE_H
#define PALETTE_H

#include <string>
#include <stdint.h>

namespace wtl
{
    /**
     * @brief Color %Palette used to visualize and colorize temperature data
     */
    class Palette
    {
        uint8_t m_Colors[256][3];
        std::string m_Name;
    public:
        /**
        * @brief Palette Constructor
        *
        */
        Palette();
        /**
         * @brief Palette Constructor
         * @param colors Palette colors
         * @param name Name of the palette
         */
        Palette(const uint8_t colors [256][3], const std::string & name);
        /**
        * @brief Copy constructor.
        * @param x Source palette instance.
        */
        Palette(const Palette & x);
        /**
        * @brief Assignment operator.
        * @param x Source palette instance.
        */
        Palette & operator=(const Palette & x);
        /**
         * @brief Comparison operator.
         * @param x Compared instance.
         * @return True if two compared instances have equal name and colors.
         */
        bool operator==(const Palette & x);
        /**
         * @brief Palette Name Getter.
         * @return Palette name string.
         */
        std::string getName() const;
        /**
         * @brief Get palette colors in RGB colorspace.
         * @param colors 2d array of 256 3-channel colors used as output.
         */
        void getPaletteRGBColors(uint8_t colors[256][3]) const;
        /**
         * @brief Get palette colors in YCbCr colorspace.
         * @param colors 2d array of 256 3-channel colors used as output.
         */
        void getPaletteYCrCbColors(uint8_t colors[256][3]) const;
        /**
         * @brief Set palette name.
         * @param name new palette name.
         */
        void setName(const std::string & name);
        /**
         * @brief Set RGB colors to %Palette.
         * @param[in] colors array of 256 3-channel colors.
         */
        void setPaletteRGBColors(const uint8_t colors[256][3]);
        /**
         * @brief Set YCbCr colors to %Palette.
         * @param colors array of 256 3-channel colors.
         */
        void setPaletteYCbCrColors(uint8_t colors[256][3]);
        /**
         * @brief Get one rgb color from palette by index.
         * @param row to table of palette colors, 0-255.
         * @return Pointer to array of three 1 byte numbers, represents onr RGB color.
         */
        const uint8_t * getRGBColorByRow(int row) const;
    private:
        static void convertYCbCrtoRGB(uint8_t rgbValues[256][3], const uint8_t YCbCrValues[256][3]);
        static void convertRGBtoYCbCr(uint8_t const rgbValues[256][3], uint8_t YCbCrValues[256][3]);
    };
}
#endif // PALETTES_H
