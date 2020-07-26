const { chunksToLinesAsync, streamWrite  } = require('@rauschma/stringio');

const {spawn} = require('child_process');
const basePath = '/home/ivan/CLionProjects/info-search/cmake-build-debug';

async function sendQuery(query) {
    const backend = spawn(`${basePath}/info_search`, ['-q', query], {
        stdio: 'pipe'
    });
    await streamWrite(backend.stdin, `${query}\n`);

    const titles = [];
    const stdoutIterator = chunksToLinesAsync(backend.stdout);

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

    return titles;
}

module.exports = {
    sendQuery
};
