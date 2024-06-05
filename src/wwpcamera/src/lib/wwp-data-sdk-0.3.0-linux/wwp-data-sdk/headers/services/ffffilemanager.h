#ifndef FFFFILEMANAGER_H
#define FFFFILEMANAGER_H

#include </home/guilherme/wwpcamera/src/wwpcamera/src/lib/wwp-data-sdk-0.3.0-linux/wwp-data-sdk/headers/services/thermalfilemanager.h>
namespace wtl
{
/**
     * @brief FFF file format manager
     * @details Implements ThermalFileManager for FFF file format
     */
class FFFFileManager : public ThermalFileManager
{
    // definition for FFFFile
    // The following main tag types are defined
    enum class FFFTagID
    {
        Free = 0x00, Pixels = 0x01, GainMap = 0x02, OffsMap = 0x03, DeadMap = 0x04, GainDeadMap = 0x05, CoarseMap = 0x06, ImageMap = 0x07,
        RRMap = 0x08, OOMap = 0x09, OPMap = 0x0A, BackgrMap = 0x0B, ShutterMap = 0x0C, MMap = 0x0D, YCbCrPixels = 0x0E, FloatOffsMap  = 0x0F,
        DiffPixels = 0x10, GasOverlay = 0x11, CompressedBurst = 0x12, DistanceMap = 0x13, SubFlirFileHead = 0x1E,
        BasicData = 0x20, Measure = 0x21, ColorPal = 0x22, TextComment  = 0x23, VoiceComment  = 0x24, MeasureResult = 0x25,
        VisualMarker = 0x26, IRMarker = 0x27, ImageOverlay = 0x29, Alarm = 0x29, Fusion = 0x2A, GPS  = 0x2B, ExternalSensors = 0x2C,
        IncompBasicData = 0x30
    };
    // Tag sub-types
    enum class FFFTagSubID
    {
        PixelsBE,   // big endian
        PixelsLE,   // little endian
        PixelsPNG   // png compressed
    };
    // Measure function types
    enum class MFType
    {
        None, Spot, Box, Ellipse, Line, Cursos, Isotherm, Reference, Difference,
        Polyline, Polyarea, Script
    };

    // MFRmskEnum
    enum class MFRmsk
    {
        Temp, Max, Maxpos, Min, Minpos, Avg, Sdev, Median, Raw, Iso
    };

    // MFLOPmskEnum
    enum class MFLOPmsk
    {
        Emiss, Dist, Tamb, ShowLabel, ShowMaxMin
    };

    // MFIsoType
    enum class MFIsoType
    {
        Below, Above, Interval, FixScaleAbove, DualAbove, DualBelow,
        InvInterval, DewPoint, FixScaleBelow, Invalid
    };

    // MFIsoAttr
    enum class MFIsoAttr
    {
        Solid, Transparent, Follow_y, Attr_invalid
    };

    // MFIsoCol
    enum class MFIsoCol
    {
        Palette_1, Palette_2, Red, Green, Blue, Yellow, Cyan, Magneta, Gray, Palette, YCbCr
    };

    // MFIsoVal
    enum class MFIsoVal
    {
        Signal, ValTemp
    };

    // MFIsoVersion
    enum class MFIsoVersion
    {
        Version102, Version103
    };

    // MFScriptType
    enum class MFScriptType
    {
        MFScript
    };

    // MFPropType
    enum class MFPropType
    {
        None, PCSymCol, PCThreshold, PCDeltaT
    };
    /**
        * A radiometric JPEG is a standard JPEG with a FFF-file inserted in the APP1-tag.
        */
    struct app1_tag_struct {
        //uint16_t length; //* Total APP1 field byte count, including the byte count value itself, but excluding the APP1 marker.
        uint8_t identifier[5]; //* ’F’, ’L’, ’I’, ’R’, 00h
        uint8_t version; //* Version number. 1 initially and changed when FFF format or Application tag is changed.
        uint8_t sequence[2]; //* First byte is sequence number of this block (first block is 0).Second byte is sequence number of last block (first block is 0). The value 0000 will then correspond to one single block. If two blocks are used, these will have the numbers 0001h and 0101h. FFF file as specified below.
    };

