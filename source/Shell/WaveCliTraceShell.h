/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Anand Subramanian                                            *
 ***************************************************************************/

#ifndef WAVECLITRACESHELL_H
#define WAVECLITRACESHELL_H 

#include "Shell/WaveCliShell.h"
#include "Framework/ObjectModel/WaveLocalObjectManagerForUserSpecificTasks.h"

namespace WaveNs
{

class WaveCliTraceShell : public WaveCliShell
{
    private :
                   WaveCliTraceShell            (WaveClientSynchronousConnection &connection);

        void       briefHelp                    ();

        ResourceId traceList                    (const vector<string> &arguments);
        void       traceListHelp                (void);

        ResourceId traceSetLevel                (const vector<string> &arguments);
        void       traceSetLevelHelp            (void);

        ResourceId traceSetAll                  (const vector<string> &arguments);
        void       traceSetAllHelp              (void);

        ResourceId traceSetDefault              (const vector<string> &arguments);
        void       traceSetDefaultHelp          (void);

        ResourceId traceLegend                  (const vector<string> &arguments);
        void       traceLegendHelp              (void);
        
        ResourceId traceHelp                    (const vector<string> &arguments);
        void       traceHelpHelp                (void);

        static TraceLevel getTraceLevelResourceId (const char* trace);
    protected :
    public :
        virtual ~WaveCliTraceShell ();

    // Now the data members

    private :
    protected :
    public :

    friend class WaveCliShell;
};

}

#endif // WAVECLITRACESHELL_H
