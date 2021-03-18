# Node native module
Build c++ into a library and expose bindings to use in NodeJS

Requires python 2 or 3.

set Python path in npm

Example:
```npm config set python "C:\Users\USERNAME\AppData\Local\Programs\Python\Python37\python.exe"```


```npm install -g node-gyp```

```npm install```

```node-gyp configure```

```node-gyp build```

```node index.js```