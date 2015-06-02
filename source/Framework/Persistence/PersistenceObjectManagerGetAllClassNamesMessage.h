/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef PERSISTENCEOBJECTMANAGERGETALLCLASSNAMESMESSAGE_H
#define PERSISTENCEOBJECTMANAGERGETALLCLASSNAMESMESSAGE_H

#include "ManagementInterface/ManagementInterfaceMessage.h"

#include <string>
#include <vector>
#include <set>

using namespace std;

namespace WaveNs
{

class PersistenceObjectManagerGetAllClassNamesMessage : public ManagementInterfaceMessage
{
    private :
        virtual void setupAttributesForSerialization  ();
                void computeCpnfigurationSegmentNames ();

    protected :
    public :
                      PersistenceObjectManagerGetAllClassNamesMessage ();
        virtual      ~PersistenceObjectManagerGetAllClassNamesMessage ();

                void  getAllClassNames                                (vector<string> &allClassNames) const;
                void  getAllClassNames                                (set<string> &allClassNames) const;
                void  setAllClassNames                                (const vector<string> &allClassNames);
                void  setAllClassNames                                (const set<string> &allClassNames);

                void  getConfigurationSegmentNames                    (vector<string> &configurationSegmentNames) const;
                void  setConfigurationSegmentNames                    (const vector<string> &configurationSegmentNames);

                void  getClassNamesForConfigurationSegmentNames       (vector<string> &classNamesForConfigurationSegmentNames) const;
                void  setClassNamesForConfigurationSegmentNames       (const vector<string> &classNamesForConfigurationSegmentNames);

                void  computeConfigurationSegmentNames                ();

    // Now the data members

    private :
        vector<string> m_allClassNames;
        vector<string> m_configurationSegmentNames;
        vector<string> m_classNamesForconfigurationSegmentNames;

    protected :
    public :
};

}

#endif // PERSISTENCEOBJECTMANAGERGETALLCLASSNAMESMESSAGE_H
