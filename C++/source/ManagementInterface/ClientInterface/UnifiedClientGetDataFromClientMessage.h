/***************************************************************************
 *   Copyright (C) 2012 Vidyasagara Guntaka                                 *
 *   All rights reserved.                                                   *
 *   Author : Anil C                                                        *
 ***************************************************************************/

#ifndef UNIFIEDCLIENTGETDATAMESSAGE_H 
#define UNIFIEDCLIENTGETDATAMESSAGE_H 

#include "ManagementInterface/ManagementInterfaceMessage.h"

namespace WaveNs
{   

class UnifiedClientGetDataFromClientMessage : public ManagementInterfaceMessage
{   
    private:
    protected:
        virtual         void        setupAttributesForSerialization ();

    public:
                                    UnifiedClientGetDataFromClientMessage   (); 
                                    UnifiedClientGetDataFromClientMessage   ( UI32 numberOfRecordsRequested, UI32 commandCode, UI32 commandType );
        virtual                    ~UnifiedClientGetDataFromClientMessage   ();

        virtual const   void       *getCStructureForInputs          ();
        virtual         void        loadOutputsFromCStructure       (const void *pOutputCStructure);

        virtual         void        deleteCStructureForInputs       (const void *pInputStruct);

                        void        setEnablePaginate               ( const bool &enablePaginate );
                        bool        getEnablePaginate               ( ) const;
            
                        void        setNumberOfRecordsRequested     ( const UI32 &numberOfRecordsRequested );
                        UI32        getNumberOfRecordsRequested     ( ) const;

                        void        setCommandCode                  ( const UI32 &commandCode );
                        UI32        getCommandCode                  ( ) const ;

                        void        setCommandType                  ( const UI32 &commandType );
                        UI32        getCommandType                  ( ) const ;

                        void        setNumberOfCommandStrings       (const SI32 numberOfCommandStrings);
                        SI32        getNumberOfCommandStrings       () const;

                        void        setCommandStrings               (const vector<string> &commandStrings);
                    vector<string>  getCommandStrings               () const;                        

// Now the data members

    private:
    protected:
    public:
                bool            m_enablePaginate;
                UI32            m_numberOfRecordsRequested;   
                UI32            m_commandCode;
                UI32            m_commandType;    
                SI32            m_numberOfCommandStrings;
                vector<string>  m_commandStrings;

};

}
#endif  //UNIFIEDCLIENTGETDATAMESSAGE_H
                            
