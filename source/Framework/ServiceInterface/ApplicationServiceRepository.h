/***************************************************************************
 *   Copyright (C) 2005-2007 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef APPLICATIONSERVICEREPOSITORY_H
#define APPLICATIONSERVICEREPOSITORY_H

#include "Framework/Types/Types.h"
#include <map>
#include <vector>

namespace WaveNs
{

class ApplicationService;
class ApplicationLocalService;

class ApplicationServiceRepository
{
    private :
    protected :
    public :
                                             ApplicationServiceRepository   ();
                                            ~ApplicationServiceRepository   ();

               void                          addNewApplicationService       (const UI32 &newApplicationServiceId, const string &newApplicationServiceName);
               void                          addNewApplicationLocalService  (const UI32 &newApplicationLocalServiceId, const string &newApplicationLocalServiceName);
               bool                          isAnApplicationLocalService    (const UI32 &applicationServiceId);
               ApplicationService           *getApplicationService          (const UI32 &applicationServiceId);
               ApplicationLocalService      *getApplicationLocalService     (const UI32 &applicationServiceId);
               void                          createApplicationServices      ();
               void                          createApplicationLocalServices ();

               void                          getApplicationServiceIds       (vector<UI32> &applicationServiceIds);
               void                          getApplicationLocalServiceIds  (vector<UI32> &applicationLocalServiceIds);

        static ApplicationServiceRepository *getInstance                    ();

    // Now the data members

    private :
        map<UI32, string>                    m_applicationServiceNamesMap;
        map<UI32, ApplicationService *>      m_applicationServicesMap;
        map<UI32, string>                    m_applicationLocalServiceNamesMap;
        map<UI32, ApplicationLocalService *> m_applicationLocalServicesMap;

    protected :
    public :
};

}

#endif // APPLICATIONSERVICEREPOSITORY_H
