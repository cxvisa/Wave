/***************************************************************************
 *   Copyright (C) 2010 Vidyasagara Guntaka                               *
 *   All rights reserved.                                                 *
 *   Author : Aashish Akhouri                                             *
 ***************************************************************************/

#ifndef WAVEMANAGEDOBJECTTOOLKIT_H
#define WAVEMANAGEDOBJECTTOOLKIT_H

#include <vector>

using namespace std;
namespace WaveNs
{
class WaveManagedObject;
class Attribute;

//Class:WaveManagedObjectToolKit
//Description: This class will contain methods to process
// do miscellaneous operations on Managed objects
class WaveManagedObjectToolKit
{

    public :
        //Releases memory from the pointers in the vector as well as 
        // as the pointer to the vector as well
        static void releaseMemoryOfWaveMOVector     (vector<WaveManagedObject *>* & pResults);
        static void releaseMemoryOfAttributeVector  (vector<Attribute *> &attrVector );


    protected :
    private :
        //This class cannot be instantiated
        //and hence not destroyed
         WaveManagedObjectToolKit();
        ~WaveManagedObjectToolKit();

    private :
    protected :
    public :

};

}

#endif // WAVEMANAGEDOBJECTTOOLKIT_H
