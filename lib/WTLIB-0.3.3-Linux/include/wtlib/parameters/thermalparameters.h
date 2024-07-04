#ifndef WTL_THERMALPARAMETERS_H
#define WTL_THERMALPARAMETERS_H

namespace wtl {
/**
 * @brief Encapsulation of all the parameters that directly influence
 * temperature measurements.
 */
struct ThermalParameters
{
    float emissivity = 0.95;
    float reflectedTemperature = 293.15;
    float objectDistance = 1;
    float atmosphericTemperature = 293.15;
    float relativeHumidity = 0.5;
    float opticsTransmission = 1;
    float opticsTemperature = 293.15;

    bool operator==(const ThermalParameters& second) const;
    bool operator!=(const ThermalParameters& second) const;
};
}
#endif // WTL_THERMALPARAMETERS_H
