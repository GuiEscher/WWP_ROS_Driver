#ifndef GPSINFO_H
#define GPSINFO_H

#include <string>
namespace wtl
{
/**
     * @brief Location related file metadata.
     */
class GPSInfo
{
private:
    double m_Altitude{};
    double m_Longitude{};
    double m_Latitude{};
    char m_AltitudeRef{};
    char m_LongitudeRef{};
    char m_LatitudeRef{};
    bool dataValid{};
    std::string m_DateTime{};

    // only for Wiris Pro M200
    double m_Azimuth{};
    double m_Pitch{};
    double m_Roll{};
public:
    GPSInfo();
    /**
         * @brief Get Altitude in which image was captured.
         * @return Altitude in meters.
         */
    double getAltitude() const;
    /**
         * @brief Get Longitude coordinate.
         * @return Longitude coordinate.
         */
    double getLongitude() const;
    /**
         * @brief Get Latitude coordinate.
         * @return Latitude coordinate.
         */
    double getLatitude() const;
    /**
         * @brief Ger Alt. Ref.
         * @return 0 for above sea level
         */
    char getAltitudeRef() const;
    /**
         * @brief Get Long. Ref.
         * @return W for west and E for east.
         */
    char getLongitudeRef() const;
    /**
         * @brief Get Latitude Ref.
         * @return N for North and S for Sourth.
         */
    char getLatitudeRef() const;
    /**
         * @brief Get timestamp of an image.
         * @return String wtih information about date and time of capture.
         */
    std::string getDateTime() const;
    /**
                 * @brief getAzimuth
                 * @return
                 */
    double getAzimuth() const;
    /**
                 * @brief getPitch
                 * @return
                 */
    double getPitch() const;
    /**
                 * @brief getRoll
                 * @return
                 */
    double getRoll() const;
    /**
         * @brief Set Altitude.
         * @param altitude new altitude in meters.
         */
    void setAltitude(double altitude);
    /**
         * @brief Set longitude to an image.
         * @param longitude Longitude coordinate.
         */
    void setLongitude(double longitude);
    /**
         * @brief Set latitude to an image.
         * @param latitude Latitude coordinate.
         */
    void setLatitude(double latitude);
    /**
         * @brief Set altitude reference.
         * @param altitudeRef 0 for above sea level, 1 for bellow.
         */
    void setAltitudeRef(char altitudeRef);
    /**
         * @brief Set longitude reference to an image.
         * @param longitudeRef W for west and E for east.
         */
    void setLongitudeRef(char longitudeRef);
    /**
         * @brief Set latitude reference to an image.
         * @param latitudeRef S for south and N for north.
         */
    void setLatitudeRef(char latitudeRef);
    /**
         * @brief Set timestamp.
         */
    void setDateTime(const std::string & dateTime);
    /**
                 * @brief setAzimuth
                 * @param azimuth
                 */
    void setAzimuth(double azimuth);
    /**
                 * @brief setRoll
                 * @param roll
                 */
    void setRoll(double roll);
    /**
                 * @brief setPitch
                 * @param pitch
                 */
    void setPitch(double pitch);
    /**
         * @brief Validate gps data.
         * @return True if gps data are valid, false otherwise.
         */
    bool isValid() const;

    void setValidity(bool valid);
};
}
#endif // GPSINFO_H
