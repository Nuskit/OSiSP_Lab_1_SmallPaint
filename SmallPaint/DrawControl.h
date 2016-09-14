#pragma once

#include "stdafx.h"
#include "AbstractDrawObject.h"
using namespace Figures;

class DrawControl
{
public:
  static DrawControl& Instance()
  {
    static DrawControl theSingleInstance;
    return theSingleInstance;
  }

private:
  DrawControl();


};
