#include "pch.h"
#include "i18n.h"
#include "../Header/TranslationAPI.h"
#include <string>
using namespace std;

void InitI18n(const string &langPack)
{
	Translation::load(langPack);
}