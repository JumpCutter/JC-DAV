export default class VAD {
  constructor(sampleRate?: number, level?: number);
  process(audio: Buffer): boolean;
}
