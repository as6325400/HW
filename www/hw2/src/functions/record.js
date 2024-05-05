import {Audio} from './audio.js';

export class Recorder {
  constructor() {
    this.isRecording = false;
    this.records = []; // 用于存储录制的音频数据和视觉数据
    this.audio = new Audio();
  }

  sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
  }

  startRecording() {
    this.records = [];
    this.isRecording = true;
  }

  stopRecording() {
    this.isRecording = false;
  }

  record(freq, keyElement) {
    if (this.isRecording) {
      this.records.push({
        freq,
        keyElement
      });
    }
  }

  clear(){
    this.records = [];
  }

  async playBack() {
    for (const note of this.records) {
      await this.sleep(1000); // 等待1秒
      // 视觉反馈
      note.keyElement.classList.add('active-key');
      setTimeout(() => note.keyElement.classList.remove('active-key'), 1000);
      this.audio.createSound(note.freq);
    }
  }
}
  