#ifndef WTL_MEASUREMENTCONTEXT_H
#define WTL_MEASUREMENTCONTEXT_H

#include "colortypes.h"

#include <memory>
#include <optional>
#include <vector>

namespace wtl {

class Roi;
class Alarm;
class Point;
class SourceMetaData;

class MeasurementContext
{
public:
    MeasurementContext(const std::weak_ptr<SourceMetaData>& metadata, const std::vector<std::shared_ptr<Roi>>& rois = {}, const std::vector<std::shared_ptr<Alarm>>& alarms = {});

    const std::vector<std::shared_ptr<Roi>>& getRois() const;
    const std::vector<std::shared_ptr<Alarm>>& getAlarms() const;

    bool addRoi(const std::shared_ptr<Roi>& roi);
    void removeRoi(const std::shared_ptr<Roi>& roi);
    void clearRois();

    bool addAlarm(const std::shared_ptr<Alarm>& alarm);
    void removeAlarm(const std::shared_ptr<Alarm>& alarm);
    void clearAlarms();

    std::optional<RGB> getOverlay(float temperature, const Point& position) const;

private:
    std::weak_ptr<SourceMetaData> m_metadata;
    std::vector<std::shared_ptr<Roi>> m_rois;
    std::vector<std::shared_ptr<Alarm>> m_alarms;

    bool checkRoiBounds(const std::shared_ptr<Roi>& roi) const;
};

} // namespace wtl

#endif // WTL_MEASUREMENTCONTEXT_H
