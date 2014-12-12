/**
Generic solution using templates to automatically define the singleton pointer and
do the work of setting it, querying it, and clearing it.  It also checks (by assert)
to make sure aren't instantiating more than one.

To convert ANY class into a singleton:
1) Publicly derive your class MyClass from Singleton<MyClass>.
2) Make sure you're constructing an instance of MyClass somewhere in system before using it.
   How you instantiate it doesn't matter.  You can let the compiler worry about it by making it 
   global or local static, or you can worry about it yourself via a new and delete through an owner
   class.  Regardless of how and when you instantiate, it will get tracked and could be used as a 
   singleton through common interface by rest of system.
3) Call MyClass::GetSingleton() to use the object from anywhere in the system.  If lazy, can 
   #define g_MyClass to be MyClass::GetSingleton() and treat it exactly like a global object
   for convenience.

e.g.
class TerxtureMgr
	: public Singleton<TextureMgr>
{
public:
	Texture* GetTexture(const char* name);
	// ...
};


#define g_TextureMgr TextureMgr::GetSingleton()

void SomeFunction()
{
	Texture* stone1 = TextureMgr::GetSingleton().GetTexture("stone1");
	Texture* wood6 = g_TextureMgr.GetTexture("wood6");
	// ...
}

*/

#include <assert.h>

template <typename T> class Singleton
{
	static T* ms_Singleton;

public:
	Singleton(void)
	{
		assert(!ms_Singleton);
		int offset = (int)(T*)1 - (int)(Singleton<T>*)(T*)1;
		ms_Singleton = (T*)((int)this + offset);
	}
	~Singleton(void)
	{
		assert(ms_Singleton);
		ms_Singleton = 0;
	}
	static T& GetSingleton(void)
	{
		assert(ms_Singleton);
		return *ms_Singleton;
	}
	static T* GetSingletonPointer(void)
	{
		return ms_Singleton;
	}
};

template <typename T> T* Singleton<T>::ms_Singleton = 0;