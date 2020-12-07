/*file renderer3D.h*/
#pragma once

#include <glm/glm.hpp>
#include <unordered_map>
#include <memory>
#include "rendering/vertexArray.h"
#include "rendering/texture.h"
#include "rendering/shader.h"
#include "rendering/shaderDataType.h"
#include "rendering/renderAPI.h"

namespace Engine {

	using SceneWideUniforms = std::unordered_map<const char*, std::pair<ShaderDataType, void*>>;

	/**\class Material
    ** \brief Hold a shader and the uniform data associated with that shader
    */
	class Material
	{
	private:
		uint32_t m_flags = 0; //!< Bitfield representation of the shader settings
		std::shared_ptr<Shader> m_shader; //!< The material shader
		std::shared_ptr<Texture> m_texture; //!< The texture to be applied to the material
		glm::vec4 m_tint; //!< Colour of the tint
		void setFlag(uint32_t flag) { m_flags = m_flags | flag; } //!< Set the flag

	public:

		Material(const std::shared_ptr<Shader>& shader) :
			m_shader(shader) 
		{} //!< Constructor with shader only

		Material(const std::shared_ptr<Shader>& shader, const std::shared_ptr<Texture>& texture) :
			m_shader(shader), m_texture(texture), m_tint(glm::vec4(0.f)) {
			setFlag(flag_texture);
		} //!< Constructor with a shader and a texture

		Material(const std::shared_ptr<Shader>& shader, const glm::vec4& tint) :
			m_shader(shader), m_texture(nullptr), m_tint(tint) {
			setFlag(flag_tint);
		} //!< Constructor with a shader and tint

		Material(const std::shared_ptr<Shader>& shader, const std::shared_ptr<Texture>& texture, const glm::vec4& tint) :
			m_shader(shader), m_texture(texture), m_tint(tint) {
			setFlag(flag_texture | flag_tint);
		} //!< Full Constructor

		inline std::shared_ptr<Shader> getShader() const { return m_shader; } //!< Get the shader
		inline std::shared_ptr<Texture> getTexture() const { return m_texture; } //!< Get the texture
		inline glm::vec4 getTint() const { return m_tint; } //!< Get the tint
		bool isFlagSet(uint32_t flag) const { return m_flags & flag; } //!< check if the flags are set

		void setTexture(const std::shared_ptr<Texture>& texture) { m_texture = texture; } //!< Setting the texture
		void setTint(const glm::vec4& tint) { m_tint = tint; } //!< Setting the tint

		constexpr static uint32_t flag_texture = 1 << 0;
		constexpr static uint32_t flag_tint = 1 << 1;


	};

	/**\class Renderer3D
	** \brief A class which renders 3D geometry instantly (non-batched
	*/
	class Renderer3D
	{
	private:
		struct InternalData
		{
			SceneWideUniforms sceneWideUniforms; //!< Replace with UBO
			std::shared_ptr<Texture> defaultTexture; //!< Empty white texture
			glm::vec4 defaultTint; //!< Default white tint
		};
	
		static std::shared_ptr<InternalData> s_data; //!< Data internal to the renderer
	
	public:
		static void init(); //!< Initialize the renderer
		static void begin(const SceneWideUniforms& sceneWideUniformz); //!< Begin a new 3D scene
		static void submit(const std::shared_ptr<VertexArray>& geometry, const std::shared_ptr<Material>& material, const glm::mat4& model); //!< Submit a piece of geometry to be rendered
		static void end(); //!< End the 3D scene
	};
}