    /**
        * The “FFF” format has all its tag location information in the general header.
        */
    struct fff_general_header {
        char formatID[4]; //* char[4]. Fileformat ID 'FFF\0
        char origin[16]; //* char[16]. File origin
        uint32_t version; //* ULONG. File format version
        uint32_t indexOff; //* ULONG. Pointer to indexes
        uint32_t numUsedIndex; //* ULONG. Number of indexes
        uint32_t nextID; //* ULONG. Next free index ID
        uint16_t swapPattern; //* USHORT. Swap pattern (0=MSBF)
        uint16_t spare[7]; //* USHORT[7]. Spare
        uint32_t reserved[2]; //* ULONG[2]. Reserved
        uint32_t checksum; //* ULONG. Head & index checksum
    };

    /**
        * Data structure for tag description
        */
    struct fff_tag_struct {
        uint16_t mainType; //* USHORT. Main type. Value taken from tag types macros
        uint16_t subType; //* USHORT. Sub-type
        uint32_t version; //* ULONG. Version for data
        uint32_t indexID; //* ULONG. Index ID
        uint32_t dataPtr; //* ULONG. Pointer to data
        uint32_t dataSize; //* ULONG. Size of data
        uint32_t parent; //* ULONG. Parent number
        uint32_t objectNr; //* ULONG. This object number
        uint32_t checksum; //* ULONG. Data checksum
    };

    /**
        * Pixel data tag: The data block for a map or an image contains a geometric info data structure followed by the pixel data itself.
        */
    struct fff_geometric_info {
        uint16_t pixelSize; //* USHORT. Size of one pixel in bytes. Normal size is 2 bytes
        uint16_t imageWidth; //* USHORT. Image width in pixels
        uint16_t imageHeight; //* USHORT. Image height in pixels
        uint16_t upperLeftX; //* USHORT. X and Y coordinates for upper left corner relative original in case this image is a cutout. Normally 0
        uint16_t upperLeftY;
        uint16_t firstValidX; //* USHORT. The following four numbers identifies the valid pixels area within the image. Normally 0
        uint16_t lastValidX; //* USHORT. Normally imageWidth - 1
        uint16_t firstValidY;  //* USHORT. Normally 0
        uint16_t lastValidY; //* USHORT. Normally imageHeight - 1
        uint16_t detectorDeep; //* USHORT. Number of bits from detector
        uint16_t detectorID; //* USHORT. Type of detector
        uint16_t upSampling; //* USHORT. Type of upsampling from detector to IR pixels: none = 0, copy XY = 1, interpolate X copy Y = 3, copy X interpolate Y = 4
        uint16_t frameCtr; //* USHORT. Image number from framebuffer
        uint16_t minMeasRadius; //* USHORT. Determines minimum inclusive circle for a valid spot measurement: 0 = undefined, 1 = 1 pixel, 2 = circle with diam=3, etc
        uint8_t stripeFields; //* UCHAR. Number of striped fields this image
        uint8_t reserved; //* USHORT. Reserved, normally 0
        uint16_t WWRecalculated; //* 0: not Recalculated; 1: recalculation started; 2: recalculated done
    };

    /**
        * Data structure for object parameters
        */
    struct fff_object_parameters {
        float emissivity; //* float. Emissivity (0-1)
        float objectDistance; //* float. Object distance [meters]
        float ambTemp; //* float. Ambient temperature [K] // For our purposses background temperature
        float atmTemp; //* float.  Atmosphere temperature [K]
        float extOptTemp; //* float. External optics temperature [K]
        float extOptTransm; //* float. External optics transmission (0-1)
        float estAtmTransm; //* float. Estimated atmosphere transm. (0-1)
        float relHum; //* float. Relative humidity
        float reserved[4]; //* long[4]. Reserved
    };

