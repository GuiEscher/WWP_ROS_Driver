#ifndef IMAGERADIOMETRIC_H
#define IMAGERADIOMETRIC_H

#include <stdint.h>
#include </home/guilherme/wwpcamera/src/wwpcamera/src/lib/wwp-data-sdk-0.3.0-linux/wwp-data-sdk/headers/thermalsources/thermalimage.h>
#include </home/guilherme/wwpcamera/src/wwpcamera/src/lib/wwp-data-sdk-0.3.0-linux/wwp-data-sdk/headers/sourceparameters/alarms.h>
#include </home/guilherme/wwpcamera/src/wwpcamera/src/lib/wwp-data-sdk-0.3.0-linux/wwp-data-sdk/headers/sourceparameters/measurements.h>
#include </home/guilherme/wwpcamera/src/wwpcamera/src/lib/wwp-data-sdk-0.3.0-linux/wwp-data-sdk/headers/sourceparameters/thermalparameters.h>
#include </home/guilherme/wwpcamera/src/wwpcamera/src/lib/wwp-data-sdk-0.3.0-linux/wwp-data-sdk/headers/sourceparameters/thermalcalculation.h>

namespace wtl
{
    /**
     * @brief Derived Class representing thermogram with temperature data and thermal parameters included.
     * @details Provides interface for extracting and saving data to radiometric images. Instances are created only trough functions in class Center.
     * A radiometric JPEG is a standard JPEG with a FFF-file inserted in the APP1-tag
     */
    class ImageRadiometric : public ThermalImage
    {
        // allow center and file manager to access private members
        friend class Center;
        friend class FFFFileManager;
        friend class SequenceRadiometric;

        std::unique_ptr<ThermalCalculation> m_Calculation;
        std::shared_ptr<ThermalParameters> m_ThermalParameters;
        std::shared_ptr<Measurements> m_Measurements;
        std::shared_ptr<Alarms> m_Alarms;
        uint16_t * m_RawPixels = nullptr;
        float m_ManualMax = 0;
        float m_ManualMin = 0;
        std::pair<int, int> m_MaxPos;
        std::pair<int, int> m_MinPos;

