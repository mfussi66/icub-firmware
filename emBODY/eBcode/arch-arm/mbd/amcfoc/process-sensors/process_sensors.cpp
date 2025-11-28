//
// Non-Degree Granting Education License -- for use at non-degree
// granting, nonprofit, education, and research organizations only. Not
// for commercial or industrial use.
//
// File: process_sensors.cpp
//
// Code generated for Simulink model 'process_sensors'.
//
// Model version                  : 2.28
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Wed Nov 26 16:56:32 2025
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex-M
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "process_sensors.h"
#include "process_sensors_types.h"
#include "rtwtypes.h"
#include <cmath>
#include "rt_remf.h"
#include "zero_crossing_types.h"
#include "embot_core.h"
   static uint32_t cnt1 = 0;

// Forward declaration for local functions
static void process_sensors_SystemCore_setup
  (dsp_simulink_MovingAverage_process_sensors_T *obj);
static void process_sensors_SystemCore_setup
  (dsp_simulink_MovingAverage_process_sensors_T *obj)
{
  obj->isInitialized = 1;

  // Start for MATLABSystem: '<S6>/Moving Average' incorporates:
  //   MATLABSystem: '<S6>/Moving Average1'

  obj->NumChannels = 1;
  obj->FrameLength = 1;
  obj->pwN = 0.0F;
  obj->pmN = 0.0F;
  obj->plambda = obj->ForgettingFactor;
  obj->isSetupComplete = true;
  obj->TunablePropsChanged = false;
}

// System initialize for referenced model: 'process_sensors'
void process_sensors_Init(DW_process_sensors_f_T *localDW)
{
  int32_T ForEach_itr;

  // SystemInitialize for Enabled SubSystem: '<S1>/Enabled Subsystem'
  // SystemInitialize for Iterator SubSystem: '<S3>/For Each Subsystem'
  for (ForEach_itr = 0; ForEach_itr < 3; ForEach_itr++) {
    // Start for MATLABSystem: '<S6>/Moving Average1'
    localDW->CoreSubsys[ForEach_itr].obj.isInitialized = 0;
    localDW->CoreSubsys[ForEach_itr].obj.NumChannels = -1;
    localDW->CoreSubsys[ForEach_itr].obj.FrameLength = -1;
    localDW->CoreSubsys[ForEach_itr].obj.matlabCodegenIsDeleted = false;
    localDW->CoreSubsys[ForEach_itr].objisempty = true;
    localDW->CoreSubsys[ForEach_itr].obj.ForgettingFactor = 0.9F;
    process_sensors_SystemCore_setup(&localDW->CoreSubsys[ForEach_itr].obj);

    // InitializeConditions for MATLABSystem: '<S6>/Moving Average1'
    localDW->CoreSubsys[ForEach_itr].obj.pwN = 0.0F;
    localDW->CoreSubsys[ForEach_itr].obj.pmN = 0.0F;

    // Start for MATLABSystem: '<S6>/Moving Average'
    localDW->CoreSubsys[ForEach_itr].obj_j.isInitialized = 0;
    localDW->CoreSubsys[ForEach_itr].obj_j.NumChannels = -1;
    localDW->CoreSubsys[ForEach_itr].obj_j.FrameLength = -1;
    localDW->CoreSubsys[ForEach_itr].obj_j.matlabCodegenIsDeleted = false;
    localDW->CoreSubsys[ForEach_itr].objisempty_k = true;
    localDW->CoreSubsys[ForEach_itr].obj_j.ForgettingFactor = 0.99F;
    process_sensors_SystemCore_setup(&localDW->CoreSubsys[ForEach_itr].obj_j);

    // InitializeConditions for MATLABSystem: '<S6>/Moving Average'
    localDW->CoreSubsys[ForEach_itr].obj_j.pwN = 0.0F;
    localDW->CoreSubsys[ForEach_itr].obj_j.pmN = 0.0F;
  }

  // End of SystemInitialize for SubSystem: '<S3>/For Each Subsystem'
  // End of SystemInitialize for SubSystem: '<S1>/Enabled Subsystem'
}

