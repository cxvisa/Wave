/***************************************************************************
*   Copyright (C) 2005-2012 Vidyasagara Guntaka                           *
*   All rights reserved.                                                  *
*   Author :Chaitanya Gangwar                                             *
***************************************************************************/

#ifndef DATABASEOBJECTMANAGERCREATEINMEMORYMANAGEDOBJECTMESSAGE_H
#define DATABASEOBJECTMANAGERCREATEINMEMORYMANAGEDOBJECTMESSAGE_H

namespace WaveNs
{

class DatabaseObjectManagerCreateInMemoryManagedObjectMessage : public WaveMessage
{
    private :
    protected :
    public :
                            DatabaseObjectManagerCreateInMemoryManagedObjectMessage (const  string &className, WaveObjectManager *pWaveObjectManager);
            virtual        ~DatabaseObjectManagerCreateInMemoryManagedObjectMessage ();
            
                    string              getClassName            () const;
                    void                setInMemoryMO           (WaveManagedObject *inMemoryManagedObject);
                    WaveManagedObject*  getInMemoryMO           () const; 
                    WaveObjectManager*  getPWaveObjectManager   () const;

    
    private :
        string            m_className;
        WaveManagedObject *m_pInMemoryManagedObject;
        WaveObjectManager *m_pWaveObjectManager;

    protected :
    public :

};

}
#endif
