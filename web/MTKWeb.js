console.log("Testing MTK WASM bindings");
var myMod = require('./bin/MTKWeb.js');

myMod().then(function(Module) {
    // this is reached when everything is ready, and you can call methods on Module
    console.log("MTK version " +Module.getVersion() +" has been loaded");
    Module.initAudio();
});