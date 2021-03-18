//
// Created by Timothy Diguiet on 18/03/2021.
//

#ifndef CPP_LIBRARY_H
#define CPP_LIBRARY_H

#define EXPORT comment(linker, "/EXPORT:" __FUNCTION__ "=" __FUNCDNAME__)

void EntryPoint(int argc, const char * argv);

#endif //CPP_LIBRARY_H
