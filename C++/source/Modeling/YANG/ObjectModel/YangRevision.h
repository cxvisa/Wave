/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef YANGREVISION_H
#define YANGREVISION_H

#include "Modeling/YANG/ObjectModel/YangElement.h"
#include "Framework/Types/Date.h"

namespace WaveNs
{

class YangRevision : public YangElement
{
    private :
    protected :
    public :
                            YangRevision   ();
                            YangRevision   (const Date &date);
        virtual            ~YangRevision   ();

        static  string      getYangName    ();

        static YangElement *createInstance ();

                Date        getDate        () const;
                void        setDate        (const Date &date);

    // Now the data members
    private :
        Date m_date;

    protected :
    public :
};

}

#endif // YANGREVISION_H
