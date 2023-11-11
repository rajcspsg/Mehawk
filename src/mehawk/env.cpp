#include <string_view>

#include <tl/optional.hpp>

#include "mehawk/env/env.hpp"

namespace hm
{

auto Env::operator[](std::string_view name) const -> tl::optional<std::string_view>
{
  return { // UHHH NOT MAIN
           "NjkyMjkyNzQ2MTk0NTgzNTcy.Gu-ZTH.0TH-TvqN9pu-F5COZM1dmnq8bpJ-1xc_xbxtVU"

  };

  /* return { // MAIN
    "NjQ0Mjg0MjE3NTI1NjY1Nzkz.GJyPBr.pSds5NgiUct-f8jK8PJaOvlj0VwRPNaPKf4K-w"
 }; */
}

} // namespace hm
