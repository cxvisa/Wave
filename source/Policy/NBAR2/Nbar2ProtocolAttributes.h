/***************************************************************************
 *   Copyright (C) 2015      Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef NBAR2PROTOCOLATTRIBUTES_H
#define NBAR2PROTOCOLATTRIBUTES_H

#include "Policy/NBAR2/Nbar2Element.h"

namespace WaveNs
{

class Nbar2ProtocolAttributes : public Nbar2Element
{
    private :
    protected :
    public :
                        Nbar2ProtocolAttributes ();
        virtual        ~Nbar2ProtocolAttributes ();

                string  getApplicationGroup     () const;
                string  getCategory             () const;
                string  getEncrypted            () const;
                string  getP2pTechnology        () const;
                string  getSubCategory          () const;
                string  getTunnel               () const;

                string  getAdjustedCategoryName () const;

    // Now the data elements

    private :
        string m_applicationGroup;
        string m_category;
        string m_encrypted;
        string m_p2pTechnology;
        string m_subCategory;
        string m_tunnel;

    protected :
    public :
};

}

#endif // NBAR2PROTOCOLATTRIBUTES_H

