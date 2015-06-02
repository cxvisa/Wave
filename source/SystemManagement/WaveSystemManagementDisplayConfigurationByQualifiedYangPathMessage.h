/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVESYSTEMMANAGEMENTDISPLAYCONFIGURATIONBYQUALIFIEDYANGPATHMESSAGE_H
#define WAVESYSTEMMANAGEMENTDISPLAYCONFIGURATIONBYQUALIFIEDYANGPATHMESSAGE_H

#include "ManagementInterface/ManagementInterfaceMessage.h"

namespace WaveNs
{

class WaveSystemManagementDisplayConfigurationByQualifiedYangPathMessage : public ManagementInterfaceMessage
{
    private :
        void setupAttributesForSerialization ();

    protected :
    public :
                        WaveSystemManagementDisplayConfigurationByQualifiedYangPathMessage ();
                        WaveSystemManagementDisplayConfigurationByQualifiedYangPathMessage (const string &qualifiedYangPath);
                        WaveSystemManagementDisplayConfigurationByQualifiedYangPathMessage (const string &qualifiedYangPath, const string &schemaName);
        virtual        ~WaveSystemManagementDisplayConfigurationByQualifiedYangPathMessage ();

                string  getQualifiedYangPath                                               () const;
                void    setQualifiedYangPath                                               (const string &qualifiedYangPath);

                string  getSchemaName                                                      () const;
                void    setSchemaName                                                      (const string &schemaName);

    // Now the Data Members

    private :
        string m_qualifiedYangPath;
        string m_schemaName;

    protected :
    public :
};

}

#endif // WAVESYSTEMMANAGEMENTDISPLAYCONFIGURATIONBYQUALIFIEDYANGPATHMESSAGE_H
