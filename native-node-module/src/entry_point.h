//
// Created by Timothy Diguiet on 18/03/2021.
//

#ifndef CPP_ENTRY_POINT_H
#define CPP_ENTRY_POINT_H

#define EXPORT comment(linker, "/EXPORT:" __FUNCTION__ "=" __FUNCDNAME__)

std::pair<void *, size_t> EntryPoint(int argc, const char * argv);

#endif //CPP_ENTRY_POINT_H
