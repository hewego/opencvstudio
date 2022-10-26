#include "pch.h"
#include "QueryPerformanceTime.h"

CQueryPerformanceTime::CQueryPerformanceTime(void)
{
	QueryPerformanceFrequency(&m_freq);
	Start();
}

CQueryPerformanceTime::~CQueryPerformanceTime(void)
{
}

void CQueryPerformanceTime::Start()
{
	QueryPerformanceCounter(&m_start);
}

LONGLONG CQueryPerformanceTime::End()
{
	double      m_Time;
	QueryPerformanceCounter(&m_end);
	m_Time = ((double)(m_end.QuadPart - m_start.QuadPart) / m_freq.QuadPart * 1000);
	QueryPerformanceCounter(&m_start);
	return m_Time;
}