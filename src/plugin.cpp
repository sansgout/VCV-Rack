#include "plugin.hpp"
#include <math.h>
Plugin* pluginInstance;


void init(Plugin* p) {
	pluginInstance = p;

	// Add modules here
	// p->addModel(modelMyModule);
	p->addModel(modelMerge8);
	p->addModel(modelMerge16);
	p->addModel(modelSplit8);
	p->addModel(modelSplit16);
	p->addModel(modelSplitMerge);
}