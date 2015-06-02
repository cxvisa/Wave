/***************************************************************************
 *   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef WAVEUSERMANAGEDOBJECT_H
#define WAVEUSERMANAGEDOBJECT_H

#include "Framework/ObjectModel/WaveManagedObject.h"

namespace WaveNs
{

class WaveUserManagedObject : public WaveManagedObject
{
    private :
        virtual void setupAttributesForPersistence ();
        virtual void setupAttributesForCreate      ();

    protected :
    public :
                                  WaveUserManagedObject       (WaveObjectManager *pWaveObjectManager);
                                  WaveUserManagedObject       (WaveObjectManager *pWaveObjectManager, const string &name);
        virtual                  ~WaveUserManagedObject       ();

        static  string            getClassName                ();

                UI32              getUserId                   () const;
                void              setUserId                   (const UI32 &userId);

                ObjectId          getGroupObjectId            () const;
                void              setGroupObjectId            (const ObjectId &groupObjectId);

                vector<ObjectId>  getAssociatedGroupObjectIds () const;
                void              setAssociatedGroupObjectIds (const vector<ObjectId> &associatedGroupObjectIds);

                string            getEncryptedPassword        () const;
                void              setEncryptedPassword        (const string &encryptedPassword);

                bool              getIsActive                 () const;
                void              setIsActive                 (const bool &isActive);

                string            getHomeDirectory            () const;
                void              setHomeDirectory            (const string &homeDirectory);


    // Now the data members

    private :
        UI32             m_userId;
        ObjectId         m_groupObjectId;
        vector<ObjectId> m_associatedGroupObjectIds;
        string           m_encryptedPassword;
        bool             m_isActive;
        string           m_homeDirectory;

    protected :
    public :
};

}
#endif // WAVEUSERMANAGEDOBJECT_H
