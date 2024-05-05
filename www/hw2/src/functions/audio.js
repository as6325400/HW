export class Audio {
  constructor(options){
    
    let defaults = {
      type: 'sine',  
      duration: 2,
      volume: 0.5
    };

    this.opts = Object.assign(defaults, options);
    this.audioCtx = new (window.AudioContext || window.webkitAudioContext)();
  }

  createSound(freq) {
    let oscillator = this.audioCtx.createOscillator();
    let gainNode = this.audioCtx.createGain();
    oscillator.connect(gainNode);
    gainNode.connect(this.audioCtx.destination);
    oscillator.type = this.opts.type;
    oscillator.frequency.value = freq;
    gainNode.gain.setValueAtTime(0, this.audioCtx.currentTime);
    gainNode.gain.linearRampToValueAtTime(1, this.audioCtx.currentTime + 0.01);
    oscillator.start(this.audioCtx.currentTime);
    gainNode.gain.exponentialRampToValueAtTime(0.001, this.audioCtx.currentTime + this.opts.duration);
    oscillator.stop(this.audioCtx.currentTime + this.opts.duration);
  }

  setVolume(volume) {
    this.opts.volume = volume;
  }
}
