#include <napi.h>
#include <string>
#include "entry_point.h"

// native C++ function that is assigned to 'entryPoint' property on 'exports' object 
Napi::ArrayBuffer entryPoint(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
	std::pair<void *, size_t> result = EntryPoint(0, {});
	// todo free result.first ?
	return Napi::ArrayBuffer::New(env, result.first, result.second);
}

// callback method when module is registered with Node.js
Napi::Object Init(Napi::Env env, Napi::Object exports) {

    // set a key on 'exports' object 
    exports.Set(
            Napi::String::New(env, "entryPoint"), // property name
            Napi::Function::New(env, entryPoint) // property value -> entryPoint function
    );
    // return 'exports' object (always)
    return exports;
}

// register 'entryPoint' module which calls the Init method
NODE_API_MODULE(entryPoint, Init)