    /**
        * Data structure for calibration parameters
        */
    struct fff_calib_parameters {
        uint32_t typeOfPixelValues; //* long. Type of pixel values: 0 = pixValUndef, 1 = pixValRawPix, 2 = pixValAbsPix, 10 = pixValGainMap, 11 = pixValOffsMap, 12 = pixValCoarseMap, 20 = pixValEmisMap, 21 = pixValAmbMap
        char unitOfPixelValues[4]; //* char[4]. 3 letter abbreviation of the pixel values
        float R; //* float. Calibration constant R
        float B; //* float.  Calibration constant B
        float F; //* float. Calibration constant F
        uint32_t wbRBFinUse; //* long. Spare RBF calib constants
        float wbRBFspare[2]; //* float[2]. Spare RBF calib constants
        float alpha1; //* float. Attenuation for atmosphere without water vapour
        float alpha2; //* float. Attenuation for atmosphere without water vapour
        float beta1; //* float. Attenuation for water vapour
        float beta2; //* float. Attenuation for water vapour
        float X; //* float. Scaling factor for attenuation
        float alfaBetaSpare[2]; //* float[2]. Spare attenuation
        float tminSpanAuto; //* float. Min span [K] (auto adjust)
        float tmax; //* float. Upper temp limit [K] when calibrated for current range
        float tmin; //* float. Lower temp limit [K] when calibrated for current range
        float tmaxClip; //* float. Upper temp limit [K] over which the calibration becomes invalid
        float tminClip; //* float. Lower temp limit [K] under which the calibration becomes invalid
        float tmaxWarn; //* float. Upper temp limit [K] over which the calibration soon will become invalid
        float tminWarn; //* float. Lower temp limit [K] under which the calibration soon will become invalid
        float tmaxSaturated; //* float. Upper temp limit [K] over which pixels should be presented with overflow color
        float tminSaturated; //* float. Lower temp limit [K] under which pixels should be presented with underflow col
        float tminSpan; //* float. Min span [K] (manual adjust)
        int16_t presPrec; //* short. Presentation precision (# of decimals)
        uint16_t specAccuracy; //* USHORT. per mille (50 = 5%), 0 = unknown
        uint16_t specRepeatability; //* USHORT. per mille (50 = 5%), 0 = unknown
        uint16_t calibMode; //* USHORT. Bit field for calibration
        uint16_t amendMode; //* USHORT. Reveals if the calibration is original or amended by some lens/filter calibration
        uint16_t wreserved; //* USHORT. Reserved
        float reserved[5]; //* long[5]. Reserved
    };

    /**
        * Data structure for optics info
        */
    struct fff_optics_info {
        //uint8_t not_defined[124]; //124
        uint8_t not_defined0[4];
        uint8_t descr[32]; // Filter description "130" or "65" in tenth of mm
        uint8_t not_defined1[66];
        uint16_t lensLength; // Lens focal length in tenth of mm
        uint8_t not_defined2[20];
    };

    /**
        * Data structure for calib info
        */
    struct fff_calib_info {
        char camera_name[32]; //* char[32]. Camera type
        char camera_artn[16]; //* char[16]. Camera part #
        char camera_sn[16]; //* char[16]. Camera serial #
        char camera_progver[16]; //* char[16]. Program version
        char calib_title[32]; //* char[32]. Calibration title
        char arc_ver[8]; //* char[8]. Arc file version
        char arc_date[16]; //* char[16]. Arc date/time
        char arc_sign[8]; //* char[8]. Arc signature
        char country_code[8]; //* char[8]. Country code
        struct fff_optics_info lens; //* OPTICS_INFO_T. Camera type
        struct fff_optics_info filter; //* OPTICS_INFO_T. Camera type
        struct fff_optics_info additional; //* OPTICS_INFO_T. Camera type
        uint8_t lFuncRestrictionMask1[4]; //* ULONG. Forbidden things
        uint8_t lFuncRestrictionMask2[4]; //* ULONG. Forbidden things
        uint8_t reserved[32]; //* long[8]. Reserved

    };

    /**
        * Data structure for adjust parameters
        */
    struct fff_presentation_parameters {
        int level;
        int span;
        uint8_t not_defined[40];
    };

    /**
        * Data structure for presentation parameters
        */
    struct fff_adjust_parameters {
        int normOffset; // Temperature compensation offset (globalOffset)
        float normGain; // Temperature compensation gain (globalGain)
        uint16_t ipixUnderflow; // Image pixel underflow limit
        uint16_t ipixOverflow; // Image pixel overflow limit
        uint8_t not_defined[36];
    };

    /**
        * Data structure for display parameters
        */
    struct fff_display_parameters {
        float yxPixRatio; //* float. y/x pixel size for non square pixels
        float zoomFactor; //* float. Zoom factor, 1.0 = normal size
        int16_t xpanVal; //* short. Pan is calculated as offset from center in Frame buffer pixels. Positive values moves image right/down. 0, 0 is centered picture
        int16_t ypanVal; //* short
        int16_t flipVal; //* short. Image pixeldata is flipped: 0 = No flip, 1 = X-axis flipped, 2 = Y-axis flipped, 3 = X & Y-axes flipped
        int16_t pad; //* short. Pad
        uint8_t reserved[12]; //* long[3]. Reserved
    };

