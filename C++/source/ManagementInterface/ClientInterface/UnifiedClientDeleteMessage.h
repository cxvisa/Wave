/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Anand Kumar Subramanian                                      *
 **************************************************************************/

#ifndef UNIFIEDCLIENTDELETEMESSAGE_H 
#define UNIFIEDCLIENTDELETEMESSAGE_H 

#include "ManagementInterface/ClientInterface/UnifiedClientUpdateMessage.h"

namespace WaveNs
{

    class UnifiedClientDeleteMessage : public UnifiedClientUpdateMessage 
    {
        private:
        protected:
            virtual void setupAttributesForSerialization();
        public:
            UnifiedClientDeleteMessage ();
            UnifiedClientDeleteMessage (const WaveManagedObjectAsynchronousPluginContext *pWaveManagedObjectAsynchronousPluginContext);

            virtual    ~UnifiedClientDeleteMessage ();
            
            virtual const void *getCStructureForInputs    ();
            virtual       void  loadOutputsFromCStructure (const void *pOutputCStructure);

// Now the data members

        private:
        protected:
        public:

    };
}
#endif                                            //UNIFIEDCLIENTDELETEMESSAGE_H

