#pragma once

template<typename Type, typename... Args>
concept ConstructibleWith = requires(Args&&... args) {
  {
    Type(static_cast<Args&&>(args)...)
  };
};
