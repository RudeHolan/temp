/*\file shaderDataType.h*/
#pragma once

#include<cstdint>

namespace Engine 
{
	enum class ShaderDataType
	{
		None = 0,
		Byte4,
		Short,
		Short2,
		Short3,
		Short4,
		Float,
		Float2,
		Float3,
		Float4,
		Int,
		Mat3,
		Mat4
	};

	namespace SDT
	{
		static uint32_t size(ShaderDataType type)
		{
			switch (type)
			{
			case ShaderDataType::Byte4:  return 1 * 4;     

			case ShaderDataType::Short:  return 2;     //size of the float is 2 bytes
			case ShaderDataType::Short2: return 2 * 2; //size of the float is 4 bytes
			case ShaderDataType::Short3: return 2 * 3;
			case ShaderDataType::Short4: return 2 * 4;

			case ShaderDataType::Float:  return 4;     //size of the float is 4 bytes
			case ShaderDataType::Float2: return 4 * 2; //size of the float is 8 bytes
			case ShaderDataType::Float3: return 4 * 3;
			case ShaderDataType::Float4: return 4 * 4; 

			case ShaderDataType::Int: return 4;

			case ShaderDataType::Mat3: return 4 * 3 * 3;
			case ShaderDataType::Mat4: return 4 * 4 * 4;

			default: return 0;
			}
		}

		static uint32_t componentCount(ShaderDataType type)
		{
			switch (type)
			{
			case ShaderDataType::Byte4:  return 4;

			case ShaderDataType::Short: return 1;  //it has 1 short
			case ShaderDataType::Short2: return 2; //it has 2 shorts
			case ShaderDataType::Short3: return 3;
			case ShaderDataType::Short4: return 4;

			case ShaderDataType::Float: return 1;  //it has 1 float
			case ShaderDataType::Float2: return 2; //it has 2 floats
			case ShaderDataType::Float3: return 3;
			case ShaderDataType::Float4: return 4;

			case ShaderDataType::Int: return 1;  

			case ShaderDataType::Mat3: return 3 * 3;
			case ShaderDataType::Mat4: return 4 * 4;

			default: return 0;
			}
		}

		static uint32_t std140alignment(ShaderDataType type)
		{
			switch (type)
			{
			case ShaderDataType::Byte4:  return 1 * 4;

			case ShaderDataType::Short:  return 2;     
			case ShaderDataType::Short2: return 2 * 2; 
			case ShaderDataType::Short3: return 2 * 4; // look at the std140 alignment and the advanced GLSL tab in learnopengl.com
			case ShaderDataType::Short4: return 2 * 4; 

			case ShaderDataType::Float:  return 4;     
			case ShaderDataType::Float2: return 4 * 2; 
			case ShaderDataType::Float3: return 4 * 4;
			case ShaderDataType::Float4: return 4 * 4;

			case ShaderDataType::Mat3: return 4 * 3 * 3;
			case ShaderDataType::Mat4: return 4 * 4 * 4;

			default: return 0;
			}
		}




	}

}
