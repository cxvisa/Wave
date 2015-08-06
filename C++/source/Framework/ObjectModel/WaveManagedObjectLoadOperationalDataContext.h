/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEMANAGEDOBJECTLOADOPERATIONALDATACONTEXT_H
#define WAVEMANAGEDOBJECTLOADOPERATIONALDATACONTEXT_H

#include "Framework/Utils/PrismAsynchronousContext.h"

namespace WaveNs
{

class WaveManagedObjectLoadOperationalDataContext : public PrismAsynchronousContext
{
    private :
    protected :
    public :
                        WaveManagedObjectLoadOperationalDataContext (WaveElement *pCaller, PrismAsynchronousCallback pCallback, void *pCallerContext = NULL);
                       ~WaveManagedObjectLoadOperationalDataContext ();

        vector<string>  getOperationalDataFields                    () const;
        void            setOperationalDataFields                    (const vector<string> &operationalDataFields);

        WaveManagedObject   *getPOwnerManagedObject                 () const;
        void                 setPOwnerManagedObject                 (WaveManagedObject *pOwnerManagedObject);

    // Now the data members

    private :
        vector<string>       m_operationalDataFields;
		WaveManagedObject   *m_pOwnerManagedObject;

    protected :
    public :
};

}

#endif // WAVEMANAGEDOBJECTLOADOPERATIONALDATACONTEXT_H
