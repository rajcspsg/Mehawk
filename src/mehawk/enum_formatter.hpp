
#pragma once

#include <type_traits>

#include <magic_enum.hpp>

#include <fmt/format.h>

template<typename T>
concept EnumType = std::is_enum_v<T>;

template<EnumType Enum>
class fmt::formatter<Enum>
{
public:
  auto constexpr parse(format_parse_context& ctx) { return ctx.end(); }

  template<typename FmtContext>
  auto constexpr format(Enum const& val, FmtContext& ctx) const
  {
    return format_to(
      ctx.out(),
      "{}::{}",
      magic_enum::enum_type_name<Enum>(),
      magic_enum::enum_name(val)
    );
  }
};
