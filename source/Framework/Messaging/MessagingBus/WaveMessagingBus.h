/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEMESSAGINGBUS_H
#define WAVEMESSAGINGBUS_H

#include "Framework/Types/Types.h"

namespace WaveNs
{

class WaveMessagingBus
{
    private :
    protected :
    public :
                        WaveMessagingBus (const string &name);
        virtual        ~WaveMessagingBus ();

                string  getName          () const;
                void    setName          (const  string &name);

    // Now the data members

    private :
        string m_name;

    protected :
    public :
};

}

#endif // WAVEMESSAGINGBUS_H
