#pragma once

#include <string_view>

#include <tl/optional.hpp>

namespace hm
{

class Env
{
public:
  Env() = default;

  auto operator[](std::string_view name) const -> tl::optional<std::string_view>;
};

} // namespace hm
