#ifndef _utils_h
#define _utils_h

#ifndef __CINT__

#include <TObject.h>
#include <RooWorkspace.h>
#include <string>

/** @return a given object from the RooWorkspace or print an error
    message (and exit the program) with the name of the object
    which could not be found. */
TObject *getObj(RooWorkspace *ws, const std::string &objName);

#endif

#endif
