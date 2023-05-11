//
// Non-Degree Granting Education License -- for use at non-degree
// granting, nonprofit, education, and research organizations only. Not
// for commercial or industrial use.
//
// File: thermal_model.cpp
//
// Code generated for Simulink model 'thermal_model'.
//
// Model version                  : 5.23
// Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
// C/C++ source code generated on : Thu May 11 10:44:06 2023
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex-M
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "thermal_model.h"
#include "thermal_model_types.h"
#include "thermal_model_private.h"

MdlrefDW_thermal_model_T thermal_model_MdlrefDW;

// Output and update for referenced model: 'thermal_model'
void thermal_model(const ControlOutputs *rtu_ControlOutputs, MotorTemperature
                   *rty_MotorTemperature)
{
  // BusCreator: '<Root>/Bus Creator1'
  rty_MotorTemperature->temperature = rtu_ControlOutputs->Power;
}

// Model initialize function
void thermal_model_initialize(const char_T **rt_errorStatus)
{
  RT_MODEL_thermal_model_T *const thermal_model_M = &(thermal_model_MdlrefDW.rtm);

  // Registration code

  // initialize error status
  rtmSetErrorStatusPointer(thermal_model_M, rt_errorStatus);
}

//
// File trailer for generated code.
//
// [EOF]
//
