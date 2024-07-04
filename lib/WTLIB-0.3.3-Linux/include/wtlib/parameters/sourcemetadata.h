#ifndef WTL_SOURCEMETADATA_H
#define WTL_SOURCEMETADATA_H

#include "gpsinfo.h"

#include <string>
#include <memory>

class ThermalImageSource;

namespace wtl {

class SourceMetaData
{
public:
    SourceMetaData();
    virtual ~SourceMetaData();

    int getHeight() const;
    int getWidth() const;

    std::string getSourceName() const;
    std::string getSourcePath() const;
    std::string getCaptureTimeExif() const;
    unsigned getCaptureTime() const;
    std::string getCameraSerialNumber() const;
    std::string getCameraManufacturer() const;
    double getIRTemp() const;
    std::string getCameraArtn() const;
    std::string getCameraFWVersion() const;
    std::string getCameraName() const;
    std::string getCameraLensModel() const;
    const GPSInfo& getGPSInfo() const;
    unsigned getFlightTime() const;
    double getGimbalCPUTemp() const;
    GPSInfo& getGPSInfo();
    uint16_t getImageFrequency() const;
    int getLensLength() const;

    std::string getResolution() const;

protected:
    std::string m_SourceName{};
    std::string m_SourcePath{};
    std::string m_CameraName{};
    std::string m_CameraArtn{};
    std::string m_CameraFW{};
    std::string m_CameraSerial{};
    std::string m_CameraManufacturer{};
    std::string m_CameraLensModel{};
    unsigned m_Timestamp{};
    int m_ImageHeight{};
    int m_ImageWidth{};
    uint16_t m_ImageFreq{};
    double m_IRTemp{};
    unsigned m_FlightTime{};
    double m_GimbalCPUTemp{};
    int m_LensLength{};

    std::shared_ptr<GPSInfo>  m_GpsInfo{};

    friend class FFFFileManager;
    friend ThermalImageSource;
};

} // namespace wtl

#endif // WTL_SOURCEMETADATA_H
