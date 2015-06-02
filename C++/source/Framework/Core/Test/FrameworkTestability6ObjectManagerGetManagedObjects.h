/***************************************************************************
 *   Copyright (C) 2005-2010 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef FRAMEWORKTESTABILITY6OBJECTMANAGERGETMANAGEDOBJECTS_H
#define FRAMEWORKTESTABILITY6OBJECTMANAGERGETMANAGEDOBJECTS_H

#include "ManagementInterface/ManagementInterfaceMessage.h"

namespace WaveNs
{

class FrameworkTestability6ObjectManagerGetManagedObjects : public ManagementInterfaceMessage
{
private :
    virtual void setupAttributesForSerialization ();

protected :
public :
    FrameworkTestability6ObjectManagerGetManagedObjects ();
    FrameworkTestability6ObjectManagerGetManagedObjects(const string &managedObjectClassName, const string &schemaName);
    virtual                ~FrameworkTestability6ObjectManagerGetManagedObjects ();

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

#endif // FRAMEWORKTESTABILITY6OBJECTMANAGERGETMANAGEDOBJECTS_H
