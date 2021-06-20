#include <iostream>
#include <regex>
#include "functions.h"
#include <vector>

int main(int argc, char* argv[])
{
  if (argc < 2) return 2;
  std::vector<std::string> argv_copy(argv + 1, argv + argc);
  auto  case_sensitivity = false, position = false;
  std::string needle_string, haystack_string;
  std::regex help_rgx(switchPairsRegexString("h", "help"));
  std::regex insensitive_rgx(switchPairsRegexString("i", "insensitive"));
  std::regex position_rgx(switchPairsRegexString("p", "position"));
  std::regex needle_opt_rgx(switchPairsRegexString("n", "needle"));
  std::regex haystack_opt_rgx(switchPairsRegexString("s", "haystack"));
  for (auto index = 0; index < (int)argv_copy.size(); ++index)
  {
    if (std::regex_match(argv_copy[index], help_rgx))
    {
      const std::string EMPTY_LINE = repeatChar(' ', 50);
      std::cout
        << EMPTY_LINE << '\n'
        << " 'contains' - Check if a hay[stack] contains a    " << '\n'
        << " [needle]. This can either return an EXIT_CODE    " << '\n'
        << " (0 or 1) on found or not or it can PRINT a       " << '\n'
        << " positional start integer with the 'position'     " << '\n'
        << " switch.                                          " << '\n'
        << EMPTY_LINE << '\n'
        << " USAGE:                                           " << '\n'
        << "     contains <SWITCH [PARAMETER]>...             " << '\n'
        << "     if contains -n needle -s stack; then ... fi  " << '\n'
        << "     contains -n needle -s stack && echo found... " << '\n'
        << "     contains -n needle -s stack --position       " << '\n'
        << EMPTY_LINE << '\n'
        << " SWITCH:                                          " << '\n'
        << "     -h, --help          This help message.       " << '\n'
        << "     -n, --needle        What to find. [needle]   " << '\n'
        << "     -s, --haystack      Where to look. [stack]   " << '\n'
        << "     -i, --insensitive   Test is case insensitive." << '\n'
        << "     -p, --position      PRINT the position of the" << '\n'
        << "                         starting character if    " << '\n'
        << "                         found. This changes the  " << '\n'
        << "                         behavior of the program  " << '\n'
        << "                         printing output rather   " << '\n'
        << "                         than returning an exit   " << '\n'
        << "                         code.                    " << '\n'
        << EMPTY_LINE << '\n'
        << " PARAMETER:                                       " << '\n'
        << "     needle - String of characters to find.       " << '\n'
        << "     stack -  String of characters to look in.    " << '\n'
        << EMPTY_LINE << std::endl;
      return 0;
    }
    if (std::regex_match(argv_copy[index], insensitive_rgx))
    {
      case_sensitivity = true;
    }
    if (std::regex_match(argv_copy[index], needle_opt_rgx))
    {
      if (index + 2 > (int)argv_copy.size()) return 3;
      needle_string = argv_copy[index + 1];
    }
    if (std::regex_match(argv_copy[index], haystack_opt_rgx))
    {
      if (index + 2 > (int)argv_copy.size()) return 4;
      haystack_string = argv_copy[index + 1];
    }
    if (std::regex_match(argv_copy[index], position_rgx))
    {
      position = true;
    }
  }
  if (needle_string.empty()) return 5;
  if (haystack_string.empty()) return 6;
  auto result = contains(needle_string, haystack_string, case_sensitivity, position);
  if (!position)
  {
    return result;
  }
  std::cout << result << std::endl;
}