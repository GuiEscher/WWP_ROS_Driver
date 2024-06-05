#ifndef CENTER_H
#define CENTER_H

#include <string>

#include </home/guilherme/wwpcamera/src/wwpcamera/src/lib/wwp-data-sdk-0.3.0-linux/wwp-data-sdk/headers/services/thermalfilemanager.h>
#include </home/guilherme/wwpcamera/src/wwpcamera/src/lib/wwp-data-sdk-0.3.0-linux/wwp-data-sdk/headers/services/ffffilemanager.h>
#include </home/guilherme/wwpcamera/src/wwpcamera/src/lib/wwp-data-sdk-0.3.0-linux/wwp-data-sdk/headers/services/licensemanager.h>
#include </home/guilherme/wwpcamera/src/wwpcamera/src/lib/wwp-data-sdk-0.3.0-linux/wwp-data-sdk/headers/sourceparameters/sourcemetadata.h>

namespace wtl
{
    /**
     * @brief Library Entrypoint, serves as its core. Users validate their copies of the Library with license keys or license files, and then are allowed to load images.
     * @details Serves as factory for thermal images and sequences classes instances. Libraryneeds to be authentificated before use by calling function authentificate().
     */
    class Center
    {
        static std::shared_ptr<FFFFileManager> m_FileManager;
        static std::unique_ptr<LicenseManager> m_LicenseManager;
        // instances forbidden
        Center() = delete;
    public:
        /**
         * @brief Activate your SDK.
         * @details Activation of serial number.Requires internet connection.
         * @param code License serial number that is shipped with SDK.
         * @return True for success.
         */
        static bool activate(const std::string & code);
        /**
         * @brief Deativate your SDK to use license on other PC.
         * @details Deactivation of serial number.Requires internet connection.
         * @return True for successful deactivation.
         */
        static bool deactivate();
        /**
         * @brief Activate trial for 14 days.
         * @details Activation of serial number.Requires internet connection.
         * @param code License serial number.
         * @return True for successful trial activation.
         */
        static bool requestTrial(const std::string & code);
        /**
         * @brief Authentificate yout library before working with images.
         * @details Check license file created during activation.
         * @return AuthState Current authentification state.
         */
        static wtl::AuthState authentificate();
        /**
         * @brief Get current Authentification state.
         * @return AuthState Current authentification state.
         */
        static wtl::AuthState getAuthState();
        /**
         * @brief Load image that contains temperature data.
         * @param path Absolute location on a disk where the image file is stored.
         * @return Loaded Shared pointer to new ImageRadiometric instance.
         */
        // todo - what if user tries to open file with no temp data? -> exception/parameter
        static std::shared_ptr<wtl::ImageRadiometric> loadImageRadiometric(const std::string & path);
        /**
         * @brief Create new image radiometric instance. Used for exports from stream.
         * @param meta Meta data of created image. Palette and thermal parameters are set to default.
         * @param calib Calibration parameters
         * @param pixels Image data
         * @return Shared pointer to new ImageRadiometric instance.
         */
        static std::shared_ptr<wtl::ImageRadiometric> createImageRadiometric(const wtl::SourceMetaData & meta, const wtl::CalibrationParameters calib, uint16_t * pixels);
        /**
         * @brief Create new image radiometric instance. Used for exports from stream.
         * @param meta Meta data of created image. Palette and thermal parameters are set to default.
         * @param calib Calibration parameters.
         * @param path Absolute location on a disk where the sequence should be saved.
         * @param pixels Image data
         * @return True for success.
         */
        static bool createAndSaveImageRadiometric(const wtl::SourceMetaData & meta, const wtl::CalibrationParameters & calib, uint16_t * pixels, const std::string & path);
        /**
         * @brief Create new image radiometric instance. Used for exports from stream.
         * @param meta Meta data of created image. Palette and thermal parameters are set to default.
         * @param calib Calibration parameters.
         * @param path Absolute location on a disk where the sequence should be saved.
         * @param palette Image palette.
         * @param pixels Image data
         * @return True for success.
         */
         static bool createAndSaveImageRadiometric(const wtl::SourceMetaData & meta, const wtl::CalibrationParameters & calib, const wtl::Palette & palette, uint16_t * pixels, const std::string & path);
        /**
         * @brief Load sequence of radiometric images.
         * @param path Absolute location on a disk where the sequence is stored.
         * @return Loaded Shared pointer to SequenceRadiometric instance.
         */
        static std::shared_ptr<SequenceRadiometric> loadSequenceRadiometric(const std::string & path);
        /**
         * @brief Create new image radiometric sequence instance and saves it Used for exports from stream.
         * @param meta Meta data of created sequence. Palette and thermal parameters are set to default.
         * @param calib Calibration parameters
         * @param frames Sequence Frames.
         * @param path Absolute location on a disk where the sequence should be saved.
         * @return True for success.
         */
        static bool createAndSaveSequenceRadiometric(const wtl::SequenceMetaData & meta, const wtl::CalibrationParameters & calib, std::vector< std::shared_ptr< ImageRadiometric > > & frames, const std::string & path);
        /**
         * @brief Save radiometric image.
         * @param path Absolute location on a disk where the sequence should be saved.
         * @param image ThermalRadiometric instance which will be saved to file.
         */
        // #TODO Přesunout metody pro ukládání do třídy Image a Sequence. Nemyslím si, že by měly být zde. Třída Center by měla sloužit pouze pro otevírání a aktivaci.
        static bool saveImageRadiometric(const std::shared_ptr<ImageRadiometric> image, const std::string & path);
        /**
         * @brief Save radiometric image, use imageData to create jpeg preview image.
         * @details Allows users to create own image representation with custom look of rois/alarms and save it to created jpeg.
         * @param image ThermalRadiometric instance which will be saved to file.
         * @param imageData Array of RGB data which will bre used to as JPEG preview.
         * @param path Absolute location on a disk where the sequence should be saved.
         */
        static bool saveImageRadiometricWithCustomJPEG(const std::shared_ptr<ImageRadiometric> image, uint8_t * imageData, const std::string & path);
        /**
         * @brief Save radiometric sequence.
         * @param path Absolute location on a disk where the sequence should be saved.
         * @param sequence SequenceRadiometric instance which will be saved to file.
         */
        static bool saveSequenceRadiometric(const std::shared_ptr<SequenceRadiometric>  & sequence, const std::string & path);
        /**
         * @brief Save part of radiometric sequence given by frame span
         * @param sequence ThermalSequence instance which will be saved to file.
         * @param from First frame included in a saved sequence.
         * @param to Last frame included in a saved sequence.
         * @param path Absolute location on a disk where the sequence should be saved.
         */
        static bool savePartOfSequenceRadiometric(const std::shared_ptr<SequenceRadiometric>  & sequence, int from, int to, const std::string & path);
        /**
         * @brief Check whether there is an license file stored at local computer.
         * @return True if license file exists.
         */
        static bool licenceFileExists();
        /**
         * @brief Check whether image saved on disk contains is thermal image with temperatures for every pixel.
         * @param path Path to image file.
         * @return True for thermal image.
         */
        static bool isRadiometricImage(const std::string & path);
        /**
         * @brief Check whether image saved on disk contains is thermal image with signal values or temperature for every pixel.
         * @param path Path to image file.
         * @return True for thermal image.
         */
        static bool isThermalImage(const std::string & path);
        /**
         * @brief Check whether image saved on disk contains is thermal image with signal values for every pixel.
         * @brief Check whether image saved on disk is super-resolution thermal image.
         * @param path Path to image file.
         * @return True for thermal image.
         * @return True for super-resolution thermal image.
         */
        static bool isSuperResolutionImage(const std::string & path);
        /**
         * @brief Extract info about location from thermal file.
         * @param path Path to image file.
         * @return Shared ptr to GPSInfo instance.
         */
        static std::shared_ptr<wtl::GPSInfo> extractGPSFromSource(const std::string & path);
    private:
        /**
         * @brief Returns default license path.
         * @return path
         */
        static std::string getDefualtLicensePath();
        /**
         * @brief Generate computer id to be used in licensing
         * @details Platform- dependent, on mac serial number is used
         * @return
         */
        static std::string getComputerID();

    };
    /**
          * @mainpage WWP Data SDK
          *
          * C++ library that provides interface for thermal images and sequences recorded by Workswell Thermal Cameras.\n
          * Developers can use this SDK to create aplications for loading, presenting and storing thermograms.\n
          * Supported radiometric cameras: Workswell Wiris Pro, Workswell Wiris Pro SC, Workswell Wiris Pro M200.\n
          * \n
          * Key Features:\n
          *     Load thermograms to display thermal data.\n
          *     Use provided palettes and modify ranges to enhance presentation of measured data.\n
          *     Read and change thermal parameters of radiometric files.\n
          *     Examine thermograms with regions of interests(ROI) and alarms.\n
          *     Load, play and export from sequences of thermal images.\n
          * \n
          * Start with class Center, which serves as library entrypoint. Load thermal files using methods of this class.\n
          * \n
          * Sample application which showcases usage of this SDK is available on GitHub public <a href="https://github.com/SoftwareWorkswell/wwp-data-sdk-sample">repository</a>.\n
          * \n
          * License Policy\n
          * Please activate your library copy before first use with provided licence serial number using function Center::activate.
          * Internet connection is required to activate the license.\n
          * Moreover, library needs to be authentificated by calling Center::authentificate before every use, for example during start of your application.\n
          * \n
          * Used third-party libraries: libjpeg, boost.\n
          * \n
          * @author Workswell, s.r.o ,support@workswell.eu
          * @version 0.3.0
          */
}

#endif /* CENTER_H */
