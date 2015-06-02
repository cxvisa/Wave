/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEGROUPMANAGEDOBJECT_H
#define WAVEGROUPMANAGEDOBJECT_H

#include "Framework/ObjectModel/WaveManagedObject.h"

namespace WaveNs
{

class WaveGroupManagedObject : public WaveManagedObject
{
    private :
        virtual void setupAttributesForPersistence ();
        virtual void setupAttributesForCreate      ();

    protected :
    public :
                                  WaveGroupManagedObject       (WaveObjectManager *pWaveObjectManager);
                                  WaveGroupManagedObject       (WaveObjectManager *pWaveObjectManager, const string &name);
        virtual                  ~WaveGroupManagedObject       ();

        static  string            getClassName                 ();

                UI32              getGroupId                   () const;
                void              setGroupId                   (const UI32 &groupId);

                bool              getIsActive                  () const;
                void              setIsActive                  (const bool &isActive);

                vector<ObjectId>  getAssociatedUserObjectIds   () const;
                void              setAssociatedUserObjectIds   (const vector<ObjectId> &associatedUserObjectIds);
                void              addAssociatedUserObjectId    (const ObjectId &associatedUserObjectId);
                void              deleteAssociatedUserObjectId (const ObjectId &associatedUserObjectId);
                bool              isAnAssociatedUserObjectId   (const ObjectId &associatedUserObjectId) const;

    // Now the data members

    private :
        UI32             m_groupId;
        bool             m_isActive;
        vector<ObjectId> m_associatedUserObjectIds;

    protected :
    public :
};

}

#endif // WAVEGROUPMANAGEDOBJECT_H
