/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Brian Adaniya                                                *
 ***************************************************************************/

#ifndef PERSISTENCEOBJECTMANAGEREXECUTETRANSACTIONASYNCHRONOUSCONTEXT_H
#define PERSISTENCEOBJECTMANAGEREXECUTETRANSACTIONASYNCHRONOUSCONTEXT_H

#include "Framework/Utils/PrismAsynchronousContext.h"

using namespace std;

namespace WaveNs
{

class PersistenceObjectManagerExecuteTransactionAsynchronousContext : public PrismAsynchronousContext
{   
    private :
    protected :
    public :
                                    PersistenceObjectManagerExecuteTransactionAsynchronousContext   (PrismElement *pCaller, PrismAsynchronousCallback pCallback, void *pCallerContext = NULL);
        virtual                    ~PersistenceObjectManagerExecuteTransactionAsynchronousContext   ();

                string              getSql                                                          () const;
                void                setSql                                                          (const string &sql);
                bool                getIsConfigurationChange                                        () const;
                void                setIsConfigurationChange                                        (const bool &isConfigurationChange);
                bool                getIsConfigurationTimeChange                                    () const;
                void                setIsConfigurationTimeChange                                    (const bool &isConfigurartionTimeChange);
                PrismServiceId      getSenderServiceCode                                            () const;
                void                setSenderServiceCode                                            (const PrismServiceId &senderServiceCode);
                LocationId          getSenderLocationId                                             () const;
                void                setSenderLocationId                                             (const LocationId &senderLocationId);
    
    // Now the data members

    private :
        string                      m_sql;
        bool                        m_isConfigurationChange;
        bool                        m_isConfigurationTimeChange;
        PrismServiceId              m_senderServiceCode;
        LocationId                  m_senderLocationId;

    protected :
    public : 
};  

}

#endif // PERSISTENCEOBJECTMANAGEREXECUTETRANSACTIONASYNCHRONOUSCONTEXT_H

