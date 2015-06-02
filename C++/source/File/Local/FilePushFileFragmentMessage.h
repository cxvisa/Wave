/*********************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                     *
 *   All rights reserved.                                            *
 *   Author : jiyer                                                  *
 *********************************************************************/

#ifndef FILEPUSHFILEFRAGMENTMESSAGE_H
#define FILEPUSHFILEFRAGMENTMESSAGE_H

#include "Framework/Messaging/Local/PrismMessage.h"

using namespace WaveNs;

namespace WaveNs
{

    class FilePushFileFragmentMessage : public PrismMessage
    {
        private:
        protected:
            virtual void setupAttributesForSerialization    ();
        public:
                         FilePushFileFragmentMessage        ();
                         FilePushFileFragmentMessage        (const string &TransferHandle,const LocationId& locationId, const UI32 &FileFragmentIndex,const UI32 &FragmentSize, bool LastFragment = false);
            virtual     ~FilePushFileFragmentMessage        ();
            void         setTransferHandle                  (const string &TransferHandle);
            string       getTransferHandle                  ()  const;
            void         setFileFragmentIndex               (const UI32 &FileFragmentIndex);
            UI32         getFileFragmentIndex               ()  const;
            void         setFragmentSize                    (const UI32 &FragmentSize);
            UI32         getFragmentSize                    ()  const;
            bool         IsLastFragment                     ()  const;
            LocationId   getSourceLocationId                () const;
            void         setSourceLocationId                (const LocationId &locationid); 

        // Now the data members
        private:
        protected:
        public:
            string       m_transferHandle;
            LocationId   m_sourceLocationId;
            UI32         m_fileFragmentIndex;
            UI32         m_fragmentSize;
            bool         m_lastFragment;
    };
}
#endif     // FILEPUSHFILEFRAGMENTMESSAGE_H

