/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Anil Channaveerasetty                                        *
 ***************************************************************************/

#ifndef MACRANGE_H
#define MACRANGE_H

#include "Framework/Types/Types.h"
#include <string>

using namespace std;

namespace WaveNs
{

class MACRange
{
    private:
            vector<string> parsingMacRange          (const string &rangeMacString) const;
            void           copy                     (const MACRange &rangeMac);
            void           copy                     (const string &rangeMacString);
    static  string         addOneElementToString    (bool &insertComma, string elem);
    static  string         addRangeToString         (bool &insertComma, string firstElem, string lastElem);
            bool           isUpperCase              (const char * lastValue) const;
    static  UI32           getRangeValueFromString  (string rangeMacString);
    protected:

    public:
                       MACRange                    ();
                       MACRange                    (const string &rangeMacString);
                       MACRange                    (const MACRange &rangeMac);
                       MACRange                    (const string &startValue, const string &endValue);
                                                  
            string     toString                    () const;
            void       fromString                  (const string &rangeMacString);
            ResourceId loadFromPlainString         (const string &rangeMacString);
            void       getMacRangeVector           (vector <string> &rangeMacVector) const;
            bool       operator ==                 (const MACRange &rangeMac) const;
            bool       operator !=                 (const MACRange &rangeMac) const;
            MACRange   &operator =                 (const MACRange &rangeMac);
    static  bool       isAValidString              (const string &rangeMAcString);
    static  string     getMacRangeStringFromVector (vector <string> &rangeMacVector);

    // now the data members
    private:
           string       m_MacRange;
};

}

#endif   //MACRANGE_H

