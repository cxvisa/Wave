/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Anil C                                                       *
 ***************************************************************************/

#ifndef ATTRIBUTEUC_H
#define ATTRIBUTEUC_H

using namespace std;

namespace WaveNs
{

class AttributeUC 
{   
    private :
    protected :
                            AttributeUC             ();
        virtual            ~AttributeUC             ();                 

    public :
        virtual bool               getIsUserConfigured                   () = 0;

};

}

#endif //ATTRIBUTEUC_H
