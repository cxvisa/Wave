/***************************************************************************
 *   Copyright (C) 2010 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Himanshu Varshney                                            *
 ***************************************************************************/

#ifndef UI32UC_H
#define UI32UC_H

#include <string>
#include "Framework/Types/Types.h"

namespace WaveNs
{

class UI32UC
{
    private:
    protected:
    public:
                            UI32UC                     ();
                            UI32UC                     (const UI32 &ui32);
                            UI32UC                     (const UI32 &ui32, const bool &isUserConfigured);
                            UI32UC                     (const UI32UC &ui32UC);
                                                       
                void        setUI32Value               (const UI32 &ui32);
                UI32        getUI32Value               () const;
                                                       
                void        setIsUserConfigured        (const bool &isUserConfigured);
                bool        getIsUserConfigured        () const;
                            
                string      toString                   ();
                void        fromString                 (const string &ui32UCInStringFormat);
                void        getPlainString             (string &valueString) const;
                ResourceId  loadFromPlainString        (const string &pUI32UCInPlainStringFormat);
                            
                bool        operator == (const UI32UC &ui32UC)  const ;
                bool        operator != (const UI32UC &ui32UC)  const ;
                UI32UC     &operator  = (const UI32UC &ui32UC);


        // Now the data members

    private:
                UI32    m_pUI32;
                bool    m_pIsUserConfigured;
};

typedef UI32UC  EnumUC;

}

#endif //UI32UC_H
