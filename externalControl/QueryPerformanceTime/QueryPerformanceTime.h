#pragma once

class  CQueryPerformanceTime
{
public:
	CQueryPerformanceTime(void);
	~CQueryPerformanceTime(void);

private:
private:
	LARGE_INTEGER m_freq;   
	LARGE_INTEGER m_start;    
	LARGE_INTEGER m_end; 

public:
	void Start();
	LONGLONG End();
};
