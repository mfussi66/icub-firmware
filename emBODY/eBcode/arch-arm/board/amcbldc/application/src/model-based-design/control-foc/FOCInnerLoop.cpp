//
// Non-Degree Granting Education License -- for use at non-degree
// granting, nonprofit, education, and research organizations only. Not
// for commercial or industrial use.
//
// File: FOCInnerLoop.cpp
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
#include "rtwtypes.h"
#include "FOCInnerLoop.h"
#include "control_foc_types.h"
#include <cmath>
#include "mw_cmsis.h"
#include "control_foc.h"

extern "C"
{

#include "rt_nonfinite.h"

}

#include "arm_math.h"
#include "control_foc_private.h"
#include "zero_crossing_types.h"

// Forward declaration for local functions
static void control_foc_SystemCore_setup(dsp_simulink_MovingRMS_contro_T *obj);
static void control_foc_SystemCore_setup(dsp_simulink_MovingRMS_contro_T *obj)
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
void control_foc_MovingRMS_Init(DW_MovingRMS_control_foc_T *localDW)
{
  g_dsp_internal_ExponentialMov_T *obj;
  boolean_T flag;

  // Start for MATLABSystem: '<S3>/Moving RMS'
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
  control_foc_SystemCore_setup(&localDW->obj);

  // End of Start for MATLABSystem: '<S3>/Moving RMS'

  // InitializeConditions for MATLABSystem: '<S3>/Moving RMS'
  obj = localDW->obj.pStatistic;
  if (obj->isInitialized == 1) {
    obj->pwN = 1.0F;
    obj->pmN = 0.0F;
  }

  // End of InitializeConditions for MATLABSystem: '<S3>/Moving RMS'
}

// Output and update for atomic system:
void control_foc_MovingRMS(real32_T rtu_0, B_MovingRMS_control_foc_T *localB,
  DW_MovingRMS_control_foc_T *localDW)
{
  g_dsp_internal_ExponentialMov_T *obj;
  real32_T a;
  real32_T lambda;
  real32_T pmLocal;
  real32_T pwLocal;
  boolean_T flag;

  // MATLABSystem: '<S3>/Moving RMS'
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

  a = std::abs(rtu_0);
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

  // MATLABSystem: '<S3>/Moving RMS'
  mw_arm_sqrt_f32(a, &localB->MovingRMS);
}

// Termination for atomic system:
void control_foc_MovingRMS_Term(DW_MovingRMS_control_foc_T *localDW)
{
  g_dsp_internal_ExponentialMov_T *obj;

  // Terminate for MATLABSystem: '<S3>/Moving RMS'
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

  // End of Terminate for MATLABSystem: '<S3>/Moving RMS'
}

// System initialize for atomic system: '<Root>/FOC inner loop'
void FOCInnerLoop_Init(void)
{
  // InitializeConditions for DiscreteIntegrator: '<S98>/Integrator'
  control_foc_DW.Integrator_PrevResetState = 2;

  // InitializeConditions for DiscreteIntegrator: '<S46>/Integrator'
  control_foc_DW.Integrator_PrevResetState_k = 2;
  control_foc_MovingRMS_Init(&control_foc_DW.MovingRMS);
  control_foc_MovingRMS_Init(&control_foc_DW.MovingRMS1);
}

