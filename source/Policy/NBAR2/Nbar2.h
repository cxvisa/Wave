/***************************************************************************
 *   Copyright (C) 2015      Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef NBAR2_H
#define NBAR2_H

#include "Framework/Types/Types.h"
#include "Policy/NBAR2/Nbar2Element.h"
#include "Policy/NBAR2/Nbar2Info.h"
#include "Policy/NBAR2/Nbar2Protocol.h"

#include <vector>
#include <string>
#include <set>

using namespace std;

namespace WaveNs
{

class Nbar2 : public Nbar2Element
{
    private :
        virtual  Nbar2Element *getNbar2ElementByName    (const string &nbar2ElementName);

                 void          computeProtocolByNameMap ();
                 bool          isAKnownProtocol         (const string &protocolName);
                 void          addToKnownProtocols      (const string &protocolName, Nbar2Protocol *pNbar2Protocol);

    protected :
    public :
                               Nbar2                    ();
        virtual               ~Nbar2                    ();

                void           load                     (const string &nbar2FileName);

        static  string         getAdjustedCategoryName  (const string &nbar2CategoryName, const string &nbar2SubCategoryName);

                set<string>    getAdjustedCategoryNames () const;

                set<string>    getAllProtocolNames      () const;

                Nbar2Protocol *getNbar2Protocol         (const string &protocolName);

    // Now the data members

    private :
        Nbar2Info                    m_info;
        vector<Nbar2Protocol *>      m_protocols;
        map<string, Nbar2Protocol *> m_protocolByNameMap;

    protected :
    public :
};

}

#endif // NBAR2_H

