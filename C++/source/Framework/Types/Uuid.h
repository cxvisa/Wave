#ifndef UUID_H
#define UUID_H

#include "Framework/Types/Types.h"
#include "uuid/uuid.h"
#include <string>

namespace WaveNs
{

class Uuid
{

    private:
    protected:
    public:
                Uuid             ();
                Uuid             (const string &uuidInStringFormat);
                Uuid             (const Uuid &uuid);
               ~Uuid             ();

        string  toString         ()                                     const;
        bool    fromString       (const string &uuidInStringFormat);

        bool    operator ==      (const Uuid &uuid)                     const;
        bool    operator !=      (const Uuid &uuid)                     const;
        Uuid    &operator =      (const Uuid &uuid);

        void    getUuid          (uuid_t out)                           const;
        string  getUuidString    ()                                     const;
        UI64    getUuidHash      ()                                     const;

        void    clear            ();

    // Now the data members
    private:
        uuid_t      m_uuidInBinary;

    protected:
    public:
};

}

#endif //UUID_H
