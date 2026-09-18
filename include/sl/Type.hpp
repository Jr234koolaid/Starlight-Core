// include/sl/Type.hpp

#pragma once

#include <cstddef>
namespace sl
{
    using Byte = std::byte;
}

#include <array>
namespace sl
{
    template<class T, size_t _Size>
    using Array = std::array<T, _Size>;
}

#include <atomic>
namespace sl
{
    template<class T>
    using Atomic = std::atomic<T>;
}

#include <chrono>
namespace sl
{
    using Nanoseconds  = std::chrono::nanoseconds::period;
    using Microseconds = std::chrono::microseconds::period;
    using Milliseconds = std::chrono::milliseconds::period;
    using Seconds      = std::chrono::seconds::period;
    using Minutes      = std::chrono::minutes::period;
    using Hours        = std::chrono::hours::period;
    using Days         = std::chrono::days::period;
    using Weeks        = std::chrono::weeks::period;
    using Years        = std::chrono::years::period;
    using Months       = std::chrono::months::period;
    using TimePoint    = std::chrono::steady_clock::time_point;
}

#include <compare>
namespace sl
{
    using StrongOrdering  = std::strong_ordering;
    using PartialOrdering = std::partial_ordering;
    using WeakOrdering    = std::weak_ordering;
}

#include <concepts>
namespace sl
{
}

#include <memory>
namespace sl
{
    template<class T>
    using DefaultAllocator = std::allocator<T>;
    template<class T>
    using DefaultDeleter   = std::default_delete<T>;
    template<class T, class _Deleter = DefaultDeleter<T>>
    using UniquePtr        = std::unique_ptr<T, _Deleter>;
    template<class T>
    using SharedPtr        = std::shared_ptr<T>;
    template<class T>
    using WeakPtr          = std::weak_ptr<T>;
}

#include <deque>
namespace sl
{
    template<class T, class _Allocator = DefaultAllocator<T>>
    using Deque = std::deque<T, _Allocator>;
}

#include <filesystem>
namespace sl
{
    using Path                       = std::filesystem::path;
    using DirectoryIterator          = std::filesystem::directory_iterator;
    using DirectoryRecursiveIterator = std::filesystem::recursive_directory_iterator;
    using DirectoryEntry             = std::filesystem::directory_entry;
}

#include <forward_list>
namespace sl
{
    template<class T, class _Allocator = DefaultAllocator<T>>
    using ForwardList = std::forward_list<T, _Allocator>;
}

#include <fstream>
namespace sl
{
    using Fstream  = std::fstream;
    using Ifstream = std::ifstream;
    using Ofstream = std::ofstream;
}

#include <functional>
namespace sl
{
    template<class _Func>
    using Function     = std::function<_Func>;
    template<class T>
    using Hash         = std::hash<T>;
    template<class T>
    using Reference    = std::reference_wrapper<T>;
    template<class T = void>
    using Equal        = std::equal_to<T>;
    template<class T = void>
    using NotEqual     = std::not_equal_to<T>;
    template<class T = void>
    using Greater      = std::greater<T>;
    template<class T = void>
    using GreaterEqual = std::greater_equal<T>;
    template<class T = void>
    using Less         = std::less<T>;
    template<class T = void>
    using LessEqual    = std::less_equal<T>;
}

#include <ios>
namespace sl
{
    using OpenMode   = std::ios::openmode;
    using StreamPos  = std::streampos;
    using StreamSize = std::streamsize;
    using StreamOff  = std::streamoff;
    using SeekDir    = std::ios_base::seekdir;
}

#include <istream>
namespace sl
{
    using IStream = std::istream;
}

#include <limits>
namespace sl
{
    template<std::integral _Integral>
    using NumericLimits = std::numeric_limits<_Integral>;
}

#include <list>
namespace sl
{
    template<class T, class _Allocator = DefaultAllocator<T>>
    using List = std::list<T, _Allocator>;
}

