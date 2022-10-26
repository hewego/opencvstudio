#pragma once

class AFX_EXT_CLASS hhLibLogger
{
public:
	hhLibLogger();
	~hhLibLogger();

public:
	struct stLogItem_t {
		CString sTitle;
		CString sLog;
		SYSTEMTIME time;
	};

public:
	bool SetLog(stLogItem_t item);
	size_t GetSize();
};