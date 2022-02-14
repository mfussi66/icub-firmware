//
// Non-Degree Granting Education License -- for use at non-degree
// granting, nonprofit, education, and research organizations only. Not
// for commercial or industrial use.
//
// File: FOCInnerLoop.cpp
//
// Code generated for Simulink model 'control_foc'.
//
// Model version                  : 2.88
// Simulink Coder version         : 9.6 (R2021b) 14-May-2021
// C/C++ source code generated on : Thu Feb 10 09:58:07 2022
//
// Target selection: ert.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex-M
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "FOCInnerLoop.h"

// Include model header file for global data
#include "control_foc.h"
#include "control_foc_private.h"

#include "embot_core.h"
#include "embot_tools.h"

class Performance{
    public:
    inline static real32_T prev_ = 0;
    real32_T curr_ = 0;
    inline static std::vector<real32_T> acc_{};
        
    Performance()
    {
        curr_ = static_cast<real32_T>(embot::core::now());
        real32_T value_ = curr_ - prev_;
        prev_ = curr_;
        acc_.push_back(value_);
                
        if (acc_.size() >= 25)
        {
            real32_T avg = 0;
            for (real32_T c : acc_)
            {
                avg += c;
            }
            avg = avg / 25.0;
            char msg6[6];
            
            sprintf(msg6, "%.3f", avg);
            embot::core::print(msg6);
            acc_.clear();
        }
    }
};

embot::tools::PeriodValidator pvalidate;

namespace amc_bldc_codegen
{
  // System initialize for atomic system: '<Root>/FOC inner loop'
  void control_foc::FOCInnerLoop_Init()
  {
    // InitializeConditions for UnitDelay: '<S3>/Delay Input1'
    //
    //  Block description for '<S3>/Delay Input1':
    //
    //   Store in Global RAM

    control_foc_DW.DelayInput1_DSTATE = ControlModes_Idle;

    // InitializeConditions for DiscreteIntegrator: '<S94>/Integrator'
    control_foc_DW.Integrator_PrevResetState = 2;

    // InitializeConditions for DiscreteIntegrator: '<S44>/Integrator'
    control_foc_DW.Integrator_PrevResetState_k = 2;
    

    embot::tools::Histogram::Config histcfg = {0, 64, 1 * embot::core::time1microsec};
    embot::tools::PeriodValidator::Config pvalidatecfg = {36, 46, 10000, histcfg};
    pvalidate.init(pvalidatecfg);
      
  }

