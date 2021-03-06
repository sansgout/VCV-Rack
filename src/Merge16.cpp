#include "plugin.hpp"

struct Merge16 : Module {
	enum ParamIds {
		NUM_PARAMS
	};
	enum InputIds {
		ENUMS(INPUTS_A,16),
		NUM_INPUTS
	};
	enum OutputIds {
		POLY_OUT_A,
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};
	
	int channels[2];

	Merge16() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		onReset();
	}

	void onReset() override {
		channels[0] = -1;
		channels[1] = -1;
	}

	void process(const ProcessArgs& args) override {
		int lastChannelA = -1;
		for (int c = 0; c < 16; c++) {
			float v = 0.f;
			
			if (inputs[INPUTS_A + c].isConnected()) {
				lastChannelA = c;
				v = inputs[INPUTS_A + c].getVoltage();
			}
			outputs[POLY_OUT_A].setVoltage(v, c);
		}
		outputs[POLY_OUT_A].channels = (channels[0] >= 0) ? channels[0] : (lastChannelA + 1);
	}

	json_t* dataToJson() override {
		json_t* rootJ = json_object();
		json_object_set_new(rootJ, "channels_merge", json_integer(channels[0]));
		return rootJ;
	}

	void dataFromJson(json_t* rootJ) override {
		json_t* channelsAJ = json_object_get(rootJ, "channels_merge");
		if (channelsAJ)
			channels[0] = json_integer_value(channelsAJ);
	}
};

struct Merge16ChannelItem : MenuItem {
	Merge16* module;
	int channels;
	int index;
	void onAction(const event::Action& e) override {
		module->channels[index] = channels;
	}
};


struct Merge16ChannelsItem : MenuItem {
	Merge16* module;
	int index;

	Menu* createChildMenu() override {
		Menu* menu = new Menu;
		for (int channels = -1; channels <= 16; channels++) {
			if(channels == 0) continue;
			Merge16ChannelItem* item = new Merge16ChannelItem;
			if (channels < 0)
				item->text = "Automatic";
			else
				item->text = string::f("%d", channels);
			item->rightText = CHECKMARK(module->channels[index] == channels);
			item->module = module;
			item->channels = channels;
			item->index = index;
			menu->addChild(item);
		}
		return menu;
	}
};

struct Merge16Widget : ModuleWidget {
	Merge16Widget(Merge16* module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Merge16.svg")));

		{
			for(int i = 0; i < 16; i++) {
				addInput(createInputCentered<MicroPort>(mm2px(Vec(5.08, 5.00 + 7.35 * i)), module, Merge16::INPUTS_A + i));
			}
			addOutput(createOutputCentered<SmallPort>(mm2px(Vec(5.08, 123.50)) , module, Merge16::POLY_OUT_A));
		}
		
	}

	void appendContextMenu(Menu* menu) override {
		Merge16* module = dynamic_cast<Merge16*>(this->module);

		menu->addChild(new MenuEntry);

		{
			Merge16ChannelsItem* channelsItem = new Merge16ChannelsItem;
			channelsItem->index = 0;
			channelsItem->text = "Channels Merge";
			channelsItem->rightText = RIGHT_ARROW;
			channelsItem->module = module;
			menu->addChild(channelsItem);
		}
	}
};


Model* modelMerge16 = createModel<Merge16, Merge16Widget>("Merge16");