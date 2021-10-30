const fs = require('fs');
const path = require('path');

const USAGE = "Usage: node rm.js [FILES/DIRS]...\n";

const args = process.argv.slice(2);

if (args.length < 1) {
    console.error(USAGE);
    throw new SyntaxError();
}

for (const f of args) {
    if (!fs.existsSync(f)) {
        console.warn(`${f} no such file or directory`)
        continue;
    }
    fs.rmSync(f, {recursive: true});
}
