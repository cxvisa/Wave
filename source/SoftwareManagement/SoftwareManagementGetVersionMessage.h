/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef SOFTWAREMANAGEMENTGETVERSIONMESSAGE_H
#define SOFTWAREMANAGEMENTGETVERSIONMESSAGE_H

#include "ManagementInterface/ManagementInterfaceMessage.h"

namespace WaveNs
{

class SoftwareManagementGetVersionMessage : public ManagementInterfaceMessage
{
    private :
        void setupAttributesForSerialization ();

    protected :
    public :
                        SoftwareManagementGetVersionMessage ();
        virtual        ~SoftwareManagementGetVersionMessage ();

                string  getVersion                          () const;
                void    setVersion                          (const string &version);

    // Now the data members

    private :
        string m_version;

    protected :
    public :
};

}

#endif // SOFTWAREMANAGEMENTGETVERSIONMESSAGE_H
