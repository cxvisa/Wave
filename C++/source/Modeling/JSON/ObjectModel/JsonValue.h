/***************************************************************************
 *   Copyright (C) 2005-2015 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef JSONVALUE_H
#define JSONVALUE_H

#include "Framework/Types/Types.h"

namespace WaveNs
{

class JsonValue
{
    private :
    protected :
        void setSuccessFullyLoaded (const bool &successFullyLoaded);

    public :
                        JsonValue             ();
        virtual        ~JsonValue             ();

        virtual string  toString              () const = 0;
        virtual void    fromString            (const string &input)= 0;

                bool    getSuccessFullyLoaded () const;

        virtual void    print                 (const UI32 &level = 0) const = 0;

    // Now the data members

    private :
        bool m_successFullyLoaded;

    protected :
    public :
};

}

#endif // JSONVALUE_H
