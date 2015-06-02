/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/Base64Utils.h"

#include <string.h>

#include <openssl/sha.h>
#include <openssl/hmac.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>

namespace WaveNs
{

string Base64Utils::encode (const string& input)
{
    BIO     *pBmem;
    BIO     *pB64;
    BUF_MEM *pBuffer;
    string   output;
    char    *pOutputBuffer = NULL;
    int      temp		   = 0;

    pB64  = BIO_new  (BIO_f_base64 ());
    pBmem = BIO_new  (BIO_s_mem ());
    pB64  = BIO_push (pB64, pBmem);

    BIO_write       (pB64, input.c_str (), input.length ());
    temp = BIO_flush       (pB64);

    if (0 != temp)
    {
    	// Nothing to do.
    }

    BIO_get_mem_ptr (pB64, &pBuffer);

    pOutputBuffer = (char *) malloc (pBuffer->length);

    memcpy (pOutputBuffer, pBuffer->data, pBuffer->length - 1);
    pOutputBuffer[pBuffer->length - 1] = 0;

    output = pOutputBuffer;

    BIO_free_all (pB64);
    free         (pOutputBuffer);

    return (output);
}

string Base64Utils::decode (const string& input)
{
    BIO    *pB64;
    BIO    *pBmem;
    char   *pOutputBuffer = (char *) malloc (input.length ());
    string  output;

    memset(pOutputBuffer, 0, input.length ());

    pB64 = BIO_new (BIO_f_base64 ());

    BIO_set_flags (pB64, BIO_FLAGS_BASE64_NO_NL);

    pBmem = BIO_new_mem_buf ((void *) input.c_str (), input.length ());
    pBmem = BIO_push        (pB64, pBmem);

    BIO_read (pBmem, pOutputBuffer, input.length ());

    output = pOutputBuffer;

    BIO_free_all (pBmem);
    free (pOutputBuffer);

    return output;
}

}
