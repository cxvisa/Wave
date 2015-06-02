/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : jiyer                                                        *
 **************************************************************************/

#ifndef FILETRANSFERHANDSHAKEMESSAGE_H
#define FILETRANSFERHANDSHAKEMESSAGE_H

#include "Framework/Messaging/Local/PrismMessage.h"

using namespace WaveNs;

namespace WaveNs
{

    class FileTransferHandshakeMessage : public PrismMessage
    {
        private:
        protected:
            virtual void                          setupAttributesForSerialization         ();
        public:
                                                  FileTransferHandshakeMessage            ();
                                                  FileTransferHandshakeMessage            (const UI32 &ServiceVersion, const string &sourceFileName, const string &DestinationFileName, const UI32 &SourceLocationId, const UI32 &FileSize, const UI32 &FileTransferFlag);
            virtual                              ~FileTransferHandshakeMessage            ();

            void                                  setServiceVersion                       (const UI32 &ServiceVersion);
            UI32                                  getServiceVersion                       ()  const;
            void                                  setSourceFileName                       (const string &SourceFileName);
            string                                getSourceFileName                       ()  const;            
            void                                  setDestinationFileName                  (const string &DestinationFileName);
            string                                getDestinationFileName                  ()  const;
            void                                  setSourceLocationId                     (const UI32 &SourceLocationId);
            UI32                                  getSourceLocationId                     ()  const;
            void                                  setFileSize                             (const UI32 &FileSize);
            UI32                                  getFileSize                             ()  const;
            void                                  setFileTransferFlag                     (const UI32 &FileTransferFlag);
            UI32                                  getFileTransferFlag                     ()  const;
            void                                  setTransferHandle                       (const string &TransferHandle);
            string                                getTransferHandle                       ()  const;

        // Now the data members
        private:
            UI32                   m_serviceVersion;
            string                 m_sourceFileName;
            string                 m_destinationFileName;
            UI32                   m_sourceLocationId;
            UI32                   m_fileSize;
            UI32                   m_fileTransferFlag;
            string                 m_transferHandle;
            UI32                   m_responseCode;

        protected:
        public:
                    
    };
}
#endif  //   FILETRANSFERHANDSHAKEMESSAGE_H