    /**
        * Data structure for image info
        */
    struct fff_image_info {
        uint32_t imageTime; //* ULONG. Time in seconds since 1970-01-01 00:00 (UTC)
        uint32_t imageMilliTime; //* ULONG. Milliseconds since last sec.
        int16_t timeZoneBias; //* short. Time zone bias in minutes UTC = local + bias
        int16_t swReserved1; //* short.
        uint32_t focusPos; //* long. Focus pos as counter value
        float fTSTemp[7]; //* float[7]. Temperatures in degrees Celsius [C]. 0 = TAU2 Core temp, 1 = TAU2 lens temp, 2. = WIRIS inner sensor temp
        float fTSTempExt[4]; //* float[4]. For lens to K
        uint16_t trigInfoType; //* USHORT. 0 = No info, 1 = THV900
        uint16_t trigHit; //* USHORT. hit count - microsecs from trig reference
        uint16_t trigFlags; //* USHORT.
        uint16_t reserved1; //* USHORT.
        uint32_t trigCount; //* ULONG.
        int16_t manipulType; //* short.
        int16_t manipFactors[5]; //* short[5].
        int32_t detectorPars[20]; //* long[20].
        uint32_t reserved[5]; //* long[5]. [20 bytes]. 0 = ms since last NUC
    };

    /**
        * Data structure for distribution data
        */
    struct fff_distribution_data {
        uint16_t imageFreq1; // Frequency of sequence
        uint8_t not_defined1[38];
        uint16_t imageFreq2;
        uint8_t not_defined2[22];
    };

    /**
        * Data structure for distribution data
        */
    struct fff_extended_image_info {
        uint8_t not_nefined[960];
    };

    /**
        * Data structure for distribution data
        */
    struct fff_waveband_RBF_parameters {
        uint8_t not_nefined[320];
    };

    /**
        * Data structure for extended presentation parameters
        */
    struct fff_extended_presentation_paramerers {
        uint8_t not_nefined[48];
    };

    /**
        * Data structure for basic image data
        */
    struct fff_basic_data {
        struct fff_geometric_info geometricInfo;
        struct fff_object_parameters objectParameters;
        struct fff_calib_parameters calibParameters;
        struct fff_calib_info calibInfo;
        struct fff_adjust_parameters adjustParameters;
        struct fff_presentation_parameters PresentParameters;
        struct fff_display_parameters DisplayParameters;
        struct fff_image_info ImageInfo;
        struct fff_distribution_data DistributionData;
        //struct fff_extended_image_info ExtendedImageInfo;
        //struct fff_waveband_RBF_parameters wbRBFParameters;
        //struct fff_extended_presentation_paramerers ExtPresentParameters;
    };

    // 1.05 Y Cb Cr
    struct fff_color_pal {
        uint16_t NoOfColors; // Number of palette colors
        uint16_t NoOfConstants; // Number of palette constants
        uint8_t Reversed; // 0 = white hot, 1 = black hot
        uint8_t UseExtremes; // 0 = Values outside span uses high/low color 1 = Use Above/below colors
        uint8_t AboveSpanColorY; // The color used for pixels that are above the span
        uint8_t AboveSpanColorCr;
        uint8_t AboveSpanColorCb;
        uint8_t BelowSpanColorY; // The color used for pixels that are above the span
        uint8_t BelowSpanColorCr;
        uint8_t BelowSpanColorCb;
        uint8_t OverflowColorY; // The color used for pixels that have a value beyond the overflow limit
        uint8_t OverflowColorCr;
        uint8_t OverflowColorCb;
        uint8_t UnderflowColorY; // The color used for pixels that have a value below the underflow limit
        uint8_t UnderflowColorCr;
        uint8_t UnderflowColorCb;
        uint8_t IsothermColor1Y; // The color used for Isotherm 1
        uint8_t IsothermColor1Cr;
        uint8_t IsothermColor1Cb;
        uint8_t IsothermColor2Y; // The color used for Isotherm 2
        uint8_t IsothermColor2Cr;
        uint8_t IsothermColor2Cb;
        uint8_t noLongerUsed1;
        uint8_t noLongerUsed2;
        uint8_t Method; // 0 = Plain color, 1 = JPEG fixed LUT
        uint8_t Stretch;
        uint16_t swapPattern; // Swap pattern (= 0x0035)
        uint8_t Reserved[18];
        char Filename[32]; // Palette file name
        uint8_t Description[32]; // Palette description
        uint8_t PaletteColors[256][3];
    };

