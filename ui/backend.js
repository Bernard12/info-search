const { chunksToLinesAsync } = require('@rauschma/stringio');

const {spawn} = require('child_process');
const basePath = '/home/ivan/CLionProjects/info-search/cmake-build-debug';

async function sendQuery(query) {
    const backend = spawn(`${basePath}/info_search`, ['-q', query], {
        stdio: 'pipe'
    });
    const titles = [];
    for await (let i of chunksToLinesAsync(backend.stdout)) {
        titles.push(i);
    }
    return { titles };
}

module.exports = {
    sendQuery
};
