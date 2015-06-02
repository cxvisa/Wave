/***************************************************************************
 *   Copyright (C) 2005-2013 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef CONFIGURATIONFILE_H
#define CONFIGURATIONFILE_H


#include "Framework/Types/Types.h"

#include <string>

using namespace std;

namespace WaveNs
{

class ConfigurationFile
{
    private :
    protected :
    public :
                        ConfigurationFile        ();
                        ConfigurationFile        (const string &configurationFilePath);
        virtual        ~ConfigurationFile        ();

        virtual void    load                     () = 0;
        virtual void    reload                   () = 0;
        virtual void    reload                   (const string &configurationFilePath) = 0;
        virtual bool    validate                 () const = 0;
        virtual void    print                    () const = 0;

                string  getConfigurationFilePath () const;
                void    setConfigurationFilePath (const string &configurationFilePath);

                bool    getIsAlreadyLoaded       () const;
                void    setIsAlreadyLoaded       (const bool &isAlreadyLoaded);

        // Now the data members

    private :
        string m_configurationFilePath;
        bool   m_isAlreadyLoaded;

    protected :
    public :
};

}

#endif // CONFIGURATIONFILE_H
