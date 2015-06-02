/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Kundan Sinha                                                 *
 ***************************************************************************/

#ifndef ATTRIBUTE_VECTOR_H
#define ATTRIBUTE_VECTOR_H


#include "Framework/Attributes/Attribute.h"


namespace WaveNs
{

    class Attribute;

    class AttributeVector
    {
        public:
            virtual   void         addAttributeToVector        (Attribute *attribute)   = 0;
            virtual   void         deleteAttributeFromVector   (Attribute *attribute)   = 0;
            virtual                ~AttributeVector            ();

    };

}

#endif //ATTRIBUTE_VECTOR_H  
