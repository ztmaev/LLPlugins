#pragma once
#include <string>

void InitI18n(const std::string& langPack);

#ifndef _TRS
	#define _TRS(x) (tr(x))
#endif

#ifndef _TR
	#define _TR(x) (trc(x))
#endif