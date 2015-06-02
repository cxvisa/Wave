/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Balachandar Mani											   *
 ***************************************************************************/

#ifndef WAVE_CONFIGURATION_SEGMENT_CONTEXT_H
#define WAVE_CONFIGURATION_SEGMENT_CONTEXT_H

#include <string>
#include "Framework/ObjectModel/ObjectId.h"

namespace WaveNs
{

class WaveConfigurationSegmentContext
{
    private :
    protected :
    public :
                WaveConfigurationSegmentContext ();
               ~WaveConfigurationSegmentContext ();

                string          getManagedObjectClassName                       () const;
                void            setManagedObjectClassName                       (const string &managedObjectClassName);

                ObjectId        getOperateOnWaveManagedObjectId                 () const;
                void            setOperateOnWaveManagedObjectId                 (const ObjectId &waveManagedObjectId);

                vector<UI32>    getAttributeUserTags                            () const;
                void            setAttributeUserTags                            (const vector<UI32> &attributeUserTags);

                vector<string>  getAttributeNames                               () const;
                void            setAttributeNames                               (const vector<string> &attributeNames);

                vector<string>  getAttributeValues                              () const;
                void            setAttributeValues                              (const vector<string> &attributeValues);

                ObjectId        getParentObjectId                               () const;
                void            setParentObjectId                               (const ObjectId &parentObjectId);

                UI32            getChildUserTag                                 () const;
                void            setChildUserTag                                 (const UI32 &childUserTag);

                LocationId      getLocationId                                   () const;
                void            setLocationId                                   (const LocationId &locationId);

                ResourceId    getConfigHandlerStatus () const;
                void          setConfigHandlerStatus (const ResourceId configHandlerStatus);

                string        getErrorString () const;

    // Member variables - start
    private :
                LocationId              m_locationId;
    protected :
    public :
        string                  m_managedObjectClassName;
        ObjectId                m_operateOnWaveManagedObjectId;
        vector<UI32>            m_attributeUserTags;
        vector<string>          m_attributeNames;
        vector<string>          m_attributeValues;
        ObjectId                m_parentObjectId;
        UI32                    m_childUserTag;
        ResourceId              m_configHandlerStatus;
};
}

#endif
