//
// ModelDatabase.h
//

#include "Common.h"

struct ModelEntry
{
    std::string hash;
    std::string name;
    std::vector<std::string> tags;
};

class ModelDatabase
{
public:
    void Init(const Parameters &params);

    std::vector<const ModelEntry*> TextQuery(const std::string &query) const;

    const ModelEntry& GetEntry(const std::string &modelHash) const;
    const std::map<std::string, ModelEntry>& Entries() const
    {
        return _entries;
    }

private:
    std::map<std::string, ModelEntry> _entries;
};
