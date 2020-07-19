/**
 * @file mega/attrmap.h
 * @brief Class for manipulating file attributes
 *
 * (c) 2013-2014 by Mega Limited, Auckland, New Zealand
 *
 * This file is part of the MEGA SDK - Client Access Engine.
 *
 * Applications using the MEGA API must present a valid application key
 * and comply with the the rules set forth in the Terms of Service.
 *
 * The MEGA SDK is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * @copyright Simplified (2-clause) BSD License.
 *
 * You should have received a copy of the license along with this
 * program.
 */

#ifndef MEGA_ATTRMAP_H
#define MEGA_ATTRMAP_H 1

#include "mega/utils.h"

namespace mega {

// maps attribute names to attribute values
struct attr_map : map<nameid, string> 
{
    attr_map() {}
    
    attr_map(nameid key, string value)
    {
        (*this)[key] = value;
    }

    attr_map(map<nameid, string>&& m)
    {
        m.swap(*this);
    }

    void applyUpdates(const attr_map& updates)
    {
        for (auto& u : updates)
        {
            if (u.second.empty()) erase(u.first);
            else operator[](u.first) = u.second;
        }
    }
};

struct MEGA_API AttrMap
{
    attr_map map;

    // compute rough storage size
    unsigned storagesize(int) const;

    // convert nameid to string
    static int nameid2string(nameid, char*);

    // convert string to nameid
    static nameid string2nameid(const char *);

    // export as JSON string
    void getjson(string*) const;

    // export as raw binary serialize
    void serialize(string*) const;

    // import raw binary serialize
    const char* unserialize(const char*, const char*);
};
} // namespace

#endif