    struct fff_gps_data {
        uint32_t dataValid = 0; // 1 = Tag data is valid
        char VersionID[4]; // EXIF Tag 0
        char LatitudeRef[2]; // EXIF Tag 1
        char LongitudeRef[2]; // EXIF Tag 3
        char AltitudeRef; // EXIF Tag 5
        uint8_t Reserved1[3];
        double Latitude; // EXIF Tag 2
        double Longitude; // EXIF Tag 4
        float Altitude; // EXIF Tag 6
        uint32_t TimeStamp; // EXIF Tag 7
        char Satellites[20]; // EXIF Tag 8
        char Status[2]; // EXIF Tag 9
        char MeasureMode[2]; // EXIF Tag 10
        float DOP; // EXIF Tag 11
        char SpeedRef[2]; // EXIF Tag 12
        char TrackRef[2]; // EXIF Tag 14
        char ImgDirectionRef[2]; // EXIF Tag 16
        uint16_t Reserved2;
        float Speed; // EXIF Tag 13
        float Track; // EXIF Tag 15
        float ImgDirection; // EXIF Tag 17
        char MapDatum[20]; // EXIF Tag 18
        char DestLatitudeRef[2]; // EXIF Tag 19
        char DestLongitudeRef[2]; // EXIF Tag 21
        char DestBearingRef[2]; // EXIF Tag 23
        char DestDistanceRef[2]; // EXIF Tag 25
        uint32_t Reserved3;
        double DestLatitude; // EXIF Tag 20
        double DestLongitude; // EXIF Tag 22
        float DestBearing; // EXIF Tag 24
        float DestDistance; // EXIF Tag 26
        char ProcessingMethod[10]; // EXIF Tag 27
        char AreaInformation[10]; // EXIF Tag 28
        char DatumStamp[11]; // EXIF Tag 29
        uint8_t reserved4[1];
        uint16_t Differential;
        uint16_t swapPattern;
        uint8_t reserved5[4];
    };

    // Measurement tags
    struct fff_measure_header {
        uint16_t endianTest;
        uint16_t firstFuncOffset;
        uint16_t funcDefHdrSize;
        uint16_t minMeasRadius;
        uint16_t reserved1;
        uint16_t reserved2;
    };

    struct fff_measure_function_header {
        uint16_t nextFuncOffset;
        uint16_t typeDepFormatRev;
        uint16_t typeDepDataSize;
        uint16_t labelSize;
        uint16_t propOffset;
        uint16_t measFuncType;
        uint16_t measFuncId;
        uint16_t ownerFuncType;
        uint16_t ownerFuncId;
        uint16_t measCalcMask;
        uint16_t measPrioRes;
        uint16_t localParamMask;
        float emiss;
        float dist;
        float tAmb;
    };

    struct fff_spot_func_def {
        int16_t x;
        int16_t y;
    };

    struct fff_box_func_def {
        int16_t x;
        int16_t y;
        int16_t width;
        int16_t height;
    };

    struct fff_ellipse_func_def {
        int16_t xcentre; // Ellipse centre x in framebuffer pixels
        int16_t ycentre; // Ellipse centre y in framebuffer pixels
        int16_t x1; // Ellipse major x in framebuffer pixels
        int16_t y1; // Ellipse major y in framebuffer pixels
        int16_t x2; // Ellipse minor x in framebuffer pixels
        int16_t y2; // Ellipse minor y in framebuffer pixels
    };

    struct fff_line_func_def {
        int16_t xstart;
        int16_t ystart;
        int16_t xend;
        int16_t yend;
    };

    struct fff_cursor_func_def {
        uint64_t absPos;
    };

    struct fff_isotherm_func_def102 {
        uint16_t type;
        uint16_t attr;
        uint16_t color;
        uint16_t valType;
        float high;
        float low;

    };

