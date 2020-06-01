#include <stdint.h>

// Maximum number of notes that can be played. Last note priority.
#define MAX_POLYPHONY 16
// Diference to account for when comparing an old parameter value with a new one obtained by the knobs (to see if the value should be updated).

// Bits to shift when applying the pitch bend (fixed point arithmetic).
#define PITCH_BEND_SHIFT 13
// Fixed point value for one unit in the pitch bend increments.
#define PITCH_BEND_UNIT 8192
// Bits to shift when applying the operators ratio (fixed point arithmetic).
#define RATIO_SHIFT 6
// Bits to shift when applying the operators level (fixed point arithmetic).
#define LEVEL_SHIFT 11
// Bits to shift when applying the operators feedback (fixed point arithmetic).
#define FEEDBACK_SHIFT 11
// Bits to shift when applying the operators ADSR envelope (fixed point arithmetic).
#define ADSR_SHIFT 12
// Bits to shift in the ADSR envelope increments (after applying the parameters).
#define ADSR_INC_SHIFT 19
// Bits to shift when applying the overall volume (fixed point arithmetic).
#define VOLUME_SHIFT 12
// Bits to shift in the table steps (after applying the parameters).
#define STEP_SHIFT 11
// Bits to shift in the Due's DAC output.
#define DAC_SHIFT 0
// Value to sum to the DAC output to make it positive.
#define DAC_SUM 1024

// Channel to listen to MIDI messages.
#define MIDI_IN_CHANNEL 1
// Number of preset voices.
#define PRESET_VOICES 1
// Number of keys and their lowest and highest values. Sine table look-up steps were calculated for these notes only. See "doc/Sine Wave Table Steps.ods" for more info.
#define USER_WAVTABLE_1 4
#define USER_WAVTABLE_2 5

#define NUM_KEYS 88
#define LOWEST_KEY 21
#define HIGHEST_KEY 108
// Number of keys and their lowest and highest values for the scaling functions.
#define NUM_SCALING_KEYS 100
#define SCALING_LOWEST_KEY 21
#define SCALING_HIGHEST_KEY 120
// Sample rate. Sine table look-up steps were calculated for this value. See "doc/Sine Wave Table Steps.ods" for more info.
#define SAMPLE_RATE 48000
// Envelope function call frequency. Approximated value for the Yamaha DX7 envelope. See page 26 of "doc\dx7-man.pdf" for more info.
#define ENVELOPE_UPDATE_FREQUENCY 128
// Size of the sine table.
#define SINE_TABLE_SIZE 1024
// Number of operators.
#define NUM_OPERATORS 6
// Number of algorithms.
#define NUM_ALGORITHMS 32
// MIDI number for the sustain pedal.
#define SUSTAIN_PEDAL 64
#define VOLUME_CC_MSB 7
#define VOLUME_CC_LSB 39
#define SOUND_CC_1_LSB 70
#define CC_LSB_MSB_OFFSET 32
#define GP1_CC_MSB 16
#define GP1_CC_LSB 48
#define GP2_CC_MSB 17
#define GP2_CC_LSB 49
#define GP3_CC_MSB 18
#define GP3_CC_LSB 50
#define GP4_CC_MSB 19
#define GP4_CC_LSB 51
#define BANKSEL_CC_LSB 32
#define BANKSEL_CC_MSB 0
#define U1_CC_MSB 20
#define U1_CC_LSB 52
#define U2_CC_MSB 21
#define U2_CC_LSB 53
#define U3_CC_MSB 22
#define U3_CC_LSB 54
#define U4_CC_MSB 23
#define U4_CC_LSB 55
#define U5_CC_MSB 24
#define U5_CC_LSB 56
#define U6_CC_MSB 25
#define U6_CC_LSB 57
#define U7_CC_MSB 26
#define U7_CC_LSB 58
#define U8_CC_MSB 27
#define U8_CC_LSB 59
#define U12_CC_MSB 31
#define U12_CC_LSB 63
#define GP5_CC_MSB 80
#define MAX_MIDI_VALUE_14 ((1<<14) -1)
#define MAX_MIDI_VALUE_7 127

