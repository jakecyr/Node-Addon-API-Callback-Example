# Node Addon API Thread Safe Callback Example (C++)

Example of how to save a JavaScript function for later use and call it on the main thread with Node Addon API (C++).

For a better description, checkout my [Medium Article](https://jakecyr.medium.com/saving-javascript-callbacks-with-node-addon-api-3c6e804aa367).

## Setup

1. Run `npm install`
2. Run `npm configure` to configure node-gyp for the project
3. Run `npm run build` to build the Node addon
4. Run the example with `node example.js`
