#include<nanogui/object.h>
#include<stdio.h>

namespace nanogui {
	void Object::decRef(bool dealloc) const noexcept {
		--m_refCount;
		if (m_refCount == 0 && dealloc) {
			delete this;
		}else if (m_refCount < 0) 
		{
			fprintf(stderr, "Internal error: Object reference count <0!\nn");
			abort();
		}
	}

	Object::~Object(){}
}