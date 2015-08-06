/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : jiyer                                                        *
 **************************************************************************/

#ifndef FILEABORTFILETRANSFERMESSAGE_H
#define FILEABORTFILETRANSFERMESSAGE_H

#include "Framework/Messaging/Local/WaveMessage.h"

using namespace WaveNs;

namespace WaveNs
{

    class FileAbortFileTransferMessage : public WaveMessage
    {
        private:
        protected:
            virtual void                     setupAttributesForSerialization         ();
        public:
                                             FileAbortFileTransferMessage            ();
                                             FileAbortFileTransferMessage            (vector<LocationId> &vecLocationIdList);
            virtual                         ~FileAbortFileTransferMessage            ();
            vector<LocationId>               getLocationdIdList                      () const;

        // Now the data members
        private:
        protected:
        public:

            vector<LocationId>               m_vecLocationId;
    };
}
#endif  //FILEABORTFILETRANSFERMESSAGE_H

