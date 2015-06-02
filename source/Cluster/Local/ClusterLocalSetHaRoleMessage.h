/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Leifang Hu                                                   *
 ***************************************************************************/

#ifndef CLUSTERLOCALSETHAROLEMESSAGE_H
#define CLUSTERLOCALSETHAROLEMESSAGE_H

#include "Framework/ObjectModel/PrismElement.h"
#include "Framework/Messaging/Local/PrismMessage.h"

namespace WaveNs
{

class PrismMessage;
class ClusterLocalSetHaRoleMessage : public PrismMessage
{
    private :
    protected :
    public :
                        ClusterLocalSetHaRoleMessage ();
                        ClusterLocalSetHaRoleMessage (const UI32 &haRole);
        virtual        ~ClusterLocalSetHaRoleMessage ();

                UI32    getHaRole                    () const;
                void    setHaRole                    (const UI32 &haRole);

    // Now the data members

    private :
        UI32 m_haRole;

    protected :
    public :
};

}

#endif // CLUSTERLOCALSETHAROLEMESSAGE_H
