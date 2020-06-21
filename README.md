# Node Signals & Slots Library
![nsslib](https://firebasestorage.googleapis.com/v0/b/cypchat-227c2.appspot.com/o/Libraries%2Fnsslib%2Fnsslib.png?alt=media&token=edd9e42d-e0dd-4e4d-89d2-03f1d8dbdfc8 "nsslib")

## What It Solves In NodeJs ?

1. You can trigger any method in the same process whenever a value changed.
2. We bring Qt Framework Signals & Slots logic to NodeJs, you can see how it works via [Qt Signals & Slots](https://doc.qt.io/qt-5/signalsandslots.html).
3. This will be much faster and performance focused then any other js based observers.

## Main Methods
```js

const nss = require('nss'); // for now call it require('path/to/build/Release/nss');

nss.initValue('loading', false); // initialize the value

nss.insertSlot('loading', (val) => console.log(val)); // Set a listener for value changes
nss.insertSlot('loading', (val) => console.log(val)); // Also set another listener for same value changes

nss.emitSignal('loading', true); // Emit a signal from anywhere to trigger listener methods

```

## How To Test and Disassemble the Codes ?
Before started this is a C addon, so to compile and run it, you should have installed <code>node-gyp</code> globally. To do that
> yarn global add node-gyp

After that, clone the repo and type npm start.
> yarn start

This will build the C codes and run it with the example javascript codes. You can see what does the "start" command inside package.json file.  
If you are working under OSX distributions, you can do the following command and start to work in Xcode.
> yarn run xcode-debug

Benefits of working in Xcode that you can set breakpoints and use debugger.  
After executing the above command, you gonna find an .xcodeproj folder under the build folder.  
Here is how you will prepare your Xcode env to run your JavaScript codes. [Debug NodeJs Native addons in Xcode](https://medium.com/@nicknaso/debug-node-js-native-addon-with-xcode-656d740003c0)

## Folders
- C source codes are found under <code>src</code> folder.
- Javascript examples are found under <code>example</code> folder.
- Docs are found under <code>docs</code> folder.

## Where To Use It ?
In any project which ever is powered by NodeJs. some examples are ElectronJs, NodeJs BackEnd Development, Embedded NodeJs projects, Mobile Frameworks(Don't forget to make manual changes) etc.
