#pragma once 

#include<GLFW/glfw3.h>
#include<Eigen/Geometry>
#include<map>

#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace half_float { class half; }
#endif

# if !defined(GL_HALF_FLOAT) || defined(DOXYGEN_DOCUMENTATION_BUILD)
	/// Ensures that ~~GL_HALF_FLOAT~~ is defined properly for all platforms
	#define GL_HALF_FLOAT 0x140B
#endif

namespace nanogui {

//Bypass template specializations
#ifndef DOXYGEN_SHOULD_SKIP_THIS

	namespace detail {
		template <typename T> struct type_traits;
		template<> struct type_traits<uint32_t> {enum{type = GL_UNSIGNED_INT, integral = 1}; };
		template<> struct type_traits<int32_t> { enum { type = GL_INT, integral = 1 }; };
		template<> struct type_traits<uint16_t> { enum { type = GL_UNSIGNED_SHORT, integral = 1 }; };
		template<> struct type_traits<int16_t> { enum { type = GL_SHORT, integral = 1 }; };
		template<> struct type_traits<uint8_t> { enum { type = GL_UNSIGNED_BYTE, integral = 1 }; };
		template<> struct type_traits<int8_t> { enum { type = GL_BYTE, integral = 1 }; };
		template<> struct type_traits<double> { enum { type = GL_DOUBLE, integral = 0 }; };
		template<> struct type_traits<half_float::half> { enum { type = GL_HALF_FLOAT, integral = 0 }; };
		template<typename T> struct serialization_helper;
	}
#endif

}