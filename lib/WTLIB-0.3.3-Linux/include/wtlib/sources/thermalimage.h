#ifndef THERMALIMAGE_H
#define THERMALIMAGE_H

#include "/home/guilherme/wwpcamera/WWP_ROS_Driver/lib/WTLIB-0.3.3-Linux/include/wtlib/wtlib_export.h"
#include "thermalsource.h"

#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace wtl {

class ThermalImageImpl;
class Point;
struct RGB;
class Roi;

class WTLIB_EXPORT ThermalImage final : public ThermalSource
{
    const std::shared_ptr<ThermalImageImpl> m_impl;

public:
    ThermalImage(const std::shared_ptr<ThermalImageImpl>& impl);
    ~ThermalImage();
    static std::shared_ptr<ThermalImage> load(const std::string& path);
    bool save(const std::string& path) const;

    uint16_t getRaw(int x, int y) const;
    float getFlux(int x, int y) const;
    float getTemperature(int x, int y) const;

    const std::vector<uint16_t>& getRaws() const;
    const std::vector<float>& getFluxes() const;
    const std::vector<float>& getTemperatures() const;

    float getMaximumTemperature() const;
    const Point& getMaximumPosition() const;

    float getMinimumTemperature() const;
    const Point& getMinimumPosition() const;

    std::vector<RGB> getGrayscaleArrayRepresentation(std::optional<float> minimum = std::nullopt, std::optional<float> maximum = std::nullopt) const;

    std::vector<RGB> getRGBArrayRepresentation(std::optional<float> minimum = std::nullopt, std::optional<float> maximum = std::nullopt) const;
    std::vector<RGB> getRGBArrayRepresentation(std::array<size_t, 256>& pixelPerColorCounter, std::optional<float> minimum = std::nullopt, std::optional<float> maximum = std::nullopt) const;

    std::vector<RGB> getRGBArrayRepresentationWithOverlay(std::optional<float> minimum = std::nullopt, std::optional<float> maximum = std::nullopt) const;
    std::vector<RGB> getRGBArrayRepresentationWithOverlay(std::array<size_t, 256>& pixelPerColorCounter, std::optional<float> minimum = std::nullopt, std::optional<float> maximum = std::nullopt) const;

    void recalculateTemperatures(const std::optional<std::vector<float>>& lookupTable = std::nullopt);

    std::vector<float> calcRoi(const Roi& roi, float& max, Point& maxPos, float& min, Point& minPos, float& avg) const;

    const std::vector<std::vector<uint16_t>>& getPixelsSuperRes() const;

    /** ThermalSource interface **/
    const std::shared_ptr<ThermalSourceImpl> getImpl() const override;
};

} // namespace wtl

#endif // THERMALIMAGE_H
