// include/sl/Expected.hpp

#pragma once

#include <expected>

namespace sl
{
    template<class _Val, class _Error>
    using Expected = std::expected<_Val, _Error>;
}
