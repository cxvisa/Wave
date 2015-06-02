/***************************************************************************
 *   Copyright (C) 2013 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Pritee Ghosh                                                 *
 ***************************************************************************/

#ifndef WAVEMANAGEDOBJECTSYNCHRONOURQUERYCONTEXTFORSETOPERATION_H
#define WAVEMANAGEDOBJECTSYNCHRONOURQUERYCONTEXTFORSETOPERATION_H

#include "Framework/ObjectModel/WaveManagedObjectSynchronousInnerQueryContext.h"
#include <vector>

using namespace std;

typedef enum
{
    OPERATOR_NONE = 0,
    OPERATOR_UNION,
    OPERATOR_INTERSECT,
    OPERATOR_EXCEPT
} SetOperation;

namespace WaveNs
{

class WaveManagedObjectSynchronousQueryContextForSetOperation
{
    private :
                void    addQueryContext                                             (WaveManagedObjectSynchronousInnerQueryContext *pQueryContext, const UI32 setOperator = OPERATOR_NONE, const bool keepDuplicate = false);

    protected :
    public :
                        WaveManagedObjectSynchronousQueryContextForSetOperation     ();
		virtual		   ~WaveManagedObjectSynchronousQueryContextForSetOperation     ();

        virtual WaveManagedObjectSynchronousInnerQueryContext* addInnerQueryContext (const string classToQueryFor, const vector<string>& selectFields, const UI32 setOperator = OPERATOR_UNION, const bool keepDuplicate = false);
                string  getSql                                                      ();

    // Now the data members

    private :
        vector<WaveManagedObjectSynchronousInnerQueryContext *>     m_waveManagedObjectInnerQueryContexts;
        vector<UI32>                                                m_contextSetOperators;
        vector<bool>                                                m_contextDuplicatesNeeded;

    protected :

    public :

};

}

#endif // WAVEMANAGEDOBJECTSYNCHRONOURQUERYCONTEXTFORSETOPERATION_H
