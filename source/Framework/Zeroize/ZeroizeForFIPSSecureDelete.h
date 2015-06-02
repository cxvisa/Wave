/***************************************************************************
 *   Copyright (C) 2005-2011 Vidyasagara Guntaka                           *
 *   All rights reserved.                                                  *
 *   Author : Vadiraj C S
 ***************************************************************************/


#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<ftw.h>
#include<string>
#include "Framework/Trace/TraceMessages.h"
#include "Framework/ObjectModel/WaveObjectManager.h"
#include "Framework/Utils/TraceUtils.h"

namespace WaveNs
{
	class ZeroizeForFIPSSecureDelete
	{
		private:
			ZeroizeForFIPSSecureDelete();
	
		public:
            static const ssize_t BLOCK_SIZE = 4096;
			static void cleanDeleteDir(const string &dirName);
			static void cleanDeleteFile(const char *fpath, const struct stat *psb,bool deleteOnClear = true);
			static int removeFileCallBack(const char *fpath, const struct stat *sb, int typeflag);
			static void secureClearFile(const string &filePath,bool deleteOnClear);
	};
	
}


