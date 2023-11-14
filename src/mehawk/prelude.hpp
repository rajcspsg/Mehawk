#pragma once
// Ideally this would be PCH but clangd no likey

#include <concepts>
#include <stdexcept>
#include <assert.hpp>

/// This function immediately stops the application, useful for optimization and warning silencing in cases in which the compiler is trippin
[[noreturn]] inline auto unreachable() noexcept -> void
{
#ifdef __GNUC__ // GCC, Clang, ICC
  __builtin_unreachable();
#elif defned(_MSC_VER)
  __assume(false);
#endif
}

/// @tparam Type Type of the raw (C) array
/// @tparam Size Size of the raw (C) array
template<typename Type, std::size_t Size>
using RawArray = Type[Size];

namespace impl
{

template<typename Type, auto Distinct>
class DistinctType
{
public:
  constexpr explicit DistinctType() = default;

  template<typename T>
  constexpr explicit DistinctType(T&& data)
    : data(static_cast<T&&>(data))
  {}

  constexpr explicit operator decltype(auto)() & noexcept { return data; }

  constexpr explicit operator decltype(auto)() && noexcept { return std::move(data); }

  constexpr explicit operator decltype(auto)() const& noexcept { return data; }

  constexpr explicit operator decltype(auto)() const&& noexcept { return std::move(data); }

private:
  Type data;
};

} // namespace impl

#define MH_UNIMPLEMENTED (ASSERT(false, "Unimplemented."), unreachable())
#define MH_TRAP(...) (ASSERT(false, "This should never happen.\n" #__VA_ARGS__), unreachable())
#define DISTINCT(Type) impl::DistinctType<Type, [] {}>
