#ifndef _____ALLOCATOR_HXX_____
#define _____ALLOCATOR_HXX_____

#include "DebugRestriction.hxx"
#include <string>
#include <typeinfo>

/// @brief Debug�p��new���Z�q�ł��B\n
/// �t�@�C�����ƍs����ۑ����A���[�N���ɕ\�����܂��B
/// @param type �^��
/// @return new�Ŏ擾�����|�C���^
#define New(Type) new(typeid(Type),__FILE__, __LINE__) Type

void* operator new(size_t size, const type_info& type, const std::string& FileName, int Line);
void* operator new[](size_t size, const type_info& type,const std::string& FileName, int Line);

void* operator new(size_t size);
void* operator new[](size_t size);
//void operator delete(void* p) noexcept;
void operator delete(void* p, size_t size) noexcept;

void addMemorySize(const std::string& type, size_t size);
void deleteMemorySize(const std::string& type, size_t size);
void ShowUsingMemorySize();

/// @brief �������Ǘ��p�̃A���P�[�^
/// @tparam T �A���P�[�^�̌^
template <typename T>
class Allocator
{
public:
    using value_type = T;
	using reference = T&;
	using const_reference = const T&;
    using pointer = T*;
	using const_pointer = const T*;
    using size_type = size_t;

    Allocator() {}

	template <class U>
	Allocator(const Allocator<U>&) {}

	pointer address(reference x) const noexcept
	{
		return &x;
	}

    const_pointer address(const_reference x) const noexcept
    {
		return &x;
    }

    pointer allocate(size_type n)
    {
        pointer p = New(T)[n];
		addMemorySize(typeid(T).name(), sizeof(T)* n);
        return p;
    }

    void deallocate(pointer p, size_type n)
    {
		deleteMemorySize(typeid(T).name(), sizeof(T)* n);
        delete[] p;
    }
};

// ��r���Z�q
template <class T, class U>
bool operator==(const Allocator<T>&, const Allocator<U>&)
{
    return true;
}

template <class T, class U>
bool operator!=(const Allocator<T>&, const Allocator<U>&)
{
    return false;
}

#endif // !_____ALLOCATOR_HXX_____