/***************************************************************************
 *   Copyright (C) 2005 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef FRAMEWORKSEQUENCEGENERATORFACTORY_H
#define FRAMEWORKSEQUENCEGENERATORFACTORY_H

namespace WaveNs
{

typedef enum
{
    FRAMEWORK_SEQUENCE_TYPE0 = 0,
    FRAMEWORK_SEQUENCE_TYPE1,
    FRAMEWORK_SEQUENCE_TYPE2
} FrameworkSequenceType;

class FrameworkSequenceGenerator;

class FrameworkSequenceGeneratorFactory
{
    private :
    protected :
    public :
        static FrameworkSequenceGenerator *obtainFrameworkSequenceGenerator (FrameworkSequenceType framewokSequenceType);

    // Now the data members

    private :
    protected :
    public :
};

}

#endif // FRAMEWORKSEQUENCEGENERATORFACTORY_H
