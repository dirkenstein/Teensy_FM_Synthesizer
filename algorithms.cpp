#include <Arduino.h>

#include "algorithms.h"
#include "Teensy_FM_Synthesizer.h"

extern synth_t synth;

// Notes info.
extern note_t notes[MAX_POLYPHONY];
// Operators info.
extern operator_t operators[NUM_OPERATORS];

#ifdef ESP8266
#include <i2s.h>

__attribute__((always_inline)) inline bool avail(void)
{
  return !i2s_available();
  
}
#endif

void algorithm0()
{
#ifdef ESP8266
    while (avail()) {
#endif
      algorithm0Code(0, MAX_POLYPHONY);

 #ifdef ESP8266
          dacOutput();
       }
#endif    
}

void algorithm1()
{
#ifdef ESP8266
    while (avail()) {
#endif          
          algorithm1Code(0, MAX_POLYPHONY);

#ifdef ESP8266
          dacOutput();
       }
#endif          

}

void algorithm2()
{
#ifdef ESP8266
    while (avail()) {
#endif      
          algorithm2Code(0, MAX_POLYPHONY);

#ifdef ESP8266
          dacOutput();
       }
#endif    
}

void algorithm3()
{
#ifdef ESP8266
    while (avail()) {
#endif    
    algorithm3Code(0, MAX_POLYPHONY);
#ifdef ESP8266
          dacOutput();
       }
#endif    
}

void algorithm4()
{
#ifdef ESP8266
    while (avail()) {
#endif 
       algorithm4Code(0, MAX_POLYPHONY);
#ifdef ESP8266
          dacOutput();
       }
#endif    
}

void algorithm5()
{
#ifdef ESP8266
    while (avail()) {
#endif 

      algorithm5Code(0, MAX_POLYPHONY);

#ifdef ESP8266
          dacOutput();
       }
#endif    
}

void algorithm6()
{
#ifdef ESP8266
    while (avail()) {
#endif 
      algorithm6Code(0, MAX_POLYPHONY);
#ifdef ESP8266
          dacOutput();
       }
#endif    
}

void algorithm7()
{
#ifdef ESP8266
    while (avail()) {
#endif      
      algorithm7Code(0, MAX_POLYPHONY);
#ifdef ESP8266
          dacOutput();
       }
#endif    
}

void algorithm8()
{
#ifdef ESP8266
    while (avail()) {
#endif
      algorithm8Code(0, MAX_POLYPHONY);
#ifdef ESP8266
          dacOutput();
       }
#endif    
}

void algorithm9()
{
#ifdef ESP8266
    while (avail()) {
#endif
      algorithm9Code(0, MAX_POLYPHONY);
#ifdef ESP8266
          dacOutput();
       }
#endif    
}

void algorithm10()
{
#ifdef ESP8266
    while (avail()) {
#endif
      algorithm10Code(0, MAX_POLYPHONY);
#ifdef ESP8266
          dacOutput();
       }
#endif    
}

void algorithm11()
{
#ifdef ESP8266
    while (avail()) {
#endif
      algorithm11Code(0, MAX_POLYPHONY);
#ifdef ESP8266
          dacOutput();
       }
#endif    
}

void algorithm12()
{
#ifdef ESP8266
    while (avail()) {
#endif      
      algorithm12Code(0, MAX_POLYPHONY);
#ifdef ESP8266
          dacOutput();
       }
#endif    
}

void algorithm13()
{
#ifdef ESP8266
    while (avail()) {
#endif      
      algorithm13Code(0, MAX_POLYPHONY);
#ifdef ESP8266
          dacOutput();
       }
#endif    
}

void algorithm14()
{
#ifdef ESP8266
    while (avail()) {
#endif     
      algorithm14Code(0, MAX_POLYPHONY);
#ifdef ESP8266
          dacOutput();
       }
#endif    
}

void algorithm15()
{
#ifdef ESP8266
    while (avail()) {
#endif      
      algorithm15Code(0, MAX_POLYPHONY);
 #ifdef ESP8266
          dacOutput();
       }
#endif    
}

void algorithm16()
{
#ifdef ESP8266
    while (avail()) {
#endif
      algorithm16Code(0, MAX_POLYPHONY);
#ifdef ESP8266
          dacOutput();
       }
#endif    
}

void algorithm17()
{
#ifdef ESP8266
    while (avail()) {
#endif
    algorithm17Code(0, MAX_POLYPHONY);
#ifdef ESP8266
          dacOutput();
       }
#endif    
}

void algorithm18()
{
#ifdef ESP8266
    while (avail()) {
#endif
     algorithm18Code(0, MAX_POLYPHONY);
 #ifdef ESP8266
          dacOutput();
       }
#endif    
}

void algorithm19()
{
#ifdef ESP8266
    while (avail()) {
#endif
      algorithm19Code(0, MAX_POLYPHONY);
 #ifdef ESP8266
          dacOutput();
       }
#endif    
}

void algorithm20()
{
#ifdef ESP8266
    while (avail()) {
#endif
      algorithm20Code(0, MAX_POLYPHONY);
#ifdef ESP8266
          dacOutput();
       }
#endif    
}

void algorithm21()
{
#ifdef ESP8266
    while (avail()) {
#endif
      algorithm21Code(0, MAX_POLYPHONY);
#ifdef ESP8266
          dacOutput();
       }
#endif    
}

void algorithm22()
{
 #ifdef ESP8266
    while (avail()) {
#endif
      algorithm22Code(0, MAX_POLYPHONY);
#ifdef ESP8266
          dacOutput();
       }
#endif    
}

void algorithm23()
{
#ifdef ESP8266
    while (avail()) {
#endif
      algorithm23Code(0, MAX_POLYPHONY);
#ifdef ESP8266
          dacOutput();
       }
#endif    
}

void algorithm24()
{
#ifdef ESP8266
    while (avail()) {
#endif
      algorithm24Code(0, MAX_POLYPHONY);
#ifdef ESP8266
          dacOutput();
       }
#endif    
}

void algorithm25()
{
#ifdef ESP8266
    while (avail()) {
#endif
      algorithm25Code(0, MAX_POLYPHONY);
    
#ifdef ESP8266
          dacOutput();
       }
#endif    
}

void algorithm26()
{
#ifdef ESP8266
    while (avail()) {
#endif
      algorithm26Code(0, MAX_POLYPHONY);
#ifdef ESP8266
          dacOutput();
       }
#endif    
}

void algorithm27()
{
#ifdef ESP8266
    while (avail()) {
#endif
      algorithm27Code(0, MAX_POLYPHONY);
#ifdef ESP8266
          dacOutput();
       }
#endif    
}

void algorithm28()
{
#ifdef ESP8266
    while (avail()) {
#endif
      algorithm28Code(0, MAX_POLYPHONY);
#ifdef ESP8266
          dacOutput();
       }
#endif    
}

void algorithm29()
{
#ifdef ESP8266
    while (avail()) {
#endif
      algorithm29Code(0, MAX_POLYPHONY);
#ifdef ESP8266
          dacOutput();
       }
#endif    
}

void algorithm30()
{
#ifdef ESP8266
    while (avail()) {
#endif
      algorithm30Code(0, MAX_POLYPHONY);
#ifdef ESP8266
          dacOutput();
       }
#endif    
}

void algorithm31()
{
#ifdef ESP8266
    while (avail()) {
#endif
      algorithm31Code(0, MAX_POLYPHONY);
#ifdef ESP8266
          dacOutput();
       }
#endif    
}

