/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "Framework/Utils/PamUtils.h"

#include <stdlib.h>

extern "C"
{

#include <security/pam_appl.h>
#include <security/pam_misc.h>

int pamConversation (int numberOfMessages, const struct pam_message **pMessage, struct pam_response **pResponse, void *pApplicationData)
{
    int                  i         = 0;
    struct pam_response *pReply    = (struct pam_response *) calloc (numberOfMessages, sizeof (struct pam_response));
    char                *pPassword = (char *) malloc (512);

    //printf ("Number of messages : %d\n", numberOfMessages);

    for (i = 0; i < numberOfMessages; i++)
    {
        //printf ("Style : %d\n", pMessage[i]->msg_style);
        //printf ("%s\n", pMessage[i]->msg);
    }

    strncpy (pPassword, (char *) pApplicationData, 512);

    pReply[0].resp_retcode = 0;
    pReply[0].resp = (char *) pPassword;

    //printf ("Password :\"%s\"\n", pPassword);

    *pResponse = pReply;

    return (PAM_SUCCESS);
}

}

namespace WaveNs
{

bool PamUtils::authenticate (const string &authenticationService, const string& userName, const string &password)
{
    char                  *pApplicationData     = (char *) malloc (512);
    const struct pam_conv  localConversation    = {&::pamConversation, pApplicationData};
    pam_handle_t          *pPamHandle           = NULL;
    int                    localStatus          = 0;
    int                    authenticationStatus = 0;

    strncpy (pApplicationData, password.c_str (), 512);

    localStatus = pam_start (authenticationService.c_str (), userName.c_str (), &localConversation, &pPamHandle);

//printf ("Status 2: %d\n", localStatus);

    authenticationStatus = pam_authenticate (pPamHandle , PAM_SILENT);
//printf ("Status : %d\n", authenticationStatus);

    localStatus = pam_end (pPamHandle , localStatus);
//printf ("Status : %d\n", localStatus);

    if (PAM_SUCCESS == authenticationStatus)
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

}
