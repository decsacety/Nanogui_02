#pragma once
#include <nanogui/common.h>
#include <atomic>

namespace nanogui {
	class NANOGUI_EXPORT Object {
	public:
		Object(){}

		Object(const Object &): m_refCount(0){}

		int getRefCount() const { return m_refCount; };

		void incRef() const { ++m_refCount; }

		void decRef(bool dealloc = true ) const noexcept;

	protected:
		virtual ~Object();
	private:
		mutable std::atomic<int> m_refCount{ 0 };
	};

	template <typename T> class ref {
	public:
		ref() {	}

		ref(T* ptr) : m_ptr(ptr) {
			if (m_ptr)
				((Object*)m_ptr)->incRef();
		}

		ref(const ref& r) :m_ptr(r.m_ptr) {
			if (m_ptr)
				((Object*)m_ptr)->incRef();
		}

		ref(ref&& r) noexcept : m_ptr(r.m_ptr) {
			r.m_ptr = nullptr;
		}

		~ref() {
			if (m_ptr)
				((Object*)m_ptr)->decRef();
		}

		ref& operator=(ref&& r) noexcept {
			if (&r != this) {
				if (m_ptr)
					((Object*)m_ptr)->decRef();
				m_ptr = r.m_ptr;
				r.m_ptr = nullptr;
			}
			return *this;
		}

		ref& operator=(const ref &r) noexcept{
			if (m_ptr != r.m_ptr) {
				if (r.m_ptr)
					((Object*)r.m_ptr)->incRef();
				if (m_ptr)
					((Object*)m_ptr)->decRef();
				m_ptr = r.m_ptr;
			}
			return *this;
		}

			ref& operator = (T* ptr) noexcept {
			if (m_ptr != ptr) {
				if (ptr)
					((Object*)ptr)->incRef();
				if (m_ptr)
					((Object*)m_ptr)->decRef();
				m_ptr = ptr;
			}
			return *this;
		}

		bool operator==(const ref& r) const {return m_ptr == r.m_ptr;}

		bool operator!=(const ref& r) const { return m_ptr != r.ptr; }

		bool operator==(const T* ptr) const { return m_ptr == ptr; }

		bool operator!=(const T* ptr) const { return m_ptr != ptr; }

		T* operator->() { return m_ptr; }

		const T* operator->() const { return m_ptr; }

		T& operator*() { return *m_ptr; }

		const T& operator*() const { return *m_ptr; }

		operator T* () { return m_ptr; }

		T* get() { return m_ptr; }

		const T* get() const { return m_ptr; }

		operator bool() const { return m_ptr != nullptr; }

	private:
		T* m_ptr = nullptr;

	};
}