#ifndef THERMALSOURCE_H
#define THERMALSOURCE_H

#include "/home/guilherme/wwpcamera/WWP_ROS_Driver/lib/WTLIB-0.3.3-Linux/include/wtlib/wtlib_export.h"

#include <memory>
#include <string>

namespace wtl {

class SourceMetaData;
class MeasurementContext;
struct ThermalParameters;
class Palette;
class ThermalSourceImpl;

class WTLIB_EXPORT ThermalSource
{
public:
    virtual ~ThermalSource() = 0;

    virtual const SourceMetaData& getMetadata() const;
    virtual SourceMetaData& getMetadata();

    const MeasurementContext& getMeasurement() const;
    MeasurementContext& getMeasurement();

    const ThermalParameters& getThermalParameters() const;
    ThermalParameters& getThermalParameters();

    const Palette& getPalette() const;
    Palette& getPalette();

    void setPalette(const std::shared_ptr<Palette>& palette);
    void setPalette(const std::string& name);

    void setThermalParameters(const std::shared_ptr<ThermalParameters>& thermalParameters);

    bool isLegacy() const;

    virtual const std::shared_ptr<ThermalSourceImpl> getImpl() const = 0;
};

} // namespace wtl

#endif // THERMALSOURCE_H
