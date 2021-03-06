/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : jiyer                                                        *
 **************************************************************************/

#include "File/Local/FileLocalObjectManager.h"
#include "File/Local/FileAbortFileTransferMessage.h"
#include "File/Local/FileLocalTypes.h"

namespace WaveNs
{

    FileAbortFileTransferMessage::FileAbortFileTransferMessage ()
        : WaveMessage (FileLocalObjectManager::getWaveServiceId (), FILESVCABORTFILETRANSFER)
    {
    }

    FileAbortFileTransferMessage::FileAbortFileTransferMessage (vector<LocationId> &vecLocationIdList)
        : WaveMessage (FileLocalObjectManager::getWaveServiceId (), FILESVCABORTFILETRANSFER),
       m_vecLocationId(vecLocationIdList)
    {
    }

    FileAbortFileTransferMessage::~FileAbortFileTransferMessage ()
    {
    }

    void  FileAbortFileTransferMessage::setupAttributesForSerialization()
    {
        WaveMessage::setupAttributesForSerialization ();
        addSerializableAttribute (new AttributeUI32Vector(&m_vecLocationId, "vecLocationId"));
    }

    vector<LocationId> FileAbortFileTransferMessage::getLocationdIdList() const
    {
        return  (m_vecLocationId);
    }

}
