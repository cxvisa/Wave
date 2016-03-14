/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVECLIGRAPEVINEROOTSHELL_H
#define WAVECLIGRAPEVINEROOTSHELL_H

#include "Shell/WaveCliShell.h"

namespace WaveNs
{

class WaveCliGrapevineRootShell : public WaveCliShell
{
    private :
                   WaveCliGrapevineRootShell             (WaveClientSynchronousConnection &connection);

        void       briefHelp                             ();

        ResourceId registerService                       (const vector<string> &arguments);
        void       registerServiceHelp                   (void);

        ResourceId registerServicesByRange               (const vector<string> &arguments);
        void       registerServicesByRangeHelp           (void);

        ResourceId registerServiceInstance               (const vector<string> &arguments);
        void       registerServiceInstanceHelp           (void);

        ResourceId unregisterServiceInstance             (const vector<string> &arguments);
        void       unregisterServiceInstanceHelp         (void);

        ResourceId registerServiceInstancesByRange       (const vector<string> &arguments);
        void       registerServiceInstancesByRangeHelp   (void);

        ResourceId unregisterServiceInstancesByRange     (const vector<string> &arguments);
        void       unregisterServiceInstancesByRangeHelp (void);

    protected :
    public :
        virtual ~WaveCliGrapevineRootShell ();

    // Now the data members

    private :
    protected :
    public :

    friend class WaveCliShell;
};

}

#endif // WAVECLIGRAPEVINEROOTSHELL_H
