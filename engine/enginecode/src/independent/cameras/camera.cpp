/**\file camera.cpp*/

#include "engine_pch.h"
#include "cameras/camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Engine
{
    OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top) : m_projection(glm::ortho(left, right, bottom, top, -1.f, -1.f)), m_view(1.f)
    {
    }

    void OrthographicCamera::setProjection(float left, float right, float bottom, float top)
    {
        m_projection = glm::ortho(left, right, bottom, top, -1.f, -1.f);
        recalculateViewMatrix();
    }

    void OrthographicCamera::recalculateViewMatrix()
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_position) *
        glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation), glm::vec3(0, 0, 1));
        m_view = transform;

    }


}