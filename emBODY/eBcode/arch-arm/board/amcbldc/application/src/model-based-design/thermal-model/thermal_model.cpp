//
// Non-Degree Granting Education License -- for use at non-degree
// granting, nonprofit, education, and research organizations only. Not
// for commercial or industrial use.
//
// File: thermal_model.cpp
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
#include "thermal_model.h"
#include "thermal_model_types.h"
#include "rtwtypes.h"
#include "thermal_model_private.h"

MdlrefDW_thermal_model_T thermal_model_MdlrefDW;

// Block states (default storage)
DW_thermal_model_f_T thermal_model_DW;

// Output and update for referenced model: 'thermal_model'
void thermal_model(const ControlOutputs *rtu_ControlOutputs, const
                   ConfigurationParameters *rtu_ConfigurationParameters,
                   MotorTemperature *rty_MotorTemperature)
{
  real32_T rtb_Gain2;
  real32_T rtb_Sum_a;
  real32_T rtb_Sum_p_tmp;

  // Gain: '<S1>/Gain2'
  rtb_Gain2 = 2.0F *
    rtu_ConfigurationParameters->motorconfig.thermal_time_constant;

  // DiscreteFilter: '<Root>/DigitalFilter' incorporates:
  //   Constant: '<Root>/Ts'
  //   Constant: '<S1>/Constant2'
  //   Product: '<S1>/Divide'
  //   Product: '<S1>/Divide1'
  //   Product: '<S1>/Product'
  //   Product: '<S1>/Product1'
  //   Sum: '<S1>/Sum'
  //   Sum: '<S1>/Sum1'

  rtb_Sum_p_tmp = 0.01F *
    rtu_ConfigurationParameters->motorconfig.thermal_resistance / (rtb_Gain2 +
    0.01F) * rtu_ControlOutputs->Power;
  rtb_Sum_a = rtb_Sum_p_tmp + thermal_model_DW.DigitalFilter_states;
  thermal_model_DW.DigitalFilter_states = rtb_Sum_p_tmp - (0.01F - rtb_Gain2) /
    (rtb_Gain2 + 0.01F) * rtb_Sum_a;

  // BusCreator: '<Root>/Bus Creator1' incorporates:
  //   Sum: '<Root>/Sum'

  rty_MotorTemperature->temperature = rtb_Sum_a +
    rtu_ConfigurationParameters->environment_temperature;
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
