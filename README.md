# Angular-Node-CPP
Angular <-> Node <-> C++
PoC project that allows to communicates back and forth between Angular, Node and C++.

## Goal
The initial goal of this project is to craft a PoC capable of computing and retrieving information from c++ sources / library and pushing them to an Angular front-end application.

## Overview
The project is currently splitted into 4 part.

Folder | Description
------------ | -------------
back | Simple NodeJS backend with ExpressJS
front | Simple Front-End using AngularJS
native-node-module | The fun part of the project, it contains some c++ sources which gets compiled using node-gyp and can then be used in a typical node script.
cpp | Contains c++ sources that can be compiled into a library which can be loaded dynamically in an executable. This folder is not required for this PoC but is nice to have to test the library.
