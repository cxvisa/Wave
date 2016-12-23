/***************************************************************************
 *   Copyright (C) 2005-2016 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/FileUtils.h"

namespace WaveNs
{

magic_t   FileUtils::s_magic;
WaveMutex FileUtils::s_mutex;

void FileUtils::initialize ()
{
    s_mutex.lock ();

    s_magic = magic_open (MAGIC_MIME_TYPE);

    if (NULL == s_magic)
    {
        s_mutex.unlock ();

        return;
    }

    int status = 0;

    status = magic_load (s_magic, NULL);

    if (0 != status)
    {
        magic_close (s_magic);

        s_magic = NULL;

        s_mutex.unlock ();

        return;
    }

    s_mutex.unlock ();
}

string FileUtils::getMimeTypeForFile (const string &filePath)
{
    string mimeType = "application/octet-stream";

    s_mutex.lock ();

    const char *pMimeType = NULL;

    if (NULL != s_magic)
    {
        pMimeType = magic_file (s_magic, filePath.c_str ());
    }

    if (NULL != pMimeType)
    {
        mimeType.assign (pMimeType);
    }

    s_mutex.unlock ();

    return (mimeType);
}

}