__attribute__((always_inline)) inline void algorithm0Code(uint8_t noteIndexLow, uint8_t noteIndexHigh)
{
    for (uint8_t i = noteIndexLow; i < noteIndexHigh; ++i)
        if (notes[i].on == true)
        {
            // OP 1.
            operators[1].value = (((operators[1].source[(notes[i].stepAccumulator[1] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[1].value) >> ADSR_SHIFT) * notes[i].scaledLevel[1]) >> LEVEL_SHIFT;
            // OP 0.
            operators[0].value = (((operators[0].source[((notes[i].stepAccumulator[0] >> STEP_SHIFT) + operators[1].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[0].value) >> ADSR_SHIFT) * notes[i].scaledLevel[0]) >> LEVEL_SHIFT;
            // OP 5 and feedback.
            operators[5].value = (((operators[5].source[((notes[i].stepAccumulator[5] >> STEP_SHIFT) + notes[i].feedback) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[5].value) >> ADSR_SHIFT) * notes[i].scaledLevel[5]) >> LEVEL_SHIFT;
            notes[i].feedback = (operators[5].value * operators[5].feedback) >> FEEDBACK_SHIFT;
            // OP 4.
            operators[4].value = (((operators[4].source[((notes[i].stepAccumulator[4] >> STEP_SHIFT) + operators[5].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[4].value) >> ADSR_SHIFT) * notes[i].scaledLevel[4]) >> LEVEL_SHIFT;
            // OP 3.
            operators[3].value = (((operators[3].source[((notes[i].stepAccumulator[3] >> STEP_SHIFT) + operators[4].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[3].value) >> ADSR_SHIFT) * notes[i].scaledLevel[3]) >> LEVEL_SHIFT;
            // OP 2.
            operators[2].value = (((operators[2].source[((notes[i].stepAccumulator[2] >> STEP_SHIFT) + operators[3].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[2].value) >> ADSR_SHIFT) * notes[i].scaledLevel[2]) >> LEVEL_SHIFT;

            // Increments note steps
            notes[i].stepAccumulator[0] += notes[i].scaledStep[0];
            notes[i].stepAccumulator[1] += notes[i].scaledStep[1];
            notes[i].stepAccumulator[2] += notes[i].scaledStep[2];
            notes[i].stepAccumulator[3] += notes[i].scaledStep[3];
            notes[i].stepAccumulator[4] += notes[i].scaledStep[4];
            notes[i].stepAccumulator[5] += notes[i].scaledStep[5];

            // Increments the synth output.
            synth.outputLeft += operators[0].value + operators[2].value;
            synth.outputRight += operators[0].value + operators[2].value;
        }
}

__attribute__((always_inline)) inline void algorithm1Code(uint8_t noteIndexLow, uint8_t noteIndexHigh)
{
    for (uint8_t i = noteIndexLow; i < noteIndexHigh; ++i)
        if (notes[i].on == true)
        {
            // OP 1 and feedback.
            operators[1].value = (((operators[1].source[((notes[i].stepAccumulator[1] >> STEP_SHIFT) + notes[i].feedback) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[1].value) >> ADSR_SHIFT) * notes[i].scaledLevel[1]) >> LEVEL_SHIFT;
            notes[i].feedback = (operators[1].value * operators[1].feedback) >> FEEDBACK_SHIFT;
            // OP 0.
            operators[0].value = (((operators[0].source[((notes[i].stepAccumulator[0] >> STEP_SHIFT) + operators[1].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[0].value) >> ADSR_SHIFT) * notes[i].scaledLevel[0]) >> LEVEL_SHIFT;
            // OP 5.
            operators[5].value = (((operators[5].source[(notes[i].stepAccumulator[5] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[5].value) >> ADSR_SHIFT) * notes[i].scaledLevel[5]) >> LEVEL_SHIFT;
            // OP 4.
            operators[4].value = (((operators[4].source[((notes[i].stepAccumulator[4] >> STEP_SHIFT) + operators[5].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[4].value) >> ADSR_SHIFT) * notes[i].scaledLevel[4]) >> LEVEL_SHIFT;
            // OP 3.
            operators[3].value = (((operators[3].source[((notes[i].stepAccumulator[3] >> STEP_SHIFT) + operators[4].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[3].value) >> ADSR_SHIFT) * notes[i].scaledLevel[3]) >> LEVEL_SHIFT;
            // OP 2.
            operators[2].value = (((operators[2].source[((notes[i].stepAccumulator[2] >> STEP_SHIFT) + operators[3].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[2].value) >> ADSR_SHIFT) * notes[i].scaledLevel[2]) >> LEVEL_SHIFT;

            // Increments note steps
            notes[i].stepAccumulator[0] += notes[i].scaledStep[0];
            notes[i].stepAccumulator[1] += notes[i].scaledStep[1];
            notes[i].stepAccumulator[2] += notes[i].scaledStep[2];
            notes[i].stepAccumulator[3] += notes[i].scaledStep[3];
            notes[i].stepAccumulator[4] += notes[i].scaledStep[4];
            notes[i].stepAccumulator[5] += notes[i].scaledStep[5];

            // Increments the synth output.
            synth.outputLeft += operators[0].value + operators[2].value;
            synth.outputRight += operators[0].value + operators[2].value;
        }
}

__attribute__((always_inline)) inline void algorithm2Code(uint8_t noteIndexLow, uint8_t noteIndexHigh)
{
    for (uint8_t i = noteIndexLow; i < noteIndexHigh; ++i)
        if (notes[i].on == true)
        {
            // OP 2.
            operators[2].value = (((operators[2].source[(notes[i].stepAccumulator[2] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[2].value) >> ADSR_SHIFT) * notes[i].scaledLevel[2]) >> LEVEL_SHIFT;
            // OP 1.
            operators[1].value = (((operators[1].source[((notes[i].stepAccumulator[1] >> STEP_SHIFT) + operators[2].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[1].value) >> ADSR_SHIFT) * notes[i].scaledLevel[1]) >> LEVEL_SHIFT;
            // OP 0.
            operators[0].value = (((operators[0].source[((notes[i].stepAccumulator[0] >> STEP_SHIFT) + operators[1].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[0].value) >> ADSR_SHIFT) * notes[i].scaledLevel[0]) >> LEVEL_SHIFT;
            // OP 5 and feedback.
            operators[5].value = (((operators[5].source[((notes[i].stepAccumulator[5] >> STEP_SHIFT) + notes[i].feedback) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[5].value) >> ADSR_SHIFT) * notes[i].scaledLevel[5]) >> LEVEL_SHIFT;
            notes[i].feedback = (operators[5].value * operators[5].feedback) >> FEEDBACK_SHIFT;
            // OP 4.
            operators[4].value = (((operators[4].source[((notes[i].stepAccumulator[4] >> STEP_SHIFT) + operators[5].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[4].value) >> ADSR_SHIFT) * notes[i].scaledLevel[4]) >> LEVEL_SHIFT;
            // OP 3.
            operators[3].value = (((operators[3].source[((notes[i].stepAccumulator[3] >> STEP_SHIFT) + operators[4].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[3].value) >> ADSR_SHIFT) * notes[i].scaledLevel[3]) >> LEVEL_SHIFT;

            // Increments note steps
            notes[i].stepAccumulator[0] += notes[i].scaledStep[0];
            notes[i].stepAccumulator[1] += notes[i].scaledStep[1];
            notes[i].stepAccumulator[2] += notes[i].scaledStep[2];
            notes[i].stepAccumulator[3] += notes[i].scaledStep[3];
            notes[i].stepAccumulator[4] += notes[i].scaledStep[4];
            notes[i].stepAccumulator[5] += notes[i].scaledStep[5];

            // Increments the synth output.
            synth.outputLeft += operators[0].value + operators[3].value;
            synth.outputRight += operators[0].value + operators[3].value;
        }
}

__attribute__((always_inline)) inline void algorithm3Code(uint8_t noteIndexLow, uint8_t noteIndexHigh)
{
    for (uint8_t i = noteIndexLow; i < noteIndexHigh; ++i)
        if (notes[i].on == true)
        {
            // OP 2.
            operators[2].value = (((operators[2].source[(notes[i].stepAccumulator[2] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[2].value) >> ADSR_SHIFT) * notes[i].scaledLevel[2]) >> LEVEL_SHIFT;
            // OP 1.
            operators[1].value = (((operators[1].source[((notes[i].stepAccumulator[1] >> STEP_SHIFT) + operators[2].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[1].value) >> ADSR_SHIFT) * notes[i].scaledLevel[1]) >> LEVEL_SHIFT;
            // OP 0.
            operators[0].value = (((operators[0].source[((notes[i].stepAccumulator[0] >> STEP_SHIFT) + operators[1].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[0].value) >> ADSR_SHIFT) * notes[i].scaledLevel[0]) >> LEVEL_SHIFT;
            // OP 5.
            operators[5].value = (((operators[5].source[((notes[i].stepAccumulator[5] >> STEP_SHIFT) + notes[i].feedback) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[5].value) >> ADSR_SHIFT) * notes[i].scaledLevel[5]) >> LEVEL_SHIFT;
            // OP 4.
            operators[4].value = (((operators[4].source[((notes[i].stepAccumulator[4] >> STEP_SHIFT) + operators[5].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[4].value) >> ADSR_SHIFT) * notes[i].scaledLevel[4]) >> LEVEL_SHIFT;
            // OP 3 and feedback.
            operators[3].value = (((operators[3].source[((notes[i].stepAccumulator[3] >> STEP_SHIFT) + operators[4].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[3].value) >> ADSR_SHIFT) * notes[i].scaledLevel[3]) >> LEVEL_SHIFT;
            notes[i].feedback = (operators[3].value * operators[3].feedback) >> FEEDBACK_SHIFT;

            // Increments note steps
            notes[i].stepAccumulator[0] += notes[i].scaledStep[0];
            notes[i].stepAccumulator[1] += notes[i].scaledStep[1];
            notes[i].stepAccumulator[2] += notes[i].scaledStep[2];
            notes[i].stepAccumulator[3] += notes[i].scaledStep[3];
            notes[i].stepAccumulator[4] += notes[i].scaledStep[4];
            notes[i].stepAccumulator[5] += notes[i].scaledStep[5];

            // Increments the synth output.
            synth.outputLeft += operators[0].value + operators[3].value;
            synth.outputRight += operators[0].value + operators[3].value;
        }
}

__attribute__((always_inline)) inline void algorithm4Code(uint8_t noteIndexLow, uint8_t noteIndexHigh)
{
    for (uint8_t i = noteIndexLow; i < noteIndexHigh; ++i)
        if (notes[i].on == true)
        {
            // OP 1.
            operators[1].value = (((operators[1].source[(notes[i].stepAccumulator[1] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[1].value) >> ADSR_SHIFT) * notes[i].scaledLevel[1]) >> LEVEL_SHIFT;
            // OP 0.
            operators[0].value = (((operators[0].source[((notes[i].stepAccumulator[0] >> STEP_SHIFT) + operators[1].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[0].value) >> ADSR_SHIFT) * notes[i].scaledLevel[0]) >> LEVEL_SHIFT;
            // OP 3.
            operators[3].value = (((operators[3].source[(notes[i].stepAccumulator[3] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[3].value) >> ADSR_SHIFT) * notes[i].scaledLevel[3]) >> LEVEL_SHIFT;
            // OP 2.
            operators[2].value = (((operators[2].source[((notes[i].stepAccumulator[2] >> STEP_SHIFT) + operators[3].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[2].value) >> ADSR_SHIFT) * notes[i].scaledLevel[2]) >> LEVEL_SHIFT;
            // OP 5 and feedback.
            operators[5].value = (((operators[5].source[((notes[i].stepAccumulator[5] >> STEP_SHIFT) + notes[i].feedback) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[5].value) >> ADSR_SHIFT) * notes[i].scaledLevel[5]) >> LEVEL_SHIFT;
            notes[i].feedback = (operators[5].value * operators[5].feedback) >> FEEDBACK_SHIFT;
            // OP 4.
            operators[4].value = (((operators[4].source[((notes[i].stepAccumulator[4] >> STEP_SHIFT) + operators[5].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[4].value) >> ADSR_SHIFT) * notes[i].scaledLevel[4]) >> LEVEL_SHIFT;

            // Increments note steps
            notes[i].stepAccumulator[0] += notes[i].scaledStep[0];
            notes[i].stepAccumulator[1] += notes[i].scaledStep[1];
            notes[i].stepAccumulator[2] += notes[i].scaledStep[2];
            notes[i].stepAccumulator[3] += notes[i].scaledStep[3];
            notes[i].stepAccumulator[4] += notes[i].scaledStep[4];
            notes[i].stepAccumulator[5] += notes[i].scaledStep[5];

            // Increments the synth output.
            synth.outputLeft += operators[0].value + operators[2].value + operators[4].value;
            synth.outputRight += operators[0].value + operators[2].value + operators[4].value;
        }
}

__attribute__((always_inline)) inline void algorithm5Code(uint8_t noteIndexLow, uint8_t noteIndexHigh)
{
    for (uint8_t i = noteIndexLow; i < noteIndexHigh; ++i)
        if (notes[i].on == true)
        {
            // OP 1.
            operators[1].value = (((operators[1].source[(notes[i].stepAccumulator[1] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[1].value) >> ADSR_SHIFT) * notes[i].scaledLevel[1]) >> LEVEL_SHIFT;
            // OP 0.
            operators[0].value = (((operators[0].source[((notes[i].stepAccumulator[0] >> STEP_SHIFT) + operators[1].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[0].value) >> ADSR_SHIFT) * notes[i].scaledLevel[0]) >> LEVEL_SHIFT;
            // OP 3.
            operators[3].value = (((operators[3].source[(notes[i].stepAccumulator[3] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[3].value) >> ADSR_SHIFT) * notes[i].scaledLevel[3]) >> LEVEL_SHIFT;
            // OP 2.
            operators[2].value = (((operators[2].source[((notes[i].stepAccumulator[2] >> STEP_SHIFT) + operators[3].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[2].value) >> ADSR_SHIFT) * notes[i].scaledLevel[2]) >> LEVEL_SHIFT;
            // OP 5.
            operators[5].value = (((operators[5].source[((notes[i].stepAccumulator[5] >> STEP_SHIFT) + notes[i].feedback) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[5].value) >> ADSR_SHIFT) * notes[i].scaledLevel[5]) >> LEVEL_SHIFT;
            // OP 4 and feedback.
            operators[4].value = (((operators[4].source[((notes[i].stepAccumulator[4] >> STEP_SHIFT) + operators[5].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[4].value) >> ADSR_SHIFT) * notes[i].scaledLevel[4]) >> LEVEL_SHIFT;
            notes[i].feedback = (operators[4].value * operators[4].feedback) >> FEEDBACK_SHIFT;

            // Increments note steps
            notes[i].stepAccumulator[0] += notes[i].scaledStep[0];
            notes[i].stepAccumulator[1] += notes[i].scaledStep[1];
            notes[i].stepAccumulator[2] += notes[i].scaledStep[2];
            notes[i].stepAccumulator[3] += notes[i].scaledStep[3];
            notes[i].stepAccumulator[4] += notes[i].scaledStep[4];
            notes[i].stepAccumulator[5] += notes[i].scaledStep[5];

            // Increments the synth output.
            synth.outputLeft += operators[0].value + operators[2].value + operators[4].value;
            synth.outputRight += operators[0].value + operators[2].value + operators[4].value;
        }
}

__attribute__((always_inline)) inline void algorithm6Code(uint8_t noteIndexLow, uint8_t noteIndexHigh)
{
    for (uint8_t i = noteIndexLow; i < noteIndexHigh; ++i)
        if (notes[i].on == true)
        {
            // OP 1.
            operators[1].value = (((operators[1].source[(notes[i].stepAccumulator[1] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[1].value) >> ADSR_SHIFT) * notes[i].scaledLevel[1]) >> LEVEL_SHIFT;
            // OP 0.
            operators[0].value = (((operators[0].source[((notes[i].stepAccumulator[0] >> STEP_SHIFT) + operators[1].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[0].value) >> ADSR_SHIFT) * notes[i].scaledLevel[0]) >> LEVEL_SHIFT;
            // OP 3.
            operators[3].value = (((operators[3].source[(notes[i].stepAccumulator[3] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[3].value) >> ADSR_SHIFT) * notes[i].scaledLevel[3]) >> LEVEL_SHIFT;
            // OP 5 and feedback.
            operators[5].value = (((operators[5].source[((notes[i].stepAccumulator[5] >> STEP_SHIFT) + notes[i].feedback) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[5].value) >> ADSR_SHIFT) * notes[i].scaledLevel[5]) >> LEVEL_SHIFT;
            notes[i].feedback = (operators[5].value * operators[5].feedback) >> FEEDBACK_SHIFT;
            // OP 4.
            operators[4].value = (((operators[4].source[((notes[i].stepAccumulator[4] >> STEP_SHIFT) + operators[5].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[4].value) >> ADSR_SHIFT) * notes[i].scaledLevel[4]) >> LEVEL_SHIFT;
            // OP 2.
            operators[2].value = (((operators[2].source[((notes[i].stepAccumulator[2] >> STEP_SHIFT) + operators[3].value + operators[4].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[2].value) >> ADSR_SHIFT) * notes[i].scaledLevel[2]) >> LEVEL_SHIFT;

            // Increments note steps
            notes[i].stepAccumulator[0] += notes[i].scaledStep[0];
            notes[i].stepAccumulator[1] += notes[i].scaledStep[1];
            notes[i].stepAccumulator[2] += notes[i].scaledStep[2];
            notes[i].stepAccumulator[3] += notes[i].scaledStep[3];
            notes[i].stepAccumulator[4] += notes[i].scaledStep[4];
            notes[i].stepAccumulator[5] += notes[i].scaledStep[5];

            // Increments the synth output.
            synth.outputLeft += operators[0].value + operators[2].value;
            synth.outputRight += operators[0].value + operators[2].value;
        }
}

__attribute__((always_inline)) inline void algorithm7Code(uint8_t noteIndexLow, uint8_t noteIndexHigh)
{
    for (uint8_t i = noteIndexLow; i < noteIndexHigh; ++i)
        if (notes[i].on == true)
        {
            // OP 1.
            operators[1].value = (((operators[1].source[(notes[i].stepAccumulator[1] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[1].value) >> ADSR_SHIFT) * notes[i].scaledLevel[1]) >> LEVEL_SHIFT;
            // OP 0.
            operators[0].value = (((operators[0].source[((notes[i].stepAccumulator[0] >> STEP_SHIFT) + operators[1].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[0].value) >> ADSR_SHIFT) * notes[i].scaledLevel[0]) >> LEVEL_SHIFT;
            // OP 3.
            operators[3].value = (((operators[3].source[((notes[i].stepAccumulator[3] >> STEP_SHIFT) + notes[i].feedback) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[3].value) >> ADSR_SHIFT) * notes[i].scaledLevel[3]) >> LEVEL_SHIFT;
            // OP 5.
            operators[5].value = (((operators[5].source[(notes[i].stepAccumulator[5] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[5].value) >> ADSR_SHIFT) * notes[i].scaledLevel[5]) >> LEVEL_SHIFT;
            // OP 4 and feedback.
            operators[4].value = (((operators[4].source[((notes[i].stepAccumulator[4] >> STEP_SHIFT) + operators[5].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[4].value) >> ADSR_SHIFT) * notes[i].scaledLevel[4]) >> LEVEL_SHIFT;
            notes[i].feedback = (operators[4].value * operators[4].feedback) >> FEEDBACK_SHIFT;
            // OP 2.
            operators[2].value = (((operators[2].source[((notes[i].stepAccumulator[2] >> STEP_SHIFT) + operators[3].value + operators[4].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[2].value) >> ADSR_SHIFT) * notes[i].scaledLevel[2]) >> LEVEL_SHIFT;

            // Increments note steps
            notes[i].stepAccumulator[0] += notes[i].scaledStep[0];
            notes[i].stepAccumulator[1] += notes[i].scaledStep[1];
            notes[i].stepAccumulator[2] += notes[i].scaledStep[2];
            notes[i].stepAccumulator[3] += notes[i].scaledStep[3];
            notes[i].stepAccumulator[4] += notes[i].scaledStep[4];
            notes[i].stepAccumulator[5] += notes[i].scaledStep[5];

            // Increments the synth output.
            synth.outputLeft += operators[0].value + operators[2].value;
            synth.outputRight += operators[0].value + operators[2].value;
        }
}

__attribute__((always_inline)) inline void algorithm8Code(uint8_t noteIndexLow, uint8_t noteIndexHigh)
{
    for (uint8_t i = noteIndexLow; i < noteIndexHigh; ++i)
        if (notes[i].on == true)
        {
            // OP 1 and feedback.
            operators[1].value = (((operators[1].source[((notes[i].stepAccumulator[1] >> STEP_SHIFT) + notes[i].feedback) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[1].value) >> ADSR_SHIFT) * notes[i].scaledLevel[1]) >> LEVEL_SHIFT;
            notes[i].feedback = (operators[1].value * operators[1].feedback) >> FEEDBACK_SHIFT;
            // OP 0.
            operators[0].value = (((operators[0].source[((notes[i].stepAccumulator[0] >> STEP_SHIFT) + operators[1].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[0].value) >> ADSR_SHIFT) * notes[i].scaledLevel[0]) >> LEVEL_SHIFT;
            // OP 3.
            operators[3].value = (((operators[3].source[(notes[i].stepAccumulator[3] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[3].value) >> ADSR_SHIFT) * notes[i].scaledLevel[3]) >> LEVEL_SHIFT;
            // OP 5.
            operators[5].value = (((operators[5].source[(notes[i].stepAccumulator[5] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[5].value) >> ADSR_SHIFT) * notes[i].scaledLevel[5]) >> LEVEL_SHIFT;
            // OP 4.
            operators[4].value = (((operators[4].source[((notes[i].stepAccumulator[4] >> STEP_SHIFT) + operators[5].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[4].value) >> ADSR_SHIFT) * notes[i].scaledLevel[4]) >> LEVEL_SHIFT;
            // OP 2.
            operators[2].value = (((operators[2].source[((notes[i].stepAccumulator[2] >> STEP_SHIFT) + operators[3].value + operators[4].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[2].value) >> ADSR_SHIFT) * notes[i].scaledLevel[2]) >> LEVEL_SHIFT;

            // Increments note steps
            notes[i].stepAccumulator[0] += notes[i].scaledStep[0];
            notes[i].stepAccumulator[1] += notes[i].scaledStep[1];
            notes[i].stepAccumulator[2] += notes[i].scaledStep[2];
            notes[i].stepAccumulator[3] += notes[i].scaledStep[3];
            notes[i].stepAccumulator[4] += notes[i].scaledStep[4];
            notes[i].stepAccumulator[5] += notes[i].scaledStep[5];

            // Increments the synth output.
            synth.outputLeft += operators[0].value + operators[2].value;
            synth.outputRight += operators[0].value + operators[2].value;
        }
}

__attribute__((always_inline)) inline void algorithm9Code(uint8_t noteIndexLow, uint8_t noteIndexHigh)
{
    for (uint8_t i = noteIndexLow; i < noteIndexHigh; ++i)
        if (notes[i].on == true)
        {
            // OP 2 and feedback.
            operators[2].value = (((operators[2].source[((notes[i].stepAccumulator[2] >> STEP_SHIFT) + notes[i].feedback) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[2].value) >> ADSR_SHIFT) * notes[i].scaledLevel[2]) >> LEVEL_SHIFT;
            notes[i].feedback = (operators[2].value * operators[2].feedback) >> FEEDBACK_SHIFT;
            // OP 1.
            operators[1].value = (((operators[1].source[((notes[i].stepAccumulator[1] >> STEP_SHIFT) + operators[2].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[1].value) >> ADSR_SHIFT) * notes[i].scaledLevel[1]) >> LEVEL_SHIFT;
            // OP 0.
            operators[0].value = (((operators[0].source[((notes[i].stepAccumulator[0] >> STEP_SHIFT) + operators[1].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[0].value) >> ADSR_SHIFT) * notes[i].scaledLevel[0]) >> LEVEL_SHIFT;
            // OP 5.
            operators[5].value = (((operators[5].source[(notes[i].stepAccumulator[5] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[5].value) >> ADSR_SHIFT) * notes[i].scaledLevel[5]) >> LEVEL_SHIFT;
            // OP 4.
            operators[4].value = (((operators[4].source[(notes[i].stepAccumulator[4] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[4].value) >> ADSR_SHIFT) * notes[i].scaledLevel[4]) >> LEVEL_SHIFT;
            // OP 3.
            operators[3].value = (((operators[3].source[((notes[i].stepAccumulator[3] >> STEP_SHIFT) + operators[5].value + operators[4].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[3].value) >> ADSR_SHIFT) * notes[i].scaledLevel[3]) >> LEVEL_SHIFT;

            // Increments note steps
            notes[i].stepAccumulator[0] += notes[i].scaledStep[0];
            notes[i].stepAccumulator[1] += notes[i].scaledStep[1];
            notes[i].stepAccumulator[2] += notes[i].scaledStep[2];
            notes[i].stepAccumulator[3] += notes[i].scaledStep[3];
            notes[i].stepAccumulator[4] += notes[i].scaledStep[4];
            notes[i].stepAccumulator[5] += notes[i].scaledStep[5];

            // Increments the synth output.
            synth.outputLeft += operators[0].value + operators[3].value;
            synth.outputRight += operators[0].value + operators[3].value;
        }
}

__attribute__((always_inline)) inline void algorithm10Code(uint8_t noteIndexLow, uint8_t noteIndexHigh)
{
    for (uint8_t i = noteIndexLow; i < noteIndexHigh; ++i)
        if (notes[i].on == true)
        {
            // OP 2.
            operators[2].value = (((operators[2].source[(notes[i].stepAccumulator[2] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[2].value) >> ADSR_SHIFT) * notes[i].scaledLevel[2]) >> LEVEL_SHIFT;
            // OP 1.
            operators[1].value = (((operators[1].source[((notes[i].stepAccumulator[1] >> STEP_SHIFT) + operators[2].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[1].value) >> ADSR_SHIFT) * notes[i].scaledLevel[1]) >> LEVEL_SHIFT;
            // OP 0.
            operators[0].value = (((operators[0].source[((notes[i].stepAccumulator[0] >> STEP_SHIFT) + operators[1].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[0].value) >> ADSR_SHIFT) * notes[i].scaledLevel[0]) >> LEVEL_SHIFT;
            // OP 5.
            operators[5].value = (((operators[5].source[((notes[i].stepAccumulator[5] >> STEP_SHIFT) + notes[i].feedback) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[5].value) >> ADSR_SHIFT) * notes[i].scaledLevel[5]) >> LEVEL_SHIFT;
            // OP 4 and feedback.
            operators[4].value = (((operators[4].source[(notes[i].stepAccumulator[4] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[4].value) >> ADSR_SHIFT) * notes[i].scaledLevel[4]) >> LEVEL_SHIFT;
            notes[i].feedback = (operators[4].value * operators[4].feedback) >> FEEDBACK_SHIFT;
            // OP 3.
            operators[3].value = (((operators[3].source[((notes[i].stepAccumulator[3] >> STEP_SHIFT) + operators[5].value + operators[4].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[3].value) >> ADSR_SHIFT) * notes[i].scaledLevel[3]) >> LEVEL_SHIFT;

            // Increments note steps
            notes[i].stepAccumulator[0] += notes[i].scaledStep[0];
            notes[i].stepAccumulator[1] += notes[i].scaledStep[1];
            notes[i].stepAccumulator[2] += notes[i].scaledStep[2];
            notes[i].stepAccumulator[3] += notes[i].scaledStep[3];
            notes[i].stepAccumulator[4] += notes[i].scaledStep[4];
            notes[i].stepAccumulator[5] += notes[i].scaledStep[5];

            // Increments the synth output.
            synth.outputLeft += operators[0].value + operators[3].value;
            synth.outputRight += operators[0].value + operators[3].value;
        }
}

__attribute__((always_inline)) inline void algorithm11Code(uint8_t noteIndexLow, uint8_t noteIndexHigh)
{
    for (uint8_t i = noteIndexLow; i < noteIndexHigh; ++i)
        if (notes[i].on == true)
        {
            // OP 1 and feedback.
            operators[1].value = (((operators[1].source[((notes[i].stepAccumulator[1] >> STEP_SHIFT) + notes[i].feedback) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[1].value) >> ADSR_SHIFT) * notes[i].scaledLevel[1]) >> LEVEL_SHIFT;
            notes[i].feedback = (operators[1].value * operators[1].feedback) >> FEEDBACK_SHIFT;
            // OP 0.
            operators[0].value = (((operators[0].source[((notes[i].stepAccumulator[0] >> STEP_SHIFT) + operators[1].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[0].value) >> ADSR_SHIFT) * notes[i].scaledLevel[0]) >> LEVEL_SHIFT;
            // OP 3.
            operators[3].value = (((operators[3].source[(notes[i].stepAccumulator[3] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[3].value) >> ADSR_SHIFT) * notes[i].scaledLevel[3]) >> LEVEL_SHIFT;
            // OP 4.
            operators[4].value = (((operators[4].source[(notes[i].stepAccumulator[4] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[4].value) >> ADSR_SHIFT) * notes[i].scaledLevel[4]) >> LEVEL_SHIFT;
            // OP 5.
            operators[5].value = (((operators[5].source[(notes[i].stepAccumulator[5] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[5].value) >> ADSR_SHIFT) * notes[i].scaledLevel[5]) >> LEVEL_SHIFT;
            // OP 2.
            operators[2].value = (((operators[2].source[((notes[i].stepAccumulator[2] >> STEP_SHIFT) + operators[3].value + operators[4].value + operators[5].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[2].value) >> ADSR_SHIFT) * notes[i].scaledLevel[2]) >> LEVEL_SHIFT;

            // Increments note steps
            notes[i].stepAccumulator[0] += notes[i].scaledStep[0];
            notes[i].stepAccumulator[1] += notes[i].scaledStep[1];
            notes[i].stepAccumulator[2] += notes[i].scaledStep[2];
            notes[i].stepAccumulator[3] += notes[i].scaledStep[3];
            notes[i].stepAccumulator[4] += notes[i].scaledStep[4];
            notes[i].stepAccumulator[5] += notes[i].scaledStep[5];

            // Increments the synth output.
            synth.outputLeft += operators[0].value + operators[2].value;
            synth.outputRight += operators[0].value + operators[2].value;
        }
}

__attribute__((always_inline)) inline void algorithm12Code(uint8_t noteIndexLow, uint8_t noteIndexHigh)
{
    for (uint8_t i = noteIndexLow; i < noteIndexHigh; ++i)
        if (notes[i].on == true)
        {
            // OP 1.
            operators[1].value = (((operators[1].source[(notes[i].stepAccumulator[1] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[1].value) >> ADSR_SHIFT) * notes[i].scaledLevel[1]) >> LEVEL_SHIFT;
            // OP 0.
            operators[0].value = (((operators[0].source[((notes[i].stepAccumulator[0] >> STEP_SHIFT) + operators[1].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[0].value) >> ADSR_SHIFT) * notes[i].scaledLevel[0]) >> LEVEL_SHIFT;
            // OP 3.
            operators[3].value = (((operators[3].source[(notes[i].stepAccumulator[3] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[3].value) >> ADSR_SHIFT) * notes[i].scaledLevel[3]) >> LEVEL_SHIFT;
            // OP 4.
            operators[4].value = (((operators[4].source[(notes[i].stepAccumulator[4] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[4].value) >> ADSR_SHIFT) * notes[i].scaledLevel[4]) >> LEVEL_SHIFT;
            // OP 5 and feedback.
            operators[5].value = (((operators[5].source[((notes[i].stepAccumulator[5] >> STEP_SHIFT) + notes[i].feedback) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[5].value) >> ADSR_SHIFT) * notes[i].scaledLevel[5]) >> LEVEL_SHIFT;
            notes[i].feedback = (operators[5].value * operators[5].feedback) >> FEEDBACK_SHIFT;
            // OP 2.
            operators[2].value = (((operators[2].source[(((notes[i].stepAccumulator[2] >> STEP_SHIFT) + operators[3].value + operators[4].value + operators[5].value)) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[2].value) >> ADSR_SHIFT) * notes[i].scaledLevel[2]) >> LEVEL_SHIFT;

            // Increments note steps
            notes[i].stepAccumulator[0] += notes[i].scaledStep[0];
            notes[i].stepAccumulator[1] += notes[i].scaledStep[1];
            notes[i].stepAccumulator[2] += notes[i].scaledStep[2];
            notes[i].stepAccumulator[3] += notes[i].scaledStep[3];
            notes[i].stepAccumulator[4] += notes[i].scaledStep[4];
            notes[i].stepAccumulator[5] += notes[i].scaledStep[5];

            // Increments the synth output.
            synth.outputLeft += operators[0].value + operators[2].value;
            synth.outputRight += operators[0].value + operators[2].value;
        }
}

__attribute__((always_inline)) inline void algorithm13Code(uint8_t noteIndexLow, uint8_t noteIndexHigh)
{
    for (uint8_t i = noteIndexLow; i < noteIndexHigh; ++i)
        if (notes[i].on == true)
        {
            // OP 1.
            operators[1].value = (((operators[1].source[(notes[i].stepAccumulator[1] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[1].value) >> ADSR_SHIFT) * notes[i].scaledLevel[1]) >> LEVEL_SHIFT;
            // OP 0.
            operators[0].value = (((operators[0].source[((notes[i].stepAccumulator[0] >> STEP_SHIFT) + operators[1].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[0].value) >> ADSR_SHIFT) * notes[i].scaledLevel[0]) >> LEVEL_SHIFT;
            // OP 5.
            operators[5].value = (((operators[5].source[((notes[i].stepAccumulator[5] >> STEP_SHIFT) + notes[i].feedback) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[5].value) >> ADSR_SHIFT) * notes[i].scaledLevel[5]) >> LEVEL_SHIFT;
            // OP 4 and feedback.
            operators[4].value = (((operators[4].source[(notes[i].stepAccumulator[4] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[4].value) >> ADSR_SHIFT) * notes[i].scaledLevel[4]) >> LEVEL_SHIFT;
            notes[i].feedback = (operators[4].value * operators[4].feedback) >> FEEDBACK_SHIFT;
            // OP 3.
            operators[3].value = (((operators[3].source[((notes[i].stepAccumulator[3] >> STEP_SHIFT) + operators[5].value + operators[4].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[3].value) >> ADSR_SHIFT) * notes[i].scaledLevel[3]) >> LEVEL_SHIFT;
            // OP 2.
            operators[2].value = (((operators[2].source[((notes[i].stepAccumulator[2] >> STEP_SHIFT) + operators[3].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[2].value) >> ADSR_SHIFT) * notes[i].scaledLevel[2]) >> LEVEL_SHIFT;

            // Increments note steps
            notes[i].stepAccumulator[0] += notes[i].scaledStep[0];
            notes[i].stepAccumulator[1] += notes[i].scaledStep[1];
            notes[i].stepAccumulator[2] += notes[i].scaledStep[2];
            notes[i].stepAccumulator[3] += notes[i].scaledStep[3];
            notes[i].stepAccumulator[4] += notes[i].scaledStep[4];
            notes[i].stepAccumulator[5] += notes[i].scaledStep[5];

            // Increments the synth output.
            synth.outputLeft += operators[0].value + operators[2].value;
            synth.outputRight += operators[0].value + operators[2].value;
        }
}

__attribute__((always_inline)) inline void algorithm14Code(uint8_t noteIndexLow, uint8_t noteIndexHigh)
{
    for (uint8_t i = noteIndexLow; i < noteIndexHigh; ++i)
        if (notes[i].on == true)
        {
            // OP 1 and feedback.
            operators[1].value = (((operators[1].source[((notes[i].stepAccumulator[1] >> STEP_SHIFT) + notes[i].feedback) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[1].value) >> ADSR_SHIFT) * notes[i].scaledLevel[1]) >> LEVEL_SHIFT;
            notes[i].feedback = (operators[4].value * operators[4].feedback) >> FEEDBACK_SHIFT;
            // OP 0.
            operators[0].value = (((operators[0].source[((notes[i].stepAccumulator[0] >> STEP_SHIFT) + operators[1].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[0].value) >> ADSR_SHIFT) * notes[i].scaledLevel[0]) >> LEVEL_SHIFT;
            // OP 5.
            operators[5].value = (((operators[5].source[(notes[i].stepAccumulator[5] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[5].value) >> ADSR_SHIFT) * notes[i].scaledLevel[5]) >> LEVEL_SHIFT;
            // OP 4.
            operators[4].value = (((operators[4].source[(notes[i].stepAccumulator[4] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[4].value) >> ADSR_SHIFT) * notes[i].scaledLevel[4]) >> LEVEL_SHIFT;
            // OP 3.
            operators[3].value = (((operators[3].source[((notes[i].stepAccumulator[3] >> STEP_SHIFT) + operators[5].value + operators[4].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[3].value) >> ADSR_SHIFT) * notes[i].scaledLevel[3]) >> LEVEL_SHIFT;
            // OP 2.
            operators[2].value = (((operators[2].source[((notes[i].stepAccumulator[2] >> STEP_SHIFT) + operators[3].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[2].value) >> ADSR_SHIFT) * notes[i].scaledLevel[2]) >> LEVEL_SHIFT;

            // Increments note steps
            notes[i].stepAccumulator[0] += notes[i].scaledStep[0];
            notes[i].stepAccumulator[1] += notes[i].scaledStep[1];
            notes[i].stepAccumulator[2] += notes[i].scaledStep[2];
            notes[i].stepAccumulator[3] += notes[i].scaledStep[3];
            notes[i].stepAccumulator[4] += notes[i].scaledStep[4];
            notes[i].stepAccumulator[5] += notes[i].scaledStep[5];

            // Increments the synth output.
            synth.outputLeft += operators[0].value + operators[2].value;
            synth.outputRight += operators[0].value + operators[2].value;
        }
}

__attribute__((always_inline)) inline void algorithm15Code(uint8_t noteIndexLow, uint8_t noteIndexHigh)
{
    for (uint8_t i = noteIndexLow; i < noteIndexHigh; ++i)
        if (notes[i].on == true)
        {
            // OP 1.
            operators[1].value = (((operators[1].source[(notes[i].stepAccumulator[1] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[1].value) >> ADSR_SHIFT) * notes[i].scaledLevel[1]) >> LEVEL_SHIFT;
            // OP 3.
            operators[3].value = (((operators[3].source[(notes[i].stepAccumulator[3] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[3].value) >> ADSR_SHIFT) * notes[i].scaledLevel[3]) >> LEVEL_SHIFT;
            // OP 2.
            operators[2].value = (((operators[2].source[((notes[i].stepAccumulator[2] >> STEP_SHIFT) + operators[3].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[2].value) >> ADSR_SHIFT) * notes[i].scaledLevel[2]) >> LEVEL_SHIFT;
            // OP 5 and feedback.
            operators[5].value = (((operators[5].source[((notes[i].stepAccumulator[5] >> STEP_SHIFT) + notes[i].feedback) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[5].value) >> ADSR_SHIFT) * notes[i].scaledLevel[5]) >> LEVEL_SHIFT;
            notes[i].feedback = (operators[5].value * operators[5].feedback) >> FEEDBACK_SHIFT;
            // OP 4.
            operators[4].value = (((operators[4].source[((notes[i].stepAccumulator[4] >> STEP_SHIFT) + operators[5].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[4].value) >> ADSR_SHIFT) * notes[i].scaledLevel[4]) >> LEVEL_SHIFT;
            // OP 0.
            operators[0].value = (((operators[0].source[((notes[i].stepAccumulator[0] >> STEP_SHIFT) + operators[1].value + operators[2].value + operators[4].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[0].value) >> ADSR_SHIFT) * notes[i].scaledLevel[0]) >> LEVEL_SHIFT;

            // Increments note steps
            notes[i].stepAccumulator[0] += notes[i].scaledStep[0];
            notes[i].stepAccumulator[1] += notes[i].scaledStep[1];
            notes[i].stepAccumulator[2] += notes[i].scaledStep[2];
            notes[i].stepAccumulator[3] += notes[i].scaledStep[3];
            notes[i].stepAccumulator[4] += notes[i].scaledStep[4];
            notes[i].stepAccumulator[5] += notes[i].scaledStep[5];

            // Increments the synth output.
            synth.outputLeft += operators[0].value;
            synth.outputRight += operators[0].value;
        }
}

__attribute__((always_inline)) inline void algorithm16Code(uint8_t noteIndexLow, uint8_t noteIndexHigh)
{
    for (uint8_t i = noteIndexLow; i < noteIndexHigh; ++i)
        if (notes[i].on == true)
        {
            // OP 1 and feedback.
            operators[1].value = (((operators[1].source[((notes[i].stepAccumulator[1] >> STEP_SHIFT) + notes[i].feedback) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[1].value) >> ADSR_SHIFT) * notes[i].scaledLevel[1]) >> LEVEL_SHIFT;
            notes[i].feedback = (operators[1].value * operators[1].feedback) >> FEEDBACK_SHIFT;
            // OP 3.
            operators[3].value = (((operators[3].source[(notes[i].stepAccumulator[3] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[3].value) >> ADSR_SHIFT) * notes[i].scaledLevel[3]) >> LEVEL_SHIFT;
            // OP 2.
            operators[2].value = (((operators[2].source[((notes[i].stepAccumulator[2] >> STEP_SHIFT) + operators[3].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[2].value) >> ADSR_SHIFT) * notes[i].scaledLevel[2]) >> LEVEL_SHIFT;
            // OP 5.
            operators[5].value = (((operators[5].source[(notes[i].stepAccumulator[5] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[5].value) >> ADSR_SHIFT) * notes[i].scaledLevel[5]) >> LEVEL_SHIFT;
            // OP 4.
            operators[4].value = (((operators[4].source[((notes[i].stepAccumulator[4] >> STEP_SHIFT) + operators[5].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[4].value) >> ADSR_SHIFT) * notes[i].scaledLevel[4]) >> LEVEL_SHIFT;
            // OP 0.
            operators[0].value = (((operators[0].source[((notes[i].stepAccumulator[0] >> STEP_SHIFT) + operators[1].value + operators[2].value + operators[4].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[0].value) >> ADSR_SHIFT) * notes[i].scaledLevel[0]) >> LEVEL_SHIFT;

            // Increments note steps
            notes[i].stepAccumulator[0] += notes[i].scaledStep[0];
            notes[i].stepAccumulator[1] += notes[i].scaledStep[1];
            notes[i].stepAccumulator[2] += notes[i].scaledStep[2];
            notes[i].stepAccumulator[3] += notes[i].scaledStep[3];
            notes[i].stepAccumulator[4] += notes[i].scaledStep[4];
            notes[i].stepAccumulator[5] += notes[i].scaledStep[5];

            // Increments the synth output.
            synth.outputLeft += operators[0].value;
            synth.outputRight += operators[0].value;
        }
}

__attribute__((always_inline)) inline void algorithm17Code(uint8_t noteIndexLow, uint8_t noteIndexHigh)
{
    for (uint8_t i = noteIndexLow; i < noteIndexHigh; ++i)
        if (notes[i].on == true)
        {
            // OP 1.
            operators[1].value = (((operators[1].source[(notes[i].stepAccumulator[1] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[1].value) >> ADSR_SHIFT) * notes[i].scaledLevel[1]) >> LEVEL_SHIFT;
            // OP 2.
            operators[2].value = (((operators[2].source[((notes[i].stepAccumulator[2] >> STEP_SHIFT) + notes[i].feedback) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[2].value) >> ADSR_SHIFT) * notes[i].scaledLevel[2]) >> LEVEL_SHIFT;
            // OP 5.
            operators[5].value = (((operators[5].source[(notes[i].stepAccumulator[5] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[5].value) >> ADSR_SHIFT) * notes[i].scaledLevel[5]) >> LEVEL_SHIFT;
            // OP 4.
            operators[4].value = (((operators[4].source[((notes[i].stepAccumulator[4] >> STEP_SHIFT) + operators[5].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[4].value) >> ADSR_SHIFT) * notes[i].scaledLevel[4]) >> LEVEL_SHIFT;
            // OP 3 and feedback.
            operators[3].value = (((operators[3].source[((notes[i].stepAccumulator[3] >> STEP_SHIFT) + operators[4].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[3].value) >> ADSR_SHIFT) * notes[i].scaledLevel[3]) >> LEVEL_SHIFT;
            notes[i].feedback = (operators[3].value * operators[3].feedback) >> FEEDBACK_SHIFT;
            // OP 0.
            operators[0].value = (((operators[0].source[((notes[i].stepAccumulator[0] >> STEP_SHIFT) + operators[1].value + operators[2].value + operators[3].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[0].value) >> ADSR_SHIFT) * notes[i].scaledLevel[0]) >> LEVEL_SHIFT;

            // Increments note steps
            notes[i].stepAccumulator[0] += notes[i].scaledStep[0];
            notes[i].stepAccumulator[1] += notes[i].scaledStep[1];
            notes[i].stepAccumulator[2] += notes[i].scaledStep[2];
            notes[i].stepAccumulator[3] += notes[i].scaledStep[3];
            notes[i].stepAccumulator[4] += notes[i].scaledStep[4];
            notes[i].stepAccumulator[5] += notes[i].scaledStep[5];

            // Increments the synth output.
            synth.outputLeft += operators[0].value;
            synth.outputRight += operators[0].value;
        }
}

__attribute__((always_inline)) inline void algorithm18Code(uint8_t noteIndexLow, uint8_t noteIndexHigh)
{
    for (uint8_t i = noteIndexLow; i < noteIndexHigh; ++i)
        if (notes[i].on == true)
        {
            // OP 2.
            operators[2].value = (((operators[2].source[(notes[i].stepAccumulator[2] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[2].value) >> ADSR_SHIFT) * notes[i].scaledLevel[2]) >> LEVEL_SHIFT;
            // OP 1.
            operators[1].value = (((operators[1].source[((notes[i].stepAccumulator[1] >> STEP_SHIFT) + operators[2].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[1].value) >> ADSR_SHIFT) * notes[i].scaledLevel[1]) >> LEVEL_SHIFT;
            // OP 0.
            operators[0].value = (((operators[0].source[((notes[i].stepAccumulator[0] >> STEP_SHIFT) + operators[1].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[0].value) >> ADSR_SHIFT) * notes[i].scaledLevel[0]) >> LEVEL_SHIFT;
            // OP 5 and feedback.
            operators[5].value = (((operators[5].source[((notes[i].stepAccumulator[5] >> STEP_SHIFT) + notes[i].feedback) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[5].value) >> ADSR_SHIFT) * notes[i].scaledLevel[5]) >> LEVEL_SHIFT;
            notes[i].feedback = (operators[5].value * operators[5].feedback) >> FEEDBACK_SHIFT;
            // OP 3.
            operators[3].value = (((operators[3].source[((notes[i].stepAccumulator[3] >> STEP_SHIFT) + operators[5].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[3].value) >> ADSR_SHIFT) * notes[i].scaledLevel[3]) >> LEVEL_SHIFT;
            // OP 4.
            operators[4].value = (((operators[4].source[((notes[i].stepAccumulator[4] >> STEP_SHIFT) + operators[5].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[4].value) >> ADSR_SHIFT) * notes[i].scaledLevel[4]) >> LEVEL_SHIFT;

            // Increments note steps
            notes[i].stepAccumulator[0] += notes[i].scaledStep[0];
            notes[i].stepAccumulator[1] += notes[i].scaledStep[1];
            notes[i].stepAccumulator[2] += notes[i].scaledStep[2];
            notes[i].stepAccumulator[3] += notes[i].scaledStep[3];
            notes[i].stepAccumulator[4] += notes[i].scaledStep[4];
            notes[i].stepAccumulator[5] += notes[i].scaledStep[5];

            // Increments the synth output.
            synth.outputLeft += operators[0].value + operators[3].value + operators[4].value;
            synth.outputRight += operators[0].value + operators[3].value + operators[4].value;
        }
}

__attribute__((always_inline)) inline void algorithm19Code(uint8_t noteIndexLow, uint8_t noteIndexHigh)
{
    for (uint8_t i = noteIndexLow; i < noteIndexHigh; ++i)
        if (notes[i].on == true)
        {
            // OP 2 and feedback.
            operators[2].value = (((operators[2].source[((notes[i].stepAccumulator[2] >> STEP_SHIFT) + notes[i].feedback) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[2].value) >> ADSR_SHIFT) * notes[i].scaledLevel[2]) >> LEVEL_SHIFT;
            notes[i].feedback = (operators[2].value * operators[2].feedback) >> FEEDBACK_SHIFT;
            // OP 0.
            operators[0].value = (((operators[0].source[((notes[i].stepAccumulator[0] >> STEP_SHIFT) + operators[2].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[0].value) >> ADSR_SHIFT) * notes[i].scaledLevel[0]) >> LEVEL_SHIFT;
            // OP 1.
            operators[1].value = (((operators[1].source[((notes[i].stepAccumulator[1] >> STEP_SHIFT) + operators[2].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[1].value) >> ADSR_SHIFT) * notes[i].scaledLevel[1]) >> LEVEL_SHIFT;
            // OP 4.
            operators[4].value = (((operators[4].source[(notes[i].stepAccumulator[4] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[4].value) >> ADSR_SHIFT) * notes[i].scaledLevel[4]) >> LEVEL_SHIFT;
            // OP 5.
            operators[5].value = (((operators[5].source[(notes[i].stepAccumulator[5] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[5].value) >> ADSR_SHIFT) * notes[i].scaledLevel[5]) >> LEVEL_SHIFT;
            // OP 3.
            operators[3].value = (((operators[3].source[((notes[i].stepAccumulator[3] >> STEP_SHIFT) + operators[4].value + operators[5].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[3].value) >> ADSR_SHIFT) * notes[i].scaledLevel[3]) >> LEVEL_SHIFT;

            // Increments note steps
            notes[i].stepAccumulator[0] += notes[i].scaledStep[0];
            notes[i].stepAccumulator[1] += notes[i].scaledStep[1];
            notes[i].stepAccumulator[2] += notes[i].scaledStep[2];
            notes[i].stepAccumulator[3] += notes[i].scaledStep[3];
            notes[i].stepAccumulator[4] += notes[i].scaledStep[4];
            notes[i].stepAccumulator[5] += notes[i].scaledStep[5];

            // Increments the synth output.
            synth.outputLeft += operators[0].value + operators[1].value + operators[3].value;
            synth.outputRight += operators[0].value + operators[1].value + operators[3].value;
        }
}

__attribute__((always_inline)) inline void algorithm20Code(uint8_t noteIndexLow, uint8_t noteIndexHigh)
{
    for (uint8_t i = noteIndexLow; i < noteIndexHigh; ++i)
        if (notes[i].on == true)
        {
            // OP 2 and feedback.
            operators[2].value = (((operators[2].source[((notes[i].stepAccumulator[2] >> STEP_SHIFT) + notes[i].feedback) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[2].value) >> ADSR_SHIFT) * notes[i].scaledLevel[2]) >> LEVEL_SHIFT;
            notes[i].feedback = (operators[2].value * operators[2].feedback) >> FEEDBACK_SHIFT;
            // OP 0.
            operators[0].value = (((operators[0].source[((notes[i].stepAccumulator[0] >> STEP_SHIFT) + operators[2].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[0].value) >> ADSR_SHIFT) * notes[i].scaledLevel[0]) >> LEVEL_SHIFT;
            // OP 1.
            operators[1].value = (((operators[1].source[((notes[i].stepAccumulator[1] >> STEP_SHIFT) + operators[2].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[1].value) >> ADSR_SHIFT) * notes[i].scaledLevel[1]) >> LEVEL_SHIFT;
            // OP 5.
            operators[5].value = (((operators[5].source[(notes[i].stepAccumulator[5] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[5].value) >> ADSR_SHIFT) * notes[i].scaledLevel[5]) >> LEVEL_SHIFT;
            // OP 3.
            operators[3].value = (((operators[3].source[((notes[i].stepAccumulator[3] >> STEP_SHIFT) + operators[5].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[3].value) >> ADSR_SHIFT) * notes[i].scaledLevel[3]) >> LEVEL_SHIFT;
            // OP 4.
            operators[4].value = (((operators[4].source[((notes[i].stepAccumulator[4] >> STEP_SHIFT) + operators[5].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[4].value) >> ADSR_SHIFT) * notes[i].scaledLevel[4]) >> LEVEL_SHIFT;

            // Increments note steps
            notes[i].stepAccumulator[0] += notes[i].scaledStep[0];
            notes[i].stepAccumulator[1] += notes[i].scaledStep[1];
            notes[i].stepAccumulator[2] += notes[i].scaledStep[2];
            notes[i].stepAccumulator[3] += notes[i].scaledStep[3];
            notes[i].stepAccumulator[4] += notes[i].scaledStep[4];
            notes[i].stepAccumulator[5] += notes[i].scaledStep[5];

            // Increments the synth output.
            synth.outputLeft += operators[0].value + operators[1].value + operators[3].value + operators[4].value;
            synth.outputRight += operators[0].value + operators[1].value + operators[3].value + operators[4].value;
        }
}

__attribute__((always_inline)) inline void algorithm21Code(uint8_t noteIndexLow, uint8_t noteIndexHigh)
{
    for (uint8_t i = noteIndexLow; i < noteIndexHigh; ++i)
        if (notes[i].on == true)
        {
            // OP 1.
            operators[1].value = (((operators[1].source[(notes[i].stepAccumulator[1] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[1].value) >> ADSR_SHIFT) * notes[i].scaledLevel[1]) >> LEVEL_SHIFT;
            // OP 0.
            operators[0].value = (((operators[0].source[((notes[i].stepAccumulator[0] >> STEP_SHIFT) + operators[1].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[0].value) >> ADSR_SHIFT) * notes[i].scaledLevel[0]) >> LEVEL_SHIFT;
            // OP 5 and feedback.
            operators[5].value = (((operators[5].source[((notes[i].stepAccumulator[5] >> STEP_SHIFT) + notes[i].feedback) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[5].value) >> ADSR_SHIFT) * notes[i].scaledLevel[5]) >> LEVEL_SHIFT;
            notes[i].feedback = (operators[5].value * operators[5].feedback) >> FEEDBACK_SHIFT;
            // OP 2.
            operators[2].value = (((operators[2].source[((notes[i].stepAccumulator[2] >> STEP_SHIFT) + operators[5].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[2].value) >> ADSR_SHIFT) * notes[i].scaledLevel[2]) >> LEVEL_SHIFT;
            // OP 3.
            operators[3].value = (((operators[3].source[((notes[i].stepAccumulator[3] >> STEP_SHIFT) + operators[5].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[3].value) >> ADSR_SHIFT) * notes[i].scaledLevel[3]) >> LEVEL_SHIFT;
            // OP 4.
            operators[4].value = (((operators[4].source[((notes[i].stepAccumulator[4] >> STEP_SHIFT) + operators[5].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[4].value) >> ADSR_SHIFT) * notes[i].scaledLevel[4]) >> LEVEL_SHIFT;

            // Increments note steps
            notes[i].stepAccumulator[0] += notes[i].scaledStep[0];
            notes[i].stepAccumulator[1] += notes[i].scaledStep[1];
            notes[i].stepAccumulator[2] += notes[i].scaledStep[2];
            notes[i].stepAccumulator[3] += notes[i].scaledStep[3];
            notes[i].stepAccumulator[4] += notes[i].scaledStep[4];
            notes[i].stepAccumulator[5] += notes[i].scaledStep[5];

            // Increments the synth output.
            synth.outputLeft += operators[0].value + operators[2].value + operators[3].value + operators[4].value;
            synth.outputRight += operators[0].value + operators[2].value + operators[3].value + operators[4].value;
        }
}

__attribute__((always_inline)) inline void algorithm22Code(uint8_t noteIndexLow, uint8_t noteIndexHigh)
{
    for (uint8_t i = noteIndexLow; i < noteIndexHigh; ++i)
        if (notes[i].on == true)
        {
            // OP 0.
            operators[0].value = (((operators[0].source[(notes[i].stepAccumulator[0] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[0].value) >> ADSR_SHIFT) * notes[i].scaledLevel[0]) >> LEVEL_SHIFT;
            // OP 2.
            operators[2].value = (((operators[2].source[(notes[i].stepAccumulator[2] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[2].value) >> ADSR_SHIFT) * notes[i].scaledLevel[2]) >> LEVEL_SHIFT;
            // OP 1.
            operators[1].value = (((operators[1].source[((notes[i].stepAccumulator[1] >> STEP_SHIFT) + operators[2].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[1].value) >> ADSR_SHIFT) * notes[i].scaledLevel[1]) >> LEVEL_SHIFT;
            // OP 5 and feedback.
            operators[5].value = (((operators[5].source[((notes[i].stepAccumulator[5] >> STEP_SHIFT) + notes[i].feedback) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[5].value) >> ADSR_SHIFT) * notes[i].scaledLevel[5]) >> LEVEL_SHIFT;
            notes[i].feedback = (operators[5].value * operators[5].feedback) >> FEEDBACK_SHIFT;
            // OP 3.
            operators[3].value = (((operators[3].source[((notes[i].stepAccumulator[3] >> STEP_SHIFT) + operators[5].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[3].value) >> ADSR_SHIFT) * notes[i].scaledLevel[3]) >> LEVEL_SHIFT;
            // OP 4.
            operators[4].value = (((operators[4].source[((notes[i].stepAccumulator[4] >> STEP_SHIFT) + operators[5].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[4].value) >> ADSR_SHIFT) * notes[i].scaledLevel[4]) >> LEVEL_SHIFT;

            // Increments note steps
            notes[i].stepAccumulator[0] += notes[i].scaledStep[0];
            notes[i].stepAccumulator[1] += notes[i].scaledStep[1];
            notes[i].stepAccumulator[2] += notes[i].scaledStep[2];
            notes[i].stepAccumulator[3] += notes[i].scaledStep[3];
            notes[i].stepAccumulator[4] += notes[i].scaledStep[4];
            notes[i].stepAccumulator[5] += notes[i].scaledStep[5];

            // Increments the synth output.
            synth.outputLeft += operators[0].value + operators[1].value + operators[3].value + operators[4].value;
            synth.outputRight += operators[0].value + operators[1].value + operators[3].value + operators[4].value;
        }
}

__attribute__((always_inline)) inline void algorithm23Code(uint8_t noteIndexLow, uint8_t noteIndexHigh)
{
    for (uint8_t i = noteIndexLow; i < noteIndexHigh; ++i)
        if (notes[i].on == true)
        {
            // OP 0.
            operators[0].value = (((operators[0].source[(notes[i].stepAccumulator[0] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[0].value) >> ADSR_SHIFT) * notes[i].scaledLevel[0]) >> LEVEL_SHIFT;
            // OP 1.
            operators[1].value = (((operators[1].source[(notes[i].stepAccumulator[1] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[1].value) >> ADSR_SHIFT) * notes[i].scaledLevel[1]) >> LEVEL_SHIFT;
            // OP 5 and feedback.
            operators[5].value = (((operators[5].source[((notes[i].stepAccumulator[5] >> STEP_SHIFT) + notes[i].feedback) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[5].value) >> ADSR_SHIFT) * notes[i].scaledLevel[5]) >> LEVEL_SHIFT;
            notes[i].feedback = (operators[5].value * operators[5].feedback) >> FEEDBACK_SHIFT;
            // OP 2.
            operators[2].value = (((operators[2].source[((notes[i].stepAccumulator[2] >> STEP_SHIFT) + operators[5].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[2].value) >> ADSR_SHIFT) * notes[i].scaledLevel[2]) >> LEVEL_SHIFT;
            // OP 3.
            operators[3].value = (((operators[3].source[((notes[i].stepAccumulator[3] >> STEP_SHIFT) + operators[5].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[3].value) >> ADSR_SHIFT) * notes[i].scaledLevel[3]) >> LEVEL_SHIFT;
            // OP 4.
            operators[4].value = (((operators[4].source[((notes[i].stepAccumulator[4] >> STEP_SHIFT) + operators[5].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[4].value) >> ADSR_SHIFT) * notes[i].scaledLevel[4]) >> LEVEL_SHIFT;

            // Increments note steps
            notes[i].stepAccumulator[0] += notes[i].scaledStep[0];
            notes[i].stepAccumulator[1] += notes[i].scaledStep[1];
            notes[i].stepAccumulator[2] += notes[i].scaledStep[2];
            notes[i].stepAccumulator[3] += notes[i].scaledStep[3];
            notes[i].stepAccumulator[4] += notes[i].scaledStep[4];
            notes[i].stepAccumulator[5] += notes[i].scaledStep[5];

            // Increments the synth output.
            synth.outputLeft += operators[0].value + operators[1].value + operators[2].value + operators[3].value + operators[4].value;
            synth.outputRight += operators[0].value + operators[1].value + operators[2].value + operators[3].value + operators[4].value;
        }
}

__attribute__((always_inline)) inline void algorithm24Code(uint8_t noteIndexLow, uint8_t noteIndexHigh)
{
    for (uint8_t i = noteIndexLow; i < noteIndexHigh; ++i)
        if (notes[i].on == true)
        {
            // OP 0.
            operators[0].value = (((operators[0].source[(notes[i].stepAccumulator[0] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[0].value) >> ADSR_SHIFT) * notes[i].scaledLevel[0]) >> LEVEL_SHIFT;
            // OP 1.
            operators[1].value = (((operators[1].source[(notes[i].stepAccumulator[1] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[1].value) >> ADSR_SHIFT) * notes[i].scaledLevel[1]) >> LEVEL_SHIFT;
            // OP 2.
            operators[2].value = (((operators[2].source[(notes[i].stepAccumulator[2] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[2].value) >> ADSR_SHIFT) * notes[i].scaledLevel[2]) >> LEVEL_SHIFT;
            // OP 5 and feedback.
            operators[5].value = (((operators[5].source[((notes[i].stepAccumulator[5] >> STEP_SHIFT) + notes[i].feedback) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[5].value) >> ADSR_SHIFT) * notes[i].scaledLevel[5]) >> LEVEL_SHIFT;
            notes[i].feedback = (operators[5].value * operators[5].feedback) >> FEEDBACK_SHIFT;
            // OP 3.
            operators[3].value = (((operators[3].source[((notes[i].stepAccumulator[3] >> STEP_SHIFT) + operators[5].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[3].value) >> ADSR_SHIFT) * notes[i].scaledLevel[3]) >> LEVEL_SHIFT;
            // OP 4.
            operators[4].value = (((operators[4].source[((notes[i].stepAccumulator[4] >> STEP_SHIFT) + operators[5].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[4].value) >> ADSR_SHIFT) * notes[i].scaledLevel[4]) >> LEVEL_SHIFT;

            // Increments note steps
            notes[i].stepAccumulator[0] += notes[i].scaledStep[0];
            notes[i].stepAccumulator[1] += notes[i].scaledStep[1];
            notes[i].stepAccumulator[2] += notes[i].scaledStep[2];
            notes[i].stepAccumulator[3] += notes[i].scaledStep[3];
            notes[i].stepAccumulator[4] += notes[i].scaledStep[4];
            notes[i].stepAccumulator[5] += notes[i].scaledStep[5];

            // Increments the synth output.
            synth.outputLeft += operators[0].value + operators[1].value + operators[2].value + operators[3].value + operators[4].value;
            synth.outputRight += operators[0].value + operators[1].value + operators[2].value + operators[3].value + operators[4].value;
        }
}

__attribute__((always_inline)) inline void algorithm25Code(uint8_t noteIndexLow, uint8_t noteIndexHigh)
{
    for (uint8_t i = noteIndexLow; i < noteIndexHigh; ++i)
        if (notes[i].on == true)
        {
            // OP 0.
            operators[0].value = (((operators[0].source[(notes[i].stepAccumulator[0] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[0].value) >> ADSR_SHIFT) * notes[i].scaledLevel[0]) >> LEVEL_SHIFT;
            // OP 2.
            operators[2].value = (((operators[2].source[(notes[i].stepAccumulator[2] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[2].value) >> ADSR_SHIFT) * notes[i].scaledLevel[2]) >> LEVEL_SHIFT;
            // OP 1.
            operators[1].value = (((operators[1].source[((notes[i].stepAccumulator[1] >> STEP_SHIFT) + operators[2].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[1].value) >> ADSR_SHIFT) * notes[i].scaledLevel[1]) >> LEVEL_SHIFT;
            // OP 4.
            operators[4].value = (((operators[4].source[(notes[i].stepAccumulator[4] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[4].value) >> ADSR_SHIFT) * notes[i].scaledLevel[4]) >> LEVEL_SHIFT;
            // OP 5 and feedback.
            operators[5].value = (((operators[5].source[((notes[i].stepAccumulator[5] >> STEP_SHIFT) + notes[i].feedback) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[5].value) >> ADSR_SHIFT) * notes[i].scaledLevel[5]) >> LEVEL_SHIFT;
            notes[i].feedback = (operators[5].value * operators[5].feedback) >> FEEDBACK_SHIFT;
            // OP 3.
            operators[3].value = (((operators[1].source[((notes[i].stepAccumulator[3] >> STEP_SHIFT) + operators[4].value + operators[5].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[3].value) >> ADSR_SHIFT) * notes[i].scaledLevel[3]) >> LEVEL_SHIFT;

            // Increments note steps
            notes[i].stepAccumulator[0] += notes[i].scaledStep[0];
            notes[i].stepAccumulator[1] += notes[i].scaledStep[1];
            notes[i].stepAccumulator[2] += notes[i].scaledStep[2];
            notes[i].stepAccumulator[3] += notes[i].scaledStep[3];
            notes[i].stepAccumulator[4] += notes[i].scaledStep[4];
            notes[i].stepAccumulator[5] += notes[i].scaledStep[5];

            // Increments the synth output.
            synth.outputLeft += operators[0].value + operators[1].value + operators[3].value;
            synth.outputRight += operators[0].value + operators[1].value + operators[3].value;
        }
}

__attribute__((always_inline)) inline void algorithm26Code(uint8_t noteIndexLow, uint8_t noteIndexHigh)
{
    for (uint8_t i = noteIndexLow; i < noteIndexHigh; ++i)
        if (notes[i].on == true)
        {
            // OP 0.
            operators[0].value = (((operators[0].source[(notes[i].stepAccumulator[0] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[0].value) >> ADSR_SHIFT) * notes[i].scaledLevel[0]) >> LEVEL_SHIFT;
            // OP 2 and feedback.
            operators[2].value = (((operators[2].source[((notes[i].stepAccumulator[2] >> STEP_SHIFT) + notes[i].feedback) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[2].value) >> ADSR_SHIFT) * notes[i].scaledLevel[2]) >> LEVEL_SHIFT;
            notes[i].feedback = (operators[2].value * operators[2].feedback) >> FEEDBACK_SHIFT;
            // OP 1.
            operators[1].value = (((operators[1].source[((notes[i].stepAccumulator[1] >> STEP_SHIFT) + operators[2].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[1].value) >> ADSR_SHIFT) * notes[i].scaledLevel[1]) >> LEVEL_SHIFT;
            // OP 4.
            operators[4].value = (((operators[4].source[(notes[i].stepAccumulator[4] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[4].value) >> ADSR_SHIFT) * notes[i].scaledLevel[4]) >> LEVEL_SHIFT;
            // OP 5.
            operators[5].value = (((operators[5].source[(notes[i].stepAccumulator[5] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[5].value) >> ADSR_SHIFT) * notes[i].scaledLevel[5]) >> LEVEL_SHIFT;
            // OP 3.
            operators[3].value = (((operators[3].source[((notes[i].stepAccumulator[3] >> STEP_SHIFT) + operators[4].value + operators[5].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[3].value) >> ADSR_SHIFT) * notes[i].scaledLevel[3]) >> LEVEL_SHIFT;

            // Increments note steps
            notes[i].stepAccumulator[0] += notes[i].scaledStep[0];
            notes[i].stepAccumulator[1] += notes[i].scaledStep[1];
            notes[i].stepAccumulator[2] += notes[i].scaledStep[2];
            notes[i].stepAccumulator[3] += notes[i].scaledStep[3];
            notes[i].stepAccumulator[4] += notes[i].scaledStep[4];
            notes[i].stepAccumulator[5] += notes[i].scaledStep[5];

            // Increments the synth output.
            synth.outputLeft += operators[0].value + operators[1].value + operators[3].value;
            synth.outputRight += operators[0].value + operators[1].value + operators[3].value;
        }
}

__attribute__((always_inline)) inline void algorithm27Code(uint8_t noteIndexLow, uint8_t noteIndexHigh)
{
    for (uint8_t i = noteIndexLow; i < noteIndexHigh; ++i)
        if (notes[i].on == true)
        {
            // OP 1.
            operators[1].value = (((operators[1].source[(notes[i].stepAccumulator[1] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[1].value) >> ADSR_SHIFT) * notes[i].scaledLevel[1]) >> LEVEL_SHIFT;
            // OP 0.
            operators[0].value = (((operators[0].source[((notes[i].stepAccumulator[0] >> STEP_SHIFT) + operators[1].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[0].value) >> ADSR_SHIFT) * notes[i].scaledLevel[0]) >> LEVEL_SHIFT;
            // OP 4 and feedback.
            operators[4].value = (((operators[4].source[((notes[i].stepAccumulator[4] >> STEP_SHIFT) + notes[i].feedback) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[4].value) >> ADSR_SHIFT) * notes[i].scaledLevel[4]) >> LEVEL_SHIFT;
            notes[i].feedback = (operators[4].value * operators[4].feedback) >> FEEDBACK_SHIFT;
            // OP 3.
            operators[3].value = (((operators[3].source[((notes[i].stepAccumulator[3] >> STEP_SHIFT) + operators[4].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[3].value) >> ADSR_SHIFT) * notes[i].scaledLevel[3]) >> LEVEL_SHIFT;
            // OP 2.
            operators[2].value = (((operators[2].source[((notes[i].stepAccumulator[2] >> STEP_SHIFT) + operators[3].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[2].value) >> ADSR_SHIFT) * notes[i].scaledLevel[2]) >> LEVEL_SHIFT;
            // OP 5.
            operators[5].value = (((operators[5].source[(notes[i].stepAccumulator[5] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[5].value) >> ADSR_SHIFT) * notes[i].scaledLevel[5]) >> LEVEL_SHIFT;

            // Increments note steps
            notes[i].stepAccumulator[0] += notes[i].scaledStep[0];
            notes[i].stepAccumulator[1] += notes[i].scaledStep[1];
            notes[i].stepAccumulator[2] += notes[i].scaledStep[2];
            notes[i].stepAccumulator[3] += notes[i].scaledStep[3];
            notes[i].stepAccumulator[4] += notes[i].scaledStep[4];
            notes[i].stepAccumulator[5] += notes[i].scaledStep[5];

            // Increments the synth output.
            synth.outputLeft += operators[0].value + operators[2].value + operators[5].value;
            synth.outputRight += operators[0].value + operators[2].value + operators[5].value;
        }
}

__attribute__((always_inline)) inline void algorithm28Code(uint8_t noteIndexLow, uint8_t noteIndexHigh)
{
    for (uint8_t i = noteIndexLow; i < noteIndexHigh; ++i)
        if (notes[i].on == true)
        {
            operators[0].value = (((operators[0].source[(notes[i].stepAccumulator[0] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[0].value) >> ADSR_SHIFT) * notes[i].scaledLevel[0]) >> LEVEL_SHIFT;
            // OP 1.
            operators[1].value = (((operators[1].source[(notes[i].stepAccumulator[1] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[1].value) >> ADSR_SHIFT) * notes[i].scaledLevel[1]) >> LEVEL_SHIFT;
            // OP 3.
            operators[3].value = (((operators[3].source[(notes[i].stepAccumulator[3] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[3].value) >> ADSR_SHIFT) * notes[i].scaledLevel[3]) >> LEVEL_SHIFT;
            // OP 2.
            operators[2].value = (((operators[2].source[((notes[i].stepAccumulator[2] >> STEP_SHIFT) + operators[3].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[2].value) >> ADSR_SHIFT) * notes[i].scaledLevel[2]) >> LEVEL_SHIFT;
            // OP 5 and feedback.
            operators[5].value = (((operators[5].source[((notes[i].stepAccumulator[5] >> STEP_SHIFT) + notes[i].feedback) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[5].value) >> ADSR_SHIFT) * notes[i].scaledLevel[5]) >> LEVEL_SHIFT;
            notes[i].feedback = (operators[5].value * operators[5].feedback) >> FEEDBACK_SHIFT;
            // OP 4.
            operators[4].value = (((operators[1].source[((notes[i].stepAccumulator[4] >> STEP_SHIFT) + operators[5].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[4].value) >> ADSR_SHIFT) * notes[i].scaledLevel[4]) >> LEVEL_SHIFT;

            // Increments note steps
            notes[i].stepAccumulator[0] += notes[i].scaledStep[0];
            notes[i].stepAccumulator[1] += notes[i].scaledStep[1];
            notes[i].stepAccumulator[2] += notes[i].scaledStep[2];
            notes[i].stepAccumulator[3] += notes[i].scaledStep[3];
            notes[i].stepAccumulator[4] += notes[i].scaledStep[4];
            notes[i].stepAccumulator[5] += notes[i].scaledStep[5];

            // Increments the synth output.
            synth.outputLeft += operators[0].value + operators[1].value + operators[2].value + operators[4].value;
            synth.outputRight += operators[0].value + operators[1].value + operators[2].value + operators[4].value;
        }
}

__attribute__((always_inline)) inline void algorithm29Code(uint8_t noteIndexLow, uint8_t noteIndexHigh)
{
    for (uint8_t i = noteIndexLow; i < noteIndexHigh; ++i)
        if (notes[i].on == true)
        {
            // OP 0.
            operators[0].value = (((operators[0].source[(notes[i].stepAccumulator[0] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[0].value) >> ADSR_SHIFT) * notes[i].scaledLevel[0]) >> LEVEL_SHIFT;
            // OP 1.
            operators[1].value = (((operators[1].source[(notes[i].stepAccumulator[1] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[1].value) >> ADSR_SHIFT) * notes[i].scaledLevel[1]) >> LEVEL_SHIFT;
            // OP 4 and feedback.
            operators[4].value = (((operators[4].source[((notes[i].stepAccumulator[4] >> STEP_SHIFT) + notes[i].feedback) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[4].value) >> ADSR_SHIFT) * notes[i].scaledLevel[4]) >> LEVEL_SHIFT;
            notes[i].feedback = (operators[4].value * operators[4].feedback) >> FEEDBACK_SHIFT;
            // OP 3.
            operators[3].value = (((operators[3].source[((notes[i].stepAccumulator[3] >> STEP_SHIFT) + operators[4].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[3].value) >> ADSR_SHIFT) * notes[i].scaledLevel[3]) >> LEVEL_SHIFT;
            // OP 2.
            operators[2].value = (((operators[2].source[((notes[i].stepAccumulator[2] >> STEP_SHIFT) + operators[3].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[2].value) >> ADSR_SHIFT) * notes[i].scaledLevel[2]) >> LEVEL_SHIFT;
            // OP 5.
            operators[5].value = (((operators[5].source[(notes[i].stepAccumulator[5] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[5].value) >> ADSR_SHIFT) * notes[i].scaledLevel[5]) >> LEVEL_SHIFT;

            // Increments note steps
            notes[i].stepAccumulator[0] += notes[i].scaledStep[0];
            notes[i].stepAccumulator[1] += notes[i].scaledStep[1];
            notes[i].stepAccumulator[2] += notes[i].scaledStep[2];
            notes[i].stepAccumulator[3] += notes[i].scaledStep[3];
            notes[i].stepAccumulator[4] += notes[i].scaledStep[4];
            notes[i].stepAccumulator[5] += notes[i].scaledStep[5];

            // Increments the synth output.
            synth.outputLeft += operators[0].value + operators[1].value + operators[2].value + operators[5].value;
            synth.outputRight += operators[0].value + operators[1].value + operators[2].value + operators[5].value;
        }
}

__attribute__((always_inline)) inline void algorithm30Code(uint8_t noteIndexLow, uint8_t noteIndexHigh)
{
    for (uint8_t i = noteIndexLow; i < noteIndexHigh; ++i)
        if (notes[i].on == true)
        {
            // OP 0.
            operators[0].value = (((operators[0].source[(notes[i].stepAccumulator[0] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[0].value) >> ADSR_SHIFT) * notes[i].scaledLevel[0]) >> LEVEL_SHIFT;
            // OP 1.
            operators[1].value = (((operators[1].source[(notes[i].stepAccumulator[1] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[1].value) >> ADSR_SHIFT) * notes[i].scaledLevel[1]) >> LEVEL_SHIFT;
            // OP 2.
            operators[2].value = (((operators[2].source[(notes[i].stepAccumulator[2] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[2].value) >> ADSR_SHIFT) * notes[i].scaledLevel[2]) >> LEVEL_SHIFT;
            // OP 3.
            operators[3].value = (((operators[3].source[(notes[i].stepAccumulator[3] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[3].value) >> ADSR_SHIFT) * notes[i].scaledLevel[3]) >> LEVEL_SHIFT;
            // OP 5 and feedback.
            operators[5].value = (((operators[5].source[((notes[i].stepAccumulator[5] >> STEP_SHIFT) + notes[i].feedback) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[5].value) >> ADSR_SHIFT) * notes[i].scaledLevel[5]) >> LEVEL_SHIFT;
            notes[i].feedback = (operators[5].value * operators[5].feedback) >> FEEDBACK_SHIFT;
            // OP 4.
            operators[4].value = (((operators[4].source[((notes[i].stepAccumulator[4] >> STEP_SHIFT) + operators[5].value) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[4].value) >> ADSR_SHIFT) * notes[i].scaledLevel[4]) >> LEVEL_SHIFT;

            // Increments note steps
            notes[i].stepAccumulator[0] += notes[i].scaledStep[0];
            notes[i].stepAccumulator[1] += notes[i].scaledStep[1];
            notes[i].stepAccumulator[2] += notes[i].scaledStep[2];
            notes[i].stepAccumulator[3] += notes[i].scaledStep[3];
            notes[i].stepAccumulator[4] += notes[i].scaledStep[4];
            notes[i].stepAccumulator[5] += notes[i].scaledStep[5];

            // Increments the synth output.
            synth.outputLeft += operators[0].value + operators[1].value + operators[2].value + operators[3].value + operators[4].value;
            synth.outputRight += operators[0].value + operators[1].value + operators[2].value + operators[3].value + operators[4].value;
        }
}

__attribute__((always_inline)) inline void algorithm31Code(uint8_t noteIndexLow, uint8_t noteIndexHigh)
{
    for (uint8_t i = noteIndexLow; i < noteIndexHigh; ++i)
        if (notes[i].on == true)
        {
            // OP 0.
            operators[0].value = (((operators[0].source[(notes[i].stepAccumulator[0] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[0].value) >> ADSR_SHIFT) * notes[i].scaledLevel[0]) >> LEVEL_SHIFT;
            // OP 1.
            operators[1].value = (((operators[1].source[(notes[i].stepAccumulator[1] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[1].value) >> ADSR_SHIFT) * notes[i].scaledLevel[1]) >> LEVEL_SHIFT;
            // OP 2.
            operators[2].value = (((operators[2].source[(notes[i].stepAccumulator[2] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[2].value) >> ADSR_SHIFT) * notes[i].scaledLevel[2]) >> LEVEL_SHIFT;
            // OP 3.
            operators[3].value = (((operators[3].source[(notes[i].stepAccumulator[3] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[3].value) >> ADSR_SHIFT) * notes[i].scaledLevel[3]) >> LEVEL_SHIFT;
            // OP 4.
            operators[4].value = (((operators[4].source[(notes[i].stepAccumulator[4] >> STEP_SHIFT) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[4].value) >> ADSR_SHIFT) * notes[i].scaledLevel[4]) >> LEVEL_SHIFT;
            // OP 5 and feedback.
            operators[5].value = (((operators[5].source[((notes[i].stepAccumulator[5] >> STEP_SHIFT) + notes[i].feedback) & (SINE_TABLE_SIZE - 1)] * notes[i].adsrStatus[5].value) >> ADSR_SHIFT) * notes[i].scaledLevel[5]) >> LEVEL_SHIFT;
            notes[i].feedback = (operators[5].value * operators[5].feedback) >> FEEDBACK_SHIFT;

            // Increments note steps
            notes[i].stepAccumulator[0] += notes[i].scaledStep[0];
            notes[i].stepAccumulator[1] += notes[i].scaledStep[1];
            notes[i].stepAccumulator[2] += notes[i].scaledStep[2];
            notes[i].stepAccumulator[3] += notes[i].scaledStep[3];
            notes[i].stepAccumulator[4] += notes[i].scaledStep[4];
            notes[i].stepAccumulator[5] += notes[i].scaledStep[5];

            // Increments the synth output.
            synth.outputLeft += operators[0].value + operators[1].value + operators[2].value + operators[3].value + operators[4].value + operators[5].value;
            synth.outputRight += operators[0].value + operators[1].value + operators[2].value + operators[3].value + operators[4].value + operators[5].value;
        }
}



__attribute__((always_inline)) inline void dacOutput()
{
  #ifdef ESP8266
    // Applies the overall volume.
    synth.outputLeft = ((synth.outputLeft * synth.volume) >> VOLUME_SHIFT);
    synth.outputRight = ((synth.outputRight * synth.volume) >> VOLUME_SHIFT);

    // Applies the shift and turns the output value to positive.
    synth.outputLeft >>= DAC_SHIFT;
    //synth.outputLeft += DAC_SUM;
    synth.outputRight >>= DAC_SHIFT;
    //synth.outputRight += DAC_SUM;


    /*
    // Clipping.
    if (synth.outputLeft < 0)
        synth.outputLeft = 0;
    else if (synth.outputLeft > 4095)
        synth.outputLeft = 4095;

    if (synth.outputRight < 0)
        synth.outputRight = 0;
    else if (synth.outputRight > 4095)
        synth.outputRight = 4095;
    */

    // Sends output data to the Due's DAC.

    i2s_write_sample(((synth.outputLeft << 16)&0xffff0000)|((synth.outputRight) & 0xffff));
    //i2s_write_sample(0x80008000); 
    currentLBuffer[bufPtr] = synth.outputLeft;
    currentRBuffer[bufPtr++] = synth.outputRight;
    if (bufPtr > AUDIO_BLOCK_SAMPLES  -1) {
      queue1.playBuffer();
      queue2.playBuffer();
      bufPtr = 0;
      currentLBuffer = queue1.getBuffer();
      currentRBuffer = queue2.getBuffer();
    }

    synth.outputLeft = 0;
    synth.outputRight = 0;
  #endif
}
