#ifndef DATABASEQUERYCURSOR_H
#define DATABASEQUERYCURSOR_H

#include "Framework/ObjectModel/ObjectId.h"
#include "Framework/Attributes/Attributes.h"

#include <string>
#include <vector>
#include <map>

using namespace std;
namespace WaveNs
{

class DatabaseQueryCursor
{
   public :

	DatabaseQueryCursor(WaveObjectManager* callingOm, const string &className, const string& queryString, UI32 pageSize = 23, UI32 startOffset = 0);
	~DatabaseQueryCursor();
	
	void setPageSize(UI32 pageSize);
	UI32 getPageSize() const;
	
	void setStartOffset(UI32 startOffset);
	UI32 getStartOffset() const;
	
//	void setCursorName(string cursorName); //This function may be removed
	string getCursorName() const;

	static string getUniqueCursorName();

	int declareCursor();
	int closeCursor();
	void fetchCursor();
	string getSqlOfFetchCursor();
	int moveCursor(unsigned int count = 23);


   private :
	string			m_cursorName;
	string			m_queryString;
	UI32				m_startOffset;
	UI32				m_pageSize;
	UI8				m_cursorState;
	WaveObjectManager* m_CallingOm;
	string             m_className;
	enum e_cursorStates
	{
		CURSOR_NOT_DECLARED,
		CURSOR_DECLARED,
		CURSOR_CLOSED
	};
};
}

#endif //DATABASEQUERYCURSOR_H
