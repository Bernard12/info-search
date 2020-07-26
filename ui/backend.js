const { chunksToLinesAsync } = require('@rauschma/stringio');

const {spawn} = require('child_process');
const basePath = '/home/ivan/CLionProjects/info-search/cmake-build-debug';

async function sendQuery(query) {
    const backend = spawn(`${basePath}/info_search`, ['-q', query], {
        stdio: 'pipe'
    });
    const titles = [];
    for await (let i of chunksToLinesAsync(backend.stdout)) {
        const converted = i.replace("\n", "").split(" ").join("_");
        titles.push({
            title: i,
            url: `https://en.wikipedia.org/wiki/${encodeURI(converted)}`
        });
    }
    return titles;
}

module.exports = {
    sendQuery
};
