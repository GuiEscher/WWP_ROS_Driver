#include <wtlib/sources/thermalsequence.h>
#include <wtlib/sources/thermalimage.h>
#include <wtlib/parameters/sequencemetadata.h>
#include <wtlib/measurement/measurementcontext.h>
#include <wtlib/measurement/roi.h>
#include <wtlib/measurement/alarm.h>
#include <wtlib/parameters/thermalparameters.h>
#include <wtlib/parameters/palette.h>

#include <string>
#include <iostream>

int main(int argc, char** argv)
{
    const std::string resourcePath = RESOURCE_PATH;
    auto sequence = wtl::ThermalSequence::load(resourcePath + "/wwe_sequence.wseq");

    if (!sequence)
    {
        std::cerr << "Failed to open sequence" << std::endl;
        return -1;
    }

    auto metadata = sequence->getMetadata();

    std::cout << "----- METADATA -----" << std::endl;
    std::cout << "Source name: " << metadata.getSourceName() << std::endl;
    std::cout << "Source path: " << metadata.getSourcePath() << std::endl;
    std::cout << "Capture time: " << metadata.getCaptureTimeExif() << std::endl;
    std::cout << "Serial number: " << metadata.getCameraSerialNumber() << std::endl;
    std::cout << "Manufacturer: " << metadata.getCameraManufacturer() << std::endl;
    std::cout << "Source name: " << metadata.getSourceName() << std::endl;
    std::cout << "Article number: " << metadata.getCameraArtn() << std::endl;
    std::cout << "FW version: " << metadata.getCameraFWVersion() << std::endl;
    std::cout << "Lens: " << metadata.getCameraLensModel() << std::endl;

    std::cout << "Framerate: " << metadata.getFrameRate() << std::endl;
    std::cout << "Duration: " << metadata.getDuration() << std::endl;
    std::cout << "File size: " << metadata.getFileSize() << std::endl;
    std::cout << "Total frames: " << metadata.getNumberOfFrames() << std::endl;

    auto measurement = sequence->getMeasurement();

    std::cout << "----- MEASUREMENT -----" << std::endl;
    std::cout << "ROI:" << std::endl;
    for (const auto& roi : measurement.getRois())
    {
        std::cout << "  " << roi->getName() << "  ";
        switch (roi->getType())
        {
        case wtl::Roi::Type::POINT:
            std::cout << "Point";
            break;
        case wtl::Roi::Type::RECTANGLE:
            std::cout << "Rectangle";
            break;
        case wtl::Roi::Type::LINE:
            std::cout << "Line";
            break;
        case wtl::Roi::Type::POLYLINE:
            std::cout << "Polyline";
            break;
        case wtl::Roi::Type::POLYAREA:
            std::cout << "Polyarea";
            break;
        case wtl::Roi::Type::ELLIPSE:
            std::cout << "Ellipse";
            break;
        }
        std::cout << std::endl;
    }

    std::cout << "Alarm:" << std::endl;
    for (const auto& alarm : measurement.getAlarms())
    {
        std::cout << "  " << alarm->m_Name << "  ";
        switch (alarm->m_Type)
        {
        case wtl::Alarm::Type::BELLOW:
            std::cout << "Bellow";
            break;
        case wtl::Alarm::Type::ABOVE:
            std::cout << "Above";
            break;
        case wtl::Alarm::Type::INTERVAL:
            std::cout << "Interval";
            break;
        case wtl::Alarm::Type::INVERTED_INTERVAL:
            std::cout << "Inverted interval";
            break;
        }
        std::cout << std::endl;
    }

    auto thermalParameters = sequence->getThermalParameters();

    std::cout << "----- THERMAL PARAMETERS -----" << std::endl;
    std::cout << "Emissivity: " << thermalParameters.emissivity << std::endl;
    std::cout << "Reflected temperature: " << thermalParameters.reflectedTemperature << std::endl;
    std::cout << "Object distance: " << thermalParameters.objectDistance << std::endl;
    std::cout << "Atmospheric temperature: " << thermalParameters.atmosphericTemperature << std::endl;
    std::cout << "Relative humidity: " << thermalParameters.relativeHumidity << std::endl;
    std::cout << "Optics transmission: " << thermalParameters.opticsTransmission << std::endl;
    std::cout << "Optics temperature: " << thermalParameters.opticsTemperature << std::endl;

    auto palette = sequence->getPalette();

    std::cout << "----- PALETTE -----" << std::endl;
    std::cout << "Name: " << palette.getName() << std::endl;

    std::cout << "----- FRAMES -----" << std::endl;
    for (int i = 0; i < metadata.getNumberOfFrames(); ++i)
    {
        auto frame = sequence->at(i);
        std::cout << "Frame: " << i << "  MAX: " << frame->getMaximumTemperature() << "  MIN: " << frame->getMinimumTemperature() << std::endl;
    }

    return 0;
}
