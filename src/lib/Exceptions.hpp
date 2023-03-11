#ifndef __EXCEPTIONS_
#define __EXCEPTIONS_

#include <exception>
#include <string>

class InvalidActionException : public std::exception
{
  public:
    InvalidActionException(std::string actionName)
        : msg("Tidak ada aksi bernama " + actionName)
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
