#ifndef __EXCEPTIONS_
#define __EXCEPTIONS_

#include <exception>
#include <string>

class InvalidActionException : public std::exception
{
  public:
    InvalidActionException(std::string actionName)
        : msg("Tidak ada aksi bernama \e[1;93m" + actionName + "\e[0m")
    {
    }

    const char* what() const throw()
    {
        return msg.c_str();
    }

  private:
    const std::string msg;
};

class AccessAbilityException : public std::exception{
  public:
    AccessAbilityException(std::string abilityName)
        : msg("Belum boleh melakukan kemampuan \e[1;93m" + abilityName + "\e[0m")
    {
    }

    const char* what() const throw()
    {
        return msg.c_str();
    }

    private:
      const std::string msg;
};

#endif // !__EXCEPTIONS_
