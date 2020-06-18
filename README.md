# Node Signals & Slots Library
![nsslib](https://firebasestorage.googleapis.com/v0/b/cypchat-227c2.appspot.com/o/Libraries%2Fnsslib%2Fnsslib.png?alt=media&token=edd9e42d-e0dd-4e4d-89d2-03f1d8dbdfc8 "nsslib")

## What It Solves In JavaScript World

1. We don't need third party state managers or observers.
2. We can trigger any method in the same process whenever a value changed.
3. We bring Qt Framework Signals & Slots logic to Node.
4. This will be much faster and performance focused then any other js based state managers or observers.

## Main Methods
```js

const nss = require('nss');

nss.initValue('loading', false); // initialize the value

nss.insertSlot('loading', (val) => console.log(val)); // Set a listener for value changes
nss.insertSlot('loading', (val) => console.log(val)); // Also set another listener for same value changes

nss.emitSignal('loading', true); // Emit a signal from anywhere to trigger listener methods

```