#pragma once

#include <rack.hpp>
#include "components.hpp"

using namespace rack;

extern Plugin *pluginInstance;

// Declare the Plugin, defined in plugin.cpp
extern Plugin* pluginInstance;

// Declare each Model, defined in each module source file
// extern Model* modelMyModule;
extern Model* modelMerge8;
extern Model* modelMerge16;
extern Model* modelSplit8;
extern Model* modelSplit16;
extern Model* modelSplitMerge;
