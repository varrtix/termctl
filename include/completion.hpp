#pragma once

// #include <cstring>
// #include <string>
// #include <vector>
//
// class completion {
// public:
//   static char *param_gen(const char *text, int state);
//
// private:
//   static std::vector<std::string> ext_params_;
// };
//
// // Static member initialization
// std::vector<std::string> completion::ext_params_ = {"param1", "param2",
//                                                     "param3"};
//
// // Parameter generator
// char *completion::param_gen(const char *text, int state) {
//   static size_t list_idx, len;
//   if (!state) {
//     list_idx = 0;
//     len = strlen(text);
//   }
//   while (list_idx < ext_params_.size()) {
//     const auto &param = ext_params_[list_idx++];
//     if (param.compare(0, len, text) == 0) {
//       return strdup(param.c_str());
//     }
//   }
//   return nullptr;
// }

#include <cstring>
#include <memory>
#include <string>
#include <vector>

class completion {
public:
  using items_type = std::vector<std::string>;

  completion() = delete;
  completion(completion &&) noexcept = default;
  completion &operator=(completion &&) noexcept = default;
  virtual ~completion() = default;

  virtual char *generator(const char *text, int state) = 0;

protected:
  items_type items_;
};

class cmd_completion : public completion {
public:
  cmd_completion(const items_type &cmds) { items_ = cmds; }
  char *generator(const char *text, int state) override;

private:
  size_t list_idx_ = 0;
  size_t len_ = 0;
};

char *cmd_completion::generator(const char *text, int state) {
  if (!state) {
    list_idx_ = 0;
    len_ = std::strlen(text);
  }
  while (list_idx_ < items_.size()) {
    const auto &cmd = items_[list_idx_++];
    if (cmd.compare(0, len_, text) == 0) {
      return std::strdup(cmd.c_str());
    }
  }
  return nullptr;
}

class parameter_completion : public completion {
public:
  parameter_completion(const std::vector<std::string> &params) {
    items_ = params;
  }
  char *generator(const char *text, int state) override;

private:
  size_t list_idx_ = 0;
  size_t len_ = 0;
};

char *parameter_completion::generator(const char *text, int state) {
  if (!state) {
    list_idx_ = 0;
    len_ = std::strlen(text);
  }
  while (list_idx_ < items_.size()) {
    const auto &param = items_[list_idx_++];
    if (param.compare(0, len_, text) == 0) {
      return std::strdup(param.c_str());
    }
  }
  return nullptr;
}

class completion_factory {
public:
  static std::unique_ptr<completion>
  create_command_completion(const std::vector<std::string> &commands) {
    return std::make_unique<cmd_completion>(commands);
  }

  static std::unique_ptr<completion>
  create_parameter_completion(const std::vector<std::string> &params) {
    return std::make_unique<parameter_completion>(params);
  }
};
