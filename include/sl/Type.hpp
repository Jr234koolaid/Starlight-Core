// include\sl\Type.hpp

#pragma once

#include <array>
#include <atomic>
#include <cctype>
#include <chrono>
#include <compare>
#include <cstddef>
#include <cstdint>
#include <deque>
#include <filesystem>
#include <forward_list>
#include <fstream>
#include <functional>
#include <list>
#include <map>
#include <memory>
#include <optional>
#include <queue>
#include <random>
#include <set>
#include <span>
#include <stack>
#include <string>
#include <string_view>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <variant>
#include <vector>

namespace sl
{
    template<typename T> requires std::is_enum_v<T>
    using UnderlyingType = std::underlying_type_t<T>;
}

namespace sl
{
    using Byte = std::byte;
}

namespace sl
{
    template<class T>
    using Hash = std::hash<T>;
}

namespace sl
{
    template<class T>
    using Atomic = std::atomic<T>;
}

namespace sl
{
    using ErrorCode = std::error_code;
}

namespace sl
{
    template<class T, size_t Extent = std::dynamic_extent>
    using Span   = std::span<T, Extent>;
    template<class T, size_t N>
    using Array  = std::array<T, N>;
    template<class T>
    using Vector = std::vector<T>;
}

namespace sl
{
    using String      = std::string;
    using StringView  = std::string_view;
    using Wstring     = std::wstring;
    using WstringView = std::wstring_view;
}

namespace sl
{
    template<class TFunction>
    using Function = std::function<TFunction>;
}

namespace sl
{
    template<class T, class U>
    using Pair  = std::pair<T, U>;
    template<class T, class... Us>
    using Tuple = std::tuple<T, Us...>;
}

namespace sl
{
    template<class T>
    using Reference = std::reference_wrapper<T>;
}

namespace sl
{
    template<class T>
    using Optional = std::optional<T>;
}

namespace sl
{
    template<class T>
    using Shared = std::shared_ptr<T>;
    template<class T>
    using Unique = std::unique_ptr<T>;
    template<class T>
    using Weak   = std::weak_ptr<T>;
}

namespace sl
{
    template<class... Ts>
    using Variant = std::variant<Ts...>;
}

namespace sl
{
    template<class T>
    using List        = std::list<T>;
    template<class T>
    using ForwardList = std::forward_list<T>;
}

namespace sl
{
    template<class Key, class T>
    using Map          = std::map<Key, T>;
    template<class Key, class T>
    using MultiMap     = std::multimap<Key, T>;
    template<class Key, class T>
    using HashMap      = std::unordered_map<Key, T>;
    template<class Key, class T>
    using MultiHashMap = std::unordered_multimap<Key, T>;
}

namespace sl
{
    template<class Key>
    using Set     = std::set<Key>;
    template<class Key>
    using HashSet = std::unordered_set<Key>;
}

namespace sl
{
    template<class T>
    using Deque         = std::deque<T>;
    template<class T>
    using Queue         = std::queue<T>;
    template<class T>
    using PriorityQueue = std::priority_queue<T>;
}

namespace sl
{
    template<class T>
    using Stack = std::stack<T>;
}

namespace sl
{
    using Path                       = std::filesystem::path;
    using DirectoryIterator          = std::filesystem::directory_iterator;
    using RecursiveDirectoryIterator = std::filesystem::recursive_directory_iterator;
    using DirectoryEntry             = std::filesystem::directory_entry;
}

namespace sl
{
    using StreamPos  = std::streampos;
    using StreamSize = std::streamsize;
    using StreamOff  = std::streamoff;
}

namespace sl
{
    using SeekDir = std::ios_base::seekdir;
}

namespace sl
{
    using IStream  = std::istream;
    using OStream  = std::ostream;
    using IFStream = std::ifstream;
    using OFStream = std::ofstream;
    using FStream  = std::fstream;
}

namespace sl
{
    using OpenMode = std::ios::openmode;
}

namespace sl
{
    template<class T = void>
    using Equals    = std::equal_to<T>;
    template<class T = void>
    using NotEquals = std::not_equal_to<T>;
}

namespace sl
{
    template<class T = void>
    using Greater       = std::greater<T>;
    template<class T = void>
    using GreaterEquals = std::greater_equal<T>;
}

namespace sl
{
    template<class T = void>
    using Less       = std::less<T>;
    template<class T = void>
    using LessEquals = std::less_equal<T>;
}

namespace sl
{
    using StrongOrdering  = std::strong_ordering;
    using PartialOrdering = std::partial_ordering;
    using WeakOrdering    = std::weak_ordering;
}

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
}

namespace sl
{
    using TimePoint = std::chrono::steady_clock::time_point;
}

namespace sl
{
    using RandomDevice      = std::random_device;
    using MersenneTwister32 = std::mt19937;
    using MersenneTwister64 = std::mt19937_64;
}

namespace sl
{
    template<class T>
    using UniformIntDistribution = std::uniform_int_distribution<T>;
}