        // superres - more frames per one image
        int m_FrameCount = 0;
        std::vector<uint16_t*> m_PixelsSuperRes;
        /**
         * @brief Private ImageRadiometric constructor, only reachable from friend class
         */
        ImageRadiometric();
    public:
        ImageRadiometric(const ImageRadiometric & x) = delete;
        ImageRadiometric& operator =(const ImageRadiometric & x) = delete;
        ~ImageRadiometric();
        /**
         * @brief Get 16 bit radiometric value of an pixel.
         * @details Radiometric value in linearized and is simply convertible to Kelvins.
         * @param x Width coordinate.
         * @param y Height coordinate.
         * @return 16 bit Radiometric value at given pixel.
         */
        uint16_t getRawRadiometricValue(int x, int y) const;
        /**
        * @brief Get signal value of a pixel.
        * @param x Width coordinate.
        * @param y Height coordinate.
        * @return Signal value at given pixel.
        */
        uint16_t getSignal(int x, int y) const;
        /**
         * @brief Get temperature of a pixel.
         * @param x Width coordinate.
         * @param y Height coordinate.
         * @return Temperature at given pixel.
         */
        float getTemperature(int x, int y) const;
        /**
         * @brief Get maximum temperature present in an image.
         * @return Maximum temperature captured in an image.
         */
        float getMaxTemperature() const;
        /**
        * @brief Get position of pixel with maximux temperature.
        * @return Coordinates of Maximum temperature captured in an image.
        */
        std::pair<int, int> getMaxPos() const;
        /**
         * @brief Get minimum temperature present in an image.
         * @return Minimm temperature captured in an image.
         */
        float getMinTemperature() const;
        /**
         * @brief Get position of pixel with minimum temperature.
         * @return Coordinates of point with minimal temperature captured in an image.
         */
        std::pair<int, int> getMinPos() const;
        /**
         * @brief wtl::ImageRadiometric::getPaletteMaxTemperature
         * @return
         */
        float getPaletteMaxTemperature() const;
        /**
         * @brief wtl::ImageRadiometric::getPaletteMinTemperature
         * @return
         */
        float getPaletteMinTemperature() const;
        /**
         * @brief Get ThermalParametres instance which contains all thermal parameters of an image.
         * @return Instance can be used to access sequence meta data such as resolution, location, date of capture etc.
         */
        const ThermalParameters & getThermalParameters() const;
        /**
         * @brief Get array with temperatures from radiometric image.
         * @param[out] imageData Output array parameter.
         * @param[out] imageSize Size of an array.
         */
        void getTemperatureArray(float ** imageData, int & imageSize) const;
        /**
        * @brief Get array with signal values from radiometric image.
        * @param[out] imageData Output array parameter.
        * @param[out] imageSize Size of an array.
        */
        void getSignalArray(uint16_t ** imageData, int & imageSize) const;
        /**
         * @brief Get array with grayscayscale representation of thermogram that can be directly used to visualize image.
         * @param[out] imageData Output array parameter.
         * @param[out] imageSize Size of an array.
         */
        void getGrayscaleArrayRepresentation(uint8_t ** imageData, int & imageSize) const;
        /**
         * @brief Get array with RGB representation of thermogram that can be directly used to visualize image.
         * @param[out] imageData Output array parameter.
         * @param[out] imageSize Size of an array.
         */
        void getRGBArrayRepresentation(uint8_t * imageData, int & imageSize) const;
        /**
         * @brief Get array with RGB representation of thermogram that can be directly used to visualize image.
         * @param[out] imageData Output array parameter.
         * @param[out] imageSize Size of an array.
         * @param[out] pixelPerColorCounter vector that has number of pixels of color i at index i.
         */
        void getRGBArrayRepresentation(uint8_t * imageData, int & imageSize, std::vector<int> & pixelPerColorCounter) const;
        /**
         * @brief Get array with RGB representation of thermogram that can be directly used to visualize image.
         * Alarms and measurements overlay is added to the image.
         * @param[out] imageData Output array parameter.
         * @param[out] imageSize Size of an array.
         */
        void getRGBArrayRepresentationWithOverlay(uint8_t * imageData, int & imageSize) const;
        /**
         * @brief Get array with RGB representation of thermogram that can be directly used to visualize image.
         * Alarms and measurements overlay is added to the image.
         * @param[out] imageData Output array parameter.
         * @param[out] imageSize Size of an array.
         * @param[out] pixelPerColorCounter vector that has number of pixels of color i at index i.
         */
        void getRGBArrayRepresentationWithOverlay(uint8_t * imageData, int & imageSize, std::vector<int> & pixelPerColorCounter) const;
        /**
         * @brief Get array with RGB representation of thermogram that can be directly used to visualize image.
         * @details Includes palette miniature.
         * @param[out] imageData Output array parameter.
         * @param[out] imageSize Size of an array.
         */
        void getRGBArrayRepresentationWithPal(uint8_t ** imageData, int & imageSize) const;
        /**
         * @brief Recalculate image temperatures.
         */
        void recalculateTemperatures();
        /**
         * @brief Check for the rois that affect temperature measurement
         */
        void prepareRadiometricData();
        /**
         * @brief Check whether image supports super-resolution.
         * @details Superresolution algorithm enhances image resolution from multipla frames captured in and image.
         * @return True if supperresolution is available.
         */
        bool isSuperResImage();
        /**
         * @brief Get number of frames captured in a image, superres image can have up to 60
         * @return
         */
        int getSuperResFrameCount();
        /**
         * @brief Get pointer to pixel arrays of each frame
         * @param frames
         * @return
         */
        uint16_t ** getPixelsSuperRes(int * frames);
        /**
          * @brief Set temperature used as maximum for palette.
          * @param value Temperature in Celsius.
          */
        void setManualMax(float value);
        /**
          * @brief Set temperature used as minimium for palette
          * @param value Temperature in Celsius.
          */
        void setManualMin(float value);
        /**
         * @brief Copy all thermal params from ThermalParameters instance
         * @param newParams
         */
        void setThermalParams(const std::shared_ptr<wtl::ThermalParameters> & newParams);
        /**
         * @brief Set emissivity of objects on an image.
         * @param value New emissivity value.
         */
        void setEmissivity(double value);
        /**
         * @brief Set Reflected Temperature of objects on an image.
         * @param value New ReflectedTemp value.
         */
        void setReflectedTemp(double value);
        /**
         * @brief Set Atmospheric Temperature.
         * @param value New Atmospheric temperature value.
         */
        void setAtmTemp(double value);
        /**
         * @brief Set External Optics Temperature.
         * @param value New value.
         */
        void setExternOpticTemp(double value);
        /**
         * @brief Set distance to objects in scene.
         * @param value New value.
         */
        void setObjectDistance(double value);
        /**
         * @brief Set External Optics Transition.
         * @param value New value.
         */
        void setExternOpticTrans(double value);
        /**
         * @brief Set humidity.
         * @param value New value.
         */
        void setHumidity(double value);
        /**
        * @brief Get Measurements
        * @return Shared pointer to all the measurements present in a source
        */
        std::shared_ptr<Measurements> getMeasurements() const;
        /**
        * @brief Get Alarms
        * @return Shared pointer to all the alarms present in a source
        */
        std::shared_ptr<Alarms> getAlarms() const;
        /**
         * @brief getEmissivity.
         * @return Image emissivity.
         */
        double getEmissivity();
        /**
         * @brief Reflected Temperature saved in an image
         * @return Reflected Temperature.
         */
        double getReflectedTemp();
        /**
         * @brief Atmospheric temperatur saved in an image
         * @return Atmospheric temperature.
         */
        double getAtmTemp();
        /**
         * @brief External Optics Temperature saved in an image.
         * @return External Optics Temperature.
         */
        double getExternOpticTemp();
        /**
         * @brief Distance of an captured object on image.
         * @return Distance of an captured object.
         */
        double getObjectDistance();
        /**
         * @brief External optics transmission saved in an image.
         * @return External optics transmission.
         */
        double getExternOpticTrans();
        /**
         * @brief Relative humidity saved in an image.
         * @return Relative humidity.
         */
        double getHumidity();
        /**
         * @brief Decide whether thermal image instance contains temperature data.
         * @return True if image contains temperature for every pixel.
         */
        bool isRadiometricImage() const;
        /**
         * @brief Add ROI item to image.
         * @param roi ROI item.
         */
        void addRoiToImage(std::shared_ptr<RoiStruct> roi);
        /**
         * @brief Remove ROI item from image.
         * @param roi ROI item.
         */
        void removeRoiFromImage(std::shared_ptr<RoiStruct> roi);
        /**
         * @brief Add ROI item to image.
         * @param roi ROI item.
         */
        void addRoiToImage(const RoiStruct & roi);
        /**
         * @brief updateCustomParamsRoi
         * @param roi
         * @param customParams
         * @param emissivity
         * @param reflTemp
         * @param distance
         */
        void updateCustomParamsRoi(RoiStruct & roi , bool customParams, float emissivity, float reflTemp, float distance);
        /**
         * @brief Add Alarm item to image.
         * @param alarm Alarm item.
         */
        void addAlarmToImage(std::shared_ptr<AlarmStruct> alarm);
        /**
         * @brief Add Alarm item to image.
         * @param alarm Alarm item.
         */
        void addAlarmToImage(const AlarmStruct & alarm);
        /**
          * @brief Recalculate temperatures inside roi item.
          */
        bool recalcRoi(std::shared_ptr<RoiStruct> roi, float & roiMax, std::pair<int,int> & maxCoords, float & roiMin, std::pair<int,int> & minCoords, float & roiAvg);
        /**
        * @brief Recalculate temperatures inside roi item.
        */
        bool recalcRoi(RoiStruct & roi, float & roiMax, std::pair<int,int> & maxCoords, float & roiMin, std::pair<int,int> & minCoords, float & roiAvg);
    private:
        bool checkRoiBounds(RoiStruct & roi);

        bool checkRoiBounds(std::shared_ptr<RoiStruct> roi);

        void recalcMinMaxRange();

        void addAlarmOverlay(uint8_t * imageData) const;

        void addMeasurementOverlay(uint8_t * imageData) const;
    };
}

#endif // IMAGERADIOMETRIC_H
