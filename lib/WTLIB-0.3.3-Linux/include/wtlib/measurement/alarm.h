#ifndef WTL_ALARM_H
#define WTL_ALARM_H

#include "wtlib/measurement/colortypes.h"

#include <limits>
#include <string>

namespace wtl {

class Alarm
{
public:
    enum class Type
    {
        BELLOW,
        ABOVE,
        INTERVAL,
        INVERTED_INTERVAL
    };

    Type m_Type{ Type::BELLOW };
	float m_UpperValue{ std::numeric_limits<float>::lowest() };
	float m_LowerValue{ std::numeric_limits<float>::max() };
	RGB m_Color = { 0xFF, 0x00, 0x00 };
	std::string m_Name;
};
}

#endif // WTL_ALARM_H
