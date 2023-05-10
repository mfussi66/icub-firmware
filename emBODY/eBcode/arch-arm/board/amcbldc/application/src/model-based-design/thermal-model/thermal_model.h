//
// Non-Degree Granting Education License -- for use at non-degree
// granting, nonprofit, education, and research organizations only. Not
// for commercial or industrial use.
//
// File: thermal_model.h
//
// Code generated for Simulink model 'thermal_model'.
//
// Model version                  : 5.21
// Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
// C/C++ source code generated on : Tue May  9 10:45:31 2023
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

// Block states (default storage) for model 'thermal_model'
#ifndef thermal_model_MDLREF_HIDE_CHILD_

struct DW_thermal_model_f_T {
  real32_T DigitalFilter_states;       // '<Root>/DigitalFilter'
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

extern void thermal_model(const ControlOutputs *rtu_ControlOutputs, const
  ConfigurationParameters *rtu_ConfigurationParameters, MotorTemperature
  *rty_MotorTemperature);

// Model reference registration function
extern void thermal_model_initialize(const char_T **rt_errorStatus);

#ifndef thermal_model_MDLREF_HIDE_CHILD_

extern MdlrefDW_thermal_model_T thermal_model_MdlrefDW;

#endif                                 //thermal_model_MDLREF_HIDE_CHILD_

#ifndef thermal_model_MDLREF_HIDE_CHILD_

// Block states (default storage)
extern DW_thermal_model_f_T thermal_model_DW;

#endif                                 //thermal_model_MDLREF_HIDE_CHILD_

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
