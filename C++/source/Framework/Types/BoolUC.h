/***************************************************************************
 *   Copyright (C) 2010 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Himanshu Varshney                                            *
 ***************************************************************************/

#ifndef BOOLUC_H
#define BOOLUC_H

#include <string>
#include "Framework/Types/Types.h"

namespace WaveNs
{

class BoolUC
{
    private:
    protected:
    public:
                                      BoolUC                      ();
                                      BoolUC                      (const bool &pBool);
                                      BoolUC                      (const bool &pBool, const bool &isUserConfigured);
                                      BoolUC                      (const BoolUC &boolUC);
                                      
                  void                setBoolValue                (const bool &pBool);
                  bool                getBoolValue                () const;
                                      
                  void                setIsUserConfigured         (const bool &isUserConfigured);
                  bool                getIsUserConfigured         () const;
                                      
                  string              toString                    ();
                  void                fromString                  (const string &pBoolUCInStringFormat);
        
                  void                getPlainString              (string &valueString) const;
                  ResourceId          loadFromPlainString         (const string &pBoolUCInPlainStringFormat);
                                      
                  bool                operator == (const BoolUC &pBoolUC)  const ;
                  bool                operator != (const BoolUC &pBoolUC)  const ;
                  BoolUC               &operator  = (const BoolUC &pBoolUC);


        // Now the data members

    private:
                bool    m_pBool;
                bool    m_pIsUserConfigured;
};

}

#endif //BOOLUC_H
