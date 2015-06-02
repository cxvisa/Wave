#include "Framework/Types/Types.h"
#include "WaveManagedObjectToolKit.h"
#include "WaveManagedObject.h"
#include "Framework/Attributes/Attribute.h"

namespace WaveNs
{

/// Name
/// WaveManagedObjectToolKit
/// Description
/// No op constructor. Should never be called.
/// Input
/// none
/// Output
/// none
/// Return
/// none  
WaveManagedObjectToolKit::WaveManagedObjectToolKit()
{
}
/// Name
/// ~WaveManagedObjectToolKit
/// Description
/// Destructor. Should never be called.
/// Input
/// none
/// Output
/// none
/// Return
/// none  
WaveManagedObjectToolKit::~WaveManagedObjectToolKit()
{
}

/// Name
/// releaseMemoryOfWaveMOVector
/// Description
/// Helper function to release memory from 
/// transient objects created due to DB query
/// Input
/// Reference to pointer of a vector containing pointers 
/// to Managed Objects 
/// Output
/// none
/// Return
/// none
void WaveManagedObjectToolKit::releaseMemoryOfWaveMOVector(vector<WaveManagedObject *>* & pResults)
{
    if (pResults)
    {
        UI32 nNodes = pResults->size();
        for (UI32 i = 0; i < nNodes; i++)
        {
            if ((*pResults)[i])
            {
                delete (*pResults)[i];
            }
        }

        pResults->clear ();
        delete pResults;
        pResults = 0;
    }
    return;
}

void WaveManagedObjectToolKit::releaseMemoryOfAttributeVector(vector<Attribute *> &attrVector )
{
    if ( false ==  attrVector.empty() )
    {   
        UI32 size = attrVector.size();
        for ( UI32 i = 0; i < size; i++)
        {   
            if ( NULL != attrVector[i] )
            {   
                delete ( attrVector[i] );
            }
        }
        attrVector.clear();
    }
    return ;
}

}
