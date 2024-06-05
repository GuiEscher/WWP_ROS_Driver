#ifndef SEQUENCERADIOMETRIC_H
#define SEQUENCERADIOMETRIC_H

#include </home/guilherme/wwpcamera/src/wwpcamera/src/lib/wwp-data-sdk-0.3.0-linux/wwp-data-sdk/headers/thermalsources/thermalsequence.h>
#include </home/guilherme/wwpcamera/src/wwpcamera/src/lib/wwp-data-sdk-0.3.0-linux/wwp-data-sdk/headers/thermalsources/imageradiometric.h>

namespace wtl
{
    /**
     * @brief Represents a radiometric sequence
     * @details Provides interface for extracting and saving data to sequences of thermal images.
     * Sequence is processed as a stream of thermal images.
     */
    class SequenceRadiometric : public ThermalSequence
    {
        friend class Center;
        friend class FFFFileManager;
        std::shared_ptr<ImageRadiometric> m_CurrentFrame;
        std::shared_ptr<ThermalParameters> m_ThermalParameters;
        std::shared_ptr<Measurements> m_Measurements;
        std::shared_ptr<Alarms> m_Alarms;
        float m_ManualMax = 0;
        float m_ManualMin = 0;
        /**
         * @brief Class constructor.
         * @param rediometric  true if image contains temperature data
         */
        SequenceRadiometric(const std::string & path, std::shared_ptr<wtl::FFFFileManager> mngr);
    public:
        /**
        * @brief Copy constructor.
        * @param x Source thermal sequence.
        */
        SequenceRadiometric(const SequenceRadiometric & x) = delete;
        /**
         * @brief Class destructor.
         */
        ~SequenceRadiometric();
        /**
         * @brief Assignment operator
         * @param x Source thermal sequence.
         */
        SequenceRadiometric & operator=(const SequenceRadiometric & x) = delete;
        /**
         * @brief Subscription operator
         * @details Enables random access to sequence frames as radiometric images.Only for sequences with temperature data.
         */
        std::shared_ptr<wtl::ImageRadiometric> operator[](size_t index);
        /**
         * @brief Constant Subscription operator
         * @details Enables random access to sequence frames as radiometric images. Only for sequences with temperature data.
         */
        const std::shared_ptr<wtl::ImageRadiometric> operator[](size_t index) const;
        /**
         * @brief Returns radiometric image representation of frame at given position.Only for sequences with temperature data.
         */
        std::shared_ptr<wtl::ImageRadiometric> at(int index);
        /**
         * @brief Returns thermal image representation of frame at given position.Only for sequences with temperature data.
         */
        std::shared_ptr<wtl::ThermalImage> thermalAt(int index) const override;
        /**
                 * @brief Returns thermal image representation of frame at given position.Only for sequences with temperature data.
                 * @details Copies thermal data from sequence to this frame which includes recalculation
                 */
                std::shared_ptr<wtl::ImageRadiometric> radiometricAt(int index) const;
        /**
         * @brief Get rgb representation of an frame
         * @param index Frame number
         * @return 1D array of rgb image data, 8 bits per chanel
         */
        std::shared_ptr<uint8_t> getRGBFrameAt(int index);
        /**
         * @brief Get rgb representation of an frame
         * Alarms and measurements overlay is added to the image
         * @param index Frame number
         * @return 1D array of rgb image data, 8 bits per chanel
         */
        std::shared_ptr<uint8_t> getRGBFrameWithOverlayAt(int index);
        /**
         * @brief Get Measurements
         * @return Shared pointer to all the measurements present in a source
         */
        std::shared_ptr<Measurements> getMeasurements();
        /**
         * @brief Get Alarms
         * @return Shared pointer to all the alarms present in a source
         */
        std::shared_ptr<Alarms> getAlarms();
        /**
        * @brief getPaletteMaxTemperature
        * @return
        */
        float getPaletteMaxTemperature() const;
        /**
        * @brief getPaletteMinTemperature
        * @return
        */
        float getPaletteMinTemperature() const;
        /**
          * @brief Set temperature used as maximum for palette
          * @param value Temperature in celsius
          */
        void setManualMax(float value);
        /**
          * @brief Set temperature used as minimium for palette
          * @param value Temperature in celsius
          */
        void setManualMin(float value);
        /**
         * @brief Set emissivity of objects on an scene
         * @param value New emissivity value
         */
        void setEmissivity(double value);
        /**
         * @brief Set Reflected Temperature of objects on an scene
         * @param value New ReflectedTemp value
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
         * @brief Set distance to objects in scene
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
         * @brief getEmissivity
         * @return Sequence emissivity
         */
        double getEmissivity();
        /**
         * @brief getReflectedTemp
         * @return Reflected Temperature
         */
        double getReflectedTemp();
        /**
         * @brief getAtmTemp
         * @return Atmospheric temperature
         */
        double getAtmTemp();
        /**
         * @brief getExternOpticTemp
         * @return External Optics Temperature
         */
        double getExternOpticTemp();
        /**
         * @brief getObjectDistance
         * @return Distance of an captured object
         */
        double getObjectDistance();
        /**
         * @brief getExternOpticTrans
         * @return External optics transmission
         */
        double getExternOpticTrans();
        /**
         * @brief getHumidity
         * @return Relative humidity
         */
        double getHumidity();
        /**
         * @brief Decide whether thermal sequence instance contains radiometric temperature data
         * @return True if image contains temperature for every pixel
         */
        bool isRadiometricSequence() const;
        /**
         * @brief Add ROI item to sequence.
         * @param roi ROI item.
         */
        void addRoiToSequence(std::shared_ptr<RoiStruct> roi);
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
         * @brief Add Alarm item to sequence.
         * @param alarm Alarm item.
         */
        void addAlarmToSequence(std::shared_ptr<AlarmStruct> alarm);
    private:
        void setParamsToFrame(std::shared_ptr<wtl::ImageRadiometric> & frame) const;
        void setThermalParamsToFrame(std::shared_ptr<wtl::ImageRadiometric> & frame) const;
        void setManualRangeToFrame(bool manualRangeActive);
        void recalcMinMaxRange();
    };
}
#endif /* SEQUENCERADIOMETRIC_H*/
