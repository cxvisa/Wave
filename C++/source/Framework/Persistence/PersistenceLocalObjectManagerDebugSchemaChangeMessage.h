/**************************************************************************************
 *  @file : PersistenceLocalObjectManagerDebugSchemaChangeMessage.h                                 *
 *   Copyright (C) 2011 Vidyasagara Guntaka                                           *
 *   All rights reserved.                                                             *
 *   Description : Declares a message Persistence OM handled message used to print    *
 *                 ORM repository information.                                        *
 *   Author : Pritee Ghosh                                                            *
 *   Date   : 12/03/2011                                                              *
 **************************************************************************************/

#ifndef PERSISTENCELOCALOBJECTMANAGERDEBUGSCHEMACHANGEMESSAGE_H
#define PERSISTENCELOCALOBJECTMANAGERDEBUGSCHEMACHANGEMESSAGE_H

#include "ManagementInterface/ManagementInterfaceMessage.h"


namespace WaveNs
{

class PersistenceLocalObjectManagerDebugSchemaChangeMessage : public ManagementInterfaceMessage
{
    private :
                void            setupAttributesForSerialization         ();
    protected :
    public :
                                PersistenceLocalObjectManagerDebugSchemaChangeMessage ();
                                PersistenceLocalObjectManagerDebugSchemaChangeMessage (const vector<string> &arguments);
        virtual                ~PersistenceLocalObjectManagerDebugSchemaChangeMessage ();


        
        const   vector<string> &getCmdArgs                              () const;

                string          getResultPrint                          () const;
                void            setResultPrint                          (const string &result);

    // Now the data members
    private :
                vector<string>  m_cmdArgs;
                string          m_resultPrint;

    protected :
    public :
};

}
#endif // PERSISTENCELOCALOBJECTMANAGERDEBUGSCHEMACHANGEMESSAGE_H
