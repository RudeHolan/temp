/**\ file cameraController.cpp*/
#include "engine_pch.h"

#include "cameras/cameraController.h"#
#include "events/eventHandler.h"

#include "core/inputPoller.h"

namespace Engine {

    CameraController::CameraController(float aspectRatio)
        : m_aspectRatio(aspectRatio), m_camera(-m_aspectRatio, m_aspectRatio, -1, 1)
    {
        m_cameraPosition = m_camera.getPosition();

    }

    void CameraController::onUpdate(float t)
    {
        if (InputPoller::isKeyPressed(NG_KEY_A))
        {
            m_cameraPosition.x += m_cameraSpeed * t;
        }
        else if (InputPoller::isKeyPressed(NG_KEY_D))
        {
            m_cameraPosition.x -= m_cameraSpeed * t;
        }
        else if (InputPoller::isKeyPressed(NG_KEY_W))
        {
            m_cameraPosition.y -= m_cameraSpeed * t;
        }
        else if (InputPoller::isKeyPressed(NG_KEY_S))
        {
            m_cameraPosition.y += m_cameraSpeed * t;
        }
        else if (InputPoller::isKeyPressed(NG_KEY_Q))
        {
            m_rotation -= t * m_rotationSpeed;
            if (m_rotation > 180.f) m_rotation -= 360.f;
            else if (m_rotation <= -180.f) m_rotation += 360.f;
        }
        else if (InputPoller::isKeyPressed(NG_KEY_E))
        {
            m_rotation += t * m_rotationSpeed;
            if (m_rotation > 180.f) m_rotation -= 360.f;
            else if (m_rotation <= -180.f) m_rotation += 360.f;
        }

        m_camera.setRotation(m_rotation);
        m_camera.setPos(m_cameraPosition);

    }

}