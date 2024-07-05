#pragma once

#include "auto_complete.h"
#include "cmds.h"
#include <iostream>
#include <map>
#include <readline/history.h>
#include <readline/readline.h>
#include <string>
#include <vector>

class cli {
public:
  cli();
  ~cli();
  void run();

private:
  static char *cmd_gen(const char *text, int state);
  static char **cmd_complete(const char *text, int start, int end);

  static std::vector<std::string> cmds_;
  static std::map<std::string, std::vector<std::string>> cmd_params_;
  static std::vector<std::string> ext_params_;

  void init_cmds();
  void exec_cmd(const std::string &cmd);

  // Command handlers
  void help();
  void list();
  void exit();
  void get(const std::string &param);
  void set(const std::string &param, const std::string &value);
};

// Static member initialization
std::vector<std::string> cli::cmds_ = {"help", "list", "exit", "get", "set"};
std::map<std::string, std::vector<std::string>> cli::cmd_params_ = {
    {"get", {"param1", "param2"}}, {"set", {"param1", "param2"}}};
std::vector<std::string> cli::ext_params_ = {"param1", "param2", "param3"};

// Constructor
cli::cli() { rl_attempted_completion_function = cmd_complete; }

// Destructor
cli::~cli() {}

// Run method
void cli::run() {
  char *input;
  while ((input = readline("> ")) != nullptr) {
    std::string cmd(input);
    free(input);
    if (!cmd.empty()) {
      add_history(cmd.c_str());
      exec_cmd(cmd);
    }
  }
}

// Execute command
void cli::exec_cmd(const std::string &cmd) {
  auto tokens = split(cmd, ' ');
  if (tokens.empty())
    return;

  const auto &command = tokens[0];
  if (command == "help") {
    help();
  } else if (command == "list") {
    list();
  } else if (command == "exit") {
    exit();
  } else if (command == "get" && tokens.size() == 2) {
    get(tokens[1]);
  } else if (command == "set" && tokens.size() == 3) {
    set(tokens[1], tokens[2]);
  } else {
    std::cerr << "Unknown command: " << command << std::endl;
  }
}

// Command handlers
void cli::help() { cmds::help(); }

void cli::list() { cmds::list(); }

void cli::exit() { cmds::exit(); }

void cli::get(const std::string &param) { cmds::get(param); }

void cli::set(const std::string &param, const std::string &value) {
  cmds::set(param, value);
}

// Command completion
char **cli::cmd_complete(const char *text, int start, int end) {
  char **matches = nullptr;
  if (start == 0) {
    matches = rl_completion_matches(text, cmd_gen);
  } else {
    matches = rl_completion_matches(text, auto_complete::param_gen);
  }
  return matches;
}

// Command generator
char *cli::cmd_gen(const char *text, int state) {
  static size_t list_idx, len;
  if (!state) {
    list_idx = 0;
    len = strlen(text);
  }
  while (list_idx < cmds_.size()) {
    const auto &cmd = cmds_[list_idx++];
    if (cmd.compare(0, len, text) == 0) {
      return strdup(cmd.c_str());
    }
  }
  return nullptr;
}

#endif // CLI_H
