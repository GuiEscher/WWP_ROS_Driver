#ifndef ALARMS_H
#define ALARMS_H

#include <stdint.h>
#include <iostream>
#include <memory>
#include <vector>

namespace wtl
{
/**
     * @brief The AlarmType enum
     */
enum class AlarmType
{
    /** @brief Bellow Treshold Alarm */
    Below,
    /** @brief Above Treshold Alarm */
    Above,
    /** @brief Interval alarm - between upper and lower value */
    Interval,
    /** @brief Inverted Interval alarm - above upper and bellow lower value */
    InvertedInterval
};
/**
    * @brief Structure representing one alarm in an image
    */
struct AlarmStruct
{
    /**
         * @brief Alarm Type. See AlarmType.
         */
    AlarmType m_Type;
    /**
         * @brief Alarm top limit.
         */
    float m_UpperValue;
    /**
         * @brief Alarm bottom limit.
         */
    float m_LowerValue;
    /**
          *  @brief 8bit RGB color.
          */
    uint8_t m_Color[3] = { 0xFF, 0x00, 0x00 };

    std::string m_Name;
};
/**
     * @brief Containter of all the alarms present in an image.
     * @details Provides interface for reading saved alarms as well as adding new alarms.
     */
class Alarms
{
    std::vector<std::shared_ptr<AlarmStruct>> m_Alarms;
public:
    /**
          * @brief Default class constructor.
          */
    Alarms() = default;
    /**
         * @brief Deleted Copy contructor.
         * @param x
         */
    Alarms(const Alarms & x) = delete;
    /**
         * @brief Deleted assignment operator.
         * @param x
         */
    Alarms& operator=(const Alarms & x) = delete;
    /**
        * @brief Add new Alarm to the image.
        * @param alarm Alarm instance that is to be added.
        */
    void addAlarm(std::shared_ptr<AlarmStruct> alarm);
    /**
        * @brief Add new Alarm to the image.
        * @param alarm Alarm instance that is to be added.
        */
    void addAlarm(const AlarmStruct & alarm);
    /**
        * @brief Get all the alarms currently saved to the image.
        * @return A Vector containing Alarm Structures.
        */
    std::vector<std::shared_ptr<AlarmStruct>> getAlarms() const;
    /**
        * @brief Get number of alarms.
        * @return Total number of rois currently added to the image.
        */
    int getAlarmCount() const;
    /**
        * @brief Get alarm by index.
        * @return Roi stucture instance on the position specified by parameter idx.
        */
    const AlarmStruct & getAlarmAt(int idx) const;
    /**
         * @brief Delete alarm at specified index.
         * @param idx Alarm index.
         * @return True for success.
         */
    bool deleteAlarmAt(int idx);
    /**
         * @brief Clear all the alarms.
         */
    void clear();
};
}

#endif // ALARMS_H
