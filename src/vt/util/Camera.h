#pragma once

#include "../Types.h"
#include "../graphics/window/Input.h"

namespace vt {

	template<typename T>
	class Camera
	{
	public:
		// The camera's position in world space.
		Vector3<T> position;
		// The camera's rotation in degrees.
		Vector3<T> rotation;
		
		inline VT_CONSTEXPR Camera(const Vector3<T>& position = Vector3<T>(), const Vector3<T>& rotation = Vector3<T>()) : position(position), rotation(rotation) {  }
		inline ~Camera() {  }

		// The camera can be controlled in a basic flying mode using
		// the mouse to rotate, WASD to move horizontally, space to
		// move up, shift to move down, and control and alt to increase
		// the speed.
		virtual void debugUpdate(T speed, T delta, const Input& input)
		{
			if (input.isMouseGrabbed()) {
				if (input.getKeyState(input.KEY_ESCAPE)) input.setMouseGrabbed(false);

				const T sensitivity = static_cast<T>(0.125);
				rotation.x -= static_cast<T>(input.getMouseDY()) * sensitivity;
				rotation.y += static_cast<T>(input.getMouseDX()) * sensitivity;

				Vector3<T> movement;
				if (input.getKeyState(input.KEY_W)) movement.z -= static_cast<T>(1);
				if (input.getKeyState(input.KEY_S)) movement.z += static_cast<T>(1);
				if (input.getKeyState(input.KEY_A)) movement.x -= static_cast<T>(1);
				if (input.getKeyState(input.KEY_D)) movement.x += static_cast<T>(1);
				if (input.getKeyState(input.KEY_SPACE)) movement.y += static_cast<T>(1);
				if (input.getKeyState(input.KEY_LEFT_SHIFT)) movement.y -= static_cast<T>(1);
				movement.normalize<T>();
				Vector2<T> horizontalMovement(movement.x, movement.z);
				horizontalMovement = horizontalMovement.rotate(toRadians(rotation.y));
				movement.x = horizontalMovement.x;
				movement.z = horizontalMovement.y;
				speed = delta * speed;
				if (input.getKeyState(input.KEY_LEFT_CONTROL)) speed *= static_cast<T>(8);
				if (input.getKeyState(input.KEY_LEFT_ALT)) speed /= static_cast<T>(4);
				position += movement * speed;
			}
			else {
				if (input.getButtonState(input.MOUSE_BUTTON_LEFT)) input.setMouseGrabbed(true);
			}
		}

		// Returns the view direction of the camera.
		Vector3<T> getViewDirection() const
		{
			T xs = sin(toRadians(rotation.x));
			T xc = -cos(toRadians(rotation.x));
			T ys = sin(toRadians(rotation.y));
			T yc = cos(toRadians(rotation.y));
			return Vector3<T>(-ys * xc, xs, yc * xc);
		}

		// Returns a 4x4 matrix that transforms model space to view space.
		virtual Matrix4<T> getViewMatrix() const
		{
			return Matrix4<T>::rotationZ(toRadians(rotation.z)) * Matrix4<T>::rotationX(toRadians(-rotation.x)) * Matrix4<T>::rotationY(toRadians(rotation.y)) * Matrix4<T>::translation(-position.x, -position.y, -position.z);
		}
	};

}