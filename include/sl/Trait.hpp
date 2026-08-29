// include/sl/Trait.hpp

#pragma once

namespace sl
{
    class NonCopyable
    {
    protected:
        NonCopyable()                   = default;
        NonCopyable(const NonCopyable&) = delete;
       ~NonCopyable()                   = default;

    protected:
        NonCopyable& operator=(const NonCopyable&) = delete;
    };
}

namespace sl
{
    class NonMoveable
    {
    protected:
        NonMoveable()              = default;
        NonMoveable(NonMoveable&&) = delete;
       ~NonMoveable()              = default;

    protected:
        NonMoveable& operator=(NonMoveable&&) = delete;
    };
}

namespace sl
{
    class NonConstructable : private NonCopyable, private NonMoveable
    {
    protected:
        NonConstructable() = delete;
       ~NonConstructable() = default;
    };
}
