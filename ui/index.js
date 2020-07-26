const express = require('express');
const app = express();
const port = 3000;
const backend = require('./backend');

// backend.sendQuery("Hello world!");

app.set('view engine', 'pug');

app.get('/', async (req, res) => {
    res.render('index', {});
});

app.get('/search', async (req, res) => {
    const urlQuery = req.query;
    const t = await backend.sendQuery(urlQuery.query || "");
    res.render('search', { title: 'Hey', message: 'Hello there!', titles: t })
});

app.listen(port, () => console.log(`Express started`));
