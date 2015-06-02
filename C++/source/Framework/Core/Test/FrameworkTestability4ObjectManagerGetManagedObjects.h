/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef FRAMEWORKTESTABILITY4OBJECTMANAGERGETMANAGEDOBJECTS_H
#define FRAMEWORKTESTABILITY4OBJECTMANAGERGETMANAGEDOBJECTS_H

#include "ManagementInterface/ManagementInterfaceMessage.h"

namespace WaveNs
{

class FrameworkTestability4ObjectManagerGetManagedObjects : public ManagementInterfaceMessage
{
    private :
        virtual void setupAttributesForSerialization ();

    protected :
    public :
                                FrameworkTestability4ObjectManagerGetManagedObjects ();
                                FrameworkTestability4ObjectManagerGetManagedObjects(const string &managedObjectClassName, const string &schemaName);
        virtual                ~FrameworkTestability4ObjectManagerGetManagedObjects ();

                string          getManagedObjectClassName                           () const;
                void            setManagedObjectClassName                           (const string &managedObjectClassName);

                string          getSchemaName                                       () const;
                void            setSchemaName                                       (const string &schemaName);

                UI32            getNumberOfManagedObjects                           () const;
                void            setNumberOfManagedObjects                           (const UI32 &numberOfManagedObjects);

                vector<string> &getManagedObjects                                   ();

                bool            getUseRawFormat                                     () const;
                void            setUseRawFormat                                     (const bool &useRawFormat);

    // now the data members

    private :
        string         m_managedObjectClassName;
        string         m_schemaName;
        UI32           m_numberOfManagedObjects;
        vector<string> m_managedObjects;
        bool           m_useRawFormat;

    protected :
    public :
};

}

#endif // FRAMEWORKTESTABILITY4OBJECTMANAGERGETMANAGEDOBJECTS_H
