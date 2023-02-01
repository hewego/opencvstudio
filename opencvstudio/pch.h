// pch.h: 미리 컴파일된 헤더 파일입니다.
// 아래 나열된 파일은 한 번만 컴파일되었으며, 향후 빌드에 대한 빌드 성능을 향상합니다.
// 코드 컴파일 및 여러 코드 검색 기능을 포함하여 IntelliSense 성능에도 영향을 미칩니다.
// 그러나 여기에 나열된 파일은 빌드 간 업데이트되는 경우 모두 다시 컴파일됩니다.
// 여기에 자주 업데이트할 파일을 추가하지 마세요. 그러면 성능이 저하됩니다.

#ifndef PCH_H
#define PCH_H

// 여기에 미리 컴파일하려는 헤더 추가
#include "framework.h"


#include <vector>
#include <queue>
#include <numeric>
#include <direct.h>
#include <ppl.h>
#include <concurrent_vector.h>
#include <concurrent_queue.h>
using namespace concurrency;
using namespace std;


//
//
#define DEF_MAX_VIEW 6


//
//Log
#define LOG_MAIN	_T("log_main")


//
//Opencv
#include "..\\ExternalControl\\Opencv34\\include.h"


//
//hhLib
#include "..\\ExternalControl\\hhLib\\hhLibINIDataStr.h"
#include "..\\ExternalControl\\hhLib\\hhLibINIDataInt.h"
#include "..\\ExternalControl\\hhLib\\hhLibINIDataRect.h"
#include "..\\ExternalControl\\hhLib\\hhLibLogger.h"
#include "..\\ExternalControl\\hhLib\\hhLibFileVersion.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\ExternalControl\\hhLib\\hhLibd.lib")
#else
#pragma comment(lib, "..\\ExternalControl\\hhLib\\hhLib.lib")
#endif


//
//hhLibImageControl
#include "..\\ExternalControl\\hhLibImageControl\\hhLibImageControlUI.h"
#ifdef _DEBUG
#pragma comment(lib, "..\\ExternalControl\\hhLibImageControl\\hhLibImageControld.lib")
#else
#pragma comment(lib, "..\\ExternalControl\\hhLibImageControl\\hhLibImageControl.lib")
#endif


//
#include "..\\ExternalControl\\QueryPerformanceTime\\QueryPerformanceTime.h"
#include "..\\ExternalControl\\LabelCtrl\\LabelCtrl.h"
#include "..\\ExternalControl\\INIFile\\INIFile.h"
#include "..\\ExternalControl\\safequeue\\safequeue.h"
#include "..\ExternalControl\GridCtrl\GridCtrl_src\GridCtrl.h"
#include "..\ExternalControl\GridCtrl\NewCellTypes\GridCellCombo.h"


#endif //PCH_H
