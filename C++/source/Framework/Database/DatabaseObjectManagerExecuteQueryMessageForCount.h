/***************************************************************************
 *   Copyright (C) 2008-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Himanshu Varshney                                            *
 ***************************************************************************/

#ifndef DATABASEOBJECTMANAGEREXECUTEQUERYMESSAGEFORCOUNT_H
#define DATABASEOBJECTMANAGEREXECUTEQUERYMESSAGEFORCOUNT_H

#include "Framework/Messaging/Local/PrismMessage.h"
#include "libpq-fe.h"

#include <string>
#include <vector>

using namespace std;

namespace WaveNs
{

class WaveManagedObject;
class WaveObjectManager;

class DatabaseObjectManagerExecuteQueryMessageForCount : public PrismMessage
{
    private :
    protected :
    public :
                                             DatabaseObjectManagerExecuteQueryMessageForCount (const string &className, WaveObjectManager *pWaveObjectManager, const string &sql);
        virtual                             ~DatabaseObjectManagerExecuteQueryMessageForCount ();

                string                       getClassName                                     () const;
                WaveObjectManager           *getPWaveObjectManager                            () const;
                string                       getSql                                           () const;
                UI32                         getCount                                         () const;
                void                         setCount                                         (const UI32 &count);
    // Now the data members

    private :
        string                       m_className;
        WaveObjectManager           *m_pWaveObjectManager;
        string                       m_sql;
        UI32                         m_count;

    protected :
    public :
};

}

#endif // DATABASEOBJECTMANAGEREXECUTEQUERYMESSAGEFORCOUNT_H
