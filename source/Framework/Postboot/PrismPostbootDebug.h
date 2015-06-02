/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Amit Agrawal                                                 *
 ***************************************************************************/

#ifndef PRISMPOSTBOOTDEBUG_H
#define PRISMPOSTBOOTDEBUG_H


namespace WaveNs
{

class PrismPostbootDebug
{
    private :
    protected :
    public :
        virtual        ~PrismPostbootDebug  ();
                        PrismPostbootDebug  ();

                        void initialize                         ();
                static  UI32 shellExecuteTriggerPostbootPasses  (UI32 argc, vector<string> argv);

    private :
    protected :
    public :
};

}

#endif // PRISMPOSTBOOTDEBUG_H