    struct fff_isotherm_func_def103 {
        uint16_t type;
        uint16_t attr;
        uint16_t color;
        uint16_t valType;
        float high;
        float low;
        uint8_t colY;
        uint8_t colCb;
        uint8_t colCr;
        uint8_t reserved[13];

    };

    struct fff_reference_func_def {
        float referenceValue;
    };

    struct fff_difference_func_def {
        uint16_t funcTypeA;
        uint16_t funcIdA;
        uint16_t funcResA;
        uint16_t funcTypeB;
        uint16_t funcIdB;
        uint16_t funcResB;
    };

    struct fff_polypt_def {
        int16_t x;
        int16_t y;
    };

    struct fff_poly_func_def {
        uint16_t numPoints;
        uint16_t firstPointOffset;
        uint16_t pointDataSize;
        uint16_t fill;
    };

    struct fff_script_func_def {
        uint64_t type;
        uint64_t codeOffset;
        uint64_t codeSize;
        uint64_t fill;
    };

    struct fff_property_func_def {
        uint16_t type;
        uint16_t nextProp;
    };

    struct fff_measure_functions {
        fff_measure_function_header header;
        void * data;
    };

    struct fff_file_struct {
        uint8_t *dataPtr;
        size_t dataSize;
    };

    // constatnt static member variables
    static const unsigned s_generalHeaderSize = sizeof(struct fff_general_header);
    static const unsigned s_tagStructSize = sizeof(struct fff_tag_struct);
    static const unsigned s_basicDataSize = sizeof(struct fff_basic_data);
    static const unsigned s_geometricInfoSize = sizeof(struct fff_geometric_info);
    static const unsigned s_colorPaletteSize = sizeof(struct fff_color_pal);
    static const unsigned s_GPSDataSize = sizeof(struct fff_gps_data);
    static const int s_numberOfTags = 16; // Total number of tags
    static const int s_version = 0x100;

public:
    /**
        * @brief Load image from the disk and save it to ThermalImage instance
        * @param[out] image Empty radiometric image instance
        * @param[in] path Path to source thermal file.
        */
    bool loadImageRadiometric(ImageRadiometric & image, const std::string & path) const;
    /**
    * @brief Load image from the disk and save it to ThermalImage instance
    * @param[out] image Empty radiometric image instance
    * @param[in] path Path to source thermal file.
    */
    bool loadImageRadiometric(ImageRadiometric & image, SourceMetaData & metaData, uint16_t * dataPtr) const;
    /**
        * @brief Save radiometric image.
        * @param[in] image Source radiometric image instance.
        * @param[in] path Target path
        */
    bool saveImageRadiometric(const ImageRadiometric & image, const std::string & path) const;
    /**
     * @brief saveImageRadiometricWithCustomJPEG
     * @param image
     * @param imageData
     * @param path
     * @return
     */
    bool saveImageRadiometricWithCustomJPEG(const ImageRadiometric & image, uint8_t * imageData, const std::string & path) const;
    /**
     * @brief loadImageRadiometric
     * @param image
     * @param path
     * @return
     */
    bool loadSequenceRadiometric(SequenceRadiometric & sequence, const std::string & path) const;
    /**
         * @brief Save radiometric sequence.
         * @param path Absolute location on a disk where the sequence should be saved.
         * @param sequence ThermalSequence instance which will be saved to file.
         */
    bool saveSequenceRadiometric(const SequenceRadiometric & sequence, const std::string & path) const;
    /**
         * @brief Cut sequence and save it.
         * @param sequence ThermalSequence instance which will be saved to file.
         * @param from First frame included in a saved sequence.
         * @param to Last frame included in a saved sequence.
         * @param path Absolute location on a disk where the sequence should be saved.
         */
    bool savePartOfSequenceRadiometric(const SequenceRadiometric & sequence, int from, int to, const std::string & path) const;
    /**
         * @brief saveFramesAsSequence Save provided radiometric images(frames) as sequence.
         * @param meta Sequence meta data
         * @param calib Sequence calibration parameters
         * @param frames Sequence Frames
         * @param path Destination path
         * @return True for success
         */
    bool saveFramesAsSequence(const wtl::SequenceMetaData & meta, const wtl::CalibrationParameters calib, std::vector< std::shared_ptr< ImageRadiometric > > & frames, const std::string & path);
    /**
         * @brief isRadiometricImage
         * @param path
         * @return
         */
    bool isRadiometricImage(const std::string & path) const;
    /**
     * @brief wtl::FFFFileManager::isRawmage
     * @param path
     * @return
     */
    bool isRawImage(const std::string & path) const;

