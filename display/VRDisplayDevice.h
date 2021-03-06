#ifndef VRDISPLAYDEVICE_H
#define VRDISPLAYDEVICE_H

#include <string>
#include <vector>

class VRDataIndex;

namespace MinVR
{
	class VRDisplayAction;
	class VRDisplayFrameAction;
	class VRFrameController;
	class VRRenderer;
	class VRRenderState;
}

/** DisplayDevice:    An as-simple-as-possible public interface for Display Devices
 */
class VRDisplayDevice {
public:
	virtual ~VRDisplayDevice() {}

	virtual std::string getName() const = 0;
	virtual void setName(std::string& name) = 0;
	virtual int getDisplayXOffset() = 0;
	virtual int getDisplayYOffset() = 0;
	virtual int getXOffset() = 0;
	virtual int getYOffset() = 0;
	virtual int getWidth() = 0;
	virtual int getHeight() = 0;
	virtual bool isOpen() = 0;
	virtual bool allowThreading() = 0;
	virtual bool allowGraphics() = 0;
	virtual bool isQuadbuffered() = 0;

	bool renderFrame(MinVR::VRDisplayFrameAction& frameAction);
	void use(const MinVR::VRDisplayAction& action);
	virtual void startRendering(const MinVR::VRRenderer& renderer, MinVR::VRRenderState& renderState) = 0;
	virtual void finishRendering() = 0;
	void render(const MinVR::VRRenderer& renderer);

	virtual VRDisplayDevice* getParent() const = 0;
	virtual void setParent(VRDisplayDevice* parent) = 0;
	virtual const std::vector<VRDisplayDevice*>& getSubDisplays() const = 0;
	virtual void addSubDisplay(VRDisplayDevice* display) = 0;

	virtual MinVR::VRFrameController* getFrameController() = 0;

protected:
	
	virtual void useDisplay(const MinVR::VRDisplayAction& action) = 0;
};

#endif
