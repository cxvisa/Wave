/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Brian Adaniya                                                *
 ***************************************************************************/

#ifndef WAVECONDITIONSETBUILDER_H
#define WAVECONDITIONSETBUILDER_H

#include "Framework/Attributes/AttributeTypes.h"

#include <vector>
#include <map>

using namespace std;

namespace WaveNs
{

class Attribute;

class WaveConditionSetBuilder
{
    private :
        class WaveConditionSet
        {
            private :
            protected :
            public :
                                                    WaveConditionSet                (const string &waveConditionSetName);            
                virtual                            ~WaveConditionSet                ();            

                const   string                     &getConditionSetName             () const; 
                        void                        addAttributeToConditionSet      (Attribute *pAttribute, AttributeConcatenationOperator concatenationOperation, AttributeConditionOperator conditionOperation);
                        string                      getSql                          ();

            // Now the data members
            private :
                        string                                              m_conditionSetName;
                        vector<Attribute *>                                 m_attributes;
                        map<Attribute *, AttributeConcatenationOperator>    m_attributeConcatenationOperatorsMap;
                        map<Attribute *, AttributeConditionOperator>        m_attributeConditionOperatorsMap;

            protected :
            public :
        };

                bool                                        isConditionSetFound                     (const string &conditionSetName);
                bool                                        isConditionSetCombinationSyntaxCorrect  (const string &conditionSetCombination);

    protected :
    public :
                                                            WaveConditionSetBuilder                 ();
        virtual                                            ~WaveConditionSetBuilder                 ();

                string                                      getSql                                  () const;

                void                                        createConditionSet                      (const string &conditionSetName);
                void                                        addAttributeToConditionSet              (const string &conditionSetName, Attribute *pAttribute, AttributeConcatenationOperator concatenationOperation, AttributeConditionOperator operation);
                void                                        combineConditionSets                    (const string &conditionSetCombination);


    // Now the data members
    private :
                map<string, WaveConditionSet *>             m_conditionSets;                   
                string                                      m_conditionSetCombinationSql;

    protected :
    public :
};

}

#endif // WAVECONDITIONSETBUILDER_H
