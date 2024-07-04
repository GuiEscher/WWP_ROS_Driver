#ifndef WTL_GPSINFO_H
#define WTL_GPSINFO_H

#include <string>

namespace wtl {
/**
 * @brief Location related file metadata.
 */
class GPSInfo
{
  public:
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
	 * @brief Get Alt. Ref.
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
	 * @return String with information about date and time of capture.
	 */
	const std::string& getDateTime() const;

	double getAzimuth() const;
	double getPitch() const;
	double getRoll() const;
	double getSpeed() const;
	double getRelativeHeight() const;
	void setAltitude(double altitude);
	void setLongitude(double longitude);
	void setLatitude(double latitude);
	void setAltitudeRef(char altitudeRef);
	void setLongitudeRef(char longitudeRef);
	void setLatitudeRef(char latitudeRef);
	void setSpeed(double speed);
	void setDateTime(const std::string& dateTime);
	void setAzimuth(double azimuth);
	void setRoll(double roll);
	void setPitch(double pitch);
	void setRelativeHeight(double height);
	bool isValid() const;
	void setValidity(bool valid);

  private:
	double m_Altitude{};
	double m_Longitude{};
	double m_Latitude{};
	char m_AltitudeRef{};
	char m_LongitudeRef{};
	char m_LatitudeRef{};
	bool dataValid{};
	std::string m_DateTime{};
	double m_Speed{};
	// only for Wiris Pro M200
	double m_Azimuth{};
	double m_Pitch{};
	double m_Roll{};
	double m_RelativeHeight{};
};
}
#endif // WTL_GPSINFO_H
