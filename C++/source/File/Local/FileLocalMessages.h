/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : jiyer                                                        *
 **************************************************************************/

#ifndef FILELOCALMESSAGES_H
#define FILELOCALMESSAGES_H

#include "Framework/Messaging/Local/WaveMessage.h"

using namespace WaveNs;

namespace WaveNs
{

// Following message(s) are internal messages.
// This message is sent by Active Wave server to its Ha Peer server.

class PushFileToHaPeerMessage : public WaveMessage
{
    private:
    protected:
        virtual void            setupAttributesForSerialization     ();

    public:
                                PushFileToHaPeerMessage             ();
                                PushFileToHaPeerMessage             (const UI32 &serviceVersion, const string &transferHandle, const string &sourceFileName, const string &destinationFileName, const UI32 &fileSize);
        virtual                ~PushFileToHaPeerMessage             ();

        void                    setServiceVersion                   (const UI32 &serviceVersion);
        UI32                    getServiceVersion                   () const;
        void                    setSourceFileName                   (const string &sourceFileName);
        string                  getSourceFileName                   () const;
        void                    setDestinationFileName              (const string &destinationFileName);
        string                  getDestinationFileName              () const;
        void                    setFileSize                         (const UI32 &fileSize);
        UI32                    getFileSize                         () const;
        void                    setTransferHandle                   (const string &transferHandle);
        string                  getTransferHandle                   () const;

    // Now the data members
    private:
        UI32                    m_serviceVersion;
        string                  m_sourceFileName;
        string                  m_destinationFileName;
        UI32                    m_fileSize;
        string                  m_transferHandle;        // for debug purpose.

    protected:
    public:

};

class FileDeleteRequestMessage : public WaveMessage
{   
    private:
    protected:

        virtual void                        setupAttributesForSerialization                 ();

    public:

                                            FileDeleteRequestMessage                        ();
                                            FileDeleteRequestMessage                        (const string &DestinationFileName, vector<UI32> &DestinationLocationId ) ;
                                            FileDeleteRequestMessage                        (const string &DestinationFileName, vector<UI32> &DestinationLocationId, const UI32 &fileTransferFlag);

        virtual                            ~FileDeleteRequestMessage                        ();
            
                void                        setDestinationFileName                          (const string &destinationFileName);
                string                      getDestinationFileName                          () const;

                void                        setDestinationLocationIdList                    (const vector<UI32> &vecLocationIdList);
                vector<UI32>                getDestinationLocationIdList                    ();

                void                        setFileTransferFlag                             (const UI32 &FileTransferFlag);
                UI32                        getFileTransferFlag                             () const;

                UI32                        getLocationCountToReceiveNextMessage            () const;
                vector<UI32>                getDestinationLocationIdListForNextMessage      ();

                void                        removeLocationForSubsequentSends                (const UI32 &nLocationId);

                vector<ResourceId>          getResponseCodeList                             ();
                void                        setResponseCodeList                             (vector<ResourceId>  &responseStatus);

    // Now the data members
    private:
                string                      m_destinationFileName;
                vector<UI32>                m_vecDestinationLocationId;             // User supplied list of Locations to which this File needs to be pushed.
                vector<UI32>                m_vecLocationToReceiveNextMessage;      // List of locations to which the next message is to be received. Initially both this and the above list are same.
                UI32                        m_fileTransferFlag;
                vector<ResourceId>          m_ResponseCodeList;
    protected:
    public:

};

class FileDeleteFileMessage : public WaveMessage
{
    private:
    protected:

        virtual void                        setupAttributesForSerialization                 ();

    public:

                                            FileDeleteFileMessage                           (); 
                                            FileDeleteFileMessage                           (const string &DestinationFileName) ;
                                            FileDeleteFileMessage                           (const string &DestinationFileName, const UI32 &m_fileTransferFlag );

        virtual                            ~FileDeleteFileMessage                           ();

                void                        setDestinationFileName                          (const string &destinationFileName);
                string                      getDestinationFileName                          () const;

                void                        setFileTransferFlag                             (const UI32 &FileTransferFlag);
                UI32                        getFileTransferFlag                             () const;

    // Now the data members
    private:    
                string                      m_destinationFileName;
                UI32                        m_fileTransferFlag;
};

class FileDeleteFileToHaPeerMessage : public WaveMessage
{
    private:
    protected:

        virtual void                        setupAttributesForSerialization                 ();

    public:

                                            FileDeleteFileToHaPeerMessage                   ();
                                            FileDeleteFileToHaPeerMessage                   (const string &DestinationFileName ) ;
                                            FileDeleteFileToHaPeerMessage                   (const string &DestinationFileName, const UI32 &m_fileTransferFlag ); 

        virtual                            ~FileDeleteFileToHaPeerMessage                   ();

                void                        setDestinationFileName                          (const string &destinationFileName);
                string                      getDestinationFileName                          () const;

                void                        setFileTransferFlag                             (const UI32 &FileTransferFlag);
                UI32                        getFileTransferFlag                             () const;

    // Now the data members
    private:
                string                      m_destinationFileName;
                UI32                        m_fileTransferFlag;
};
 
}
#endif  // FILELOCALMESSAGES_H
