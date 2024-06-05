#ifndef THERMALCALCULATION_H
#define THERMALCALCULATION_H

#include <memory>
#include <cstring>
#include <cmath>

#include </home/guilherme/wwpcamera/src/wwpcamera/src/lib/wwp-data-sdk-0.3.0-linux/wwp-data-sdk/headers/sourceparameters/thermalparameters.h>
#include </home/guilherme/wwpcamera/src/wwpcamera/src/lib/wwp-data-sdk-0.3.0-linux/wwp-data-sdk/headers/sourceparameters/calibrationparameters.h>
#include </home/guilherme/wwpcamera/src/wwpcamera/src/lib/wwp-data-sdk-0.3.0-linux/wwp-data-sdk/headers/sourceparameters/measurements.h>

namespace wtl {
    /**
     * @brief Class responsible for all the temperatura raleted computations
     */
    class ThermalCalculation
    {
        std::shared_ptr<ThermalParameters> m_ThermalParameters;
        std::shared_ptr<CalibrationParameters> m_CalibParameters;
        std::unique_ptr<float []> m_Temperatures;
        float m_MaxTemp = -273.15;
        float m_MinTemp = 5000;
        int m_DataLen = 0;
        int m_ImageWidth = 0;
    public:
        // TODO - make this private or move to image class
                // there are small errors when recalculating radio->raw->radio becouse of rounding and limited capacity of uint16_t
                // this helper array holds raw values multiplied by 100, this way two-decimal accuracy is maintained
        std::unique_ptr<uint32_t []> m_RawsNotRounded;

        /**
        * @brief Class constructor
        * @details Calculation instance gets shared pointer to parameters of image it belongs to.
        * No need to notify calculation when parameters are changed.
        * @param thermalParameters Image thermal parameters instance.
        */
        ThermalCalculation(std::shared_ptr<ThermalParameters> thermalParameters, std::shared_ptr<CalibrationParameters> calibParameters);
        /**
         * * @brief Class destructor
         */
        ~ThermalCalculation();
        /**
         * @brief Copy constructor not allowed
         * @param x
         */
        ThermalCalculation(const ThermalCalculation & x) = delete;
        /**
          * @brief Initialize calculation class, allocates memory according the dimensions of image etc.
          * @param imageWidth Image width
          * @param imageHeight Image height
          */
        void initCalculation(int imageWidth, int imageHeight);

        void refreshCalculationParameters();
        /**
         * @brief refreshTemperatures
         * @param pixels
         * @param imageHeight
         * @param imageWidth
         * @param maxCoords
         * @param minCoords
         */
        void refreshTemperatures(uint16_t * pixels, int imageHeight,  int imageWidth, std::pair<int, int> & maxCoords, std::pair<int, int> & minCoords);
        /**
         * @brief Redo temperature calculation after change in thermal parameters
         */
        void refreshTemperatures(uint16_t * pixels, int imageHeight,  int imageWidth);
        /**
         * @brief recalculatePixelsToLinearRadiometric
         * @param pixels
         * @param imageHeight
         * @param imageWidth
         */
        void refreshTemperaturesFromExtended(int imageHeight, int imageWidth, std::pair<int, int> & maxCoords, std::pair<int, int> & minCoords);
        void refreshTemperature(uint16_t * pixels, int idx);
        void recalculatePixelToSignal(uint16_t * pixels, int idx);
        void recalculatePixelsToSignal(uint16_t * pixels, int imageHeight, int imageWidth);
        /**
         * @brief Recalculate raw value.
         * @details Used in recalculation of sequence from wseq format to seq
         */
        void recalculatePixelsToLinearRadiometric(uint16_t * pixels, int imageHeight, int imageWidth);
         void recalculatePixelToLinearRadiometric(uint16_t * pixels, int idx);
        /**
        * @brief Calculate temperatures inside Roi item
        * @param[in] roi Roi instance
        * @param[out] max Maximal temperature inside Roi
        * @param[out] min Minimal temperature inside Roi
        * @param[out] avg Average roi temperature
        */
        void calculateRoiTemperatures(const RoiStruct & roi, float & max, std::pair<int,int> & maxCoords, float & min, std::pair<int,int> & minCoords, float & avg, int imageWidth, int imageHeight) const;

        void calculateRoiRadiometricValues(const RoiStruct & roi, uint16_t * pixels);
        void removeRoiRecalc(const RoiStruct & roi, uint16_t * pixels);
        /**
        * @brief Calculate pixel of roi with custom params to temp
        * @return
        */
        float calculateRoiPixToTemp(const RoiStruct & roi, float oldTemp);

        float getMaxTemp() const;

        float getMinTemp() const;

        float getTemperature(int idx) const;

        uint16_t getSignal(int idx) const;

        void getTemperatures(float ** imageData, int & imageSize) const;

        void getSignals(uint16_t ** imageData, int & imageSize) const;

        static float kelvinsToRightTemp(float temp, wtl::TempsUnit unit);

        static float rightTempToKelvins(float temp, wtl::TempsUnit unit);
        // recalculate from linearized temp data to raw format wo be
    private:
        uint16_t calculateTemptoRAW(double temp) const;
        void calculateTemptoSignalExtended(double temp, int idx) const;
        float calculateRAWtoTemp(uint16_t raw) const;
        uint16_t calculateTempFtoInt(float temp) const;
        void calculateTemperaturesLookupTable();
        float calculateTempForLookupTable(uint16_t pixel) const;
        float kelvinsToRightTemp (float temp) const;
        float rightTempToKelvins(float temp) const;
        float tempToObjSig(float dblKelvin);
        float calculateTauAtm() const;
        float doCalcAtmTao() const;
        float doCalcK1(float m_AtmTao) const;
        float doCalcK2(float dAmbObjSig, float dAtmObjSig, float dExtOptTempObjSig, float m_AtmTao) const;
        float CalculateM(float T) const;
        float CalculateMap(uint16_t pixel) const;
        float CalculateMapFromExtended(uint32_t pixel) const;
        float CalculateMobj(uint16_t pixel) const;
        float CalculateMobjFromExtended(uint32_t pixel) const;
        static float getCalibBreakingPointX(float calib[5]);
        void refreshCalibrationParameters();
    };
}
#endif // THERMALCALCULATION_H
