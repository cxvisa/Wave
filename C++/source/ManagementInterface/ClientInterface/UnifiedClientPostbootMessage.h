/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Anil C                                                       *
 **************************************************************************/

#ifndef UNIFIEDCLIENTPOSTBOOTMESSAGE_H 
#define UNIFIEDCLIENTPOSTBOOTMESSAGE_H 

#include "ManagementInterface/ClientInterface/UnifiedClientUpdateMessage.h"

namespace WaveNs
{   
    class UnifiedClientPostbootMessage : public UnifiedClientUpdateMessage
    {   
        private:
        protected:
            virtual void setupAttributesForSerialization();
        public:
            UnifiedClientPostbootMessage ();
            UnifiedClientPostbootMessage (const GetHardwareConfigurationDetailsForPostbootContext *pContext);

            virtual                ~UnifiedClientPostbootMessage ();

            virtual const   void   *getCStructureForInputs      ();
            virtual         void    loadOutputsFromCStructure   (const void *pOutputCStructure);
            virtual         void    initializeFromContext       ( const WaveManagedObjectAsynchronousPluginContext *pContext );
                          
// Now the data members

        private:
        protected:
        public:

    };
}
#endif      //UNIFIEDCLIENTPOSTBOOTMESSAGE_H
