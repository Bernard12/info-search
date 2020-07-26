const { chunksToLinesAsync, streamWrite  } = require('@rauschma/stringio');

const {spawn} = require('child_process');
const basePath = '/home/ivan/CLionProjects/info-search/cmake-build-debug';
const backend = spawn(`${basePath}/info_search`);
const stdoutIterator = chunksToLinesAsync(backend.stdout);

const cache = new Map();

async function sendQuery(query) {
    if (cache.has(query)) {
        return cache.get(query);
    }
    await streamWrite(backend.stdin, `${query.toLowerCase()}\n`);

    const titles = [];
    const docCountRaw = await stdoutIterator.next();
    const docCount = Number(docCountRaw.value.replace("\n", ""));

    for (let i = 0; i < docCount; i++) {
        const next = await stdoutIterator.next();
        const val = next.value;
        const converted = val.replace("\n", "").split(" ").join("_");
        titles.push({
            title: val,
            url: `https://en.wikipedia.org/wiki/${encodeURI(converted)}`
        });
    }

    cache.set(query, titles);
    return titles;
}

module.exports = {
    sendQuery
};
