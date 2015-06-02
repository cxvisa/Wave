#ifndef DISTRIBUTEDDEBUGPARAMETERS_H
#define DISTRIBUTEDDEBUGPARAMETERS_H

#include <vector>

#include "Framework/Types/Types.h"

using namespace std;

namespace WaveNs
{

class DistributedDebugParameters
{

   public:
                                        DistributedDebugParameters      ();
                                        DistributedDebugParameters      (const string & inputStringFromScript, const string & nosOrBash, const string & commaDelimitedLocations);
        virtual                        ~DistributedDebugParameters      ();

                void                    setInputStringFromScript        (const string & inputStringFromScript);
        const   string &                getInputStringFromScript        () const;
                void                    setNosOrBash                    (const string & nosOrBash);
        const   string &                getNosOrBash                    () const;
                void                    setCommaDelimitedLocationIds    (const string & commaDelimitedLocationIds);
        const   string &                getCommaDelimitedLocationIds    () const;
                void                    setOutputStringVector           (const vector<string> & outputStringVector);
        const   vector<string> &        getOutputStringVector           () const;
                void                    setLocationsToRunDebugScript    (const vector<LocationId> & locationsToRunDebugScript);
        const   vector<LocationId> &    getLocationsToRunDebugScript    () const;

   private:

                string                  m_inputStringFromScript;
                string                  m_nosOrBash;
                string                  m_commaDelimitedLocationIds;
                vector<LocationId>      m_locationsToRunDebugScript;
                vector<string>          m_outputStringVector;
};

}

#endif // DISTRIBUTEDDEBUGPARAMETERS_H
