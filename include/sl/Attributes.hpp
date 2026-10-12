// include/sl/Attributes.hpp

#pragma once

#define SL_NO_RETURN      [[noreturn]]
#define SL_DEPRECATED     [[deprecated]]
#define SL_FALLTHROUGH    [[fallthrough]]
#define SL_UNUSED         [[maybe_unused]]
#define SL_NODISCARD      [[nodiscard]]
#define SL_LIKELY	      [[likely]]
#define SL_UNLIKELY       [[unlikely]]
#define SL_ASSUME(_expr_) [[assume(_expr_)]]
