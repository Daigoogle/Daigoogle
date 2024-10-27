#ifndef _____DDD_SDL_HXX_____
#define _____DDD_SDL_HXX_____

#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <list>
#include <forward_list>
#include <memory>

#include "Allocator.hxx"

namespace ddd {
	//template <typename Type, size_t Size>
	//	class array : public std::array<Type, Size, Allocator<Type>> {};

	template <typename Type>
		class vector : public std::vector<Type, Allocator<Type>> {};

	//template <typename Type, size_t Size>
	//	class array : public std::array<Type, Size, Allocator<Type>> {};
	//
	//template <typename Type>
	//	class stack : public std::stack<Type, Allocator<Type>> {};
	//
	//template <typename Type>
	//	class queue : public std::queue<Type, Allocator<Type>> {};

	template <typename Type>
		class priority_queue : public std::priority_queue<Type, Allocator<Type>> {};

	template <typename Type>
		class deque : public std::deque<Type, Allocator<Type>> {};

	//template <typename Key, typename Type>
		//class map : public std::map<Key, Type, Allocator<Type>> {};

	template <typename Key, typename Type>
		class multimap : public std::multimap<Key, Type, Allocator<Type>> {};

	template <typename Key, typename Type>
		class unordered_map : public std::unordered_map<Key, Type, Allocator<Type>> {};

	template <typename Key, typename Type>
		class unordered_multimap : public std::unordered_multimap<Key, Type, Allocator<Type>> {};

	template <typename Type>
		class set : public std::set<Type, Allocator<Type>> {};

	template <typename Type>
		class multiset : public std::multiset<Type, Allocator<Type>> {};

	template <typename Type>
		class unordered_set : public std::unordered_set<Type, Allocator<Type>> {};

	template <typename Type>
		class unordered_multiset : public std::unordered_multiset<Type, Allocator<Type>> {};

	template <typename Type>
		class list : public std::list<Type, Allocator<Type>> {};

	template <typename Type>
		class forward_list : public std::forward_list<Type, Allocator<Type>> {};

	//template <typename Type>
	//	class shared_ptr : public std::shared_ptr<Type, Allocator<Type>> {};

	//template <typename Type>
	//	class unique_ptr : public std::unique_ptr<Type, Allocator<Type>> {};

	//template <typename Type>
	//	class weak_ptr : public std::weak_ptr<Type, Allocator<Type>> {};

	//template <typename Type>
	//	class auto_ptr : public std::auto_ptr<Type, Allocator<Type>> {};

	//template <typename Type>
	//Type* New(size_t size = 1)
	//{
	//	Allocator<Type> a;
	//	return a.allocate(size);
	//}

	//template <typename Type>
	//void Delete(Type* p , size_t size = 1)
	//{
	//	Allocator<Type> a;
	//	a.deallocate(p, size);
	//}
}

#endif // !_____DDD_SDL_HXX_____