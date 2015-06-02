/***************************************************************************
 *   Copyright (C) 2011 Vidyasagara Guntaka                                *
 *   All rights reserved.                                                  *
 *   Author : Mayur Mahajan                                                *
 ***************************************************************************/

#ifndef MOSCHEMAINFOMANAGEDOBJECT_H
#define MOSCHEMAINFOMANAGEDOBJECT_H


namespace WaveNs
{
class MoSchemaInfoManagedObject : public  WaveManagedObject
{
    private :
        virtual void setupAttributesForPersistence ();
        virtual void setupAttributesForCreate      ();
    protected :
    public :
                                MoSchemaInfoManagedObject       (WaveObjectManager *pWaveObjectManager);
        virtual                 ~MoSchemaInfoManagedObject      ();
        const string &          getManagedObjectName            () const;
        const vector<string> &  getManagedObjectFieldNames      () const;
        const vector<string> &  getManagedObjectFieldTypes      () const;
        const vector<string> &  getManagedObjectUserDefinedFieldNames       () const;
        const vector<string> &  getManagedObjectUserDefinedFieldTypes       () const;
        const vector<string> &  getManagedObjectExpandedFieldTypes          () const;
              UI32              getManagedObjectClassId         () const;
              UI32              getManagedObjectParentClassId   () const;
       static string            getClassName                    ();
              bool              getIsALocalManagedObject        () const;
       const  string &          getDerivedFromClassName         () const;        
        
    // Now the data members

    private :
        string                                  m_managedObjectName;
        vector<string>                          m_fieldNames;
        vector<string>                          m_fieldTypes;
        UI32                                    m_classId;
        UI32                                    m_parentClassId;
        vector<string>                          m_expandedFieldTypes;
        vector<string>                          m_userDefinedFieldNames;
        vector<string>                          m_userDefinedFieldTypes;
        bool                                    m_isALocalManagedObject;
        string                                  m_derivedFromClassName;

    protected :
    public :
};
}
#endif //MOSCHEMAINFOMANAGEDOBJECT_H

