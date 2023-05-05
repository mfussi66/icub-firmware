//
// Non-Degree Granting Education License -- for use at non-degree
// granting, nonprofit, education, and research organizations only. Not
// for commercial or industrial use.
//
// File: thermal_model.cpp
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
#include "thermal_model.h"
#include "rtwtypes.h"
#include "thermal_model_types.h"
#include <cmath>
#include "mw_cmsis.h"
#include "thermal_model_private.h"

MdlrefDW_thermal_model_T thermal_model_MdlrefDW;

// Block signals (default storage)
B_thermal_model_c_T thermal_model_B;

// Block states (default storage)
DW_thermal_model_f_T thermal_model_DW;

// Forward declaration for local functions
static void thermal_model_SystemCore_setup(dsp_simulink_MovingRMS_therma_T *obj);
static void thermal_model_SystemCore_setup(dsp_simulink_MovingRMS_therma_T *obj)
{
  real32_T val;
  boolean_T flag;
  obj->isSetupComplete = false;
  obj->isInitialized = 1;
  obj->NumChannels = 1;
  obj->FrameLength = 1;
  if (obj->ForgettingFactor != 0.0F) {
    val = obj->ForgettingFactor;
  } else {
    val = 2.22044605E-16F;
  }

  obj->_pobj0.isInitialized = 0;
  obj->_pobj0.isInitialized = 0;
  flag = (obj->_pobj0.isInitialized == 1);
  if (flag) {
    obj->_pobj0.TunablePropsChanged = true;
  }

  obj->_pobj0.ForgettingFactor = val;
  obj->pStatistic = &obj->_pobj0;
  obj->isSetupComplete = true;
  obj->TunablePropsChanged = false;
}

// System initialize for atomic system:
void thermal_model_MovingRMS_Init(DW_MovingRMS_thermal_model_T *localDW)
{
  g_dsp_internal_ExponentialMov_T *obj;
  boolean_T flag;

  // Start for MATLABSystem: '<Root>/Moving RMS'
  localDW->obj.isInitialized = 0;
  localDW->obj.NumChannels = -1;
  localDW->obj.FrameLength = -1;
  localDW->obj.matlabCodegenIsDeleted = false;
  localDW->objisempty = true;
  flag = (localDW->obj.isInitialized == 1);
  if (flag) {
    localDW->obj.TunablePropsChanged = true;
  }

  localDW->obj.ForgettingFactor = 0.995F;
  thermal_model_SystemCore_setup(&localDW->obj);

  // End of Start for MATLABSystem: '<Root>/Moving RMS'

  // InitializeConditions for MATLABSystem: '<Root>/Moving RMS'
  obj = localDW->obj.pStatistic;
  if (obj->isInitialized == 1) {
    obj->pwN = 1.0F;
    obj->pmN = 0.0F;
  }

  // End of InitializeConditions for MATLABSystem: '<Root>/Moving RMS'
}

// Output and update for atomic system:
void thermal_model_MovingRMS(const real32_T *rtu_0, B_MovingRMS_thermal_model_T *
  localB, DW_MovingRMS_thermal_model_T *localDW)
{
  g_dsp_internal_ExponentialMov_T *obj;
  real32_T a;
  real32_T lambda;
  real32_T pmLocal;
  real32_T pwLocal;
  boolean_T flag;

  // MATLABSystem: '<Root>/Moving RMS'
  if (localDW->obj.ForgettingFactor != 0.995F) {
    flag = (localDW->obj.isInitialized == 1);
    if (flag) {
      localDW->obj.TunablePropsChanged = true;
    }

    localDW->obj.ForgettingFactor = 0.995F;
  }

  if (localDW->obj.TunablePropsChanged) {
    localDW->obj.TunablePropsChanged = false;
    obj = localDW->obj.pStatistic;
    flag = (obj->isInitialized == 1);
    if (flag) {
      obj->TunablePropsChanged = true;
    }

    localDW->obj.pStatistic->ForgettingFactor = localDW->obj.ForgettingFactor;
  }

  a = std::abs(*rtu_0);
  obj = localDW->obj.pStatistic;
  if (obj->isInitialized != 1) {
    obj->isSetupComplete = false;
    obj->isInitialized = 1;
    obj->pwN = 1.0F;
    obj->pmN = 0.0F;
    obj->plambda = obj->ForgettingFactor;
    obj->isSetupComplete = true;
    obj->TunablePropsChanged = false;
    obj->pwN = 1.0F;
    obj->pmN = 0.0F;
  }

  if (obj->TunablePropsChanged) {
    obj->TunablePropsChanged = false;
    obj->plambda = obj->ForgettingFactor;
  }

  pwLocal = obj->pwN;
  pmLocal = obj->pmN;
  lambda = obj->plambda;
  a = (1.0F - 1.0F / pwLocal) * pmLocal + 1.0F / pwLocal * (a * a);
  obj->pwN = lambda * pwLocal + 1.0F;
  obj->pmN = a;

  // MATLABSystem: '<Root>/Moving RMS'
  mw_arm_sqrt_f32(a, &localB->MovingRMS);
}

