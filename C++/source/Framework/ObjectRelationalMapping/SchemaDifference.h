/***************************************************************************
 *   Copyright (C) 2011 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Mayur Mahajan                                                *
 ***************************************************************************/

#ifndef SCHEMADIFFERENCE_H
#define SCHEMADIFFERENCE_H

#include "Framework/Types/Types.h"

#include <vector>

namespace WaveNs
{
template <class _Tdiff>
class SchemaDifference
{
    private :
    protected :
    public :
                                SchemaDifference                ();
                                ~SchemaDifference               ();

                bool            hasDifferences                  () const;
          const vector<_Tdiff>  &getAdditions                   () const;
          const vector<_Tdiff>  &getDeletions                   () const;
          const vector<_Tdiff>  &getChanges                     () const;
                void            insertAddition                  (const _Tdiff &difference);
                void            insertDeletion                  (const _Tdiff &difference);
                void            insertChange                    (const _Tdiff &difference);

    // Now the data members

    private :
            vector<_Tdiff>  m_additionsVec;
            vector<_Tdiff>  m_deletionsVec;
            vector<_Tdiff>  m_changesVec;
    protected :
    public :
};

}
#endif //SCHEMADIFFERENCE_H

