#ifndef SOURCEMETADATA_H
#define SOURCEMETADATA_H

#include <string>
#include </home/guilherme/wwpcamera/src/wwpcamera/src/lib/wwp-data-sdk-0.3.0-linux/wwp-data-sdk/headers/sourceparameters/gpsinfo.h>

namespace wtl {
/**
     * @brief Image data not related to thermal analysis.
     * @details Class instances are used to provide user with metadata.
     * acquired from thermogram that are not directly related to temperature calculations.
     */
class SourceMetaData
{
    friend class FFFFileManager;
    friend class ThermalFileManager;
protected:
    std::string m_SourceName {};
    std::string m_SourcePath {};
    std::string m_CameraName {};
    std::string m_CameraArtn {};
    std::string m_CameraFW {};
    std::string m_CameraSerial {};
    std::string m_CameraManufacturer {};
    unsigned m_Timestamp {}; //Time in seconds since 1970-01-01 00:00 (UTC)
    int m_ImageHeight {};
    int m_ImageWidth {};
    GPSInfo m_GpsInfo {};
    uint16_t m_ImageFreq {};
    // for wiris m200
    unsigned m_FlightTime {};
    double m_GimbalCPUTemp {};
public:
    SourceMetaData();

    SourceMetaData(const SourceMetaData & x) = default;
    // defailt copy const. and operators are sufficient
    /**
         * @brief Image Height.
         * @return Height in pixels.
         */
    int getHeight() const;
    /**
         * @brief Image Width.
         * @return Width in pixels.
         */
    int getWidth() const;
    /**
         * @brief Image Resolution.
         * @return Image Pixel Resolution.
         */
    std::string getResolution() const;
    /**
         * @brief Image Name.
         * @return Image Name
         */
    std::string getSourceName() const;
    /**
         * @brief Image Path
         * @return Image Path
         */
    std::string getSourcePath() const;
    /**
         * @brief Unix timestamp of an image saved in exif
         * @return Unix timestamp as string
         */
    std::string getCaptureTimeExif() const;
    /**
         * @brief Unix timestamp of an imag
         * @return Unix timestamp as uint
         */
    unsigned getCaptureTime() const;
    /**
         * @brief Serial number of camera that captured the image.
         * @return Camera SN string.
         */
    std::string getCameraSerialNumber() const;
    /**
         * @brief Manufacturer of camera that captured the image.
         * @return Manufacturer as string.
         */
    std::string getCameraManufacturer() const;
    /**
         * @brief Article number of camera that captured the image.
         * @return Camera article number
         */
    std::string getCameraArtn() const;
    /**
         * @brief Get Camera Firmware Version
         * @return
         */
    std::string getCameraFWVersion() const;
    /**
         * @brief Camera model name.
         * @return
         */
    std::string getCameraName() const;
    /**
         * @brief Get information about location of an image.
         * @return Read-only gps info instance.
         */
    const GPSInfo & getGPSInfo() const;
    /**
         * @brief Get information about location of an image.
         * @return Modyfiable GPS info instance.
         */
    GPSInfo & getGPSInfo();
    /**
             * @brief getFlightTime
             */
            unsigned getFlightTime() const;
            /**
             * @brief getGimbalCPUTemp
             * @return
             */
            double getGimbalCPUTemp() const;
    /**
         * @brief getImageFrequency
         * @return
         */
    uint16_t getImageFrequency() const;
    /**
         * @brief Set name of an image.
         * @param[in] imageName new image name string.
         */
    void setSourceName(const std::string & imageName);
    /**
         * @brief Set path to the image.
         * @param[in] imagePath new image path.
         */
    void setSourcePath(const std::string & imagePath);
    /**
         * @brief setWidth
         * @param width
         */
    void setWidth(int width);
    /**
         * @brief setHeight
         * @param height
         */
    void setHeight(int height);
    /**
         * @brief setCaptureTime
         * @param timestamp
         */
    void setCaptureTime(unsigned timestamp);
    /**
         * @brief setCameraSerialNumber
         * @param serialNumber
         */
    void setCameraSerialNumber(const std::string & serialNumber);
    /**
         * @brief setCameraManufacturer
         * @param cameraManufacturer
         */
    void setCameraManufacturer(const std::string & cameraManufacturer);
    /**
         * @brief setCameraModelName
         * @param cameraModelName
         */
    void setCameraArtn(const std::string & cameraModelName);
    /**
         * @brief getCameraName
         * @param cameraName
         */
    void setCameraName(const std::string & cameraName);

    /**
         * @brief Set Camera Firmware Version
         * @param cameraFW
         */
    void setCameraFWVersion(const std::string & cameraFW);
    /**
     * @brief setImageFrequency
     * @param imgFreq
     */
    void setImageFrequency(uint16_t imgFreq);
    /**
     * @brief setFlightTime
     * @param flightTime
     */
    void setFlightTime(unsigned flightTime);
    /**
     * @brief setGimbalCPUTemp
     * @param temp
     */
    void setGimbalCPUTemp(double temp);
};
}
#endif // SOURCEMETADATA_H
