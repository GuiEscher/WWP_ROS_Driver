#ifndef THERMALSEQUENCE_H
#define THERMALSEQUENCE_H

#include "wtlib/wtlib_export.h"
#include "wtlib/sources/thermalsource.h"
#include "wtlib/parameters/sequencemetadata.h"

#include <memory>

namespace wtl {

class ThermalImage;
class ThermalSequenceImpl;

class WTLIB_EXPORT ThermalSequence final : public ThermalSource
{
    const std::shared_ptr<ThermalSequenceImpl> m_impl;

public:
    ThermalSequence(const std::shared_ptr<ThermalSequenceImpl>& impl);
    ~ThermalSequence();

    static std::shared_ptr<ThermalSequence> load(const std::string& path);
    bool save(const std::string& path) const;
    bool save(const std::string& path, int from, int to) const;

    std::shared_ptr<ThermalImage> at(size_t index, bool sequential = true) const;

    /** ThermalSource interface **/
    const SequenceMetaData& getMetadata() const override;
    SequenceMetaData& getMetadata() override;
    const std::shared_ptr<ThermalSourceImpl> getImpl() const override;
};

} // namespace wtl

#endif // THERMALSEQUENCE_H
