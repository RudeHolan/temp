/**\file camera.h*/
#pragma once

#include <glm/glm.hpp>

namespace Engine
{
    // Code inspired by the Game Engine Series by "The Cherno" and the lecture slides


    /**
    \class OrthographicCamera - This class creates an orthographic camera that can be controlled from the cameraController class
    */
    class OrthographicCamera
    {
    public:

        OrthographicCamera(float left, float right, float bottom, float top); //!< Constructor

        void setPos(const glm::vec3& position) { m_position = position; recalculateViewMatrix(); } //!< Set the camera positon and update
        void setRotation(float rotation) { m_rotation = rotation; recalculateViewMatrix(); } //!< Set the camera rotation and update
        void setProjection(float left, float right, float bottom, float top); //!< Set the projection

        const glm::vec3& getPosition() const { return m_position; } //!< Get the camera position
        const glm::mat4& getView() const { return m_view; } //!< Get the camera view
        const glm::mat4& getProjection()const { return m_projection; } //!< Get the camera projection matrix

        float getRotation() const { return m_rotation; } //!< Get the camera rotation
        glm::mat4 m_view; //!< The view matrix
        glm::mat4 m_projection; //!< The projection matrix

    private:
        void recalculateViewMatrix(); //!< update the camera 
        glm::vec3 m_position = { 0.f, 0.f, 0.f }; //!< The position of the camera
        float m_rotation = 0.0f; //!< The rotation of the camera
    };



}