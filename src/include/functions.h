#ifndef FUNCTIONS_H_INCLUDE
#define FUNCTIONS_H_INCLUDE

inline std::string repeatChar (const char chr,int repeat_number)
{
  return std::string(repeat_number,chr);
}

inline std::string insensitiveRegexString (std::string str)
{
  std::string regexString;
  for (auto & chr : str)
  {
    std::string lower (1,std::tolower(chr)),
                upper (1,std::toupper(chr));
    regexString.append("[" + lower + upper + "]");
  }
  return regexString;
}

inline int iMatch (std::string first, std::string second)
{
  std::string firststr, secondstr;
  for (char elem : first) firststr += std::toupper (elem);
  for (char elem : second) secondstr += std::toupper (elem);
  return (firststr == secondstr);
}

inline std::string switchPairsRegexString (std::string chr, std::string str)
{

  std::string rgx_str = "^-(";
  rgx_str.append(insensitiveRegexString (chr));
  rgx_str.append("|-");
  rgx_str.append(insensitiveRegexString (str));
  rgx_str.append(")$");
  return rgx_str;
}

inline int contains
(
  std::string needle,
  std::string haystack,
  bool insensitive = false,
  bool getpos = false
)
{
  unsigned int find_length = needle.length ();
  for (auto index = 0; index < (int)haystack.length (); index++)
  {
    auto this_test = haystack.substr (index, find_length);
    if (!insensitive)
    {
      if (this_test == needle) 
      {
        if (getpos) return (index + 1);
        return 0;
      }
    }
    else
    {
      if (iMatch (needle, this_test)) 
      {
        if (getpos) return (index + 1);
        return 0;
      }
    }
  }
  if (! getpos) return 1;
  return 0;
}

#endif