/***************************************************************************
 *   Copyright (C) 2010 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Himanshu Varshney                                            *
 ***************************************************************************/

#ifndef STRINGUC_H
#define STRINGUC_H

#include <string>
#include "Framework/Types/Types.h"

namespace WaveNs
{

class StringUC
{
    private:
    protected:
    public:
                               StringUC                     ();
                               StringUC                     (const string &pString);
                               StringUC                     (const string &pString, const bool &isUserConfigured);
                               StringUC                     (const StringUC &stringUC);
                                                            
                void           setStringValue               (const string &pString);
                string         getStringValue               () const;
                                                            
                void           setIsUserConfigured          (const bool &isUserConfigured);
                bool           getIsUserConfigured          () const;
                               
                string         toString                     ();
                void           fromString                   (const string &pStringUCInStringFormat);
                void           getPlainString               (string &valueString) const;
                ResourceId     loadFromPlainString          (const string &pStringUCInPlainStringFormat);
                               
                bool           operator ==                  (const StringUC &pStringUC)  const ;
                bool           operator !=                  (const StringUC &pStringUC)  const ;
                StringUC      &operator =                   (const StringUC &pStringUC);


        // Now the data members

    private:
                string  m_pString;
                bool    m_pIsUserConfigured;
};

}

#endif //StringUC_H
