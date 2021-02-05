#include "plugin.hpp"

struct Split8 : Module {
	enum ParamIds {
		NUM_PARAMS
	};
	enum InputIds {
		POLY_IN_B,
		NUM_INPUTS
	};
	enum OutputIds {
        ENUMS(OUTPUTS_B,8),
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};
	
	int channels[2];

	Split8() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		onReset();
	}

	void onReset() override {
		channels[0] = -1;
		channels[1] = -1;
	}

    	void process(const ProcessArgs& args) override {
		for (int c = 0; c < 8; c++) {
			float v = inputs[POLY_IN_B].getVoltage(c);
			outputs[OUTPUTS_B + c].setVoltage(v);
		}
	}
};

struct Split8Widget : ModuleWidget {
	Split8Widget(Split8* module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Split.svg")));

		{		
            for(int i = 0; i < 8; i++) {
		        addOutput(createOutputCentered<MicroPort>(mm2px(Vec(5.08, 11.00 + 10.00 * i)), module, Split8::OUTPUTS_B + i));
		    }
		    addInput(createInputCentered<SmallPort>(mm2px(Vec(5.08, 123.50)), module, Split8::POLY_IN_B));
        }

	}
};

Model* modelSplit8 = createModel<Split8, Split8Widget>("Split8");