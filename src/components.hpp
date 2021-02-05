using namespace rack;

extern Plugin *pluginInstance;

struct SmallPort : app::SvgPort {
	SmallPort() {
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/SmallPort.svg")));
	}
};

struct MicroPort : app::SvgPort {
	MicroPort() {
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/MicroPort.svg")));
	}
};

struct MicroPortblue : app::SvgPort {
	MicroPortblue() {
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/MicroPort-blue.svg")));
	}
};

struct MicroPortpink : app::SvgPort {
	MicroPortpink() {
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/MicroPort-pink.svg")));
	}
};