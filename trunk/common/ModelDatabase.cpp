//
// ModelDatabase.cpp
//

#include "Common.h"

const ModelEntry& ModelDatabase::GetEntry(const std::string &modelHash) const
{
    return _entries.find(modelHash)->second;
}

void ModelDatabase::Init(const Parameters &params)
{
    std::cout << "Initializing model database\n";

    const std::string fieldsDirectory = params.databaseDirectory + "fields/";
    
    auto nameLines = Utility::GetFileLines(fieldsDirectory + "names.txt", 2);
    auto tagLines  = Utility::GetFileLines(fieldsDirectory + "tags.txt", 2);
    
    for(auto nameLineIterator = nameLines.begin(); nameLineIterator != nameLines.end(); nameLineIterator++)
    {
        const std::string &curLine = *nameLineIterator;
        auto parts = Utility::PartitionString(curLine, "|");
        
        ModelEntry &curEntry = _entries[parts[0]];
        curEntry.hash = parts[0];
        curEntry.name = parts[1];
    }

    for(auto tagLineIterator = tagLines.begin(); tagLineIterator != tagLines.end(); tagLineIterator++)
    {
        const std::string &curLine = *tagLineIterator;
        auto parts = Utility::PartitionString(curLine, "|");
        
        ModelEntry &curEntry = _entries[parts[0]];
        for(unsigned int partIndex = 1; partIndex < parts.size(); partIndex++)
        {
            curEntry.tags.push_back(parts[partIndex]);
        }
    }
}

std::vector<const ModelEntry*> ModelDatabase::TextQuery(const std::string &query) const
{
    if(query == "@")
    {
        srand(time(NULL));
        std::cout << "No text query specified, returning all models in random order\n";
    }
    else
    {
        std::cout << "Sorting models, query=" << query << '\n';
    }

    struct Entry
    {
        const ModelEntry *entry;
        float value;
    };
    struct EntrySorter
    {
        bool operator()(const Entry &a, const Entry &b) const
        {
            return (a.value > b.value);
        }
    };
    EntrySorter sorter;

    std::vector<Entry> allEntries;
    for(auto entryIterator = _entries.begin(); entryIterator != _entries.end(); entryIterator++)
    {
        Entry newEntry;
        newEntry.entry = &entryIterator->second;
        if(query == "@")
        {
            newEntry.value = float(rand());
        }
        else
        {
            newEntry.value = 0.0f;

            if(newEntry.entry->name.find(query) != std::string::npos)
            {
                newEntry.value += 10.0f;
                if(newEntry.entry->name.length() == query.length())
                {
                    newEntry.value += 10.0f;
                }
            }
            for(auto tagIterator = newEntry.entry->tags.begin(); tagIterator != newEntry.entry->tags.end(); tagIterator++)
            {
                const std::string &curTag = *tagIterator;
                if(curTag.find(query) != std::string::npos)
                {
                    newEntry.value += 1.0f;
                    if(curTag.length() == query.length())
                    {
                        newEntry.value += 1.0f;
                    }
                }
            }
        }
        allEntries.push_back(newEntry);
    }

    std::sort(allEntries.begin(), allEntries.end(), sorter);

    std::vector<const ModelEntry*> result;
    for(auto entryIterator = allEntries.begin(); entryIterator != allEntries.end(); entryIterator++)
    {
        result.push_back(entryIterator->entry);
    }
    return result;
}
