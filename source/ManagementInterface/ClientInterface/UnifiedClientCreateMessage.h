/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Anand Kumar Subramanian                                      *
 **************************************************************************/

#ifndef UNIFIEDCLIENTCREATEMESSAGE_H 
#define UNIFIEDCLIENTCREATEMESSAGE_H 

#include "ManagementInterface/ClientInterface/UnifiedClientUpdateMessage.h"

namespace WaveNs
{

    class UnifiedClientCreateMessage : public UnifiedClientUpdateMessage 
    {
        private:
        protected:
            virtual void setupAttributesForSerialization();
        public:
            UnifiedClientCreateMessage ();
            UnifiedClientCreateMessage (const WaveManagedObjectAsynchronousPluginContext *pWaveManagedObjectAsynchronousPluginContext);

            virtual    ~UnifiedClientCreateMessage ();
            
            virtual const void *getCStructureForInputs    ();
            virtual       void  loadOutputsFromCStructure (const void *pOutputCStructure);

// Now the data members

        private:
        protected:
        public:

    };
}
#endif                                            //UNIFIEDCLIENTCREATEMESSAGE_H