// Pins for the buttons to change the operators parameters.
#define OP0_PARAMETERS_BUTTON 0
#define OP1_PARAMETERS_BUTTON 1
#define OP2_PARAMETERS_BUTTON 2
#define OP3_PARAMETERS_BUTTON 3
#define OP4_PARAMETERS_BUTTON 4
#define OP5_PARAMETERS_BUTTON 5
#define MIN_PARAM_BUTTON 0
#define MAX_PARAM_BUTTON 5
#define MIN_STATEFUL_BUTTON 6
#define MAX_STATEFUL_BUTTON 10

// Pin for the button to change the algorithms.
#define ALGORITHM_BUTTON 8 
// Pin for the button to change the operators left side level scaling function.
#define LEVEL_SCALING_LEFT_BUTTON 6
// Pin for the button to change the operators right side level scaling function.
#define LEVEL_SCALING_RIGHT_BUTTON 7
// Pin for the button to control the operators ADSR envelopes.
#define ADSR_BUTTON 9
// Pin for the button to play the preset voices.
#define PRESET_BUTTON 20 //Not used

#define MENU_BUTTON 10

// Pins for the knobs.
#define MAX_KNOBS 14
#define MAX_BUTTONS 14
#define KNOB0 0
#define KNOB1 1
#define KNOB2 2
#define KNOB3 3
#define KNOB4 4
#define KNOB5 5
#define KNOB6 6
#define KNOB7 7
#define KNOB8 8
#define KNOB9 9
#define KNOB10 10
#define KNOB11 11
#define KNOB12 12
#define KNOB13 13

#define VOLUME_KNOB KNOB11
#define ALG_KNOB KNOB8
#define PRESET_KNOB KNOB9
#define MENU_KNOB KNOB10
#define LONG_PRESS_TIME 500
#define REALLY_LONG_PRESS_TIME 2000

// Number of bits of Due's analog input.
#define ANALOG_RESOLUTION 12
// Maximum value of Due's analog IO.
#define MAX_ANALOG_VALUE 4095
#define MAX_DIGITAL_VALUE 4095

// Maximum level of the parameters.
#define MAX_PARAMETERS_LEVEL 7

#define REVMAP(a) map(a, 0, MAX_ANALOG_VALUE, MAX_ANALOG_VALUE, 0)

#define KNOBMAP(a) map(a, 0, MAX_DIGITAL_VALUE, 0, MAX_ANALOG_VALUE)
#define REVKNOBMAP(a) map(a, 0, MAX_DIGITAL_VALUE, MAX_ANALOG_VALUE, 0)
#define PARAMMAP(a) map(a, 0, MAX_ANALOG_VALUE, 0, MAX_DIGITAL_VALUE)
#define REVPARAMMAP(a) map(a, 0, MAX_ANALOG_VALUE, MAX_DIGITAL_VALUE, 0)
#define MIDIMAP(a) map(a, 0, MAX_MIDI_VALUE_14, 0, MAX_ANALOG_VALUE)
#define REVMIDIMAP(a) map(a, 0, MAX_MIDI_VALUE_14, MAX_ANALOG_VALUE, 0)

#define NUM_VOICE_PARAMS 22

// Preset voices parameters for the operators.
extern const int16_t default_presetVoice[PRESET_VOICES][NUM_OPERATORS][NUM_VOICE_PARAMS];
// Preset voices algorithms.
extern const uint8_t default_presetAlgorithm[PRESET_VOICES];

extern const char * default_patchNames[PRESET_VOICES];

#define NUM_BANKS 2
#define USER_BANK 1

// 10 bit sine wave table.
extern const int16_t sineTable[SINE_TABLE_SIZE];
extern const int16_t sawTable [SINE_TABLE_SIZE];
extern const int16_t triTable [SINE_TABLE_SIZE]; 
extern const int16_t sqrTable [SINE_TABLE_SIZE];
extern const char * sourcesDisp [];