// Output and update for referenced model: 'process_sensors'
void process_sensors(const ActuatorConfiguration *rtu_ActuatorConfig, const
                     Flags *rtu_Flags, const SensorsData *rtu_SensorData,
                     SensorsData *rty_SensorDataDecoded, B_process_sensors_c_T
                     *localB, DW_process_sensors_f_T *localDW,
                     ZCE_process_sensors_T *localZCE)
{
  int32_T ForEach_itr;
  real32_T rtb_Subtract[3];
  real32_T rtb_SumofElements;
  real32_T rtb_bt;

  // BusAssignment: '<S1>/Bus Assignment' incorporates:
  //   BusAssignment: '<S2>/Bus Assignment'

  *rty_SensorDataDecoded = *rtu_SensorData;

  // Outputs for Enabled SubSystem: '<S1>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S3>/Enable'

  if (rtu_Flags->enable_currents_bias_removal) {
    // Outputs for Iterator SubSystem: '<S3>/For Each Subsystem' incorporates:
    //   ForEach: '<S5>/For Each'
    for (ForEach_itr = 0; ForEach_itr < 3; ForEach_itr++) {
      // Sum: '<S6>/Sum' incorporates:
      //   Delay: '<S6>/Delay One Step1'
      //   ForEachSliceSelector generated from: '<S5>/Iabc'
			
      localB->CoreSubsys[ForEach_itr].gt = rtu_SensorData->
        motorsensors.Iabc[ForEach_itr] - localDW->CoreSubsys[ForEach_itr].
        DelayOneStep1_DSTATE;

      // MATLABSystem: '<S6>/Moving Average1'
      if (localDW->CoreSubsys[ForEach_itr].obj.ForgettingFactor != 0.9F) {
        if (localDW->CoreSubsys[ForEach_itr].obj.isInitialized == 1) {
          localDW->CoreSubsys[ForEach_itr].obj.TunablePropsChanged = true;
        }

        localDW->CoreSubsys[ForEach_itr].obj.ForgettingFactor = 0.9F;
      }

      if (localDW->CoreSubsys[ForEach_itr].obj.TunablePropsChanged) {
        localDW->CoreSubsys[ForEach_itr].obj.TunablePropsChanged = false;
        localDW->CoreSubsys[ForEach_itr].obj.plambda = 0.9F;
      }

      rtb_bt = localDW->CoreSubsys[ForEach_itr].obj.plambda *
        localDW->CoreSubsys[ForEach_itr].obj.pwN + 1.0F;

      // Start for MATLABSystem: '<S6>/Moving Average1'
      rtb_SumofElements = 1.0F / rtb_bt;

      // MATLABSystem: '<S6>/Moving Average1'
      rtb_SumofElements = (1.0F - rtb_SumofElements) * localDW->
        CoreSubsys[ForEach_itr].obj.pmN + rtb_SumofElements * localB->
        CoreSubsys[ForEach_itr].gt;
      localDW->CoreSubsys[ForEach_itr].obj.pwN = rtb_bt;
      localDW->CoreSubsys[ForEach_itr].obj.pmN = rtb_SumofElements;

      // MATLABSystem: '<S6>/Moving Average1'
      localB->CoreSubsys[ForEach_itr].mt = rtb_SumofElements;

      // Math: '<S6>/Square'
      localB->CoreSubsys[ForEach_itr].Square = localB->CoreSubsys[ForEach_itr].
        gt * localB->CoreSubsys[ForEach_itr].gt;

      // MATLABSystem: '<S6>/Moving Average'
      if (localDW->CoreSubsys[ForEach_itr].obj_j.ForgettingFactor != 0.99F) {
        if (localDW->CoreSubsys[ForEach_itr].obj_j.isInitialized == 1) {
          localDW->CoreSubsys[ForEach_itr].obj_j.TunablePropsChanged = true;
        }

        localDW->CoreSubsys[ForEach_itr].obj_j.ForgettingFactor = 0.9F;
      }

      if (localDW->CoreSubsys[ForEach_itr].obj_j.TunablePropsChanged) {
        localDW->CoreSubsys[ForEach_itr].obj_j.TunablePropsChanged = false;
        localDW->CoreSubsys[ForEach_itr].obj_j.plambda = 0.99F;
      }

      rtb_bt = localDW->CoreSubsys[ForEach_itr].obj_j.plambda *
        localDW->CoreSubsys[ForEach_itr].obj_j.pwN + 1.0F;

      // Start for MATLABSystem: '<S6>/Moving Average'
      rtb_SumofElements = 1.0F / rtb_bt;

      // MATLABSystem: '<S6>/Moving Average'
      rtb_SumofElements = (1.0F - rtb_SumofElements) * localDW->
        CoreSubsys[ForEach_itr].obj_j.pmN + rtb_SumofElements *
        localB->CoreSubsys[ForEach_itr].Square;
      localDW->CoreSubsys[ForEach_itr].obj_j.pwN = rtb_bt;
      localDW->CoreSubsys[ForEach_itr].obj_j.pmN = rtb_SumofElements;

      // Gain: '<S6>/Learning rate' incorporates:
      //   Bias: '<S6>/eps'
      //   MATLABSystem: '<S6>/Moving Average'
      //   Product: '<S6>/Reciprocal'
      //   Sqrt: '<S6>/Square Root'
      //
      rtb_bt = 1.0F / (std::sqrt(rtb_SumofElements) + 1.0E-6F) * 0.003F;

      // Saturate: '<S6>/Saturation'
      if (rtb_bt > 0.99999F) {
        rtb_bt = 0.99999F;
      } else if (rtb_bt < 1.0E-6F) {
        rtb_bt = 1.0E-6F;
      }

      // Sum: '<S6>/Sum1' incorporates:
      //   Delay: '<S6>/Delay One Step1'
      //   Product: '<S6>/Product'
      //   Saturate: '<S6>/Saturation'

      rtb_bt = rtb_bt * localB->CoreSubsys[ForEach_itr].mt + localDW->
        CoreSubsys[ForEach_itr].DelayOneStep1_DSTATE;

      // Update for Delay: '<S6>/Delay One Step1'
      localDW->CoreSubsys[ForEach_itr].DelayOneStep1_DSTATE = rtb_bt;

      // ForEachSliceAssignment generated from: '<S5>/Iabc bias '
      localB->ImpAsg_InsertedFor_Iabcbias_at_inport_0[ForEach_itr] = rtb_bt;
    }

    // End of Outputs for SubSystem: '<S3>/For Each Subsystem'
  }

  // End of Outputs for SubSystem: '<S1>/Enabled Subsystem'

  // Sum: '<S1>/Subtract' incorporates:
  //   ForEachSliceAssignment generated from: '<S5>/Iabc bias '

  for (ForEach_itr = 0; ForEach_itr < 3; ForEach_itr++) {
    rtb_Subtract[ForEach_itr] = rtu_SensorData->motorsensors.Iabc[ForEach_itr] -
      localB->ImpAsg_InsertedFor_Iabcbias_at_inport_0[ForEach_itr];

  }

  // End of Sum: '<S1>/Subtract'

  // Outputs for Triggered SubSystem: '<S2>/Sample and Hold' incorporates:
  //   TriggerPort: '<S8>/Trigger'

  // UnitDelay: '<S2>/Unit Delay1'
  if (localDW->UnitDelay1_DSTATE && (localZCE->SampleandHold_Trig_ZCE !=
       POS_ZCSIG)) {
    // SignalConversion generated from: '<S8>/In'
    localB->In_b = rtu_SensorData->motorsensors.qencoder.Idx_counter;
  }

  localZCE->SampleandHold_Trig_ZCE = localDW->UnitDelay1_DSTATE;

  // End of Outputs for SubSystem: '<S2>/Sample and Hold'

  // Outputs for Triggered SubSystem: '<S2>/Sample and Hold1' incorporates:
  //   TriggerPort: '<S9>/Trigger'

  if (localDW->UnitDelay1_DSTATE && (localZCE->SampleandHold1_Trig_ZCE !=
       POS_ZCSIG)) {
    // SignalConversion generated from: '<S9>/In' incorporates:
    //   Constant: '<S2>/One'

    localB->In = 1.0F;
  }

  // Outputs for Triggered SubSystem: '<S2>/Sample and Hold' incorporates:
  //   TriggerPort: '<S8>/Trigger'

  localZCE->SampleandHold1_Trig_ZCE = localDW->UnitDelay1_DSTATE;

  // End of UnitDelay: '<S2>/Unit Delay1'
  // End of Outputs for SubSystem: '<S2>/Sample and Hold'
  // End of Outputs for SubSystem: '<S2>/Sample and Hold1'

  // Switch: '<S2>/Switch1' incorporates:
  //   Sum: '<S2>/Add'
  //   Sum: '<S2>/Add2'

  if (localB->In > 0.0F) {
    rtb_bt = rtu_SensorData->motorsensors.qencoder.counter - localB->In_b;
  } else {
    rtb_bt = rtu_SensorData->motorsensors.qencoder.counter -
      rtu_SensorData->motorsensors.qencoder.Idx_counter;
  }

  // End of Switch: '<S2>/Switch1'

  // If: '<S12>/If' incorporates:
  //   Constant: '<S14>/Constant'
  //   Product: '<S17>/Product'
  //   Sum: '<S14>/Add'
  //   Sum: '<S15>/Add'
  //   Switch: '<S11>/Switch'

  if (rtb_bt <= rtu_ActuatorConfig->motor.externals.rotor_index_offset) {
    // Outputs for IfAction SubSystem: '<S12>/If Action Subsystem' incorporates:
    //   ActionPort: '<S14>/Action Port'

    rtb_SumofElements = (rtb_bt + 360.0F) - static_cast<real32_T>
      (rtu_ActuatorConfig->motor.externals.rotor_index_offset);

    // End of Outputs for SubSystem: '<S12>/If Action Subsystem'
  } else {
    // Outputs for IfAction SubSystem: '<S12>/If Action Subsystem1' incorporates:
    //   ActionPort: '<S15>/Action Port'

    rtb_SumofElements = rtb_bt - static_cast<real32_T>
      (rtu_ActuatorConfig->motor.externals.rotor_index_offset);

    // End of Outputs for SubSystem: '<S12>/If Action Subsystem1'
  }

  rtb_SumofElements *= static_cast<real32_T>
    (rtu_ActuatorConfig->motor.externals.pole_pairs);

  // End of If: '<S12>/If'

  // BusAssignment: '<S2>/Bus Assignment' incorporates:
  //   BusAssignment: '<S1>/Bus Assignment'
  //   Constant: '<S2>/Constant'
  //   Gain: '<S13>/Multiply'
  //   Gain: '<S13>/Multiply1'
  //   Math: '<S2>/Rem'
  //   Rounding: '<S13>/Floor'
  //   Sum: '<S13>/Add'

  rty_SensorDataDecoded->motorsensors.electrical_angle = rt_remf
    (rtb_SumofElements - std::floor(0.00277777785F * rtb_SumofElements) * 360.0F,
     360.0F);
  rty_SensorDataDecoded->motorsensors.qencoder.rotor_angle = rtb_bt;

  // Switch: '<S2>/Switch'
  if (!rtu_ActuatorConfig->motor.externals.has_quadrature_encoder) {
    // BusAssignment: '<S1>/Bus Assignment'
    *rty_SensorDataDecoded = *rtu_SensorData;
  }

  // End of Switch: '<S2>/Switch'

  // Sum: '<S4>/Sum of Elements'
  rtb_SumofElements = -0.0F;
  for (ForEach_itr = 0; ForEach_itr < 3; ForEach_itr++) {
    rtb_SumofElements += rtb_Subtract[ForEach_itr];
  }

  // Gain: '<S4>/Gain' incorporates:
  //   Sum: '<S4>/Sum of Elements'

  rtb_bt = 0.333333343F * rtb_SumofElements;

  // BusAssignment: '<S1>/Bus Assignment' incorporates:
  //   Sum: '<S4>/Subtract'

  for (ForEach_itr = 0; ForEach_itr < 3; ForEach_itr++) {
    rty_SensorDataDecoded->motorsensors.Iabc[ForEach_itr] =
      rtb_Subtract[ForEach_itr];
  }
		 if((++cnt1 % 9001) == 0)
	{
		for (uint8_t i = 0; i < 3; i++) {
				embot::core::print("----" + std::to_string(i) + "----\n" + "Iabc " + std::to_string(rtu_SensorData->motorsensors.Iabc[i]));
  			embot::core::print("Bias " + std::to_string(localB->ImpAsg_InsertedFor_Iabcbias_at_inport_0[i]));
				embot::core::print("Iabc UB " + std::to_string(rty_SensorDataDecoded->motorsensors.Iabc[i]));
		}		
		cnt1 = 0;    
	} 
  // Update for UnitDelay: '<S2>/Unit Delay1'
  localDW->UnitDelay1_DSTATE = rtu_Flags->calibration_done;
}

