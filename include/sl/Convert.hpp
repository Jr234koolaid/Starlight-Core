// include/sl/Convert.hpp

#pragma once

#include <concepts>
#include <cstddef>
#include <type_traits>

#include "sl\Alias.hpp"
#include "sl\Define.hpp"
#include "sl\Type.hpp"

namespace sl
{
    template<class TFrom>
    concept convert_all_from_type = std::is_class_v<TFrom>;

    template<class TTo>
    concept convert_all_to_type = std::is_class_v<std::remove_pointer_t<TTo>> or std::is_integral_v<std::remove_pointer_t<TTo>>;

    template<class TContainer>
    concept convert_all_container_type = std::is_class_v<TContainer> and requires(const TContainer& _Container) {
        { _Container.size() } -> std::convertible_to<size_t>;
    };
}

namespace sl
{
    template<class TFrom>
    concept convert_all_cast_from_type = convert_all_from_type<TFrom>;

    template<class TContainer>
    concept convert_all_cast_type = convert_all_cast_from_type<typename TContainer::value_type>;

    template<class TContainer>
    concept convert_all_cast_container_type = convert_all_container_type<TContainer> and convert_all_cast_type<TContainer>;

    template<class TTo, class TContainer>
    concept convert_all_cast_constraint = (
        convert_all_to_type<TTo> and convert_all_cast_container_type<TContainer> and std::convertible_to<typename TContainer::value_type, TTo>
    );
}

namespace sl
{
    template<convert_all_to_type TTo, convert_all_cast_container_type TContainer> requires convert_all_cast_constraint<TTo, TContainer>
    SL_NODISCARD inline Vector<TTo> ConvertAll(const TContainer& _from)
    {
        Vector<TTo> to;
        to.reserve(_from.size());

        for (const auto& castable : _from)
            to.push_back(static_cast<TTo>(castable));

        return to;
    }
}

namespace sl
{
    template<class TFrom>
    struct ConvertAllIsReferenceable
    {
        static inline constexpr bool value = true;
    };

    template<>
    struct ConvertAllIsReferenceable<const char*>
    {
        static inline constexpr bool value = true;
    };

    template<>
    struct ConvertAllIsReferenceable<String>
    {
        static inline constexpr bool value = true;
    };
}

namespace sl
{
    template<class TFrom, class TTo>
    struct ConvertAllReferenceTraits { };

    template<class TFrom, class TTo>
    struct ConvertAllReferenceTraits<TFrom, Reference<TTo>>
    {
        using type = Reference<TTo>;
    };

    template<class TFrom, class TTo>
    struct ConvertAllReferenceTraits<TFrom, Alias<TTo>>
    {
        using type = Alias<TTo>;
    };

    template<>
    struct ConvertAllReferenceTraits<const char*, StringView>
    {
        using type = StringView;
    };

    template<>
    struct ConvertAllReferenceTraits<String, StringView>
    {
        using type = StringView;
    };

    template<>
    struct ConvertAllReferenceTraits<String, const char*>
    {
        using type = const char*;
    };
}

namespace sl
{
    template<class TFrom>
    concept convert_all_reference_from_type = ConvertAllIsReferenceable<TFrom>::value;

    template<class TContainer>
    concept convert_all_reference_type = convert_all_reference_from_type<typename TContainer::value_type>;

    template<class TContainer>
    concept convert_all_reference_container_type = convert_all_container_type<TContainer> and convert_all_reference_type<TContainer>;

    template<class TTo, class TContainer>
    concept convert_all_reference_constraint = convert_all_to_type<TTo> and convert_all_reference_container_type<TContainer> and requires {
        typename ConvertAllReferenceTraits<typename TContainer::value_type, TTo>::type;
    };
}

namespace sl
{
    template<convert_all_to_type TTo, convert_all_reference_container_type TContainer> requires convert_all_reference_constraint<TTo, TContainer>
    SL_NODISCARD inline Vector<TTo> ConvertAll(TContainer& _from)
    {
        Vector<TTo> to;
        to.reserve(_from.size());

        for (auto& referenceable : _from)
        {
            if constexpr (std::same_as<typename TContainer::value_type, String>)
                to.push_back(referenceable.c_str());
            else
                to.emplace_back(referenceable);
        }
        return to;
    }
}

namespace sl
{
    template<class TFrom>
    struct ConvertAllIsCopyable
    {
        static inline constexpr bool value = false;
    };

    template<class TFrom>
    struct ConvertAllIsCopyable<Reference<TFrom>>
    {
        static inline constexpr bool value = true;
    };

    template<class TFrom>
    struct ConvertAllIsCopyable<Alias<TFrom>>
    {
        static inline constexpr bool value = true;
    };

    template<>
    struct ConvertAllIsCopyable<StringView>
    {
        static inline constexpr bool value = true;
    };
}

namespace sl
{
    template<class TFrom, class TTo>
    struct ConvertAllCopyTraits{ };

    template<class TFrom, class TTo>
    struct ConvertAllCopyTraits<Reference<TFrom>, TTo>
    {
        using type = TTo;
    };

    template<class TFrom, class TTo>
    struct ConvertAllCopyTraits<Alias<TFrom>, TTo>
    {
        using type = TTo;
    };

    template<>
    struct ConvertAllCopyTraits<StringView, const char*>
    {
        using type = const char*;
    };

    template<>
    struct ConvertAllCopyTraits<StringView, String>
    {
        using type = String;
    };
}

namespace sl
{
    template<class TFrom>
    concept convert_all_copy_from_type = ConvertAllIsCopyable<TFrom>::value;

    template<class TContainer>
    concept convert_all_copy_type = convert_all_copy_from_type<typename TContainer::value_type>;

    template<class TContainer>
    concept convert_all_copy_container_type = convert_all_container_type<TContainer> and convert_all_copy_type<TContainer>;

    template<class TTo, class TContainer>
    concept convert_all_copy_constraint = convert_all_to_type<TTo> and convert_all_copy_container_type<TContainer> and requires {
        typename ConvertAllCopyTraits<typename TContainer::value_type, TTo>::type;
    };
}

namespace sl
{
    template<convert_all_to_type TTo, convert_all_copy_container_type TContainer> requires convert_all_copy_constraint<TTo, TContainer>
    SL_NODISCARD inline Vector<TTo> ConvertAll(TContainer& _from)
    {
        Vector<TTo> to;
        to.reserve(_from.size());

        for (auto& copyable : _from)
        {
            if constexpr (std::same_as<typename TContainer::value_type, StringView>)
                to.emplace_back(copyable.data());
            else
                to.push_back(copyable.get());
        }
        return to;
    }
}
