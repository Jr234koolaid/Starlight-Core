// include/sl/Variant.hpp

#pragma once

#include <variant>

namespace sl
{
    template<typename... Ts>
    using Variant = std::variant<Ts...>;
}
