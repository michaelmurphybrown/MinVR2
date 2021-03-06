/*
 * Copyright Regents of the University of Minnesota, 2016.  This software is released under the following license: http://opensource.org/licenses/GPL-2.0
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#ifndef BASEDISPLAYDEVICE_H_
#define BASEDISPLAYDEVICE_H_

#include "display/VRDisplayDevice.h"

namespace MinVR {

class BaseDisplayDevice : public VRDisplayDevice {
public:
	virtual ~BaseDisplayDevice();

	virtual std::string getName() const;
	virtual void setName(std::string& name);
	virtual int getDisplayXOffset();
	virtual int getDisplayYOffset();
	virtual int getXOffset();
	virtual int getYOffset();
	virtual int getWidth();
	virtual int getHeight();
	virtual bool isOpen();
	virtual bool allowThreading();
	virtual bool allowGraphics();
	virtual void setAllowThreading(bool allowed);
	virtual bool isQuadbuffered();

	VRDisplayDevice* getParent() const;
	void setParent(VRDisplayDevice* parent);
	const std::vector<VRDisplayDevice*>& getSubDisplays() const;
	void addSubDisplay(VRDisplayDevice* display);

	virtual MinVR::VRFrameController* getFrameController();

protected:
	BaseDisplayDevice();

	virtual void useDisplay(const MinVR::VRDisplayAction& action);
	void startRenderingAllDisplays(const MinVR::VRRenderer& renderer, VRRenderState& state);
	void useAllDisplays(const MinVR::VRDisplayAction& action);
	void finishRenderingAllDisplays();

private:
	std::string name;
	VRDisplayDevice* parent;
	std::vector<VRDisplayDevice*> subDisplays;
	bool _allowThreading;
};

} /* namespace MinVR */

#endif /* BASEDISPLAYDEVICE_H_ */
