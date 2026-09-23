// include/sl/Trait.hpp

#pragma once

namespace sl
{
    class NonCopyable
    {
    protected:
        constexpr NonCopyable()                   = default;
        constexpr NonCopyable(const NonCopyable&) = delete;
        constexpr ~NonCopyable()                  = default;
    protected:
        constexpr NonCopyable& operator=(const NonCopyable&) = delete;
    };
}

namespace sl
{
    class NonMoveable
    {
    protected:
        constexpr NonMoveable()              = default;
        constexpr NonMoveable(NonMoveable&&) = delete;
        constexpr ~NonMoveable()             = default;
    protected:
        constexpr NonMoveable& operator=(NonMoveable&&) = delete;
    };
}

namespace sl
{
    class NonConstructable : private NonCopyable, private NonMoveable
    {
    protected:
        constexpr NonConstructable()  = delete;
        constexpr ~NonConstructable() = default;
    };
}
