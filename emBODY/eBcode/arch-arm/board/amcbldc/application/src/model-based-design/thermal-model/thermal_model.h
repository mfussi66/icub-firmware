//
// Non-Degree Granting Education License -- for use at non-degree
// granting, nonprofit, education, and research organizations only. Not
// for commercial or industrial use.
//
// File: thermal_model.h
//
// Code generated for Simulink model 'thermal_model'.
//
// Model version                  : 5.17
// Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
// C/C++ source code generated on : Fri May  5 17:34:51 2023
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex-M
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef RTW_HEADER_thermal_model_h_
#define RTW_HEADER_thermal_model_h_
#include "rtwtypes.h"
#include "thermal_model_types.h"

// Block signals for system '<Root>/Moving RMS'
#ifndef thermal_model_MDLREF_HIDE_CHILD_

struct B_MovingRMS_thermal_model_T {
  real32_T MovingRMS;                  // '<Root>/Moving RMS'
};

#endif                                 //thermal_model_MDLREF_HIDE_CHILD_

// Block states (default storage) for system '<Root>/Moving RMS'
#ifndef thermal_model_MDLREF_HIDE_CHILD_

struct DW_MovingRMS_thermal_model_T {
  dsp_simulink_MovingRMS_therma_T obj; // '<Root>/Moving RMS'
  boolean_T objisempty;                // '<Root>/Moving RMS'
};

#endif                                 //thermal_model_MDLREF_HIDE_CHILD_

// Block signals for model 'thermal_model'
#ifndef thermal_model_MDLREF_HIDE_CHILD_

struct B_thermal_model_c_T {
  B_MovingRMS_thermal_model_T MovingRMS1;// '<Root>/Moving RMS'
  B_MovingRMS_thermal_model_T MovingRMS;// '<Root>/Moving RMS'
};

#endif                                 //thermal_model_MDLREF_HIDE_CHILD_

// Block states (default storage) for model 'thermal_model'
#ifndef thermal_model_MDLREF_HIDE_CHILD_

struct DW_thermal_model_f_T {
  DW_MovingRMS_thermal_model_T MovingRMS1;// '<Root>/Moving RMS'
  DW_MovingRMS_thermal_model_T MovingRMS;// '<Root>/Moving RMS'
};

#endif                                 //thermal_model_MDLREF_HIDE_CHILD_

#ifndef thermal_model_MDLREF_HIDE_CHILD_

// Real-time Model Data Structure
struct tag_RTM_thermal_model_T {
  const char_T **errorStatus;
};

#endif                                 //thermal_model_MDLREF_HIDE_CHILD_

#ifndef thermal_model_MDLREF_HIDE_CHILD_

struct MdlrefDW_thermal_model_T {
  RT_MODEL_thermal_model_T rtm;
};

#endif                                 //thermal_model_MDLREF_HIDE_CHILD_

extern void thermal_model_Init(void);
extern void thermal_model(const ControlOutputs *rtu_ControlOutputs, const
  ConfigurationParameters *rtu_ConfigurationParameters, MotorTemperature
  *rty_MotorTemperature);
extern void thermal_model_Term(void);

// Model reference registration function
extern void thermal_model_initialize(const char_T **rt_errorStatus);

#ifndef thermal_model_MDLREF_HIDE_CHILD_

extern void thermal_model_MovingRMS_Init(DW_MovingRMS_thermal_model_T *localDW);
extern void thermal_model_MovingRMS(const real32_T *rtu_0,
  B_MovingRMS_thermal_model_T *localB, DW_MovingRMS_thermal_model_T *localDW);
extern void thermal_model_MovingRMS_Term(DW_MovingRMS_thermal_model_T *localDW);

#endif                                 //thermal_model_MDLREF_HIDE_CHILD_

#ifndef thermal_model_MDLREF_HIDE_CHILD_

extern MdlrefDW_thermal_model_T thermal_model_MdlrefDW;

#endif                                 //thermal_model_MDLREF_HIDE_CHILD_

#ifndef thermal_model_MDLREF_HIDE_CHILD_

// Block signals (default storage)
extern B_thermal_model_c_T thermal_model_B;

#endif                                 //thermal_model_MDLREF_HIDE_CHILD_

#ifndef thermal_model_MDLREF_HIDE_CHILD_

// Block states (default storage)
extern DW_thermal_model_f_T thermal_model_DW;

#endif                                 //thermal_model_MDLREF_HIDE_CHILD_

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<S1>/Cast To Single1' : Unused code path elimination
//  Block '<S1>/Cast To Single2' : Unused code path elimination
//  Block '<S1>/Constant2' : Unused code path elimination
//  Block '<S1>/Constant3' : Unused code path elimination
//  Block '<S1>/Divide' : Unused code path elimination
//  Block '<S1>/Divide1' : Unused code path elimination
//  Block '<S1>/Gain2' : Unused code path elimination
//  Block '<S1>/Product' : Unused code path elimination
//  Block '<S1>/Product1' : Unused code path elimination
//  Block '<S1>/Sum' : Unused code path elimination
//  Block '<S1>/Sum1' : Unused code path elimination
//  Block '<Root>/DigitalFilter' : Unused code path elimination
//  Block '<Root>/Sum' : Unused code path elimination
//  Block '<Root>/Ts' : Unused code path elimination


//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Use the MATLAB hilite_system command to trace the generated code back
//  to the model.  For example,
//
//  hilite_system('<S3>')    - opens system 3
//  hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'thermal_model'
//  '<S1>'   : 'thermal_model/Compute coefficients'

#endif                                 // RTW_HEADER_thermal_model_h_

//
// File trailer for generated code.
//
// [EOF]
//
