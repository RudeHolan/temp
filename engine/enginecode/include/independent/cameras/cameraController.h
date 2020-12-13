/**\ file cameraController.h*/

#pragma once

#include "cameras/camera.h"
#include "events/Events.h"

namespace Engine
{


    // Code inspired by the Game Engine Series by "The Cherno" and the lecture slides

        /**
        \class CameraController 
        ** \brief This class creates a camera that is controlled by user keyboard input
        */
    class CameraController
    {
    public:
        CameraController(float aspectRatio); //!< Constructor
        OrthographicCamera& getCamera() { return m_camera; } //!< Get the camera object
        void onUpdate(float t);  //!< Update the camera

    private:

        float m_aspectRatio; //!< Aspect ratio of the window
        float m_cameraSpeed = 5.f; //!< Camera translation speed
        float m_rotationSpeed = 50.f; //!< Camera rotation speed
        float m_rotation = 0; //!< The cameras rotation
        glm::vec3 m_cameraPosition; //!< Camera position
        OrthographicCamera m_camera; //!< The camera that will be controlled
    };

}