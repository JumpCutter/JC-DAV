const fs = require('fs');
const path = require('path');

const USAGE = "Usage: node cp.js [SOURCE_FILES]... [DESTINATION_DIR]\n";

const args = process.argv.slice(2);

if (args.length < 2) {
    console.error(USAGE);
    throw new SyntaxError();
}
const src = args.slice(0, -1);
const dest = args[args.length - 1]

if (!fs.existsSync(dest)) {
    console.error(`${dest} no such file or directory`)
}
if (!fs.statSync(dest).isDirectory()) {
    console.error(`${dest} is not a directory`);
    throw new TypeError();
}

for (const f of src) {
    if (!fs.existsSync(f)) {
        console.error(`${f} no such file or directory`)
    }
    if (!fs.statSync(f).isFile()) {
        console.error(`${f} is not a file`);
        throw new TypeError();
    }
    fs.copyFileSync(f, path.join(dest, path.basename(f)));
}
