// include/sl/Memory.hpp

#pragma once

#include <memory>

namespace sl
{
    template<typename T>
    using DefaultAllocator = std::allocator<T>;
    template<typename T>
    using DefaultDeleter   = std::default_delete<T>;
}

namespace sl
{
    template<typename T, class _Deleter = DefaultDeleter<T>>
    using UniquePointer = std::unique_ptr<T, _Deleter>;
    template<typename T>
    using SharedPointer = std::shared_ptr<T>;
    template<typename T>
    using WeakPointer   = std::weak_ptr<T>;
}
