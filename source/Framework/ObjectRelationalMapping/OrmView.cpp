/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : MITHUN BS                                                    *
 ***************************************************************************/

#include "Framework/ObjectRelationalMapping/OrmView.h"
namespace WaveNs
{

OrmView::OrmView (const string &viewName)
    : m_name                 (viewName)
{
}

OrmView::~OrmView ()
{
}

string OrmView::getName () const
{
    return (m_name);
}

string OrmView::getSqlForCreateView () const
{
    return (m_viewDefinition);
}

void OrmView::setSqlForCreateView (string &viewDefinition)
{
    m_viewDefinition = viewDefinition;
}

}
