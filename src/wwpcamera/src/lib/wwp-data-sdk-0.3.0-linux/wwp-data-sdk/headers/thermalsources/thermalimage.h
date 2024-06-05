#ifndef THERMALIMAGE_H
#define THERMALIMAGE_H

#include <memory>
#include <vector>

#include </home/guilherme/wwpcamera/src/wwpcamera/src/lib/wwp-data-sdk-0.3.0-linux/wwp-data-sdk/headers/sourceparameters/sourcemetadata.h>
#include </home/guilherme/wwpcamera/src/wwpcamera/src/lib/wwp-data-sdk-0.3.0-linux/wwp-data-sdk/headers/sourceparameters/palette.h>
#include </home/guilherme/wwpcamera/src/wwpcamera/src/lib/wwp-data-sdk-0.3.0-linux/wwp-data-sdk/headers/sourceparameters/calibrationparameters.h>
#include </home/guilherme/wwpcamera/src/wwpcamera/src/lib/wwp-data-sdk-0.3.0-linux/wwp-data-sdk/headers/services/palettemanager.h>

namespace wtl {
    /**
     * @brief Base Class for thermograms captured by all cameras.
     * @details Provides interface for extracting and saving data to thermal images.
     */
    class ThermalImage
    {
        friend class FFFFileManager;
    protected:
        std::shared_ptr<SourceMetaData> m_ImageMetaData;
        std::shared_ptr<CalibrationParameters> m_CalibrationParams;
        std::shared_ptr<Palette> m_Palette;
        uint16_t * m_VisiblePixels = nullptr;
        bool m_ManualRangeActive = false;
        /**
         * @brief Thermal Image contructor.
         */
        ThermalImage();
    public:
        /**
        * @brief Copy constructor.
        * @param x Source thermal image.
        */
        ThermalImage(const ThermalImage & x) = delete;
        /**
         * @brief Class destructor.
         */
        virtual ~ThermalImage();
        /**
         * @brief Assignment operator.
         * @param x Source Thermal Image.
         */
        // TODO - virtual?
        ThermalImage & operator=(const ThermalImage & x) = delete;
        /**
         * @brief Get SourceMetaData instance which contains non-temperature related data about an image.
         * @return Instance can be used to access image meta data such as resolution, location, date of capture etc.
         */
        SourceMetaData & getImageMetaData() const;
        /**
        * @brief Get Calibration params instance.
        * @return
        */
        CalibrationParameters & getImageCalibParams() const;
        /**
         * @brief Get Palette.
         * @return Palette instance that contains palette colors.
         */
        std::shared_ptr<wtl::Palette> getPalette() const;
        /**
         * @brief Set palette to image.
         * @param palette One of palettes provided by SDK.
         * @details Provided palettes: BlueRed, BWIron,  BWIron1. BWRainbow, BWRainbowHC, Gradient.
         * Gray, Iron, Iron1, Natural, Sepia, Steps, Temperature, WBRGB, BlackRed, BWRGB, Fire, Rainbow, RainbowHC.
         */
        void setPalette(const std::string & palette);
        /**
        * @brief wtl::ThermalImage::setPalette
        * @param palette
        */
        void setPalette(std::shared_ptr<wtl::Palette> palette);
        /**
         * @brief Set manual range.
         * @param manualRangeActive true for activation, false for deactivation.
         */
        void setManualRange(bool manualRangeActive);
        /**
        * @brief Is Manual Range Active.
        * @return manualRangeActive true for activation, false for deactivation.
        */
        bool isManualRangeActive();
        /**
         * @brief Digital image in visible spectrum saved in thermogram.
         * @return True if image contains visible pixels.
         */
        bool containsVisiblePixels() const;
        /**
         * @brief Decide whether thermal image instance contains temperature data.
         * @return True if image contains temperature for every pixel.
         */
        virtual bool isRadiometricImage() const = 0;
        /**
         * @brief Get Digital image pixels in visible spectrum saved in thermogram.
         * @return 1d Array of visible 3-channel rgb pixels.
         */
        uint16_t * getVisiblePixels() const;
        /**
         * @brief Get Image size in bytes without metadata.
         * @details Image size in bytes, heigth * width * bytes per pixel.
         */
        int getImageSize() const;
        /**
         * @brief Total number of pixels.
         * @return total number of pixels of an image.
         */
        int getNumberOfPixels() const;
        /**
          */
        int getVisibleImageSize() const;
        /**
         * @brief Get array with grayscayscale representation of thermogram that can be directly used to visualize image.
         * @param[out] imageData Output array parameter.
         * @param[out] imageSize Size of an array.
         */
        virtual void getGrayscaleArrayRepresentation(uint8_t ** imageData, int & imageSize) const = 0;
        /**
        * @brief Get array with RGB representation of thermogram that can be directly used to visualize image.
        * Alarms and measurements overlay is added to the image.
        * @param[out] imageData Output array parameter.
        * @param[out] imageSize Size of an array.
        */
        virtual void getRGBArrayRepresentationWithOverlay(uint8_t * imageData, int & imageSize) const = 0;
        /**
         * @brief Get array with RGB representation of thermogram that can be directly used to visualize image.
         * @details  Colors of every pixel is determined by pixel temperature. Colors from current palette are used.
         * @param[out] imageData Output array parameter.
         * @param[out] imageSize Size of an array.
         */
        virtual void getRGBArrayRepresentation(uint8_t * imageData, int & imageSize) const = 0;
        /**
         * @brief Get position of pixel with maximal temperature or signal.
         * @return Coordinates of point with maximal temperature or signal captured in an image.
         */
        virtual std::pair<int, int> getMaxPos() const = 0;
        /**
         * @brief Get position of pixel with minimum temperature or signal.
         * @return Coordinates of point with minimal temperature or signal captured in an image.
         */
        virtual std::pair<int, int> getMinPos() const = 0;
    protected:
        // recalc min and max signal/temp and set these limits to min max manual range
        virtual void recalcMinMaxRange() = 0;
    };
}
#endif // THERMALIMAGE_H
