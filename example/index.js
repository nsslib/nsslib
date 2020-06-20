/**
 * Node Signal Slot has 3 native methods
 * @nss {init, register, emit}
 */

const nss = require('../build/Release/nss');
const listeners = require('./statelisteners')

function initValues() {
    nss.initValue('loading', false); // initial value of loading is false.
    nss.initValue('name', 'john'); // initial value of name is john.
    nss.initValue('identity', {name: 'john', surname: 'Doe'}); // initial value of name is john.
}

function registerFunctions() {
    nss.insertSlot('loading', listeners.loading); // loading function is registered into nss to listen changes on 'loading' value.
    nss.insertSlot('name', listeners.didNameChange); // didNameChange function is registered into nss to listen changes on 'name' value.
    nss.insertSlot('name', listeners.didNameChangeForWhat); // didNameChangeForWhat function is registered into nss too, to listen changes on 'name' value. This shows we can register multiple slots to listen one value change.
}

(function main() {
    initValues();
    registerFunctions();

    nss.emitSignal('loading', true); // this should trigger loading function.
    nss.emitSignal('name', 'doe'); // this should trigger didNameChange and didNameChangeForWhat functions.
})()
