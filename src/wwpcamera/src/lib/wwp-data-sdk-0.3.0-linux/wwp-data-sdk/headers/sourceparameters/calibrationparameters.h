#ifndef CALIBRATIONPARAMETERS_H
#define CALIBRATIONPARAMETERS_H


namespace wtl {
    /**
    * @brief Possible recalculation states
    */
    enum class RecalculationState
    {
        /** @brief Linear temperature data - radiometric images. */
        NotRecalculated,
        /** @brief Recalculation started but was not finished */
        RecalculationStarted,
        /** @brief Recalculation finished successfully to signal values and thermal parameters can be set */
        RecalculationCompleted
    };
    enum class TempsUnit
    {
        Kelvin,
        Celsius,
        Fahrenheit
    };
    enum class FileType
    {
        Workswell = 1,                   // general for raw images, non camera spefific, just signal values
        WorkswellMini = 2,
        WorkswellGIS = 4,                // radiometric camera
        WorkswellWWP = 5,                // radiometric camera
        WorkswellWWS = 6,                // non-radiometric camera - only 1?
        WorkswellWiris = 7,              // radiometric camera
        WorkswellSAFETIS = 8,            // radiometric camera
        NIT = 9,                          // swir camera
        WorkswellWPM = 10
    };

    struct CalibrationParameters
    {
        // calib params
        /** @brief RThg */
        double m_RThg;
        /** @brief RGev */
        double m_RGev;
        /** @brief R */
        double m_R;
        /** @brief B */
        double m_B;
        /** @brief F */
        double m_F;
        /** @brief O */
        double m_O;
        /** @brief Scaling factor for attenuation */
        double m_X;
        /** * @brief J1 */
        double m_J1;
        /** * @brief TauAtm */
        double m_TauAtm;
        /** @brief Matm */
        double m_Matm;
        /** @brief Mbgr */
        double m_Mbgr;
        /** @brief Map */
        double m_Map;
        /** @brief K1 */
        double m_K1;
        /** @brief K2 */
        double m_K2;
        /** @brief  Attenuation for atmosphere without water vapour */
        double m_Alpha1 ;
        /** @brief Attenuation for atmosphere without water vapour */
        double m_Alpha2;
        /** @brief  Attenuation for water vapour */
        double m_Beta1;
        /** @brief  Attenuation for water vapour */
        double m_Beta2;
         /** @brief Temperature compensation offset (globalOffset) */
        int m_NormOffset;
         /** @brief Temperature compensation gain (globalGain) */
        float m_NormGain;
        /** @brief Radiometric constant */
        float m_RadiometricConst;
        /** @brief Radiometric constant */
        float m_Reserved[5]{};
        /** @brief Holds pre-computed temperatures for all possible raw value (16 bit number) */
        float m_TempLookupTable[65536]{};
        /** @brief Recalculation Status */
        RecalculationState m_RecalculationState;
        /** @brief Temperature Units */
        TempsUnit m_TempsUnitType;
        /** @brief File type decided by camera model */
        FileType m_CameraFileType;

        CalibrationParameters();

        ~CalibrationParameters();

        CalibrationParameters(const CalibrationParameters & x);

        CalibrationParameters & operator=(const CalibrationParameters & x);
    };
}

#endif // CALIBRATIONPARAMETERS_H
