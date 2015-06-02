/***************************************************************************
 *   Copyright (C) 2011 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Cindy Hou                                                    *
 ***************************************************************************/

#ifndef UI32VECTORUC_H
#define UI32VECTORUC_H

#include <string>
#include "Framework/Types/Types.h"

namespace WaveNs
{

class UI32VectorUC
{
    private:
    protected:
    public:
                              UI32VectorUC        ();
                              UI32VectorUC        (const vector<UI32> &ui32Vector);
                              UI32VectorUC        (const vector<UI32> &ui32Vector, const bool &isUserConfigured);
                              UI32VectorUC        (const UI32VectorUC &ui32VectorUC);
                             ~UI32VectorUC        ();

                void          setUI32Vector       (const vector<UI32> &ui32Vector);
                vector<UI32>  getUI32Vector       () const;

                void          setIsUserConfigured (const bool &isUserConfigured);
                bool          getIsUserConfigured () const;
    
                void          toString            (string &valueString);
                void          fromString          (const string &ui32VectorUCInStringFormat);
            
                bool          operator ==         (const UI32VectorUC &ui32VectorUC) const ;
                bool          operator !=         (const UI32VectorUC &ui32VectorUC) const ;
                UI32VectorUC &operator  =         (const UI32VectorUC &ui32VectorUC);


        // Now the data members

    private:
                vector<UI32>  m_pUI32Vector;
                bool          m_pIsUserConfigured;
};

}
#endif //UI32VECTORUC_H
