#include "plugin.hpp"

struct Split16 : Module {
	enum ParamIds {
		NUM_PARAMS
	};
	enum InputIds {
		POLY_IN_B,
		NUM_INPUTS
	};
	enum OutputIds {
        ENUMS(OUTPUTS_B,16),
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};
	
	int channels[2];

	Split16() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		onReset();
	}

	void onReset() override {
		channels[0] = -1;
		channels[1] = -1;
	}

    	void process(const ProcessArgs& args) override {
		for (int c = 0; c < 16; c++) {
			float v = inputs[POLY_IN_B].getVoltage(c);
			outputs[OUTPUTS_B + c].setVoltage(v);
		}
	}
};

struct Split16Widget : ModuleWidget {
	Split16Widget(Split16* module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Split16.svg")));

		{		
            for(int i = 0; i < 16; i++) {
		        addOutput(createOutputCentered<MicroPort>(mm2px(Vec(5.08, 5.00 + 7.35 * i)), module, Split16::OUTPUTS_B + i));
		    }
		    addInput(createInputCentered<SmallPort>(mm2px(Vec(5.08, 123.50)), module, Split16::POLY_IN_B));
        }

	}
};

Model* modelSplit16 = createModel<Split16, Split16Widget>("Split16");