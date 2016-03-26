#include "com_CxWave_Wave_Framework_Utils_AAA_PamUtils.h"

#include <string>
#include <iostream>

#include "Framework/Utils/PamUtils.h"

using namespace std;
using namespace WaveNs;

#ifdef __cplusplus
extern "C"
{
#endif

JNIEXPORT jboolean JNICALL Java_com_CxWave_Wave_Framework_Utils_AAA_PamUtils_authenticateUsingWaveCpp (JNIEnv *pJEnv, jclass jClass, jstring jAuthenticationService, jstring jUserName, jstring jPassword)
{
    jboolean isACopyForAuthenticationService = JNI_TRUE;
    jboolean isACopyForUserName              = JNI_TRUE;
    jboolean isACopyForPassword              = JNI_TRUE;

    const char *pAuthenticationService = pJEnv->GetStringUTFChars (jAuthenticationService, &isACopyForAuthenticationService);
    const char *pUserName              = pJEnv->GetStringUTFChars (jUserName, &isACopyForUserName);
    const char *pPassword              = pJEnv->GetStringUTFChars (jPassword, &isACopyForPassword);

    string authenticationService (pAuthenticationService);
    string userName              (pUserName);
    string password              (pPassword);

    cout << authenticationService << ":" << userName << ":" << password << endl;

    bool result = PamUtils::authenticate (authenticationService, userName, password);

    if (true == result)
    {
        return (JNI_TRUE);
    }
    else
    {
        return (JNI_FALSE);
    }
}

#ifdef __cplusplus
}
#endif
