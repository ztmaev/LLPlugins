#include "pch.h"
#include "i18n.h"
#include "headers/stl/langPack.h"
#include <string>
using namespace std;

LangPack LangP;

void InitI18n(const string &langPack)
{
	LangP.load(langPack);
}