#include <utility>
namespace sl
{
    template<class T, class U>
    using Pair = std::pair<T, U>;
}

#include <map>
namespace sl
{
    template<class _Key, class T, class _Compare = Less<_Key>, class _Allocator = DefaultAllocator<Pair<const _Key, T>>>
    using Map      = std::map<_Key, T, _Compare, _Allocator>;
    template<class _Key, class T, class _Compare = Less<_Key>, class _Allocator = DefaultAllocator<Pair<const _Key, T>>>
    using MultiMap = std::multimap<_Key, T, _Compare, _Allocator>;
}

#include <optional>
namespace sl
{
    template<class T>
    using Optional = std::optional<T>;
}

#include <ostream>
namespace sl
{
    using OStream  = std::ostream;
}

#include <vector>
namespace sl
{
    template<class T, class _Allocator = DefaultAllocator<T>>
    using Vector = std::vector<T, _Allocator>;
}

#include <queue>
namespace sl
{
    template<class T, class _Container = Deque<T>>
    using Queue         = std::queue<T, _Container>;
    template<class T, class _Container = Vector<T>, class _Compare = Less<typename _Container::value_type>>
    using PriorityQueue = std::priority_queue<T, _Container, _Compare>;
}

#include <random>
namespace sl
{
    template<class T = int>
    using UniformIntDistribution = std::uniform_int_distribution<T>;

    using RandomDevice           = std::random_device;
    using MersenneTwister32      = std::mt19937;
    using MersenneTwister64      = std::mt19937_64;
}

#include <set>
namespace sl
{
    template<class T, class _Compare = Less<T>, class _Allocator = DefaultAllocator<T>>
    using Set = std::set<T, _Compare, _Allocator>;
}

#include <span>
namespace sl
{
    template<class T, size_t _Extent = std::dynamic_extent>
    using Span = std::span<T, _Extent>;
}

#include <stack>
namespace sl
{
    template<class T, class _Container = Deque<T>>
    using Stack = std::stack<T, _Container>;
}

#include <string>
namespace sl
{
    using String  = std::string;
    using Wstring = std::wstring;
}

#include <string_view>
namespace sl
{
    using StringView  = std::string_view;
    using WstringView = std::wstring_view;
}

#include <system_error>
namespace sl
{
    using ErrorCode = std::error_code;
}

#include <tuple>
namespace sl
{
    template<class T, class... Us>
    using Tuple = std::tuple<T, Us...>;
}

#include <typeindex>
namespace sl
{
    using TypeIndex = std::type_index;
}

#include <typeinfo>
namespace sl
{
    using TypeInfo = std::type_info;
}

#include <type_traits>
namespace sl
{
    template<class T>
    using UnderlyingType   = std::underlying_type_t<T>;
    template<class T, T _Val>
    using IntegralConstant = std::integral_constant<T, _Val>;

    using Truable          = std::true_type;
    using Falsable         = std::false_type;
}

#include <unordered_map>
namespace sl
{
    template<class _Key, class T, class _Hasher = Hash<_Key>, class _Equal = Equal<_Key>, class _Allocator = DefaultAllocator<Pair<const _Key, T>>>
    using HashMap      = std::unordered_map<_Key, T, _Hasher, _Equal, _Allocator>;
    template<class _Key, class T, class _Hasher = Hash<_Key>, class _Equal = Equal<_Key>, class _Allocator = DefaultAllocator<Pair<const _Key, T>>>
    using HashMultiMap = std::unordered_multimap<_Key, T, _Hasher, _Equal, _Allocator>;
}

#include <unordered_set>
namespace sl
{
    template<class T, class _Hasher = Hash<T>, class _Equal = Equal<T>, class _Allocator = DefaultAllocator<T>>
    using HashSet = std::unordered_set<T, _Hasher, _Equal, _Allocator>;
}

#include <variant>
namespace sl
{
    template<class... Ts>
    using Variant = std::variant<Ts...>;
}
