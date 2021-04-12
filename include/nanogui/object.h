#pragma once
#include <nanogui/common.h>
#include <atomic>

namespace nanogui {
	/*class NANOGUI_EXPORT Object {
		
	};*/

	template <template T> class ref {
	public:
		ref() {

		}
		ref(T *ptr): m_ptr()
	};
}