/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Amr Sabaa                                                    *
 ***************************************************************************/

#ifndef HEARTBEATDEBUG_H
#define HEARTBEATDEBUG_H


namespace WaveNs
{


class HeartBeatDebug
{
    private :
    protected :
    public :
        virtual        ~HeartBeatDebug  ();
                        HeartBeatDebug  ();

                        void initialize                     ();
                static  UI32 shellExecuteStartHeartBeat     (UI32 argc, vector<string> argv);
                static  UI32 shellExecuteStopHeartBeat      (UI32 argc, vector<string> argv);
                static  UI32 shellExecutePauseHeartBeat     (UI32 argc, vector<string> argv);
                static  UI32 shellExecuteResumeHeartBeat    (UI32 argc, vector<string> argv);
                static  UI32 shellExecuteConfigHeartBeat    (UI32 argc, vector<string> argv);
                static  UI32 shellExecuteShowStatHeartBeat  (UI32 argc, vector<string> argv);
                static  UI32 shellExecuteGetStatHeartBeat   (UI32 argc, vector<string> argv);

    private :
    protected :
    public :
};


}

#endif // HEARTBEATDEBUG_H
