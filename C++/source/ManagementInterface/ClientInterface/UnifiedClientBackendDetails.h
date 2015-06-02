/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : cgangwar                                                     *
 ***************************************************************************/

#ifndef UNIFIEDCLIENTBACKENDDETAILS_H
#define UNIFIEDCLIENTBACKENDDETAILS_H

#include "Framework/Types/WaveCValue.h"

namespace WaveNs
{
    class UnifiedClientBackendDetails
    {
        private:
        protected:
        public:
                                UnifiedClientBackendDetails      ();
            virtual             ~UnifiedClientBackendDetails     ();
                        void    setBackendNotifyValue (UI32 &backendNotifyValue);
                        UI32    getBackendNotifyValue();
                        void    setClientName(string &clientName);
                        string  getClientName();

       private:
           string      m_clientName;              
           UI32        m_backendNotifyValue;
       protected:
       public:
    };        
}
#endif
