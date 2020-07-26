const express = require('express');
const app = express();
const port = 3000;
const backend = require('./backend');

// backend.sendQuery("list || moon").then(console.log);
// backend.sendQuery("list || moon").then(console.log);

app.set('view engine', 'pug');

app.get('/', async (req, res) => {
    res.render('index', {});
});

app.get('/search', async (req, res) => {
    const urlQuery = req.query;
    const foundTitle = await backend.sendQuery(urlQuery.query || "");
    const page = !!urlQuery.page && Number(urlQuery.page) || 1;
    const start = 50 * (page - 1);
    const end = 1 + 50 * page;
    res.render('search', {
        title: 'Hey',
        message: 'Hello there!',
        titles: foundTitle.filter((x, idx) => idx >= start && idx < end)
    })
});

app.listen(port, () => console.log(`Express started`));
