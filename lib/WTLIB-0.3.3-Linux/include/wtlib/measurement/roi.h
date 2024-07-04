#ifndef WTL_ROI_H
#define WTL_ROI_H

#include "wtlib/measurement/colortypes.h"
#include "wtlib/measurement/point.h"
#include "wtlib/measurement/rectangle.h"

#include <set>
#include <string>
#include <variant>
#include <vector>
#include <memory>
#include <optional>

namespace wtl {

class RoiImpl;

class Roi
{
public:
    struct LineRoiDefinition
    {
        Point pointA;
        Point pointB;
    };

    struct EllipseRoiDefinition
    {
        Point center;
        int xAxis;
        int yAxis;
    };

    enum class Type
    {
        POINT,
        RECTANGLE,
        LINE,
        POLYLINE,
        POLYAREA,
        ELLIPSE
    };

    using Mask = std::set<Point>;
    using VariantDefinition = std::variant<Point, Rectangle, LineRoiDefinition, std::vector<Point>, EllipseRoiDefinition>;

    struct ThermalParameters
    {
        std::optional<float> emissivity = std::nullopt;
        std::optional<float> reflectedTemperature = std::nullopt;
        std::optional<float> objectDistance = std::nullopt;

        bool isAnyCustom() const;
    };

    Roi(const Roi& other);
    ~Roi();

    static std::shared_ptr<Roi> createRoi(const std::string& name, const RGB& color, Type type, std::optional<VariantDefinition> definition = std::nullopt);

    void changeDefinition(const VariantDefinition& definition);
    const VariantDefinition& getDefinition() const;

    const std::string& getName() const;
    void setName(const std::string& name);

    RGB getColor() const;
    void setColor(RGB color);

    Type getType() const;

    const Roi::ThermalParameters& thermalParameters() const;
    Roi::ThermalParameters& thermalParameters();

    const Mask& getMask() const;
    const Rectangle& getHull() const;
    bool contains(const Point& point) const;

private:
    Roi();

    std::shared_ptr<RoiImpl> m_impl;
};

} // namespace wtl

#endif // WTL_ROI_H
