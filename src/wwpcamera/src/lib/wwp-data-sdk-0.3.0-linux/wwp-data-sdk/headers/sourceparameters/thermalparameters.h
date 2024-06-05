#ifndef THERMALPARAMETERS_H
#define THERMALPARAMETERS_H

#include <memory>

namespace wtl {
    /**
     * @brief Encapsulation of all the parametrs that directly influence temperature measurements.
     */
    struct ThermalParameters
    {
        friend class FFFFileManager;
        friend class ThermalCalculation;
        /**
         * @brief Emissivity of captured object
         * @details Effectiveness in emitting energy.
         * Defined as ratio of tradiation of object and a black body.
         */
        double m_Emissivity;
        /** @brief Reflected temperature */
        double m_ReflTemp;
        /** @brief Atmospheric temperature */
        double m_AtmTemp;
        /** @brief External Optics temperature */
        double m_ExternOpticTemp;
        /** @brief Distance to the measured object */
        double m_ObjectDistance;
        /** @brief Air relative humidity */
        double m_Humidity;
        /** @brief External Optics transmission */
        double m_ExternOpticTrans;
        /**
         * @brief ThermalParameters contructor
         */
        ThermalParameters();
        /**
        * @brief Copy constructor.
        * @param x Source thermal parameters instance
        */
        ThermalParameters(const ThermalParameters & x);
        /**
         * @brief Assgnment operator
         * @param x Source thermal parameters instance
         */
        ThermalParameters & operator=(const ThermalParameters & x);
        /**
          * @brief Class destructor
          */
        ~ThermalParameters();
    };
}
#endif // THERMALPARAMETERS_H
