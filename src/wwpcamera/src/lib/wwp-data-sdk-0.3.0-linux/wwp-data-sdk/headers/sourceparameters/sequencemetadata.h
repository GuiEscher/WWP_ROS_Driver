#ifndef SEQUENCEMETADATA_H
#define SEQUENCEMETADATA_H

#include </home/guilherme/wwpcamera/src/wwpcamera/src/lib/wwp-data-sdk-0.3.0-linux/wwp-data-sdk/headers/sourceparameters/sourcemetadata.h>

namespace wtl
{
    /**
     * @brief Derived class for sequence metadata
     *
     */
    class SequenceMetaData : public SourceMetaData
    {
        friend class FFFFileManager;
        int m_CurrentTime;  // in miliseconds
       // int m_FrameRate;    // number of frames per second frame rate is saved in img freq
        int m_FileSize;     // total file size in bytes
        int m_FrameSize;    // size of one frame in bytes
        int m_TotalFrames;
    public:
        SequenceMetaData();
        /**
         * @brief Sequence frame span.
         * @return Duration of one frame of sequence in miliseconds.
         */
        int getFrameSpan() const;
        /**
         * @brief Sequence frame rate.
         * @return Number of frames per second.
         */
        int getFrameRate() const;
        /**
         * @brief Total sequence duration.
         * @return Sequence duration in miliseconds.
         */
        int getDuration() const;
        /**
         * @brief Sequence Frame Size.
         * @return Size of one frame in bytes.
         */
        int getFrameSize() const;
        /**
         * @brief Sequence file size.
         * @return Size of while file in bytes.
         */
        int getFileSize() const;
        /**
         * @brief Number of frames sequence constists of.
         * @return Number of frames.
         */
        int getNumberOfFrames() const;
    private:
        void setFrameSize(int val);

        void setFileSize(int val);

        void setNumberOfFrames(int val);

    };
}
#endif // SEQUENCEMETADATA_H
