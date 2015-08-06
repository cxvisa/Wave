/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/ObjectModel/WaveManagedObjectLoadOperationalDataContext.h"
#include "Framework/ObjectModel/WaveManagedObject.h"

namespace WaveNs
{

WaveManagedObjectLoadOperationalDataContext::WaveManagedObjectLoadOperationalDataContext (WaveElement *pCaller, PrismAsynchronousCallback pCallback, void *pCallerContext)
    : PrismAsynchronousContext (pCaller, pCallback, pCallerContext),
      m_pOwnerManagedObject    (NULL)
{
}

WaveManagedObjectLoadOperationalDataContext::~WaveManagedObjectLoadOperationalDataContext ()
{
}

vector<string> WaveManagedObjectLoadOperationalDataContext::getOperationalDataFields () const
{
    return (m_operationalDataFields);
}

void WaveManagedObjectLoadOperationalDataContext::setOperationalDataFields (const vector<string> &operationalDataFields)
{
    m_operationalDataFields = operationalDataFields;
}

WaveManagedObject *WaveManagedObjectLoadOperationalDataContext::getPOwnerManagedObject () const
{
    return (m_pOwnerManagedObject);
}

void WaveManagedObjectLoadOperationalDataContext::setPOwnerManagedObject (WaveManagedObject *pOwnerManagedObject)
{
    m_pOwnerManagedObject = pOwnerManagedObject;
}

}
