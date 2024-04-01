/*
 * POINTER
 * Reference Counted Pointers.
 * This is adapted from the implementation in the MAL repo (cpp impl)
 */


#ifndef __MAL_CPP_POINTER_HPP
#define __MAL_CPP_POINTER_HPP


// Inherit from this to add reference counting
class RefCountable 
{
	mutable int count;

	public:
		RefCountable() : count(0) {} 
		RefCountable(const RefCountable& that) = delete;
		RefCountable& operator=(const RefCountable& that) = delete;

		const RefCountable* acquire(void) const {
			this->count++;
			return this;
		}

		int release(void) const {
			return this->count--;
		}

		int ref_count(void) const {
			return this->count;
		}

};


// Managed pointer to a reference counted object
// Note that the objects that we hold references to must inherit from RefCountable
template <class T> class RcPtr
{
	T* obj;

	public:
		RcPtr() : obj(0) {}
		RcPtr(T* object) : obj(0) {
			this->acquire(object);
		}

		~RcPtr() {
			this->release();
		}

		const RcPtr& operator=(const RcPtr& that) 
		{
			this->acquire(that.obj);
			return *this;
		}

		bool operator==(const RcPtr& that) const {
			return this->object == that.object;
		}

		bool operator!=(const RcPtr& that) const {
			return (*this != that);
		}

		operator bool(void) const {
			return this->obj != nullptr;
		}

		T* operator->(void) const {
			return this->obj;
		}

		T* ptr(void) const {
			return this->obj;
		}

		void acquire(T* object)
		{
			if(this->obj != nullptr)
				this->obj->acquire();
			this->realease();
			this->obj = object;
		}

		void release(void)
		{
			if((this->obj != nullptr) && (this->obj->release() == 0))
				delete this->obj;
		}

};

#endif /*__MAL_CPP_POINTER_HPP*/
