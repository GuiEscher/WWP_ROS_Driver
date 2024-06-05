#ifndef THERMALFILEMANAGER_H
#define THERMALFILEMANAGER_H

#include <string>
#include <memory>
#include <jpeglib.h>
#include <cstdint>
#include <cstdlib>
#include <vector>
#include <set>

#include </home/guilherme/wwpcamera/src/wwpcamera/src/lib/wwp-data-sdk-0.3.0-linux/wwp-data-sdk/headers/sourceparameters/gpsinfo.h>
#include </home/guilherme/wwpcamera/src/wwpcamera/src/lib/wwp-data-sdk-0.3.0-linux/wwp-data-sdk/headers/sourceparameters/sourcemetadata.h>
#include </home/guilherme/wwpcamera/src/wwpcamera/src/lib/wwp-data-sdk-0.3.0-linux/wwp-data-sdk/headers/thermalsources/imageradiometric.h>
#include </home/guilherme/wwpcamera/src/wwpcamera/src/lib/wwp-data-sdk-0.3.0-linux/wwp-data-sdk/headers/thermalsources/sequenceradiometric.h>

namespace wtl
{
    /**
     * @brief Virtual class providing interface for extracting and saving thermal images.
     * @details Handles JPEG and EXIF formats using libraries.
     */
    class ThermalFileManager
    {
    public:
        ThermalFileManager();
        /**
         * @brief ThermalFileManger
         * @param x
         */
        ThermalFileManager(const ThermalFileManager & x) = delete;
        /**
         * @brief operator =
         * @param x
         * @return
         */
        ThermalFileManager & operator=(const ThermalFileManager & x) = delete;
        /**
         * @brief ~ThermalFileManager
         */
        virtual ~ThermalFileManager();
        /**
        * @brief Load image from the disk and save it to ThermalImage instance
        * @param[out] image Empty radiometric image instance
        * @param[in] path Path to source thermal file.
        */
        virtual bool loadImageRadiometric(ImageRadiometric & image, const std::string & path) const = 0;
        /**
        * @brief Load image from the disk and save it to ThermalImage instance
        * @param[out] image Empty radiometric image instance
        * @param[in] path Path to source thermal file.
        */
        virtual bool loadImageRadiometric(ImageRadiometric & image, SourceMetaData & metaData, uint16_t * dataPtr) const = 0;
        /**
        * @brief Save radiometric image.
        * @param[in] image Source radiometric image instance.
        * @param[in] path Target path
        */
        virtual bool saveImageRadiometric(const ImageRadiometric & image, const std::string & path) const = 0;
        /**
         * @brief loadImageRadiometric
         * @param image
         * @param path
         * @return
         */
        virtual bool loadSequenceRadiometric(SequenceRadiometric & image, const std::string & path) const = 0;
        /**
         * @brief Save radiometric sequence.
         * @param path Absolute location on a disk where the sequence should be saved.
         * @param sequence ThermalSequence instance which will be saved to file.
         */
        virtual bool saveSequenceRadiometric(const SequenceRadiometric & sequence, const std::string & path) const = 0;
        /**
         * @brief Cut sequence and save it.
         * @param sequence ThermalSequence instance which will be saved to file.
         * @param from First frame included in a saved sequence.
         * @param to Last frame included in a saved sequence.
         * @param path Absolute location on a disk where the sequence should be saved.
         */
        virtual bool savePartOfSequenceRadiometric(const SequenceRadiometric & sequence, int from, int to, const std::string & path) const = 0;
        /**
         * @brief isRadiometricImage
         * @param path
         * @return
         */
        virtual bool isRadiometricImage(const std::string & path) const = 0;
        /**
         * @brief Check whether image saved on disk is super-resolution thermal image.
         * @param path Path to image file.
         * @return True for super-resolution thermal image.
         */
        virtual bool isSuperResolutionImage(const std::string & path) const = 0;
        /**
         * @brief Extract info about location from thermal file.
         * @param path Path to image file.
         * @return Shared ptr to GPSInfo instance. @return
         */
        virtual std::shared_ptr<wtl::GPSInfo> extractGPSFromSource(const std::string & path) const = 0;
        /**
         * @brief isThermalImage
         * @param path
         * @return
         */
        bool isThermalImage(const std::string & path);
        /**
         * @brief extractRadiometricSequenceFramePixels
         * @param frame
         * @param sequence
         * @return
         */
        virtual bool extractRadiometricSequenceFrame(ImageRadiometric & frame, const SequenceRadiometric & sequence, int index) const = 0;
    protected:
        /**
        * @brief Decompress jpeg image file.
        * @details Uses libjpeg.
        * @param[in] path Path to JPEG source.
        * @param[out] data Raw decompressed data
        */
        uint8_t * openAndDecompressJPEG(const char * path, uint8_t * data, size_t & fileSize) const;

        void copyMetaData(SourceMetaData & imgData, SequenceMetaData & sequenceData) const;

        std::string filenameFromPath(const std::string & path) const;

        std::vector<std::string> splitpath( const std::string& str, const std::set<char> delimiters) const;
    };
}
#endif // THERMALFILEMANAGER_H