// Termination for atomic system:
void thermal_model_MovingRMS_Term(DW_MovingRMS_thermal_model_T *localDW)
{
  g_dsp_internal_ExponentialMov_T *obj;

  // Terminate for MATLABSystem: '<Root>/Moving RMS'
  if (!localDW->obj.matlabCodegenIsDeleted) {
    localDW->obj.matlabCodegenIsDeleted = true;
    if ((localDW->obj.isInitialized == 1) && localDW->obj.isSetupComplete) {
      obj = localDW->obj.pStatistic;
      if (obj->isInitialized == 1) {
        obj->isInitialized = 2;
      }

      localDW->obj.NumChannels = -1;
      localDW->obj.FrameLength = -1;
    }
  }

  // End of Terminate for MATLABSystem: '<Root>/Moving RMS'
}

// System initialize for referenced model: 'thermal_model'
void thermal_model_Init(void)
{
  thermal_model_MovingRMS_Init(&thermal_model_DW.MovingRMS);
  thermal_model_MovingRMS_Init(&thermal_model_DW.MovingRMS1);
}

// Output and update for referenced model: 'thermal_model'
void thermal_model(const ControlOutputs *rtu_ControlOutputs, const
                   ConfigurationParameters *rtu_ConfigurationParameters,
                   MotorTemperature *rty_MotorTemperature)
{
  real32_T rtb_Square[2];
  real32_T rtb_TmpSignalConversionAtSquare[2];
  thermal_model_MovingRMS(&rtu_ControlOutputs->Iq_fbk.current,
    &thermal_model_B.MovingRMS, &thermal_model_DW.MovingRMS);
  thermal_model_MovingRMS(&rtu_ControlOutputs->Id_fbk.current,
    &thermal_model_B.MovingRMS1, &thermal_model_DW.MovingRMS1);

  // SignalConversion generated from: '<Root>/Square'
  rtb_TmpSignalConversionAtSquare[0] = thermal_model_B.MovingRMS.MovingRMS;
  rtb_TmpSignalConversionAtSquare[1] = thermal_model_B.MovingRMS1.MovingRMS;

  // Math: '<Root>/Square'
  mw_arm_mult_f32(&rtb_TmpSignalConversionAtSquare[0],
                  &rtb_TmpSignalConversionAtSquare[0], &rtb_Square[0], 2U);

  // BusCreator: '<Root>/Bus Creator1' incorporates:
  //   Product: '<Root>/Product'
  //   Sum: '<Root>/Sum1'

  rty_MotorTemperature->temperature = (rtb_Square[0] + rtb_Square[1]) *
    rtu_ConfigurationParameters->motorconfig.resistance;
}

// Termination for referenced model: 'thermal_model'
void thermal_model_Term(void)
{
  thermal_model_MovingRMS_Term(&thermal_model_DW.MovingRMS);
  thermal_model_MovingRMS_Term(&thermal_model_DW.MovingRMS1);
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
