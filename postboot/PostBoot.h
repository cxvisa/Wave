#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

using namespace std;

typedef enum // bits in bitmap
{
    WAVE_RECOVERY_TYPE_INVALID = 0,
    WAVE_RECOVERY_TYPE_COLD = 1,
    WAVE_RECOVERY_TYPE_WARM = 2
} configReplayRecoveryTypeEnum;

class configReplayTable {

    private:
        void    printHeader             (string filePath);
        string  printServicePushBack    (string serviceName);
    protected:
    public:
                configReplayTable             ();
               ~configReplayTable             ();

        void    printCpp                (string filePath);
        void    printDotH               (string filePath);
        void    addPass                 (string *tablename, int passNumber, vector< pair<string, int> > pass_service_Name);

    // Data Members 
    private:
        // map of <tablename, map of <pass#, vector of <OM name, recovery type enum>>>
        map<string, map<int, vector <pair<string, int> > > >      configReplayMap;
		
    protected:
    public:
};
