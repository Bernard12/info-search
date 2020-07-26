const express = require('express');
const app = express();
const port = 3000;
const backend = require('./backend');

// backend.sendQuery("Hello world!");

app.set('view engine', 'pug');

app.get('/', async (req, res) => {
    const t = await backend.sendQuery("list");
    res.render('index', { title: 'Hey', message: 'Hello there!', titles: t })
});

app.listen(port, () => console.log(`Express started`));
