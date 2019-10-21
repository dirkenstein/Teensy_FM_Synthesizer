A FM synthesizer based on the famous Yamaha DX7.
For Teensy 4.0 and ESP8266
Orignally from:
https://bitbucket.org/folle/arduino-fm-synthesizer/

Sound are synthesized from a sine wave
32 algorithms (same as the ones in the Yamaha DX7)
6 operators
6 envelopes generators (one per operator)
Rate Scaling
Level Scaling
MIDI velocity (8 curves)
MIDI input (supports pitch bend and a sustain pedal)
48000 Hz sampling rate
6 note polyphony
Internal and external DAC support (by using the i2s bus)
Real-time response to hardware controls (to change operators settings and volume)
