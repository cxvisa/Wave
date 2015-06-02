/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Raymond Lai		                                           *
 ***************************************************************************/

#ifndef LARGEOBJECT_H
#define LARGEOBJECT_H

#include "Framework/Types/Types.h"

namespace WaveNs
{

class LargeObject
{
    private:
              void          construct			(const UI32 &numberOfBytes);
              void          destroy				();
			  void			resizewithoutcopy	(const UI32 &numberOfBytes);
              void          copy				(const LargeObject &largeObject);

    protected:
    public:
                            LargeObject			();
                            LargeObject			(const UI32 &numberOfBytes);
                            LargeObject			(const LargeObject &largeObject);
							~LargeObject		();

              void          resize				(const UI32 &numberOfBytes);
              string        toString			() const;
              void          fromString			(const string &largeObjectInStringFormat, const UI32 &noOfBytes = 0);
			  UI32			getNumberOfBytes	() const;
			  UI8			operator []			(const UI32 &index);
              bool          operator ==			(const LargeObject &largeObject) const;
              bool          operator !=			(const LargeObject &largeObject) const;
              LargeObject  	&operator =			(const LargeObject &largeObject);


            // now the data members
    private:
              UI8			*m_pByteBlocks;
              UI32        	m_numberOfBytes;

    protected:
    public:
};

}

#endif    // LARGEOBJECT_H