// Termination for referenced model: 'process_sensors'
void process_sensors_Term(DW_process_sensors_f_T *localDW)
{
  // Terminate for Enabled SubSystem: '<S1>/Enabled Subsystem'
  // Terminate for Iterator SubSystem: '<S3>/For Each Subsystem'
  for (int32_T ForEach_itr = 0; ForEach_itr < 3; ForEach_itr++) {
    // Terminate for MATLABSystem: '<S6>/Moving Average1'
    if (!localDW->CoreSubsys[ForEach_itr].obj.matlabCodegenIsDeleted) {
      localDW->CoreSubsys[ForEach_itr].obj.matlabCodegenIsDeleted = true;
      if ((localDW->CoreSubsys[ForEach_itr].obj.isInitialized == 1) &&
          localDW->CoreSubsys[ForEach_itr].obj.isSetupComplete) {
        localDW->CoreSubsys[ForEach_itr].obj.NumChannels = -1;
        localDW->CoreSubsys[ForEach_itr].obj.FrameLength = -1;
      }
    }

    // End of Terminate for MATLABSystem: '<S6>/Moving Average1'

    // Terminate for MATLABSystem: '<S6>/Moving Average'
    if (!localDW->CoreSubsys[ForEach_itr].obj_j.matlabCodegenIsDeleted) {
      localDW->CoreSubsys[ForEach_itr].obj_j.matlabCodegenIsDeleted = true;
      if ((localDW->CoreSubsys[ForEach_itr].obj_j.isInitialized == 1) &&
          localDW->CoreSubsys[ForEach_itr].obj_j.isSetupComplete) {
        localDW->CoreSubsys[ForEach_itr].obj_j.NumChannels = -1;
        localDW->CoreSubsys[ForEach_itr].obj_j.FrameLength = -1;
      }
    }

    // End of Terminate for MATLABSystem: '<S6>/Moving Average'
  }

  // End of Terminate for SubSystem: '<S3>/For Each Subsystem'
  // End of Terminate for SubSystem: '<S1>/Enabled Subsystem'
}

// Model initialize function
void process_sensors_initialize(ZCE_process_sensors_T *localZCE)
{
  localZCE->SampleandHold_Trig_ZCE = POS_ZCSIG;
  localZCE->SampleandHold1_Trig_ZCE = POS_ZCSIG;
}

//
// File trailer for generated code.
//
// [EOF]
//
