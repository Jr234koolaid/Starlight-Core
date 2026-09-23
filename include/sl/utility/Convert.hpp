// include/sl/utility/Convert.hpp

#pragma once

#include <concepts>
#include <cstddef>
#include <ranges>
#include <type_traits>

#include "sl/Alias.hpp"
#include "sl/Define.hpp"
#include "sl/Type.hpp"

namespace sl::utility
{
    template<class TValue>
    concept convert_type_value     = std::is_object_v<TValue>;
    template<class TTo>
    concept convert_type_to        = std::copyable<TTo> and std::is_object_v<TTo> and not std::is_const_v<TTo>;
    template<class TContainer>
    concept convert_type_container = std::ranges::sized_range<TContainer> and convert_type_value<typename TContainer::value_type>;
}

namespace sl::utility
{
    template<class TTo, class TContainer>
    concept convert_cast_constraint = convert_type_to<TTo> and convert_type_container<TContainer> and std::convertible_to<typename TContainer::value_type, TTo>;
}

namespace sl::utility
{
    template<convert_type_to TTo, convert_type_container TContainer> requires convert_cast_constraint<TTo, TContainer>
    SL_NODISCARD inline constexpr Vector<TTo> ConvertAll(const TContainer& values)
    {
        Vector<TTo> to;
        to.reserve(values.size());

        for (const auto& castable : values)
            to.push_back(static_cast<TTo>(castable));

        return to;
    }
}

namespace sl::utility
{
    template<class>
    struct ConvertValueIsReference : public Falsable { };
    template<class T>
    struct ConvertValueIsReference<Reference<T>> : public Truable { };
}

namespace sl::utility
{
    template<class T>
    concept convert_reference_value = (convert_type_value<T> or convert_type_to<T>) and ConvertValueIsReference<T>::value;
}

namespace sl::utility
{
    template<class>
    struct ConvertValueIsAlias : public Falsable { };
    template<class T>
    struct ConvertValueIsAlias<Alias<T>> : public Truable { };
}

namespace sl::utility
{
    template<class T>
    concept convert_alias_value = (convert_type_value<T> or convert_type_to<T>) and ConvertValueIsAlias<T>::value;
}

namespace sl::utility
{
    template<class>
    struct ConvertValueIsCString : public Falsable { };
    template<>
    struct ConvertValueIsCString<const char*> : public Truable { };
}

namespace sl::utility
{
    template<class T>
    concept convert_cstring_value = (convert_type_value<T> or convert_type_to<T>) and ConvertValueIsCString<T>::value;
}

namespace sl::utility
{
    template<class>
    struct ConvertValueIsStringView : public Falsable { };
    template<>
    struct ConvertValueIsStringView<StringView> : public Truable { };
}

namespace sl::utility
{
    template<class T>
    concept convert_stringview_value = (convert_type_value<T> or convert_type_to<T>) and ConvertValueIsStringView<T>::value;
}

namespace sl::utility
{
    template<class>
    struct ConvertValueIsString : public Falsable { };
    template<>
    struct ConvertValueIsString<String> : public Truable { };
}

namespace sl::utility
{
    template<class T>
    concept convert_string_value = (convert_type_value<T> or convert_type_to<T>) and ConvertValueIsString<T>::value;
}

namespace sl::utility
{
    template<class TFrom, class TTo>
    struct ConvertTypeIsReferenceable : public Falsable { };
    template<class TFrom, class TTo>
    struct ConvertTypeIsReferenceable<TFrom, Reference<TTo>> : public Truable { };
    template<class TFrom, class TTo>
    struct ConvertTypeIsReferenceable<TFrom, Alias<TTo>> : public Truable { };
    template<>
    struct ConvertTypeIsReferenceable<const char*, StringView> : public Truable { };
    template<>
    struct ConvertTypeIsReferenceable<String, const char*> : public Truable { };
    template<>
    struct ConvertTypeIsReferenceable<String, StringView> : public Truable { };
}

namespace sl::utility
{
    template<convert_type_to TTo, convert_type_container TContainer>
    static inline constexpr bool ConvertTypeIsReferenceableValue = ConvertTypeIsReferenceable<typename TContainer::value_type, TTo>::value;
}

namespace sl::utility
{
    template<class TTo, class TContainer>
    concept convert_reference_constraint = convert_type_to<TTo> and convert_type_container<TContainer> and ConvertTypeIsReferenceableValue<TTo, TContainer>;
}

namespace sl::utility
{
    template<convert_type_to TTo, convert_type_container TContainer> requires convert_reference_constraint<TTo, TContainer>
    SL_NODISCARD inline constexpr Vector<TTo> ConvertAll(TContainer& values)
    {
        Vector<TTo> to;
        to.reserve(values.size());

        for (auto& referenceable : values)
        {
            if constexpr (convert_string_value<typename TContainer::value_type> && convert_cstring_value<TTo>)
                to.push_back(referenceable.c_str());
            else
                to.emplace_back(referenceable);
        }
        return to;
    }
}

namespace sl::utility
{
    template<class TFrom, class TTo>
    struct ConvertTypeIsCopyable : public Falsable { };
    template<class TFrom, class TTo>
    struct ConvertTypeIsCopyable<Reference<TFrom>, TTo> : public Truable { };
    template<class TFrom, class TTo>
    struct ConvertTypeIsCopyable<Alias<TFrom>, TTo> : public Truable { };
    template<>
    struct ConvertTypeIsCopyable<const char*, String> : public Truable { };
    template<>
    struct ConvertTypeIsCopyable<StringView, const char*> : public Truable { };
    template<>
    struct ConvertTypeIsCopyable<StringView, String> : public Truable { };
}

namespace sl::utility
{
    template<convert_type_to TTo, convert_type_container TContainer>
    static inline constexpr bool ConvertTypeIsCopyableValue = ConvertTypeIsCopyable<typename TContainer::value_type, TTo>::value;
}

namespace sl::utility
{
    template<class TTo, class TContainer>
    concept convert_copy_constraint = convert_type_to<TTo> and convert_type_container<TContainer> and ConvertTypeIsCopyableValue<TTo, TContainer>;
}

namespace sl::utility
{
    template<convert_type_to TTo, convert_type_container TContainer> requires convert_copy_constraint<TTo, TContainer>
    SL_NODISCARD inline constexpr Vector<TTo> ConvertAll(TContainer& values)
    {
        Vector<TTo> to;
        to.reserve(values.size());

        for (auto& copyable : values)
        {
            if constexpr (convert_reference_value<typename TContainer::value_type>)
                to.push_back(copyable.get());
            else if constexpr (convert_alias_value<typename TContainer::value_type>)
                to.push_back(copyable.get());
            else if constexpr (convert_cstring_value<typename TContainer::value_type>)
                to.emplace_back(copyable);
            else if constexpr (convert_stringview_value<typename TContainer::value_type> and convert_cstring_value<TTo>)
                to.push_back(copyable.data());
            else if constexpr (convert_stringview_value<typename TContainer::value_type> and convert_string_value<TTo>)
                to.emplace_back(copyable.data());
            else
                static_assert("Convert copy container type is not copyable from a reference/value type");
        }
        return to;
    }
}
