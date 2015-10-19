/***************************************************************************
 *   Copyright (C) 2005-2009 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#include <iostream>
#include <strings.h>
#include <string>
#include <map>

#include "Framework/Core/Wave.h"
#include "Framework/Core/WaveFrameworkConfiguration.h"
#include "WaveResourceIds.h"

using namespace std;
using namespace WaveNs;

void displayUsage (const char *pProgramName)
{
    cout << "USAGE:" << endl;
    cout << pProgramName << "<-cfgfile <File Path> [[name<=value>]*] [-showattributes]>";
    cout << endl;
    cout << endl;
    cout << "Command Line Options:" << endl;
    cout << endl;
}

int main (int argc, char *argv[])
{
    int                 i                        = 0;
    map<string, string> nameValueMap;
    vector<string>      tokenizedStrings;
    UI32                numberOfTokenizedStrings = 0;
    string              commandLineArgument;
    string              configurationFileName;
    bool                showAttributeNames       = false;
    vector<string>      attributeNames;

    for (i = 1; i < argc; i++)
    {
        if (0 == (strncmp ("-cfgfile", argv[i], sizeof ("-cfgfile"))))
        {
            if (argc > (i + 1))
            {
                configurationFileName = argv[i + 1];

                i++;
            }
            else
            {
                displayUsage (argv[0]);
                return (-1);
            }
        }
        else if (0 == (strncmp ("-showattributenames", argv[i], sizeof ("-showattributenames"))))
        {
            showAttributeNames = true;
        }
        else
        {
            commandLineArgument = argv[i];

            tokenizedStrings.clear ();
 
            StringUtils::tokenize (commandLineArgument, tokenizedStrings, '=');

            numberOfTokenizedStrings = tokenizedStrings.size ();

            if (2 == numberOfTokenizedStrings)
            {
                nameValueMap[tokenizedStrings[0]] = tokenizedStrings[1];
            }
            else
            {
                displayUsage (argv[0]);
                return (-2);
            }
        }
    }

    if ("" != configurationFileName)
    {
        WaveNs::initializeWaveResourceIds ();

        WaveFrameworkConfiguration waveFrameworkConfiguration;

        waveFrameworkConfiguration.loadConfiguration (configurationFileName);

        cout << "Initial Configuration" << endl;

        waveFrameworkConfiguration.displayToTerminal ();

        map<string, string>::const_iterator element    = nameValueMap.begin ();
        map<string, string>::const_iterator endElement = nameValueMap.end   ();

        while (endElement != element)
        {
            Attribute *pAttribute = waveFrameworkConfiguration.getAttribute (element->first);

            if (NULL != pAttribute)
            {
                cout << "setting via attribute." << endl;
                pAttribute->fromString (element->second);
            } 

            element++;
        }

        if (true == showAttributeNames)
        {
            waveFrameworkConfiguration.getAllAttributeNames (attributeNames);

            UI32 numberOfAttributeNames = attributeNames.size ();
            UI32 j                      = 0;
 
            cout << "Total Number of Attribute Names : " << numberOfAttributeNames << endl;
            
            for (j = 0; j < numberOfAttributeNames; j++)
            {
                printf ("%03u. %s\n", j, attributeNames[j].c_str ());
            }
        }
        else
        {
            cout << "Final Configuration" << endl;

            waveFrameworkConfiguration.displayToTerminal ();

            waveFrameworkConfiguration.saveConfiguration (configurationFileName);
        }
    }
    else
    {
        displayUsage (argv[0]);
        return (-3);
    }

    return (0);
}
