function loading(value) {
    console.log('State of loading: ' + value);
}

function didNameChange(value) {
    console.log('New name: ' + value);
}

function didNameChangeForWhat(value) {
    console.log('Second listener for name: ' + value);
}

module.exports = {
    loading,
    didNameChange,
    didNameChangeForWhat
}