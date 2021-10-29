export default class Vad {
  constructor(sampleRate?: number, level?: number);
  process(audio: Buffer): boolean;
}
