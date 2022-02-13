// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "ResourceInformation.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

namespace ScriptPluginUtils {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA
    MCAPI std::unique_ptr<class Scripting::IRuntime> CreateRuntimeByType(enum ScriptRuntimeType, class Scripting::LifetimeRegistry&);
    MCAPI enum ScriptRuntimeType GetRuntimeType(std::string const&);
    MCAPI enum ScriptRuntimeType GetRuntimeTypeFromFileExtension(std::string const&);
    MCAPI extern std::string const JAVA_SCRIPT_RUNTIME_NAME;
    MCAPI struct PluginDefStack PluginDefsFromPackStack(enum ResourceInformation::ResourceType, std::string const&, std::vector<class PackInstance> const&, std::vector<class PackInstance> const&);
    MCAPI std::string SanitizeRuntimeName(std::string const&);

};