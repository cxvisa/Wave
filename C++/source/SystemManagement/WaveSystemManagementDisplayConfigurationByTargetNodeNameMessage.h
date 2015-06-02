/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVESYSTEMMANAGEMENTDISPLAYCONFIGURATIONBYTARGETNODENAMEMESSAGE_H
#define WAVESYSTEMMANAGEMENTDISPLAYCONFIGURATIONBYTARGETNODENAMEMESSAGE_H

#include "ManagementInterface/ManagementInterfaceMessage.h"

namespace WaveNs
{

class WaveSystemManagementDisplayConfigurationByTargetNodeNameMessage : public ManagementInterfaceMessage
{
    private :
        void setupAttributesForSerialization ();

    protected :
    public :
                        WaveSystemManagementDisplayConfigurationByTargetNodeNameMessage ();
                        WaveSystemManagementDisplayConfigurationByTargetNodeNameMessage (const string &targetNodeName);
                        WaveSystemManagementDisplayConfigurationByTargetNodeNameMessage (const string &targetNodeName, const string &schemaName);
        virtual        ~WaveSystemManagementDisplayConfigurationByTargetNodeNameMessage ();

                string  getTargetNodeName                                               () const;
                void    setTargetNodeName                                               (const string &targetNodeName);

                string  getSchemaName                                                   () const;
                void    setSchemaName                                                   (const string &schemaName);

    // Now the Data Members

    private :
        string m_targetNodeName;
        string m_schemaName;

    protected :
    public :
};

}

#endif // WAVESYSTEMMANAGEMENTDISPLAYCONFIGURATIONBYTARGETNODENAMEMESSAGE_H
