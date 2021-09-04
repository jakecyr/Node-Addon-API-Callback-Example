const { SetCallback, TriggerCallback } = require('./index');

SetCallback(() => {
    console.log('hello world');
});

TriggerCallback();

// 'hello world' is logged