    bool extractRadiometricSequenceFrame(ImageRadiometric & frame, const SequenceRadiometric & sequence, int index) const;
    /**
         * @brief Check whether image saved on disk is super-resolution thermal image.
         * @param path Path to image file.
         * @return True for super-resolution thermal image.
         */
    bool isSuperResolutionImage(const std::string & path) const;
    /**
         * @brief Extract info about location from thermal file.
         * @param path Path to image file.
         * @return Shared ptr to GPSInfo instance.
         */
    std::shared_ptr<wtl::GPSInfo> extractGPSFromSource(const std::string & path) const;
private:
    /* --------------------------------------------------------------------------------------------------------- */
    // OPENING IMAGES

    /**
        * @brief Extract data from fff file to radiometric image instance
        */
    bool extractFFFFile(ImageRadiometric & thermalImage, std::shared_ptr<fff_file_struct> fffFile, int & fffFileSize) const;
    /**
         * @brief extractFFFFileTag of radiometric image
         * @param thermalImage
         * @param fffFile
         * @param tagHeader
         */

    void extractFFFFileTag(ImageRadiometric & thermalImage, std::shared_ptr<fff_file_struct> fffFile, const fff_tag_struct & tagHeader) const;
    /**
         * @brief extractBasicDataTag
         * @details Extract just metadata - for both radiometric and raw
         * @param thermalImage
         * @param basicData
         */
    void extractBasicDataTag(ThermalImage & thermalImage, fff_basic_data & basicData) const;
    /**
         * @brief extractBasicDataTag
         * @details Extract thermal params from basic tag - just radiometric
         * @param thermalImage
         * @param basicData
         */
    void extractThermalFromBasicDataTag(ImageRadiometric & thermalImage, const fff_basic_data & basicData) const;

    void extractCalibFromBasicDataTag(ThermalImage & thermalImage, const fff_basic_data & basicData) const;
    /**
         * @brief Extract one measure function and save it to thermalimage instance
         */
    void extractMeasureFunction(ImageRadiometric & thermalImage, const fff_measure_functions & function) const;

    void extractAlarmFromMeasureFunction(ImageRadiometric & thermalImage, const fff_measure_functions & function) const;

    void extractGPSInfo(ThermalImage & thermalImage, const fff_gps_data & gpsData) const;
    /* --------------------------------------------------------------------------------------------------------- */
    // SAVING IMAGES
    /**
     * @brief Create file and save data from ThermalImage with radiometric data to it.
     */
    void createFFFFile(const ImageRadiometric & thermalImage, fff_file_struct * fffFile) const;
    /**
     * @brief compressAndSaveJPEG
     * @param path
     * @param fffFileVect
     */
    bool compressAndSaveJPEG(const ThermalImage & image, const char * path, fff_file_struct * fffFile,int sizeOfFFF) const;
    /**
         * @brief compressAndSaveJPEG
         * @param image
         * @param imageData
         * @param path
         * @param fffFile
         * @param sizeOfFFF
         * @return
         */
    bool compressAndSaveJPEG(const ThermalImage & image, uint8_t * imageData, const char * path, fff_file_struct * fffFile, int sizeOfFFF) const;

