#ifndef THERMALSEQUENCE_H
#define THERMALSEQUENCE_H

#include <fstream>
#include <memory>

#include </home/guilherme/wwpcamera/src/wwpcamera/src/lib/wwp-data-sdk-0.3.0-linux/wwp-data-sdk/headers/sourceparameters/sequencemetadata.h>
#include </home/guilherme/wwpcamera/src/wwpcamera/src/lib/wwp-data-sdk-0.3.0-linux/wwp-data-sdk/headers/sourceparameters/palette.h>
#include </home/guilherme/wwpcamera/src/wwpcamera/src/lib/wwp-data-sdk-0.3.0-linux/wwp-data-sdk/headers/thermalsources/thermalimage.h>

namespace wtl
{
    class ThermalFileManager;
    class FFFFileManager;
    /**
    * @brief Base Class for sequences of thermograms of all file types
    * @details Provides interface for extracting and saving data to sequences of thermal images.
    */
    class ThermalSequence
    {
    protected:
        std::shared_ptr<SequenceMetaData> m_SequenceMetaData;
        //std::unique_ptr<Palette> m_Palette; // palette just in imagee
        std::shared_ptr<wtl::FFFFileManager> m_FileManager; // fff file manager instance used to read and create images from ifstream
        std::shared_ptr<Palette> m_Palette;
        bool m_ManualRangeActive = false;
        /**
         * @brief ThermalSequence constructor.
         */
        ThermalSequence(const std::string & path, std::shared_ptr<wtl::FFFFileManager> mngr);
        /**
         * @brief ThermalSequence constructor.
         */
        ThermalSequence() = default;
    public:
        /**
         * @brief Class destructor.
         */
        virtual ~ThermalSequence();
        /**
        * @brief Copy constructor.
        * @param x Source thermal sequence.
        */
        ThermalSequence(const ThermalSequence & x) = delete;
        /**
         * @brief Assignment operator.
         * @param x Source thermal sequence.
         */
        ThermalSequence & operator=(const ThermalSequence & x) = delete;
        /**
         * @brief Get SequenceMetaData instance which contains non-temperature related data about an image sequence.
         * @return Instance can be used to access sequence meta data such as resolution, duration, framerate etc.
         */
        SequenceMetaData & getSequenceMetaData();
        /**
         * @brief Get constant SequenceMetaData instance which contains non-temperature related data about an image sequence.
         * @return Instance can be used to access sequence meta data such as resolution, duration, framerate etc.
         */
        SequenceMetaData & getSequenceMetaData() const;
        /**
         * @brief Returns thermal image representation of frame at given position.O nly for sequences with temperature data.
         */
        virtual std::shared_ptr<wtl::ThermalImage> thermalAt(int index) const = 0;
        /**
         * @brief Returns 1d array with rgb representaion of frame at given position.
         * @details  Colors of every pixel is determined by pixel temperature. Colors from current palette are used.
         */
        virtual std::shared_ptr<uint8_t> getRGBFrameAt(int index) = 0;
        /**
         * @brief Set palette to sequence.
         * @param palette Name of one of palettes provided by SDK.
         * @details Provided palettes: BlueRed, BWIron,  BWIron1. BWRainbow, BWRainbowHC, Gradient.
         * Gray, Iron, Iron1, Natural, Sepia, Steps, Temperature, WBRGB, BlackRed, BWRGB, Fire, Rainbow, RainbowHC.
         */
        void setPalette(const std::string & palette);
        /**
        * @brief wtl::ThermalSequence::setPalette
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
         * @return manualRangeActive true for active, false otherwise.
         */
        bool isManualRangeActive();
        /**
        * @return Palette instance that contains palette colors
        * @return Palette instance that contains palette colors.
        */

        std::shared_ptr<wtl::Palette> getPalette() const;
        /**
         * @brief FileSize in bytes
         * @return
         */
        int getFileSize();
        /**
         * @brief Decide whether sequence is composed of thermal image instances with radiometric temperature data
         * @return True if image contains temperature for every pixel
         */
        virtual bool isRadiometricSequence() const = 0;
    private:
        virtual void setManualRangeToFrame(bool manualRangeActive) = 0;
        virtual void recalcMinMaxRange() = 0;
    };
}

#endif // THERMALSEQUENCE_H
