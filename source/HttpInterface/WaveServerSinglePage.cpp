/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include "HttpInterface/WaveServerSinglePage.h"
#include "HttpInterface/HttpInterfaceReceiverObjectManager.h"

namespace WaveNs
{

WaveServerSinglePage::WaveServerSinglePage (HttpInterfaceReceiverObjectManager* pHttpInterfaceReceiverObjectManager, const string& path)
    : WaveServerPage (pHttpInterfaceReceiverObjectManager, path)
{
}

WaveServerSinglePage::~WaveServerSinglePage ()
{
}

}
