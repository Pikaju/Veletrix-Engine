#include "ALListener.h"

#include <OpenAL/al.h>

namespace vt {

	ALListener::ALListener()
	{
	}

	ALListener::~ALListener()
	{
	}

	void ALListener::setPosition(const f32v3& position)
	{
		alListener3f(AL_POSITION, position.x, position.y, position.z);
	}

	void ALListener::setVelocity(const f32v3& velocity)
	{
		alListener3f(AL_VELOCITY, velocity.x, velocity.y, velocity.z);
	}

	void ALListener::setOrientation(const f32v3& direction, const f32v3& up)
	{
		f32 orientation[] {
			direction.x, direction.y, direction.z,
			up.x, up.y, up.z
		};
		alListenerfv(AL_ORIENTATION, orientation);
	}

	void ALListener::applyCamera(const Camera<f32>& camera)
	{
		setPosition(camera.position);
		setVelocity(f32v3());
		f32v3 direction = camera.getViewDirection();
		f32v3 right = direction.cross(f32v3(0.0f, 1.0f, 0.0f));
		f32v3 up = right.cross(direction);
		setOrientation(direction, up.normalized<f32>());
	}

}