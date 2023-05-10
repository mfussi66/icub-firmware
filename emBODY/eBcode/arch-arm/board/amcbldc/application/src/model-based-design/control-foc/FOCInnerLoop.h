//
// Non-Degree Granting Education License -- for use at non-degree
// granting, nonprofit, education, and research organizations only. Not
// for commercial or industrial use.
//
// File: FOCInnerLoop.h
//
// Code generated for Simulink model 'control_foc'.
//
// Model version                  : 5.12
// Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
// C/C++ source code generated on : Tue May  9 10:44:57 2023
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex-M
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef RTW_HEADER_FOCInnerLoop_h_
#define RTW_HEADER_FOCInnerLoop_h_
#include "rtwtypes.h"
#include "control_foc_types.h"

// Block signals for system '<S3>/Moving RMS'
#ifndef control_foc_MDLREF_HIDE_CHILD_

struct B_MovingRMS_control_foc_T {
  real32_T MovingRMS;                  // '<S3>/Moving RMS'
};

#endif                                 //control_foc_MDLREF_HIDE_CHILD_

// Block states (default storage) for system '<S3>/Moving RMS'
#ifndef control_foc_MDLREF_HIDE_CHILD_

struct DW_MovingRMS_control_foc_T {
  dsp_simulink_MovingRMS_contro_T obj; // '<S3>/Moving RMS'
  boolean_T objisempty;                // '<S3>/Moving RMS'
};

#endif                                 //control_foc_MDLREF_HIDE_CHILD_

#ifndef control_foc_MDLREF_HIDE_CHILD_

extern void control_foc_MovingRMS_Init(DW_MovingRMS_control_foc_T *localDW);
extern void control_foc_MovingRMS(real32_T rtu_0, B_MovingRMS_control_foc_T
  *localB, DW_MovingRMS_control_foc_T *localDW);
extern void FOCInnerLoop_Init(void);
extern void FOCInnerLoop_Update(const ControlOuterOutputs *rtu_OuterOutputs);
extern void FOCInnerLoop(const ConfigurationParameters
  *rtu_ConfigurationParameters, const SensorsData *rtu_Sensors, const
  EstimatedData *rtu_Estimates, const Targets *rtu_Targets, const
  ControlOuterOutputs *rtu_OuterOutputs, ControlOutputs *rty_FOCOutputs);
extern void control_foc_MovingRMS_Term(DW_MovingRMS_control_foc_T *localDW);
extern void FOCInnerLoop_Term(void);

#endif                                 //control_foc_MDLREF_HIDE_CHILD_
#endif                                 // RTW_HEADER_FOCInnerLoop_h_

//
// File trailer for generated code.
//
// [EOF]
//
