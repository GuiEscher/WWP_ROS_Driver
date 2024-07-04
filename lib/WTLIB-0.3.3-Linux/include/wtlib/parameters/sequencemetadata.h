#ifndef WTL_SEQUENCEMETADATA_H
#define WTL_SEQUENCEMETADATA_H

#include "sourcemetadata.h"

namespace wtl {

class SequenceMetaData : public SourceMetaData
{
public:
    SequenceMetaData(const SourceMetaData& sourceMeta, uint64_t fileSize, uint64_t frameSize);

    uint64_t getFrameSpan() const;
    uint64_t getFrameRate() const;
    uint64_t getDuration() const;
    uint64_t getFrameSize() const;
    uint64_t getFileSize() const;
    uint64_t getNumberOfFrames() const;

private:
    uint64_t m_FrameSize{};
    uint64_t m_TotalFrames{};

    friend class FFFFileManager;
};

} // namespace wtl

#endif // WTL_SEQUENCEMETADATA_H