// Outputs for atomic system: '<Root>/FOC inner loop'
void FOCInnerLoop(const ConfigurationParameters *rtu_ConfigurationParameters,
                  const SensorsData *rtu_Sensors, const EstimatedData
                  *rtu_Estimates, const Targets *rtu_Targets, const
                  ControlOuterOutputs *rtu_OuterOutputs, ControlOutputs
                  *rty_FOCOutputs)
{
  // local block i/o variables
  MotorCurrent rtb_Iq;
  MotorCurrent rtb_Id;
  int32_T i;
  real32_T TmpSignalConversionAtFilterDiff[2];
  real32_T rtb_IaIbIc0[2];
  real32_T rtb_Add;
  real32_T rtb_FilterDifferentiatorTF;
  real32_T rtb_PProdOut;
  real32_T rtb_Product;
  real32_T rtb_SinCos_o1;
  real32_T rtb_SinCos_o2;
  real32_T rtb_Unary_Minus;
  real32_T rtb_algDD_o1_p;
  real32_T rtb_algDD_o2_n;
  real32_T rtb_sum_alpha;
  int8_T tmp;
  int8_T tmp_0;

  // Sum: '<S1>/Add' incorporates:
  //   Product: '<S1>/Product1'
  //   Product: '<S1>/Product2'

  rtb_Add = rtu_OuterOutputs->motorcurrent.current *
    rtu_ConfigurationParameters->motorconfig.Rphase +
    rtu_Estimates->jointvelocities.velocity *
    rtu_ConfigurationParameters->motorconfig.Kbemf;

  // MinMax: '<S1>/Min'
  if ((rtu_ConfigurationParameters->motorconfig.Vcc <=
       rtu_ConfigurationParameters->motorconfig.Vmax) || rtIsNaNF
      (rtu_ConfigurationParameters->motorconfig.Vmax)) {
    rtb_sum_alpha = rtu_ConfigurationParameters->motorconfig.Vcc;
  } else {
    rtb_sum_alpha = rtu_ConfigurationParameters->motorconfig.Vmax;
  }

  // Product: '<S1>/Product' incorporates:
  //   Gain: '<S1>/Gain4'
  //   MinMax: '<S1>/Min'

  rtb_Product = 0.5F * rtb_sum_alpha * control_foc_ConstB.Sum5;

  // Gain: '<S1>/Ia+Ib+Ic=0'
  rtb_algDD_o2_n = rtu_Sensors->motorsensors.Iabc[1];
  rtb_SinCos_o1 = rtu_Sensors->motorsensors.Iabc[0];
  rtb_Unary_Minus = rtu_Sensors->motorsensors.Iabc[2];
  for (i = 0; i < 2; i++) {
    rtb_IaIbIc0[i] = (rtCP_IaIbIc0_Gain[i + 2] * rtb_algDD_o2_n +
                      rtCP_IaIbIc0_Gain[i] * rtb_SinCos_o1) +
      rtCP_IaIbIc0_Gain[i + 4] * rtb_Unary_Minus;
  }

  // End of Gain: '<S1>/Ia+Ib+Ic=0'

  // Outputs for Atomic SubSystem: '<S1>/Clarke Transform'
  // AlgorithmDescriptorDelegate generated from: '<S2>/a16'
  arm_clarke_f32(rtb_IaIbIc0[0], rtb_IaIbIc0[1], &rtb_algDD_o1_p,
                 &rtb_algDD_o2_n);

  // End of Outputs for SubSystem: '<S1>/Clarke Transform'

  // Gain: '<S1>/deg2rad'
  rtb_Unary_Minus = 0.0174532924F * rtu_Sensors->motorsensors.angle;

  // Trigonometry: '<S1>/SinCos'
  rtb_SinCos_o1 = std::sin(rtb_Unary_Minus);
  rtb_SinCos_o2 = std::cos(rtb_Unary_Minus);

  // Outputs for Atomic SubSystem: '<S1>/Park Transform'
  // Switch: '<S115>/Switch' incorporates:
  //   Product: '<S8>/acos'
  //   Product: '<S8>/asin'
  //   Product: '<S8>/bcos'
  //   Product: '<S8>/bsin'
  //   Sum: '<S8>/sum_Ds'
  //   Sum: '<S8>/sum_Qs'
  //   UnaryMinus: '<S115>/Unary_Minus'

  rtb_IaIbIc0[0] = -(rtb_algDD_o2_n * rtb_SinCos_o2 - rtb_algDD_o1_p *
                     rtb_SinCos_o1);
  rtb_IaIbIc0[1] = rtb_algDD_o1_p * rtb_SinCos_o2 + rtb_algDD_o2_n *
    rtb_SinCos_o1;

  // AlgorithmDescriptorDelegate generated from: '<S8>/a16'
  rtb_algDD_o2_n = rtb_IaIbIc0[1];

  // Sum: '<S1>/Sum' incorporates:
  //   AlgorithmDescriptorDelegate generated from: '<S8>/a16'

  rtb_Unary_Minus = rtu_OuterOutputs->motorcurrent.current - rtb_IaIbIc0[1];

  // End of Outputs for SubSystem: '<S1>/Park Transform'

  // Product: '<S103>/PProd Out'
  rtb_PProdOut = rtb_Unary_Minus * rtu_ConfigurationParameters->CurLoopPID.P;

  // Product: '<S95>/IProd Out'
  rtb_algDD_o1_p = rtb_Unary_Minus * rtu_ConfigurationParameters->CurLoopPID.I;

  // SampleTimeMath: '<S93>/Tsamp' incorporates:
  //   SampleTimeMath: '<S41>/Tsamp'
  //
  //  About '<S93>/Tsamp':
  //   y = u * K where K = ( w * Ts )
  //
  //  About '<S41>/Tsamp':
  //   y = u * K where K = ( w * Ts )

  rtb_FilterDifferentiatorTF = rtu_ConfigurationParameters->CurLoopPID.N *
    1.82857148E-5F;

  // Math: '<S91>/Reciprocal' incorporates:
  //   Constant: '<S91>/Filter Den Constant'
  //   Math: '<S39>/Reciprocal'
  //   SampleTimeMath: '<S93>/Tsamp'
  //   Sum: '<S91>/SumDen'
  //
  //  About '<S91>/Reciprocal':
  //   Operator: reciprocal
  //
  //  About '<S39>/Reciprocal':
  //   Operator: reciprocal
  //
  //  About '<S93>/Tsamp':
  //   y = u * K where K = ( w * Ts )

  rtb_sum_alpha = 1.0F / (rtb_FilterDifferentiatorTF + 1.0F);

  // DiscreteTransferFcn: '<S91>/Filter Differentiator TF'
  if (rtu_OuterOutputs->pid_reset &&
      (control_foc_PrevZCX.FilterDifferentiatorTF_Reset_ZC != POS_ZCSIG)) {
    control_foc_DW.FilterDifferentiatorTF_states = 0.0F;
  }

  control_foc_PrevZCX.FilterDifferentiatorTF_Reset_ZC =
    rtu_OuterOutputs->pid_reset;

  // Product: '<S91>/Divide' incorporates:
  //   Constant: '<S91>/Filter Den Constant'
  //   Math: '<S91>/Reciprocal'
  //   Product: '<S39>/Divide'
  //   SampleTimeMath: '<S93>/Tsamp'
  //   Sum: '<S91>/SumNum'
  //
  //  About '<S91>/Reciprocal':
  //   Operator: reciprocal
  //
  //  About '<S93>/Tsamp':
  //   y = u * K where K = ( w * Ts )

  rtb_FilterDifferentiatorTF = (rtb_FilterDifferentiatorTF - 1.0F) *
    rtb_sum_alpha;

  // DiscreteTransferFcn: '<S91>/Filter Differentiator TF' incorporates:
  //   Product: '<S90>/DProd Out'
  //   Product: '<S91>/Divide'

  control_foc_DW.FilterDifferentiatorTF_tmp = rtb_Unary_Minus *
    rtu_ConfigurationParameters->CurLoopPID.D - rtb_FilterDifferentiatorTF *
    control_foc_DW.FilterDifferentiatorTF_states;

  // Product: '<S101>/NProd Out' incorporates:
  //   DiscreteTransferFcn: '<S91>/Filter Differentiator TF'
  //   Math: '<S91>/Reciprocal'
  //   Product: '<S91>/DenCoefOut'
  //
  //  About '<S91>/Reciprocal':
  //   Operator: reciprocal

  rtb_Unary_Minus = (control_foc_DW.FilterDifferentiatorTF_tmp -
                     control_foc_DW.FilterDifferentiatorTF_states) *
    rtb_sum_alpha * rtu_ConfigurationParameters->CurLoopPID.N;

  // Sum: '<S110>/SumI1' incorporates:
  //   Sum: '<S108>/Sum Fdbk'
  //   Sum: '<S109>/SumI3'
  //   UnitDelay: '<S1>/Unit Delay'

  control_foc_B.SumI1 = (control_foc_DW.UnitDelay_DSTATE - ((rtb_PProdOut +
    control_foc_DW.Integrator_DSTATE) + rtb_Unary_Minus)) + rtb_algDD_o1_p;

  // DiscreteIntegrator: '<S98>/Integrator'
  if (rtu_OuterOutputs->pid_reset && (control_foc_DW.Integrator_PrevResetState <=
       0)) {
    control_foc_DW.Integrator_DSTATE = 0.0F;
  }

  // DiscreteIntegrator: '<S98>/Integrator'
  control_foc_B.Integrator = 1.82857148E-5F * control_foc_B.SumI1 +
    control_foc_DW.Integrator_DSTATE;

  // Switch: '<S1>/Switch1' incorporates:
  //   Gain: '<S1>/Gain6'
  //   Product: '<S1>/Divide2'
  //   Sum: '<S107>/Sum'
  //   Sum: '<S1>/Sum2'
  //   Sum: '<S1>/Sum6'

  if (rtu_OuterOutputs->cur_en) {
    rtb_PProdOut = ((rtb_PProdOut + control_foc_B.Integrator) + rtb_Unary_Minus)
      + rtb_Add;
  } else {
    rtb_PProdOut = rtu_Targets->motorvoltage.voltage * rtb_Product * 0.01F +
      rtu_OuterOutputs->current_limiter;
  }

  // End of Switch: '<S1>/Switch1'

  // Switch: '<S9>/Switch2' incorporates:
  //   Gain: '<S1>/Gain2'
  //   RelationalOperator: '<S9>/LowerRelop1'
  //   RelationalOperator: '<S9>/UpperRelop'
  //   Switch: '<S9>/Switch'

  if (rtb_PProdOut > rtb_Product) {
    rtb_PProdOut = rtb_Product;
  } else if (rtb_PProdOut < -rtb_Product) {
    // Switch: '<S9>/Switch' incorporates:
    //   Gain: '<S1>/Gain2'

    rtb_PProdOut = -rtb_Product;
  }

  // End of Switch: '<S9>/Switch2'

  // Outputs for Atomic SubSystem: '<S1>/Park Transform'
  // Product: '<S51>/PProd Out' incorporates:
  //   AlgorithmDescriptorDelegate generated from: '<S8>/a16'
  //   Gain: '<S1>/Gain'

  rtb_Unary_Minus = -rtb_IaIbIc0[0] * rtu_ConfigurationParameters->CurLoopPID.P;

  // End of Outputs for SubSystem: '<S1>/Park Transform'

  // DiscreteTransferFcn: '<S39>/Filter Differentiator TF' incorporates:
  //   AlgorithmDescriptorDelegate generated from: '<S8>/a16'
  //   DiscreteTransferFcn: '<S91>/Filter Differentiator TF'
  //   Gain: '<S1>/Gain'
  //   Product: '<S38>/DProd Out'

  if (rtu_OuterOutputs->pid_reset &&
      (control_foc_PrevZCX.FilterDifferentiatorTF_Reset__o != POS_ZCSIG)) {
    control_foc_DW.FilterDifferentiatorTF_states_k = 0.0F;
  }

  control_foc_PrevZCX.FilterDifferentiatorTF_Reset__o =
    rtu_OuterOutputs->pid_reset;

  // Outputs for Atomic SubSystem: '<S1>/Park Transform'
  control_foc_DW.FilterDifferentiatorTF_tmp_c = -rtb_IaIbIc0[0] *
    rtu_ConfigurationParameters->CurLoopPID.D - rtb_FilterDifferentiatorTF *
    control_foc_DW.FilterDifferentiatorTF_states_k;

  // End of Outputs for SubSystem: '<S1>/Park Transform'

  // Product: '<S49>/NProd Out' incorporates:
  //   DiscreteTransferFcn: '<S39>/Filter Differentiator TF'
  //   Product: '<S39>/DenCoefOut'

  rtb_FilterDifferentiatorTF = (control_foc_DW.FilterDifferentiatorTF_tmp_c -
    control_foc_DW.FilterDifferentiatorTF_states_k) * rtb_sum_alpha *
    rtu_ConfigurationParameters->CurLoopPID.N;

  // Sum: '<S57>/Sum Fdbk'
  rtb_algDD_o1_p = (rtb_Unary_Minus + control_foc_DW.Integrator_DSTATE_o) +
    rtb_FilterDifferentiatorTF;

  // Switch: '<S37>/Switch' incorporates:
  //   Gain: '<S1>/Gain2'
  //   RelationalOperator: '<S37>/u_GTE_up'
  //   RelationalOperator: '<S37>/u_GT_lo'
  //   Switch: '<S37>/Switch1'

  if (rtb_algDD_o1_p >= rtb_Product) {
    rtb_sum_alpha = rtb_Product;
  } else if (rtb_algDD_o1_p > -rtb_Product) {
    // Switch: '<S37>/Switch1'
    rtb_sum_alpha = rtb_algDD_o1_p;
  } else {
    rtb_sum_alpha = -rtb_Product;
  }

  // Sum: '<S37>/Diff' incorporates:
  //   Switch: '<S37>/Switch'

  rtb_algDD_o1_p -= rtb_sum_alpha;

  // Outputs for Atomic SubSystem: '<S1>/Park Transform'
  // Product: '<S43>/IProd Out' incorporates:
  //   AlgorithmDescriptorDelegate generated from: '<S8>/a16'
  //   Gain: '<S1>/Gain'

  rtb_sum_alpha = -rtb_IaIbIc0[0] * rtu_ConfigurationParameters->CurLoopPID.I;

  // End of Outputs for SubSystem: '<S1>/Park Transform'

  // Switch: '<S34>/Switch1' incorporates:
  //   Constant: '<S34>/Clamping_zero'
  //   Constant: '<S34>/Constant'
  //   Constant: '<S34>/Constant2'
  //   RelationalOperator: '<S34>/fix for DT propagation issue'

  if (rtb_algDD_o1_p > 0.0F) {
    tmp = 1;
  } else {
    tmp = -1;
  }

  // Switch: '<S34>/Switch2' incorporates:
  //   Constant: '<S34>/Clamping_zero'
  //   Constant: '<S34>/Constant3'
  //   Constant: '<S34>/Constant4'
  //   RelationalOperator: '<S34>/fix for DT propagation issue1'

  if (rtb_sum_alpha > 0.0F) {
    tmp_0 = 1;
  } else {
    tmp_0 = -1;
  }

  // Switch: '<S34>/Switch' incorporates:
  //   Constant: '<S34>/Clamping_zero'
  //   Logic: '<S34>/AND3'
  //   RelationalOperator: '<S34>/Equal1'
  //   RelationalOperator: '<S34>/Relational Operator'
  //   Switch: '<S34>/Switch1'
  //   Switch: '<S34>/Switch2'

  if ((rtb_algDD_o1_p != 0.0F) && (tmp == tmp_0)) {
    // Switch: '<S34>/Switch' incorporates:
    //   Constant: '<S34>/Constant1'

    control_foc_B.Switch = 0.0F;
  } else {
    // Switch: '<S34>/Switch'
    control_foc_B.Switch = rtb_sum_alpha;
  }

  // End of Switch: '<S34>/Switch'

  // DiscreteIntegrator: '<S46>/Integrator'
  if (rtu_OuterOutputs->pid_reset && (control_foc_DW.Integrator_PrevResetState_k
       <= 0)) {
    control_foc_DW.Integrator_DSTATE_o = 0.0F;
  }

  // DiscreteIntegrator: '<S46>/Integrator'
  control_foc_B.Integrator_j = 1.82857148E-5F * control_foc_B.Switch +
    control_foc_DW.Integrator_DSTATE_o;

  // Sum: '<S56>/Sum'
  rtb_algDD_o1_p = (rtb_Unary_Minus + control_foc_B.Integrator_j) +
    rtb_FilterDifferentiatorTF;

  // Switch: '<S54>/Switch2' incorporates:
  //   RelationalOperator: '<S54>/LowerRelop1'

  if (!(rtb_algDD_o1_p > rtb_Product)) {
    // Switch: '<S54>/Switch' incorporates:
    //   Gain: '<S1>/Gain2'
    //   RelationalOperator: '<S54>/UpperRelop'

    if (rtb_algDD_o1_p < -rtb_Product) {
      rtb_Product = -rtb_Product;
    } else {
      rtb_Product = rtb_algDD_o1_p;
    }

    // End of Switch: '<S54>/Switch'
  }

  // End of Switch: '<S54>/Switch2'

  // Outputs for Atomic SubSystem: '<S1>/Inverse Park Transform'
  // Sum: '<S6>/sum_beta' incorporates:
  //   Product: '<S6>/dsin'
  //   Product: '<S6>/qcos'

  rtb_Unary_Minus = rtb_PProdOut * rtb_SinCos_o2 + rtb_Product * rtb_SinCos_o1;

  // Switch: '<S64>/Switch' incorporates:
  //   Product: '<S6>/dcos'
  //   Product: '<S6>/qsin'
  //   Sum: '<S6>/sum_alpha'
  //   UnaryMinus: '<S64>/Unary_Minus'

  rtb_IaIbIc0[1] = -(rtb_Product * rtb_SinCos_o2 - rtb_PProdOut * rtb_SinCos_o1);

  // End of Outputs for SubSystem: '<S1>/Inverse Park Transform'

  // Switch: '<S1>/Switch2' incorporates:
  //   Constant: '<S1>/Constant1'

  if (rtu_OuterOutputs->out_en) {
    // Gain: '<S1>/Gain3' incorporates:
    //   Product: '<S1>/Divide1'

    rtb_Product = rtb_PProdOut / rtu_ConfigurationParameters->motorconfig.Vcc *
      100.0F;

    // Outputs for Atomic SubSystem: '<S1>/Inverse Park Transform'
    // Gain: '<S5>/sqrt3_by_two' incorporates:
    //   AlgorithmDescriptorDelegate generated from: '<S6>/a16'

    rtb_algDD_o1_p = 0.866025388F * rtb_IaIbIc0[1];

    // Gain: '<S5>/one_by_two' incorporates:
    //   Sum: '<S6>/sum_beta'

    rtb_SinCos_o1 = 0.5F * rtb_Unary_Minus;

    // End of Outputs for SubSystem: '<S1>/Inverse Park Transform'

    // Sum: '<S5>/add_c'
    rtb_SinCos_o2 = (0.0F - rtb_SinCos_o1) - rtb_algDD_o1_p;

    // Sum: '<S5>/add_b'
    rtb_SinCos_o1 = rtb_algDD_o1_p - rtb_SinCos_o1;

    // Outputs for Atomic SubSystem: '<S1>/Inverse Park Transform'
    // MinMax: '<S1>/Min1'
    if ((rtb_Unary_Minus <= rtb_SinCos_o1) || rtIsNaNF(rtb_SinCos_o1)) {
      rtb_algDD_o1_p = rtb_Unary_Minus;
    } else {
      rtb_algDD_o1_p = rtb_SinCos_o1;
    }

    // End of Outputs for SubSystem: '<S1>/Inverse Park Transform'
    if ((!(rtb_algDD_o1_p <= rtb_SinCos_o2)) && (!rtIsNaNF(rtb_SinCos_o2))) {
      rtb_algDD_o1_p = rtb_SinCos_o2;
    }

    // Saturate: '<S1>/Saturation1'
    if (rtb_Product > 100.0F) {
      // BusCreator: '<S1>/Bus Creator'
      rty_FOCOutputs->Vq = 100.0F;
    } else if (rtb_Product < -100.0F) {
      // BusCreator: '<S1>/Bus Creator'
      rty_FOCOutputs->Vq = -100.0F;
    } else {
      // BusCreator: '<S1>/Bus Creator'
      rty_FOCOutputs->Vq = rtb_Product;
    }

    // End of Saturate: '<S1>/Saturation1'

    // Outputs for Atomic SubSystem: '<S1>/Inverse Park Transform'
    // Sum: '<S1>/Sum1' incorporates:
    //   Constant: '<S1>/Constant2'
    //   Gain: '<S1>/Gain1'
    //   MinMax: '<S1>/Min1'
    //   Product: '<S1>/Divide'
    //   Sum: '<S1>/Sum4'
    //   Sum: '<S6>/sum_beta'

    rtb_Product = (rtb_Unary_Minus - rtb_algDD_o1_p) /
      rtu_ConfigurationParameters->motorconfig.Vcc * 100.0F + 5.0F;

    // End of Outputs for SubSystem: '<S1>/Inverse Park Transform'

    // Saturate: '<S1>/Saturation'
    if (rtb_Product > 100.0F) {
      rtb_Product = 100.0F;
    } else if (rtb_Product < 0.0F) {
      rtb_Product = 0.0F;
    }

    // Sum: '<S1>/Sum1' incorporates:
    //   Constant: '<S1>/Constant2'
    //   Gain: '<S1>/Gain1'
    //   MinMax: '<S1>/Min1'
    //   Product: '<S1>/Divide'
    //   Sum: '<S1>/Sum4'

    rtb_SinCos_o1 = (rtb_SinCos_o1 - rtb_algDD_o1_p) /
      rtu_ConfigurationParameters->motorconfig.Vcc * 100.0F + 5.0F;

    // Saturate: '<S1>/Saturation'
    if (rtb_SinCos_o1 > 100.0F) {
      rtb_SinCos_o1 = 100.0F;
    } else if (rtb_SinCos_o1 < 0.0F) {
      rtb_SinCos_o1 = 0.0F;
    }

    // Sum: '<S1>/Sum1' incorporates:
    //   Constant: '<S1>/Constant2'
    //   Gain: '<S1>/Gain1'
    //   MinMax: '<S1>/Min1'
    //   Product: '<S1>/Divide'
    //   Sum: '<S1>/Sum4'

    rtb_SinCos_o2 = (rtb_SinCos_o2 - rtb_algDD_o1_p) /
      rtu_ConfigurationParameters->motorconfig.Vcc * 100.0F + 5.0F;

    // Saturate: '<S1>/Saturation'
    if (rtb_SinCos_o2 > 100.0F) {
      rtb_SinCos_o2 = 100.0F;
    } else if (rtb_SinCos_o2 < 0.0F) {
      rtb_SinCos_o2 = 0.0F;
    }
  } else {
    // BusCreator: '<S1>/Bus Creator' incorporates:
    //   Constant: '<S1>/Constant1'

    rty_FOCOutputs->Vq = 0.0F;
    rtb_Product = 0.0F;
    rtb_SinCos_o1 = 0.0F;
    rtb_SinCos_o2 = 0.0F;
  }

  // End of Switch: '<S1>/Switch2'

  // BusCreator: '<S1>/Bus Creator1'
  rtb_Iq.current = rtb_algDD_o2_n;

  // Outputs for Atomic SubSystem: '<S1>/Park Transform'
  // BusCreator: '<S1>/Bus Creator2' incorporates:
  //   AlgorithmDescriptorDelegate generated from: '<S8>/a16'

  rtb_Id.current = rtb_IaIbIc0[0];

  // End of Outputs for SubSystem: '<S1>/Park Transform'
  control_foc_MovingRMS(rtb_Iq.current, &control_foc_B.MovingRMS,
                        &control_foc_DW.MovingRMS);
  control_foc_MovingRMS(rtb_Id.current, &control_foc_B.MovingRMS1,
                        &control_foc_DW.MovingRMS1);

  // SignalConversion generated from: '<S3>/Square'
  rtb_IaIbIc0[0] = control_foc_B.MovingRMS.MovingRMS;
  rtb_IaIbIc0[1] = control_foc_B.MovingRMS1.MovingRMS;

  // Math: '<S3>/Square'
  mw_arm_mult_f32(&rtb_IaIbIc0[0], &rtb_IaIbIc0[0],
                  &TmpSignalConversionAtFilterDiff[0], 2U);

  // BusCreator: '<S1>/Bus Creator' incorporates:
  //   Product: '<S3>/Product'
  //   Sum: '<S3>/Sum of Elements'

  rty_FOCOutputs->Vabc[0] = rtb_Product;
  rty_FOCOutputs->Vabc[1] = rtb_SinCos_o1;
  rty_FOCOutputs->Vabc[2] = rtb_SinCos_o2;
  rty_FOCOutputs->Iq_fbk = rtb_Iq;
  rty_FOCOutputs->Id_fbk = rtb_Id;
  rty_FOCOutputs->Power = (TmpSignalConversionAtFilterDiff[0] +
    TmpSignalConversionAtFilterDiff[1]) *
    rtu_ConfigurationParameters->motorconfig.resistance;

  // Sum: '<S1>/Sum3'
  control_foc_B.Sum3 = rtb_PProdOut - rtb_Add;
}

