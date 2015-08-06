/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : MITHUN BS                                                    *
 ***************************************************************************/

#include "Framework/ObjectModel/WaveManagedView.h"

namespace WaveNs
{

WaveManagedView::WaveManagedView (WaveObjectManager *pWaveObjectManager)
    : WaveElement           (pWaveObjectManager),
      PrismPersistableObject (WaveManagedView::getClassName ()),
      WaveManagedObject      (pWaveObjectManager)
{   
}

WaveManagedView::~WaveManagedView ()
{
}

string WaveManagedView::getClassName ()
{
    return ("WaveManagedView");
}

void WaveManagedView::setupAttributesForPersistence ()
{
}

void WaveManagedView::setupAttributesForCreate ()
{
}

string WaveManagedView::getSqlForCreateView ()
{
    return "";
}

//void WaveManagedView::getSetContextForCreateView (WaveManagedObjectSynchronousQueryContextForSetOperation* &pViewContext)
//void WaveManagedView::getSetContextForCreateView (WaveManagedObjectSynchronousQueryContextForSetOperation *pViewContext)
void WaveManagedView::getSetContextForCreateView (WaveManagedObjectSynchronousQueryContextForSetOperation &viewContext)
{
}
}