extern const int16_t * sources [];

#define MAX_SOURCES 6

  // Sample steps for each note. Used to access the sine table.

extern const uint32_t sineTableStep[NUM_KEYS];

// Velocity curves.
extern const uint8_t velocityCurve[MAX_PARAMETERS_LEVEL + 1][128];
// Rate scaling for each level/key.
extern const uint16_t rateScaling[MAX_PARAMETERS_LEVEL + 1][NUM_SCALING_KEYS];

// Values for each key to calculate the keyboard level scaling values (for linear and exponetial functions).
extern const uint16_t levelScalingFunction[2][NUM_SCALING_KEYS];

extern const uint8_t feedBackOsc [NUM_ALGORITHMS];

// Enum to define what the synthesizer's knobs will control.
enum knobsControl
{
    STANDBY,
    ADSR,
    PARAMETERS,
    MENU,
    SAVE,
    MENU_EDIT
};

extern const char * knobsControlDisp[];

// Enum to define the operators keyboard level scaling function.
enum levelScalingFunction_e
{
    NONE,
    LINEAR,
    EXPONENTIAL
};

extern const char * levelScalingFunctionDisp [];

// Enum to define the ADSR envelope parameters.
enum adsrParameters_e
{
    ATTACK,
    DECAY,
    SUSTAIN,
    RRELEASE
};

extern const char * adsrParamDisp [];


// Typedef to know the key to note index relation.
typedef struct
{
    bool on;
    uint8_t index;
} keyToNote_t;

// Typedef to control the pitch bend.
typedef struct
{
    bool bentDown;
    uint16_t value;
} pitchBend_t;

// Typedef with the synthesizer's IO and control info.
typedef struct
{
    bool playMode;
    knobsControl control;
    bool sustainPedalOn;
    pitchBend_t pitchBend;
    uint8_t channel;
    uint8_t selectedOperator;
    uint8_t algorithm;
    uint8_t presetVoice;
    uint8_t bank;
    uint8_t prevVoice;
    uint8_t prevBank;
    bool modified;
    uint16_t volume;
    keyToNote_t keyMapping[NUM_KEYS];
    int32_t outputLeft;
    int32_t outputRight;
    int32_t outputBufferLeft;
    int32_t outputBufferRight;
} synth_t;

// Typedef to control the keyboard level scaling.
typedef struct
{
    uint8_t breakPointKey;
    uint16_t depth[2];
    int8_t sign[2];
    levelScalingFunction_e function[2];
} levelScaling_t;

// Typedef for the ADSR envelopes.
typedef struct
{
    uint16_t rate[4];
    uint16_t level[4];
} envelope_t;

// Typedef for the operators.
typedef struct
{
    uint16_t ratio;
    uint16_t level;
    uint16_t feedback;
    uint8_t velocity;
    uint8_t rateScaling;
    levelScaling_t levelScaling;
    envelope_t adsr;
    int16_t value;
    uint8_t src_sel;
    const int16_t * source;
    uint32_t fixed_freq_step;
} operator_t;

// Typedef for a given note status on the ADSR envelope.
typedef struct
{
    bool releaseReady;
    uint16_t value;
    int32_t increment[4];
    uint32_t incrementAccumulator[4];
    int16_t timer[4];
    adsrParameters_e parameter;
} envelopeStatus_t;

// Typedef for the note to be played.
typedef struct
{
    bool on;
    bool sustained;
    bool released;
    uint8_t keyIndex;
    uint8_t velocity[NUM_OPERATORS];
    uint16_t scaledLevel[NUM_OPERATORS];
    uint32_t scaledStep[NUM_OPERATORS];
    uint32_t stepAccumulator[NUM_OPERATORS];
    int16_t feedback;
    envelopeStatus_t adsrStatus[NUM_OPERATORS];
} note_t;
