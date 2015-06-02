/***************************************************************************
 *   Copyright (C) 2005-2008 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vidyasagara Reddy Guntaka                                    *
 ***************************************************************************/

#ifndef REDUNDANCYOPTIMIZERBASE_H
#define REDUNDANCYOPTIMIZERBASE_H

#include <string>
#include <map>
#include <ftw.h>

#include "Mathematics/Z2/Z2.h"

using namespace std;

namespace WaveNs
{

class RedundancyOptimizerBase
{
    private :
    protected :
                 RedundancyOptimizerBase ();
        virtual ~RedundancyOptimizerBase ();

    public :
        virtual UI64 getOriginalSize                  () const;
        virtual UI64 getTotalNumberOfChunks           () const;
        virtual UI64 getTotalNumberOfUniqueChunks     () const;
        virtual UI64 getOptimizedSize                 () const;
        virtual bool getEnableCompression             () const;
        virtual void setEnableCompression             (const bool &enableCompression);
        virtual bool getStoreUniqueChunkData          () const;
        virtual void setStoreUniqueChunkData          (const bool &storeUniqueChunkData);
        virtual bool getResetPerFile                  () const;
        virtual void setResetPerFile                  (const bool &resetPerFile);
        virtual bool getPrintFileNameOnly             () const;
        virtual void setPrintFileNameOnly             (const bool &printFileNameOnly);
        virtual bool getPrintPerFileStatistics        () const;
        virtual void setPrintPerFileStatistics        (const bool &printPerFileStatistics);
        virtual UI64 getOptimizedCompressedSize       () const;
        virtual UI64 getFileIoSize                    () const;
        virtual void setFileIoSize                    (const UI64 &fileIoSize);
        virtual UI64 getFixedChunkSize                () const;
        virtual void setFixedChunkSize                (const UI64 &fixedChunkSize);

        virtual void  optimizeFile                    (const string &fileName)                                              = 0;
        virtual void  optimizePath                    (const string &baseDirectoryName);

        virtual void  print                           ()                                                                    = 0;
        virtual void  printStatistics                 () const;
        virtual void  printStatisticsHeader1          () const;
        virtual void  printStatisticsHeader2          () const;
        virtual void  printStatisticsHeader           () const;
        virtual void  printStatisticsHorizontal       (const string &currentFileName) const;
        virtual void  printGlobalStatisticsHeader1    () const;
        virtual void  printGlobalStatisticsHeader2    () const;
        virtual void  printGlobalStatisticsHeader     () const;
        virtual void  printGlobalStatisticsHorizontal () const;

        virtual void  destroyUniqueChunks             ()                                                                    = 0;
        virtual void  resetCounts                     ();
        virtual void  reset                           ();

        virtual int   fileTreeWalk                    (const char *filePath, const struct stat *pStatBuffer, int typeFlag);

        static  int   fileTreeWalkCallback            (const char *filePath, const struct stat *pStatBuffer, int typeFlag);

        static void   displayUsage                    (const string &command);
        static UI32   optimizePathDebugShellEntree    (UI32 argc, vector<string> argv);

    // Now the data members

    private :
    protected :
        Z2     m_z2;

        bool   m_enableCompression;
        bool   m_storeUniqueChunkData;
        bool   m_resetPerFile;
        bool   m_printFileNameOnly;
        bool   m_printPerFileStatistics;

        UI64   m_globalOriginalSize;
        UI64   m_globalTotalNumberOfChunks;
        UI64   m_globalTotalNumberOfUniqueChunks;
        UI64   m_globalOptimizedSize;
        UI64   m_globalOptimizedCompressedSize;

        UI64   m_originalSize;
        UI64   m_totalNumberOfChunks;
        UI64   m_totalNumberOfUniqueChunks;
        UI64   m_optimizedSize;
        UI64   m_optimizedCompressedSize;

        UI64   m_fileIoSize;
        UI64   m_fixedChunksize;

    public :
};

}

#endif // REDUNDANCYOPTIMIZERBASE_H
