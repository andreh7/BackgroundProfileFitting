#include "utils.h"

#include <iostream>

using namespace std;

//----------------------------------------------------------------------

TObject *
getObj(RooWorkspace *ws, const std::string &objName)
{
  TObject *retval = ws->obj(objName.c_str());
  if (retval == NULL)
  {
    cerr << "could not find object '" << objName << "' in workspace " << ws->GetName() << ", exiting" << endl;
    exit(1);
  }

  return retval;
}
//----------------------------------------------------------------------