  // Output and update for atomic system: '<Root>/FOC inner loop'
  void control_foc::FOCInnerLoop(const Flags *rtu_Flags, const
    ConfigurationParameters *rtu_ConfigurationParameters, const SensorsData
    *rtu_Sensors, const EstimatedData *rtu_Estimates, const Targets *rtu_Targets,
    const ControlOuterOutputs *rtu_OuterOutputs, ControlOutputs *rty_FOCOutputs)
  {
    uint64_t deltatime;
    pvalidate.tick(embot::core::now(), deltatime);
      
    if(pvalidate.report())
    {
        const embot::tools::Histogram * phisto = pvalidate.histogram();
        const embot::tools::Histogram::Values * vv = phisto->getvalues();
        static char msg3[64];
        for(int i=0; i<vv->inside.size(); i++)
        {
            sprintf(msg3, "%llu", vv->inside[i]);
            embot::core::print(msg3);
        }
    }
      
    real32_T rtb_IaIbIc0[2];
    real32_T rtb_Add;
    real32_T rtb_Saturation1;
    real32_T rtb_SinCos_o1;
    real32_T rtb_SinCos_o2;
    real32_T rtb_SumFdbk;
    real32_T rtb_SumFdbk_0;
    real32_T rtb_Unary_Minus;
    real32_T rtb_algDD_o1_p;
    real32_T rtb_algDD_o2_n;
    real32_T rtb_sum_alpha;
    real32_T rtb_sum_beta;
    real32_T tmp;
    real32_T u0;
    boolean_T rtb_FixPtRelationalOperator;

    // Switch: '<S1>/Switch3'
    if (rtu_OuterOutputs->vel_en) {
      rtb_Unary_Minus = rtu_OuterOutputs->motorcurrent.current;
    } else {
      rtb_Unary_Minus = rtu_Targets->motorcurrent.current;
    }

    // End of Switch: '<S1>/Switch3'

    // Sum: '<S1>/Add' incorporates:
    //   Product: '<S1>/Product1'
    //   Product: '<S1>/Product2'

    rtb_Add = rtb_Unary_Minus * rtu_ConfigurationParameters->motorconfig.Rphase
      + rtu_Estimates->jointvelocities.velocity *
      rtu_ConfigurationParameters->motorconfig.Kbemf;

    // Gain: '<S1>/Ia+Ib+Ic=0'
    for (int32_T i = 0; i < 2; i++) {
      rtb_IaIbIc0[i] = 0.0F;
      rtb_IaIbIc0[i] += rtCP_IaIbIc0_Gain[i] * rtu_Sensors->motorsensors.Iabc[0];
      rtb_IaIbIc0[i] += rtCP_IaIbIc0_Gain[i + 2] *
        rtu_Sensors->motorsensors.Iabc[1];
      rtb_IaIbIc0[i] += rtCP_IaIbIc0_Gain[i + 4] *
        rtu_Sensors->motorsensors.Iabc[2];
    }

    // End of Gain: '<S1>/Ia+Ib+Ic=0'

    // Outputs for Atomic SubSystem: '<S1>/Clarke Transform'
    // AlgorithmDescriptorDelegate generated from: '<S2>/a16'
    arm_clarke_f32(rtb_IaIbIc0[0], rtb_IaIbIc0[1], &rtb_algDD_o1_p,
                   &rtb_algDD_o2_n);

    // End of Outputs for SubSystem: '<S1>/Clarke Transform'

    // Gain: '<S1>/deg2rad'
    rtb_Saturation1 = 0.0174532924F * rtu_Sensors->motorsensors.angle;

    // Trigonometry: '<S1>/SinCos'
    rtb_SinCos_o1 = std::sin(rtb_Saturation1);
    rtb_SinCos_o2 = std::cos(rtb_Saturation1);

    // Outputs for Atomic SubSystem: '<S1>/Park Transform'
    // Switch: '<S111>/Switch' incorporates:
    //   Product: '<S8>/acos'
    //   Product: '<S8>/asin'
    //   Product: '<S8>/bcos'
    //   Product: '<S8>/bsin'
    //   Sum: '<S8>/sum_Ds'
    //   Sum: '<S8>/sum_Qs'
    //   UnaryMinus: '<S111>/Unary_Minus'

    rtb_IaIbIc0[0] = -(rtb_algDD_o2_n * rtb_SinCos_o2 - rtb_algDD_o1_p *
                       rtb_SinCos_o1);
    rtb_IaIbIc0[1] = rtb_algDD_o1_p * rtb_SinCos_o2 + rtb_algDD_o2_n *
      rtb_SinCos_o1;

    //if(rtb_IaIbIc0[1] < 0){
//        char msg6[64];
//        static uint32_t cnt;
//        if(cnt % 1000 == 0)
//        {
//            sprintf(msg6, "%.3f %.3f %.3f %.3f %.3f %.3f",
//                             rtu_Sensors->motorsensors.Iabc[0],
//                             rtu_Sensors->motorsensors.Iabc[1],
//                             rtu_Sensors->motorsensors.Iabc[2],
//                                rtb_IaIbIc0[0],                 
//                                rtb_IaIbIc0[1],
//                                rtb_Saturation1); // electrical angle
//            cnt = 0;
//            embot::core::print(msg6);
//        }
//        cnt++;
    //}

    // Sum: '<S1>/Sum' incorporates:
    //   AlgorithmDescriptorDelegate generated from: '<S8>/a16'

    rtb_Unary_Minus -= rtb_IaIbIc0[1];

    // End of Outputs for SubSystem: '<S1>/Park Transform'

    // Product: '<S99>/PProd Out'
    rtb_Saturation1 = rtb_Unary_Minus *
      rtu_ConfigurationParameters->motorconfig.Kp;

    // Sum: '<S106>/SumI1' incorporates:
    //   Product: '<S91>/IProd Out'
    //   Sum: '<S104>/Sum Fdbk'
    //   Sum: '<S105>/SumI3'
    //   UnitDelay: '<S1>/Unit Delay'

    rtb_algDD_o2_n = (control_foc_DW.UnitDelay_DSTATE - (rtb_Saturation1 +
      control_foc_DW.Integrator_DSTATE)) + rtb_Unary_Minus *
      rtu_ConfigurationParameters->motorconfig.Ki;

    // RelationalOperator: '<S3>/FixPt Relational Operator' incorporates:
    //   UnitDelay: '<S3>/Delay Input1'
    //
    //  Block description for '<S3>/Delay Input1':
    //
    //   Store in Global RAM

    rtb_FixPtRelationalOperator = (rtu_Flags->control_mode !=
      control_foc_DW.DelayInput1_DSTATE);

    // DiscreteIntegrator: '<S94>/Integrator'
    if (rtb_FixPtRelationalOperator && (control_foc_DW.Integrator_PrevResetState
         <= 0)) {
      control_foc_DW.Integrator_DSTATE = 0.0F;
    }

    // DiscreteIntegrator: '<S94>/Integrator'
    rtb_algDD_o1_p = 1.82857148E-5F * rtb_algDD_o2_n +
      control_foc_DW.Integrator_DSTATE;

    // Switch: '<S1>/Switch1' incorporates:
    //   Sum: '<S103>/Sum'
    //   Sum: '<S1>/Sum2'

    if (rtu_OuterOutputs->cur_en) {
        rtb_Saturation1 = (rtb_Saturation1 + rtb_algDD_o1_p) + rtb_Add;
        //rtb_Saturation1 = 2.0F;
    } else {
      rtb_Saturation1 = rtu_Targets->motorvoltage.voltage;
    }

    // End of Switch: '<S1>/Switch1'

    // Switch: '<S9>/Switch2' incorporates:
    //   Gain: '<S1>/Gain2'
    //   RelationalOperator: '<S9>/LowerRelop1'
    //   RelationalOperator: '<S9>/UpperRelop'
    //   Switch: '<S9>/Switch'

    if (rtb_Saturation1 > rtu_ConfigurationParameters->motorconfig.Vmax) {
      rtb_Saturation1 = rtu_ConfigurationParameters->motorconfig.Vmax;
    } else if (rtb_Saturation1 < -rtu_ConfigurationParameters->motorconfig.Vmax)
    {
      // Switch: '<S9>/Switch' incorporates:
      //   Gain: '<S1>/Gain2'

      rtb_Saturation1 = -rtu_ConfigurationParameters->motorconfig.Vmax;
    }

    // End of Switch: '<S9>/Switch2'

    // Gain: '<S1>/Gain3' incorporates:
    //   Product: '<S1>/Divide1'

    u0 = rtb_Saturation1 / rtu_ConfigurationParameters->motorconfig.Vcc * 100.0F;

    // Outputs for Atomic SubSystem: '<S1>/Park Transform'
    // Product: '<S49>/PProd Out' incorporates:
    //   AlgorithmDescriptorDelegate generated from: '<S8>/a16'
    //   Gain: '<S1>/Gain'

    rtb_Unary_Minus = -rtb_IaIbIc0[0] *
      rtu_ConfigurationParameters->motorconfig.Kp;

    // End of Outputs for SubSystem: '<S1>/Park Transform'

    // Sum: '<S55>/Sum Fdbk'
    rtb_SumFdbk = rtb_Unary_Minus + control_foc_DW.Integrator_DSTATE_o;

    // Switch: '<S37>/Switch' incorporates:
    //   Gain: '<S1>/Gain2'
    //   RelationalOperator: '<S37>/u_GTE_up'
    //   RelationalOperator: '<S37>/u_GT_lo'
    //   Switch: '<S37>/Switch1'

    if (rtb_SumFdbk >= rtu_ConfigurationParameters->motorconfig.Vmax) {
      rtb_SumFdbk_0 = rtu_ConfigurationParameters->motorconfig.Vmax;
    } else if (rtb_SumFdbk > -rtu_ConfigurationParameters->motorconfig.Vmax) {
      // Switch: '<S37>/Switch1'
      rtb_SumFdbk_0 = rtb_SumFdbk;
    } else {
      rtb_SumFdbk_0 = -rtu_ConfigurationParameters->motorconfig.Vmax;
    }

    // End of Switch: '<S37>/Switch'

    // Sum: '<S37>/Diff'
    rtb_sum_beta = rtb_SumFdbk - rtb_SumFdbk_0;

    // Outputs for Atomic SubSystem: '<S1>/Park Transform'
    // Product: '<S41>/IProd Out' incorporates:
    //   AlgorithmDescriptorDelegate generated from: '<S8>/a16'
    //   Gain: '<S1>/Gain'

    rtb_sum_alpha = -rtb_IaIbIc0[0] *
      rtu_ConfigurationParameters->motorconfig.Ki;

    // End of Outputs for SubSystem: '<S1>/Park Transform'

    // Signum: '<S34>/SignPreSat'
    if (rtb_sum_beta < 0.0F) {
      // DataTypeConversion: '<S34>/DataTypeConv1'
      rtb_SumFdbk_0 = -1.0F;
    } else if (rtb_sum_beta > 0.0F) {
      // DataTypeConversion: '<S34>/DataTypeConv1'
      rtb_SumFdbk_0 = 1.0F;
    } else if (rtb_sum_beta == 0.0F) {
      // DataTypeConversion: '<S34>/DataTypeConv1'
      rtb_SumFdbk_0 = 0.0F;
    } else {
      // DataTypeConversion: '<S34>/DataTypeConv1'
      rtb_SumFdbk_0 = (rtNaNF);
    }

    // End of Signum: '<S34>/SignPreSat'

    // DataTypeConversion: '<S34>/DataTypeConv1'
    if (rtIsNaNF(rtb_SumFdbk_0)) {
      rtb_SumFdbk_0 = 0.0F;
    } else {
      rtb_SumFdbk_0 = std::fmod(rtb_SumFdbk_0, 256.0F);
    }

    // Signum: '<S34>/SignPreIntegrator'
    if (rtb_sum_alpha < 0.0F) {
      // DataTypeConversion: '<S34>/DataTypeConv2'
      tmp = -1.0F;
    } else if (rtb_sum_alpha > 0.0F) {
      // DataTypeConversion: '<S34>/DataTypeConv2'
      tmp = 1.0F;
    } else if (rtb_sum_alpha == 0.0F) {
      // DataTypeConversion: '<S34>/DataTypeConv2'
      tmp = 0.0F;
    } else {
      // DataTypeConversion: '<S34>/DataTypeConv2'
      tmp = (rtNaNF);
    }

    // End of Signum: '<S34>/SignPreIntegrator'

    // DataTypeConversion: '<S34>/DataTypeConv2'
    if (rtIsNaNF(tmp)) {
      tmp = 0.0F;
    } else {
      tmp = std::fmod(tmp, 256.0F);
    }

    // Switch: '<S34>/Switch' incorporates:
    //   Constant: '<S34>/Constant1'
    //   DataTypeConversion: '<S34>/DataTypeConv1'
    //   DataTypeConversion: '<S34>/DataTypeConv2'
    //   Gain: '<S34>/ZeroGain'
    //   Logic: '<S34>/AND3'
    //   RelationalOperator: '<S34>/Equal1'
    //   RelationalOperator: '<S34>/NotEqual'

    if ((0.0F * rtb_SumFdbk != rtb_sum_beta) && ((rtb_SumFdbk_0 < 0.0F ?
          static_cast<int32_T>(static_cast<int8_T>(-static_cast<int8_T>(
             static_cast<uint8_T>(-rtb_SumFdbk_0)))) : static_cast<int32_T>(
           static_cast<int8_T>(static_cast<uint8_T>(rtb_SumFdbk_0)))) == (tmp <
          0.0F ? static_cast<int32_T>(static_cast<int8_T>(-static_cast<int8_T>(
             static_cast<uint8_T>(-tmp)))) : static_cast<int32_T>
          (static_cast<int8_T>(static_cast<uint8_T>(tmp)))))) {
      rtb_sum_alpha = 0.0F;
    }

    // End of Switch: '<S34>/Switch'

    // DiscreteIntegrator: '<S44>/Integrator'
    if (rtb_FixPtRelationalOperator &&
        (control_foc_DW.Integrator_PrevResetState_k <= 0)) {
      control_foc_DW.Integrator_DSTATE_o = 0.0F;
    }

    // DiscreteIntegrator: '<S44>/Integrator'
    rtb_SumFdbk = 1.82857148E-5F * rtb_sum_alpha +
      control_foc_DW.Integrator_DSTATE_o;

    // Sum: '<S54>/Sum'
    rtb_Unary_Minus += rtb_SumFdbk;

    // Switch: '<S52>/Switch2' incorporates:
    //   Gain: '<S1>/Gain2'
    //   RelationalOperator: '<S52>/LowerRelop1'
    //   RelationalOperator: '<S52>/UpperRelop'
    //   Switch: '<S52>/Switch'

    if (rtb_Unary_Minus > rtu_ConfigurationParameters->motorconfig.Vmax) {
      rtb_Unary_Minus = rtu_ConfigurationParameters->motorconfig.Vmax;
    } else if (rtb_Unary_Minus < -rtu_ConfigurationParameters->motorconfig.Vmax)
    {
      // Switch: '<S52>/Switch' incorporates:
      //   Gain: '<S1>/Gain2'

      rtb_Unary_Minus = -rtu_ConfigurationParameters->motorconfig.Vmax;
    }

    // End of Switch: '<S52>/Switch2'

    // Outputs for Atomic SubSystem: '<S1>/Inverse Park Transform'
    // Switch: '<S62>/Switch' incorporates:
    //   Product: '<S6>/dsin'
    //   Product: '<S6>/qcos'
    //   Sum: '<S6>/sum_beta'

    rtb_IaIbIc0[0] = rtb_Saturation1 * rtb_SinCos_o2 + rtb_Unary_Minus *
      rtb_SinCos_o1;

    // End of Outputs for SubSystem: '<S1>/Inverse Park Transform'

    // Switch: '<S1>/Switch2' incorporates:
    //   Constant: '<S1>/Constant1'

    if (rtu_OuterOutputs->out_en) {
      // Outputs for Atomic SubSystem: '<S1>/Inverse Park Transform'
      // Gain: '<S5>/sqrt3_by_two' incorporates:
      //   Product: '<S6>/dcos'
      //   Product: '<S6>/qsin'
      //   Sum: '<S6>/sum_alpha'
      //   UnaryMinus: '<S62>/Unary_Minus'

      rtb_SinCos_o1 = -(rtb_Unary_Minus * rtb_SinCos_o2 - rtb_Saturation1 *
                        rtb_SinCos_o1) * 0.866025388F;

      // Gain: '<S5>/one_by_two' incorporates:
      //   AlgorithmDescriptorDelegate generated from: '<S6>/a16'

      rtb_SinCos_o2 = 0.5F * rtb_IaIbIc0[0];

      // End of Outputs for SubSystem: '<S1>/Inverse Park Transform'

      // Sum: '<S5>/add_c'
      rtb_Unary_Minus = (0.0F - rtb_SinCos_o2) - rtb_SinCos_o1;

      // Sum: '<S5>/add_b'
      rtb_SinCos_o2 = rtb_SinCos_o1 - rtb_SinCos_o2;

      // Outputs for Atomic SubSystem: '<S1>/Inverse Park Transform'
      // MinMax: '<S1>/Min' incorporates:
      //   AlgorithmDescriptorDelegate generated from: '<S6>/a16'

      if ((rtb_IaIbIc0[0] <= rtb_SinCos_o2) || rtIsNaNF(rtb_SinCos_o2)) {
        rtb_SinCos_o1 = rtb_IaIbIc0[0];
      } else {
        rtb_SinCos_o1 = rtb_SinCos_o2;
      }

      // End of Outputs for SubSystem: '<S1>/Inverse Park Transform'
      if ((!(rtb_SinCos_o1 <= rtb_Unary_Minus)) && (!rtIsNaNF(rtb_Unary_Minus)))
      {
        rtb_SinCos_o1 = rtb_Unary_Minus;
      }

      // End of MinMax: '<S1>/Min'

      // Outputs for Atomic SubSystem: '<S1>/Inverse Park Transform'
      // Gain: '<S1>/Gain1' incorporates:
      //   AlgorithmDescriptorDelegate generated from: '<S6>/a16'
      //   Product: '<S1>/Divide'
      //   Sum: '<S1>/Sum1'

      rtb_SumFdbk_0 = (rtb_IaIbIc0[0] - rtb_SinCos_o1) /
        rtu_ConfigurationParameters->motorconfig.Vcc * 100.0F;

      // End of Outputs for SubSystem: '<S1>/Inverse Park Transform'

      // Saturate: '<S1>/Saturation'
      if (rtb_SumFdbk_0 > 100.0F) {
        rty_FOCOutputs->Vabc[0] = 100.0F;
      } else if (rtb_SumFdbk_0 < 0.0F) {
        rty_FOCOutputs->Vabc[0] = 0.0F;
      } else {
        rty_FOCOutputs->Vabc[0] = rtb_SumFdbk_0;
      }

      // Gain: '<S1>/Gain1' incorporates:
      //   Product: '<S1>/Divide'
      //   Sum: '<S1>/Sum1'

      rtb_SumFdbk_0 = (rtb_SinCos_o2 - rtb_SinCos_o1) /
        rtu_ConfigurationParameters->motorconfig.Vcc * 100.0F;

      // Saturate: '<S1>/Saturation'
      if (rtb_SumFdbk_0 > 100.0F) {
        rty_FOCOutputs->Vabc[1] = 100.0F;
      } else if (rtb_SumFdbk_0 < 0.0F) {
        rty_FOCOutputs->Vabc[1] = 0.0F;
      } else {
        rty_FOCOutputs->Vabc[1] = rtb_SumFdbk_0;
      }

      // Gain: '<S1>/Gain1' incorporates:
      //   Product: '<S1>/Divide'
      //   Sum: '<S1>/Sum1'

      rtb_SumFdbk_0 = (rtb_Unary_Minus - rtb_SinCos_o1) /
        rtu_ConfigurationParameters->motorconfig.Vcc * 100.0F;

      // Saturate: '<S1>/Saturation'
      if (rtb_SumFdbk_0 > 100.0F) {
        rty_FOCOutputs->Vabc[2] = 100.0F;
      } else if (rtb_SumFdbk_0 < 0.0F) {
        rty_FOCOutputs->Vabc[2] = 0.0F;
      } else {
        rty_FOCOutputs->Vabc[2] = rtb_SumFdbk_0;
      }
    } else {
      rty_FOCOutputs->Vabc[0] = 0.0F;
      rty_FOCOutputs->Vabc[1] = 0.0F;
      rty_FOCOutputs->Vabc[2] = 0.0F;
    }

    // End of Switch: '<S1>/Switch2'

    // Outputs for Atomic SubSystem: '<S1>/Park Transform'
    // BusCreator: '<S1>/Bus Creator1' incorporates:
    //   AlgorithmDescriptorDelegate generated from: '<S8>/a16'

    rty_FOCOutputs->Iq_fbk.current = rtb_IaIbIc0[1];

    // End of Outputs for SubSystem: '<S1>/Park Transform'

    // Saturate: '<S1>/Saturation1'
    if (u0 > 100.0F) {
      // BusCreator: '<S1>/Bus Creator'
      rty_FOCOutputs->Vq = 100.0F;
    } else if (u0 < -100.0F) {
      // BusCreator: '<S1>/Bus Creator'
      rty_FOCOutputs->Vq = -100.0F;
    } else {
      // BusCreator: '<S1>/Bus Creator'
      rty_FOCOutputs->Vq = u0;
    }

    // End of Saturate: '<S1>/Saturation1'

    // Update for UnitDelay: '<S1>/Unit Delay' incorporates:
    //   Sum: '<S1>/Sum3'

    control_foc_DW.UnitDelay_DSTATE = rtb_Saturation1 - rtb_Add;

    // Update for UnitDelay: '<S3>/Delay Input1'
    //
    //  Block description for '<S3>/Delay Input1':
    //
    //   Store in Global RAM

    control_foc_DW.DelayInput1_DSTATE = rtu_Flags->control_mode;

    // Update for DiscreteIntegrator: '<S94>/Integrator'
    control_foc_DW.Integrator_DSTATE = 1.82857148E-5F * rtb_algDD_o2_n +
      rtb_algDD_o1_p;
    control_foc_DW.Integrator_PrevResetState = static_cast<int8_T>
      (rtb_FixPtRelationalOperator);

    // Update for DiscreteIntegrator: '<S44>/Integrator'
    control_foc_DW.Integrator_DSTATE_o = 1.82857148E-5F * rtb_sum_alpha +
      rtb_SumFdbk;
    control_foc_DW.Integrator_PrevResetState_k = static_cast<int8_T>
      (rtb_FixPtRelationalOperator);
  }
}

//
// File trailer for generated code.
//
// [EOF]
//
