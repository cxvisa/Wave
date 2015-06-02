/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : jiyer                                                        *
 **************************************************************************/

#ifndef FILELOCALTYPESH_H
#define FILELOCALTYPESH_H

using namespace WaveNs;

namespace WaveNs
{

const unsigned int sFILESERVICEVERSION = 0x0100;    // version major = 01, minor = 00.

    typedef enum
    {
        FILESVCFILETRANSFERHANDSHAKE = 0 ,
        FILESVCPUSHFILE,
        FILESVCPUSHFILEFRAGMENT,
        FILESVCABORTFILETRANSFER,
        FILESVCPUSHFILETOHAPEER,        // internal
        FILESVCFILEPUSHFILETOHAPEER,     // (as api)
        FILESVCREQUESTDELETEFILE,
        FILESVCDELETEFILE,
        FILESVCDELETEFILETOHAPEER
    }FileLocalMessageTypes;

     typedef enum
     {
     // Const flags related to file transfer.
     FILE_OVERWRITE_DEST_FILE_IF_EXIST=0,    // DEFAULT
     FILE_FAIL_IF_DEST_FILE_EXIST=1,
     FILE_DEST_PATH_ABSOLUTE=2, // At destination use the filename as absolute path.
     FILE_DEST_PATH_IWD=4, 		// At destination, prepend the initial_working_directory to the filename.
     FILE_DEST_PATH_CWD     = 8,   	// At destination, prepend the current_working_directory to the filename.
     FILE_PUSH_TO_HA_PEER   = 16   	// At destination, send the file to Ha peer location. (i.e. send to standby)
     } FileTransferFlag;

     typedef enum
     {
        // const enums for FileSvc message buffer types. 
        FILESVC_FILE_FRAGMENT_BUFFER_TAG            = 0,
        FILESVC_COMPLETE_FILE_BUFFER_FOR_HA_PEER
     }BufferTagsForFrameworkFileSvcMessages;

}
#endif   //FILELOCALTYPESH_H