// Update for atomic system: '<Root>/FOC inner loop'
void FOCInnerLoop_Update(const ControlOuterOutputs *rtu_OuterOutputs)
{
  // Update for DiscreteTransferFcn: '<S91>/Filter Differentiator TF'
  control_foc_DW.FilterDifferentiatorTF_states =
    control_foc_DW.FilterDifferentiatorTF_tmp;

  // Update for UnitDelay: '<S1>/Unit Delay'
  control_foc_DW.UnitDelay_DSTATE = control_foc_B.Sum3;

  // Update for DiscreteIntegrator: '<S98>/Integrator'
  control_foc_DW.Integrator_DSTATE = 1.82857148E-5F * control_foc_B.SumI1 +
    control_foc_B.Integrator;
  control_foc_DW.Integrator_PrevResetState = static_cast<int8_T>
    (rtu_OuterOutputs->pid_reset);

  // Update for DiscreteTransferFcn: '<S39>/Filter Differentiator TF'
  control_foc_DW.FilterDifferentiatorTF_states_k =
    control_foc_DW.FilterDifferentiatorTF_tmp_c;

  // Update for DiscreteIntegrator: '<S46>/Integrator' incorporates:
  //   DiscreteIntegrator: '<S98>/Integrator'

  control_foc_DW.Integrator_DSTATE_o = 1.82857148E-5F * control_foc_B.Switch +
    control_foc_B.Integrator_j;
  control_foc_DW.Integrator_PrevResetState_k = static_cast<int8_T>
    (rtu_OuterOutputs->pid_reset);
}

// Termination for atomic system: '<Root>/FOC inner loop'
void FOCInnerLoop_Term(void)
{
  control_foc_MovingRMS_Term(&control_foc_DW.MovingRMS);
  control_foc_MovingRMS_Term(&control_foc_DW.MovingRMS1);
}

//
// File trailer for generated code.
//
// [EOF]
//
