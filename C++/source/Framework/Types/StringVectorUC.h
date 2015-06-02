/***************************************************************************
 *   Copyright (C) 2011 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Cindy Hou                                                    *
 ***************************************************************************/

#ifndef STRINGVECTORUC_H
#define STRINGVECTORUC_H

#include <string>
#include "Framework/Types/Types.h"

namespace WaveNs
{

class StringVectorUC
{
    private:
    protected:
    public:
                                StringVectorUC      ();
                                StringVectorUC      (const vector<string> &stringVector);
                                StringVectorUC      (const vector<string> &stringVector, const bool &isUserConfigured);
                                StringVectorUC      (const StringVectorUC &stringVectorUC);
                               ~StringVectorUC      ();

                void            setStringVector     (const vector<string> &stringVector);
                vector<string>  getStringVector     () const;

                void            setIsUserConfigured (const bool &isUserConfigured);
                bool            getIsUserConfigured () const;
    
                void            toString            (string &valueString);
                void            fromString          (const string &stringVectorUCInStringFormat);
            
                bool            operator ==         (const StringVectorUC &stringVectorUC) const ;
                bool            operator !=         (const StringVectorUC &stringVectorUC) const ;
                StringVectorUC &operator  =         (const StringVectorUC &stringVectorUC);

                string          getPlainString      () const;


        // Now the data members

    private:
                vector<string>  m_pStringVector;
                bool            m_pIsUserConfigured;
};

}
#endif //STRINGVECTORUC_H