    /**
    * @brief Load App1Tag based on camera type
    * @param app1Tag
    */
    void loadApp1Tag(app1_tag_struct & app1Tag) const;
    /**
                 * @brief Load empty tag
                 * @param emptyTag
                 */
    void loadEmptyTag(fff_tag_struct & emptyTag) const;
    /**
                 * @brief Load pixel data tag based on constants and header size
                 * @param pixelDataTag
                 */
    void loadPixelDataTag(int imageSize, fff_tag_struct & pixelDataTag) const;
    /**
                 * @brief Load basic data tag
                 * @param basicDataTag
                 */
    void loadBasicDataTag(int imageSize, fff_tag_struct & basicDataTag) const;
    /**
                 * @brief Load color palette tag from file
                 * @param colorPaletteTag
                 */
    void loadColorPaletteTag(int imageSize, fff_tag_struct & colorPaletteTag) const;
    /**
                 * @brief Load gps data tag
                 * @param GPSDataTag
                 */
    void loadGPSDataTag(int imageSize, fff_tag_struct & GPSDataTag) const;
    /**
                 * @brief Load measure data tag
                 * @param measureDataTag
                 */
    void loadMeasureDataTag(int imageSize, fff_tag_struct & measureDataTag) const;
    /**
                 * @brief Load visible pixels tag
                 * @param visiblePixelsTag
                 */
    void loadVisiblePixelsTag(const ImageRadiometric & image, fff_tag_struct & visiblePixelsTag) const;
    /**
                 * @brief Load measure header
                 * @param measureHeader
                 */
    void loadMeasureHeader(fff_measure_header & measureHeader) const;
    /**
                 * @brief Load geometric info
                 * @param geometricInfo
                 */
    void loadGeometricInfo(const ThermalImage & image, fff_geometric_info & geometricInfo) const;
    /**
                 * @brief Load basic data
                 * @param basicData
    */
    void loadVisibleGeometricInfo(const ThermalImage & thermalImage, fff_geometric_info & visibleGeometricInfo) const;
    /**
                 * @brief Load general header
                 * @param generalHeader
                 */
    void loadGeneralHeader(const ThermalImage & image, fff_general_header & generalHeader) const;
    /**
     * @brief Load data from an radiometric image to the basic data struct
     * @param image
     * @param basicData
     */
    void loadThermalBasicData(const ImageRadiometric & image, fff_basic_data & basicData) const;
    /**
     * @brief Load data from an raw image to the basic data struct
     * @param image
     * @param basicData
     */
    void loadBasicData(const ThermalImage & image, fff_basic_data * basicData) const;
    /**
     * @brief loadBasicData
     * @param image
     * @param basicData
     */
    void loadColorPal(const ThermalImage & image, fff_color_pal & colorPal) const;
    /**
     * @brief loadGPSData
     * @param image
     * @param gpsData
     */
    void loadGPSData(const ImageRadiometric & image, fff_gps_data & gpsData) const;
    /**
     * @brief Load rois from image to list of fff measure functions for saving
     * @param image
     * @param listOfRois
     */
    void loadRoiData(const ImageRadiometric & image, std::vector<fff_measure_functions> & listOfRois, int & measureDataSize) const;
    /**
     * @brief Load alarms from image to list of fff measure functions for saving
     * @param image
     * @param listOfRois
     */
    void loadAlarmData(const ImageRadiometric & image, std::vector<fff_measure_functions> & listOfRois, int & measureDataSize) const;

    void setCustomMeasurementParameters(const uint16_t *localParamMask, std::shared_ptr<RoiStruct> roi,const fff_measure_function_header & header) const;
    /* --------------------------------------------------------------------------------------------------------- */
    // ENDIAN SWAPS
    /**
        * @brief Swap endian in general header
        */
    static void swapGeneralHeader(fff_general_header & generalHeader);
    /**
         * @brief Swap endians in tag header
         * @param tag header
         */
    static void swapTagHeader(fff_tag_struct & tagHeader);
    /**
         * @brief Swap endians in basic data
         * @param basic data
         */
    static void swapBasicData(fff_basic_data & basicData);
    /**
         * @brief Swap endians in geometric info
         * @param geometric info
         */
    static void swapGeometricInfo(fff_geometric_info & geometricInfo);
    /**
         * @brief Swap endians in gps data
         * @param gps data
         */
    static void swapGPSData(fff_gps_data & gps);
    /**
         * @brief Swap endians in color palette
         * @param color palette
         */
    static void swapColorPal(fff_color_pal & colorPal);
    /**
         * @brief Swap endians in measure header
         * @param mesure header
         */
    static void swapMeasureHeader(fff_measure_header & measureHeader);
    /**
         * @brief Swap endians in measure function header
         * @param measure function header
         */
    static void swapMeasureFunctionHeader(fff_measure_function_header & measureFunctionHeader);
    //swap of endians
    static uint16_t bswap16(uint16_t n);
    static uint32_t bswap32(uint32_t n);
    static uint64_t bswap64(uint64_t n);
    static float  bswapF( const float inFloat);
    static double bswapD( const double inDouble);

};
}
#endif // FFFFILEMANAGER_H
