/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : cgangwar                                                     *
 ***************************************************************************/

#ifndef UNIFIEDCLIENTNOTIFYMESSAGE_H
#define UNIFIEDCLIENTNOTIFYMESSAGE_H

#include "ManagementInterface/ManagementInterfaceMessage.h"
#include "Framework/ObjectModel/WaveManagedObjectAsynchronousPluginContext.h"
#include "Framework/Types/WaveCValue.h"

namespace WaveNs
{
    class UnifiedClientNotifyMessage : public ManagementInterfaceMessage
    {
        private:
        protected:
            virtual void    setupAttributesForSerialization();
        public:
                            UnifiedClientNotifyMessage ();
    
            virtual         ~UnifiedClientNotifyMessage ();
    
            virtual const void *getCStructureForInputs ();
    
                    void    deleteCStructureForInputs (const void *pInputStruct);
                    void 	setbackendNotifyValue (UI32 &backendNotifyValue);
                    UI32 	getbackendNotifyValue();	

        // Now the data members
        private:
            UI32 		m_backendNotifyValue; 
        protected:
        public:
    };
}
#endif
