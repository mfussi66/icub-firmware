//
// Non-Degree Granting Education License -- for use at non-degree
// granting, nonprofit, education, and research organizations only. Not
// for commercial or industrial use.
//
// File: process_sensors.h
//
// Code generated for Simulink model 'process_sensors'.
//
// Model version                  : 2.28
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Thu Nov 27 12:11:49 2025
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex-M
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef process_sensors_h_
#define process_sensors_h_
#include "rtwtypes.h"
#include "process_sensors_types.h"
#include "zero_crossing_types.h"

// Block signals for system '<S3>/For Each Subsystem'
struct B_CoreSubsys_process_sensors_T {
  real32_T gt;                         // '<S6>/Sum'
  real32_T Square;                     // '<S6>/Square'
  real32_T mt;                         // '<S6>/Moving Average1'
};

// Block states (default storage) for system '<S3>/For Each Subsystem'
struct DW_CoreSubsys_process_sensors_T {
  dsp_simulink_MovingAverage_process_sensors_T obj;// '<S6>/Moving Average1'
  dsp_simulink_MovingAverage_process_sensors_T obj_j;// '<S6>/Moving Average'
  real32_T DelayOneStep1_DSTATE;       // '<S6>/Delay One Step1'
  boolean_T objisempty;                // '<S6>/Moving Average1'
  boolean_T objisempty_k;              // '<S6>/Moving Average'
};

// Block signals for model 'process_sensors'
struct B_process_sensors_c_T {
  real32_T In;                         // '<S9>/In'
  real32_T In_b;                       // '<S8>/In'
  real32_T ImpAsg_InsertedFor_Iabcbias_at_inport_0[3];// '<S5>/Adaptive Exponential Smoother' 
  B_CoreSubsys_process_sensors_T CoreSubsys[3];// '<S3>/For Each Subsystem'
};

// Block states (default storage) for model 'process_sensors'
struct DW_process_sensors_f_T {
  boolean_T UnitDelay1_DSTATE;         // '<S2>/Unit Delay1'
  DW_CoreSubsys_process_sensors_T CoreSubsys[3];// '<S3>/For Each Subsystem'
};

// Zero-crossing (trigger) state for model 'process_sensors'
struct ZCE_process_sensors_T {
  ZCSigState SampleandHold1_Trig_ZCE;  // '<S2>/Sample and Hold1'
  ZCSigState SampleandHold_Trig_ZCE;   // '<S2>/Sample and Hold'
};

struct MdlrefDW_process_sensors_T {
  B_process_sensors_c_T rtb;
  DW_process_sensors_f_T rtdw;
  ZCE_process_sensors_T rtzce;
};

// Model reference registration function
extern void process_sensors_initialize(ZCE_process_sensors_T *localZCE);
extern void process_sensors_Init(DW_process_sensors_f_T *localDW);
extern void process_sensors(const ActuatorConfiguration *rtu_ActuatorConfig,
  const Flags *rtu_Flags, const SensorsData *rtu_SensorData, SensorsData
  *rty_SensorDataDecoded, B_process_sensors_c_T *localB, DW_process_sensors_f_T *
  localDW, ZCE_process_sensors_T *localZCE);
extern void process_sensors_Term(DW_process_sensors_f_T *localDW);

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<S11>/Data Type Duplicate' : Unused code path elimination


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
//  '<Root>' : 'process_sensors'
//  '<S1>'   : 'process_sensors/Remove ADC bias'
//  '<S2>'   : 'process_sensors/Remove encoder offset'
//  '<S3>'   : 'process_sensors/Remove ADC bias/Enabled Subsystem'
//  '<S4>'   : 'process_sensors/Remove ADC bias/Enfoce Kirchoff'
//  '<S5>'   : 'process_sensors/Remove ADC bias/Enabled Subsystem/For Each Subsystem'
//  '<S6>'   : 'process_sensors/Remove ADC bias/Enabled Subsystem/For Each Subsystem/Adaptive Exponential Smoother'
//  '<S7>'   : 'process_sensors/Remove encoder offset/Mechanical to Electrical Position'
//  '<S8>'   : 'process_sensors/Remove encoder offset/Sample and Hold'
//  '<S9>'   : 'process_sensors/Remove encoder offset/Sample and Hold1'
//  '<S10>'  : 'process_sensors/Remove encoder offset/Mechanical to Electrical Position/MechToElec'
//  '<S11>'  : 'process_sensors/Remove encoder offset/Mechanical to Electrical Position/MechToElec/floating-point'
//  '<S12>'  : 'process_sensors/Remove encoder offset/Mechanical to Electrical Position/MechToElec/floating-point/Compensate Offset'
//  '<S13>'  : 'process_sensors/Remove encoder offset/Mechanical to Electrical Position/MechToElec/floating-point/Mech To Elec'
//  '<S14>'  : 'process_sensors/Remove encoder offset/Mechanical to Electrical Position/MechToElec/floating-point/Compensate Offset/If Action Subsystem'
//  '<S15>'  : 'process_sensors/Remove encoder offset/Mechanical to Electrical Position/MechToElec/floating-point/Compensate Offset/If Action Subsystem1'
//  '<S16>'  : 'process_sensors/Remove encoder offset/Mechanical to Electrical Position/MechToElec/floating-point/Mech To Elec/Variant Subsystem'
//  '<S17>'  : 'process_sensors/Remove encoder offset/Mechanical to Electrical Position/MechToElec/floating-point/Mech To Elec/Variant Subsystem/Input Port'

#endif                                 // process_sensors_h_

//
// File trailer for generated code.
//
// [EOF]
//
