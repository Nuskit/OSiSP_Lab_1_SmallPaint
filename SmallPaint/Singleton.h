#pragma once
#include "stdafx.h"

namespace Templates
{
  template<typename T>
  class Singleton
  {
  public:
    static const T& Instance()
    {
      static T theSingleInstance;
      return theSingleInstance;
    }

  protected:
    Singleton() {}
  private:
    Singleton(const Singleton&);
    Singleton& operator=(const Singleton&);
  };
}