/***************************************************************************
 *   Copyright (C) 2010 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Mandar Datar                                                 *
 *   Note   : Copied from Framework/Types/UI32UC.h                         *
 ***************************************************************************/

#ifndef UI64UC_H
#define UI64UC_H

#include <string>
#include "Framework/Types/Types.h"

namespace WaveNs
{

class UI64UC
{
    private:
    protected:
    public:
                            UI64UC                     ();
                            UI64UC                     (const UI64 &ui64);
                            UI64UC                     (const UI64 &ui64, const bool &isUserConfigured);
                            UI64UC                     (const UI64UC &ui64UC);
                                                       
                void        setUI64Value               (const UI64 &ui64);
                UI64        getUI64Value               () const;
                                                       
                void        setIsUserConfigured        (const bool &isUserConfigured);
                bool        getIsUserConfigured        () const;
                            
                string      toString                   ();
                void        fromString                 (const string &ui64UCInStringFormat);
                void        getPlainString             (string &valueString) const;
                ResourceId  loadFromPlainString        (const string &pUI64UCInPlainStringFormat);
                            
                bool        operator == (const UI64UC &ui64UC)  const ;
                bool        operator != (const UI64UC &ui64UC)  const ;
                UI64UC     &operator  = (const UI64UC &ui64UC);


        // Now the data members

    private:
                UI64    m_pUI64;
                bool    m_pIsUserConfigured;
};

}

#endif //UI64UC_H
