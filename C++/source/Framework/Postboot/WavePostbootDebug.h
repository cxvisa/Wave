/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Amit Agrawal                                                 *
 ***************************************************************************/

#ifndef WAVEPOSTBOOTDEBUG_H
#define WAVEPOSTBOOTDEBUG_H


namespace WaveNs
{

class WavePostbootDebug
{
    private :
    protected :
    public :
        virtual        ~WavePostbootDebug  ();
                        WavePostbootDebug  ();

                        void initialize                         ();
                static  UI32 shellExecuteTriggerPostbootPasses  (UI32 argc, vector<string> argv);

    private :
    protected :
    public :
};

}

#endif // WAVEPOSTBOOTDEBUG_H
