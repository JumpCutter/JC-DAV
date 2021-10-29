import Vad from "./index";

const vad = new Vad();

const testArr = [];
for (let i = 0; i < 320; i++) {
    testArr.push(1);
}

console.log(testArr.length);
const buff = Buffer.from(testArr);


console.log(vad.process(buff));
