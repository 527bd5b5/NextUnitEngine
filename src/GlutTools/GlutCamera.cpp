#include <cmath>

#include "Classes/KeySignal.hpp"
#include "Classes/Vector2.hpp"
#include "Classes/Vector3.hpp"
#include "GlutTools/GlutCamera.hpp"
#include "GlutTools/GlutEvent.hpp"
#include "Utils/Math.hpp"

#define CAMERA_POS_MOVE_ACCELERATION 0.05
#define CAMERA_POS_MOVE_SPEED 0.03
#define CAMERA_ROT_MOVE_ACCELERATION 0.1
#define CAMERA_ROT_MOVE_SPEED 1.0
#define CAMERA_ROT_MOUSE_MOVE_SPEED 0.3

namespace glutCamera
{
    Vector3 cameraPosition(3.0, 3.0, 3.0);
    Vector2 cameraRotation(-30.0, 45.0); // deg

    Vector2 prevMousePosition(0.0, 0.0);
    bool isDragMouse = false;

    KeySignal keySignals[17] = {
        // for camera position
        KeySignal('d', CAMERA_POS_MOVE_ACCELERATION), // right
        KeySignal('a', CAMERA_POS_MOVE_ACCELERATION), // left
        KeySignal('e', CAMERA_POS_MOVE_ACCELERATION), // up
        KeySignal('q', CAMERA_POS_MOVE_ACCELERATION), // down
        KeySignal('s', CAMERA_POS_MOVE_ACCELERATION), // backward
        KeySignal('w', CAMERA_POS_MOVE_ACCELERATION), // forward

        // for camera rotation
        KeySignal('i', CAMERA_ROT_MOVE_ACCELERATION), // up
        KeySignal('k', CAMERA_ROT_MOVE_ACCELERATION), // down
        KeySignal('j', CAMERA_ROT_MOVE_ACCELERATION), // left
        KeySignal('l', CAMERA_ROT_MOVE_ACCELERATION), // right

        // quick point
        KeySignal('1', 1.0), // top
        KeySignal('2', 1.0), // bottom
        KeySignal('3', 1.0), // front
        KeySignal('4', 1.0), // right
        KeySignal('5', 1.0), // back
        KeySignal('6', 1.0), // left
        KeySignal('7', 1.0) // default
    };

    void updateKeySignals()
    {
        for (KeySignal& keySignal : keySignals)
        {
            keySignal.setState(glutEvent::pressedKeys[keySignal.getKey()]);
            keySignal.updateState();
        }
    }

    void updateCameraPosition()
    {
        static Vector2 move;

        move.x = keySignals[0].getSignal() - keySignals[1].getSignal();
        move.y = keySignals[4].getSignal() - keySignals[5].getSignal();

        double direction =
            move.direction() -
            (cameraRotation.y / 360.0 - 90.0) * 2.0 * util::PI_15;
        double magnitude = move.magnitude() * CAMERA_POS_MOVE_SPEED;

        cameraPosition.x += std::cos(direction) * magnitude;
        cameraPosition.z += std::sin(direction) * magnitude;
        cameraPosition.y +=
            (keySignals[2].getSignal() - keySignals[3].getSignal()) *
            CAMERA_POS_MOVE_SPEED;
    }

    void updateCameraRotation()
    {
        Vector2& currentMousePosition = glutEvent::mousePosition;

        if (!isDragMouse && glutEvent::pressedMouseButtons[0])
        {
            isDragMouse = true;
            prevMousePosition = currentMousePosition;
        }
        else if (isDragMouse && glutEvent::pressedMouseButtons[0])
        {
            cameraRotation.x -= (currentMousePosition.y - prevMousePosition.y) *
                                CAMERA_ROT_MOUSE_MOVE_SPEED;
            cameraRotation.y -= (currentMousePosition.x - prevMousePosition.x) *
                                CAMERA_ROT_MOUSE_MOVE_SPEED;

            prevMousePosition = currentMousePosition;
        }
        else
        {
            isDragMouse = false;
        }

        cameraRotation.x +=
            (keySignals[6].getSignal() - keySignals[7].getSignal()) *
            CAMERA_ROT_MOVE_SPEED;
        cameraRotation.y +=
            (keySignals[8].getSignal() - keySignals[9].getSignal()) *
            CAMERA_ROT_MOVE_SPEED;
    }

    void setCameraQuickPoint()
    {
        if (keySignals[10].getIsPressed())
        {
            cameraPosition = Vector3(0.0, 5.0, 0.0);
            cameraRotation = Vector2(-90.0, 0.0);
        }

        if (keySignals[11].getIsPressed())
        {
            cameraPosition = Vector3(0.0, -5.0, 0.0);
            cameraRotation = Vector2(90.0, 0.0);
        }

        if (keySignals[12].getIsPressed())
        {
            cameraPosition = Vector3(0.0, 0.0, 5.0);
            cameraRotation = Vector2(0.0, 0.0);
        }

        if (keySignals[13].getIsPressed())
        {
            cameraPosition = Vector3(5.0, 0.0, 0.0);
            cameraRotation = Vector2(0.0, 90.0);
        }

        if (keySignals[14].getIsPressed())
        {
            cameraPosition = Vector3(0.0, 0.0, -5.0);
            cameraRotation = Vector2(0.0, 180.0);
        }

        if (keySignals[15].getIsPressed())
        {
            cameraPosition = Vector3(-5.0, 0.0, 0.0);
            cameraRotation = Vector2(0.0, 270.0);
        }

        if (keySignals[16].getIsPressed())
        {
            cameraPosition = Vector3(3.0, 3.0, 3.0);
            cameraRotation = Vector2(-30.0, 45.0);
        }
    }

    void update()
    {
        updateKeySignals();
        updateCameraPosition();
        updateCameraRotation();
        setCameraQuickPoint();
    }
}
