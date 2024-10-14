`timescale 1ns / 1ps

module minus_plus(
    input clk,
    input load,
    input clear,
    input op,
    input [31:0] elem1,
    input [31:0] elem2,
    output [31:0] result
    );
    
    wire [15:0] exp;
    wire [47:0] manti;
    
    wire [15:0] up_exps;
    wire [47:0] up_manti;
    wire up_op;
    
    wire [15:0] exp_after_comp;
    wire [8:0] val1;
    wire [56:0] manti_concat;
    wire op2;
    
    wire [15:0] exp_for_seg2;
    wire [56:0] mnts_concat_for_seg2;
    wire op3;
    
    wire [7:0] chosen_exp;
    wire [47:0] mantis_align;
    wire op4;
    
    wire [7:0] chosen_exp_seg3;
    wire [47:0] mnts_align_for_seg3;
    wire op_for_seg3;
    
    wire [25:0] mantis_result;
    
    wire [7:0] exp_result_for_seg4;
    wire [25:0] mantis_result_for_seg4;
    
    wire [7:0] exp_adj;
    wire [23:0] mantis_norm;
    wire [8:0] val2;
    
    wire [7:0] final_exp;
    wire [23:0] final_mantis;
    
    // data prep
    assign exp = {elem1[30:23],elem2[30:23]};
    assign manti = {elem1[31],elem1[22:0],elem2[31],elem2[22:0]};
    
    reg1_exps prep_exps(exp, clk, load, clear, up_exps);
    reg1_mantise prep_mantis(manti, clk, load, clear, up_manti);
    get_op prep_op(op, clk, load, clear, up_op);
    
    // 1st Segment - compare exp and concat mantis
    mod1_comp_exp seg1_comp_exps(up_exps, val1, exp_after_comp);
    mod7_concat seg1_concat_mantis(up_manti, val1, manti_concat);
    transfer_op seg1_op(up_op, op2);
    
    // transfer to 2nd Segment
    reg1_exps seg1_seg2_exp(exp_after_comp, clk, load, clear, exp_for_seg2);
    reg4_mantise seg1_seg2_mantise(manti_concat, clk, load, clear, mnts_concat_for_seg2);
    get_op seg1_seg2_op(op2, clk, load, clear, op3);
    
    
    // 2nd Segment - chose exp and align mantis
    mod2_alege_exp seg2_chose_exp(exp_for_seg2,chosen_exp);
    mod4_alin_mantise seg2_alin_mantise(mnts_concat_for_seg2, mantis_align);
    transfer_op seg2_op(op3, op4);
    
    // transfer to 3rd Segment
    reg1_exp seg2_seg3_exp(chosen_exp, clk, load, clear, chosen_exp_seg3);
    reg1_mantise seg2_seg3_mantise(mantis_align, clk, load, clear, mnts_align_for_seg3);
    get_op seg2_seg3_op(op4, clk, load, clear, op_for_seg3);
    
    
    // 3rd Segment - + or - mantis considering op type
    mod5_add_diff_mantise seg3_add_diff_mantise(op_for_seg3, mnts_align_for_seg3, mantis_result); 
    
    // transfer to 4th Segment
    reg2_exp seg3_seg4_exp(chosen_exp_seg3, clk, load, clear, exp_result_for_seg4);
    reg2_mantisa seg3_seg4_mantise(mantis_result, clk, load, clear, mantis_result_for_seg4);
    
    
    // 4th Segment - adj exp and norm mantis
    mod6_norm seg4_norm_mantise(mantis_result_for_seg4, val2, mantis_norm);
    mod3_adj_exp seg4_adj_exp(exp_result_for_seg4, val2, exp_adj);
    
    // transfer to final result
    reg2_exp seg4_final_exp(exp_adj, clk, load, clear, final_exp);
    reg3_mantisa seg4_final_mantise(mantis_norm, clk, load, clear, final_mantis);
    
    // get final result
    assign result = {final_mantis[23],final_exp, final_mantis[22:0]};
endmodule
