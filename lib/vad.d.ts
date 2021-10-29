export class VAD {
    constructor(sampleRate: number, level: number);
}

export type vadInstance = {
    process(audio: Buffer, length: number): boolean;
}
